#ifndef VEC3
#define VEC3
#include <math.h>
#include <iostream>
// 基本三元vec类

namespace yph {
	template<class T>
	class vec3 {
	private:
		T e[3];
	public:
		vec3() { e[0] = 0; e[1] = 0; e[2] = 0; }
		vec3(T e0, T e1, T e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
		~vec3() {}

		inline T getX() { return e[0]; }
		inline T getY() { return e[1]; }
		inline T getZ() { return e[2]; }
		inline T getR() { return e[0]; }
		inline T getG() { return e[1]; }
		inline T getB() { return e[2]; }

		inline const vec3& operator+() { return *this; }
		inline vec3 operator-() { return vec3(-e[0], -e[1], -e[2]); }
		inline T operator[](int i) const { return e[i]; }
		inline T& operator[](int i) { return e[i]; }

		inline vec3& operator+=(const vec3 &v2) ;
		inline vec3& operator-=(const vec3 &v2) ;
		inline vec3& operator*=(const vec3 &v2) ;
		inline vec3& operator/=(const vec3 &v2) ;
		inline vec3& operator*=(T t) ;
		inline vec3& operator/=(T t) ;


		inline vec3 operator+(const vec3 &v2) const;
		inline vec3 operator-(const vec3 &v2) const;
		inline vec3 operator*(const vec3 &v2) const;
		inline vec3 operator/(const vec3 &v2) const;
		inline vec3 operator*(T t) const;
		inline vec3 operator/(T t) const;

		inline std::istream& operator>>(std::istream &is) {
			is >> e[0] >> e[1] >> e[2];
			return is;
		}

		inline std::ostream& operator<<(std::ostream &os) const {
			os << e[0] << e[1] << e[2];
			return os;
		}

		inline float length() const {
			return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
		}
		inline float squaredLength() const {
			return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
		}
		inline vec3<T>& makeUnitVector();
	};

	template<class T>
	inline vec3<T>& vec3<T>::operator+=(const vec3 &v2) {
		e[0] += v2[0];
		e[1] += v2[1];
		e[2] += v2[2];
		return *this;
	}

	template<class T>
	inline vec3<T>& vec3<T>::operator-=(const vec3<T> &v2) {
		e[0] -= v2[0];
		e[1] -= v2[1];
		e[2] -= v2[2];
		return *this;
	}

	template<class T>
	inline vec3<T>& vec3<T>::operator*=(const vec3<T> &v2) {
		e[0] *= v2[0];
		e[1] *= v2[1];
		e[2] *= v2[2];
		return *this;
	}

	template<class T>
	inline vec3<T>& vec3<T>::operator/=(const vec3<T> &v2) {
		e[0] /= v2[0];
		e[1] /= v2[1];
		e[2] /= v2[2];
		return *this;
	}

	template<class T>
	inline vec3<T>& vec3<T>::operator*=(T t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	template<class T>
	inline vec3<T>& vec3<T>::operator/=(T t) {
		e[0] /= t;
		e[1] /= t;
		e[2] /= t;
		return *this;
	}

	template<class T>
	inline vec3<T> vec3<T>::operator+(const vec3<T> &v2) const{
		return vec3<T>(e[0] + v2[0], e[1] + v2[1], e[2] + v2[2]);
	}

	template<class T>
	inline vec3<T> vec3<T>::operator-(const vec3<T> &v2) const {
		return vec3<T>(e[0] - v2[0], e[1] - v2[1], e[2] - v2[2]);
	}

	template<class T>
	inline vec3<T> vec3<T>::operator*(const vec3<T> &v2) const {
		return vec3<T>(e[0] * v2[0], e[1] * v2[1], e[2] * v2[2]);
	}

	template<class T>
	inline vec3<T> vec3<T>::operator/(const vec3<T> &v2) const {
		return vec3<T>(e[0] / v2[0], e[1] / v2[1], e[2] / v2[2]);
	}

	template<class T>
	inline vec3<T> vec3<T>::operator*(T t) const {
		return vec3<T>(e[0] * t, e[1] * t, e[2] * t);
	}

	template<class T>
	inline vec3<T> vec3<T>::operator/(T t) const {
		return vec3<T>(e[0] / t, e[1] / t, e[2] / t);
	}

	template<class T>
	inline vec3<T>& vec3<T>::makeUnitVector() {
		float f = 1.0 / length();
		e[0] = f * e[0];
		e[1] = f * e[1];
		e[2] = f * e[2];
		return *this;
	}

	template<class T>
	inline float dot(const vec3<T> &v1, const vec3<T> &v2) {
		return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	}

	template<class T>
	inline vec3<T> cross(const vec3<T> &v1, const vec3<T> &v2) {
		return vec3<T>(
			(v1[1] * v2[2] - v1[2] * v2[1]),
			(v1[2] * v2[0] - v1[0] * v2[2]),
			(v1[0] * v2[1] - v1[1] * v2[0])
			);
	}

	template<class T>
	inline vec3<T> operator*(T t, const vec3<T> &v1) {
		return vec3<T>(v1[0] * t, v1[1] * t, v1[2] * t);
	} //之前的那个只保证了乘号后一项为T类型数字
}

#endif