#include "pch.h"
#include "ray.h"
#include "vec3.h"
#include "hitable.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include <iostream>
#include <stdlib.h>     
#include <time.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace yph;
// cosnt 和 & 一定要注意起来，不要忘了各种位置的意义及区别

vec3f color(const ray<float>& r, hitable *world, int depth) {
	hitRecord rec;
	if (world->hit(r, T_MIN, T_MAX, rec)) {			// 这里下限是为了防止shadow acne，即微小光线也漫反射，无穷无尽下去
		ray<float> scattered;
		vec3f attenuation;
		if (depth < 50 && rec.materialPtr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);		// 漫反射了0.5的。设置了一个迭代的最深深度，与之前的T_MIN一起作用
		}
		else {
			return vec3f(0, 0, 0);
		}
	}
	else { // 背景色:蓝色天空渐变
		vec3f unitDirection = r.getDirection().makeUnitVector();
		float t = 0.5*(unitDirection.getY() + 1.0);						//限定在0到1
		return (1.0f - t)*vec3f(1.0, 1.0, 1.0) + t * vec3f(0.5, 0.7, 1.0);
	}
}

#define RAND ((rand() % 10) / 10.0)

int main()
{
	FILE *stream;
	srand(time(NULL));

	int nx = 200;
	int ny = 100;
	int ns = 100;
	int nn;
	unsigned char* texData = stbi_load("test.jpg", &nx,&ny,&nn,0);
	material *mat = new lambertian(new imageTexture(texData,nx,ny));

	hitable* list[1];																// 指针数组
	// list[0] = new sphere(vec3f(0, -1000, 0), 1000, new lambertian(new checkerTexture(new constantTexture(vec3f(0, 0, 0)), new constantTexture(vec3f(0.1, 0.3, 0.1)))));
	// list[0] = new sphere(vec3f(0, -1000, 0), 1000, new lambertian(new noiseTexture(0.5)));
	// list[1] = new sphere(vec3f(0, 2, 0), 2, new lambertian(new noiseTexture(1)));
	list[0] = new sphere(vec3f(0, 0, 0), 2, mat);
	hitable* world = new hitableList(list, 1);

	vec3f lookfrom(13, 2, 3);
	vec3f lookat(0, 0, 0);
	float distToFocus = (lookfrom - lookat).length();
	float aperture = 2.0;
	camera cam(lookfrom, lookat, vec3f(0, 1, 0), 20, float(nx) / float(ny), aperture, distToFocus);

	freopen_s(&stream, "test.ppm", "w", stdout);
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; --j) {												 //从左上角开始绘制
		for (int i = 0; i < nx; ++i) {
			vec3f col(0, 0, 0);
			for (int s = 0; s < ns; ++s) {
				// 一个像素照射多次，每次随机产生一个偏差防止总是取一个像素的一个位置造成颜色剧变和锯齿，对颜色求和后再求平均值
				float u = float(i + RAND) / float(nx);
				float v = float(j + RAND) / float(ny);
				ray<float> r = cam.getRay(u, v);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = vec3f(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));			// 这个是做gamma矫正，视觉与相机的偏差
			int ir = int(col[0] * 255.99);
			int ig = int(col[1] * 255.99);
			int ib = int(col[2] * 255.99);
			std::cout << ir << " " << ig << " " << ib << std::endl;
		}
	}
}
