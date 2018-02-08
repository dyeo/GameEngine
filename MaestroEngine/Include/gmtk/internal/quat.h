#ifndef _GMTK_QUAT_H_
#define _GMTK_QUAT_H_

//

#include "..\util.h"
#include <math.h>
#include <ostream>

//

//! Unrolls a component-wise vector manipulation for generic implementation
#define GMTK_QUAT_LOOP(oper) GMTK_UNROLL_LOOP(i,4,oper)

//

#define GMTK_QUAT_OPERATOR(oper) { Quat<T> res; GMTK_QUAT_LOOP(res[i] = oper); return res; }

//

#define GMTK_QUAT_REF_OPERATOR(oper) { GMTK_QUAT_LOOP(oper); return *this; }

//

#define GMTK_QUAT_SLERP_THRESHOLD = 0.9995

//

namespace GMTK_NAMESPACE
{
	//! quaternion class
	template< typename T = float >
	struct Quat
	{////

		// DATA

		union
		{
			struct { T data[4]; };
			struct { T w, x, y, z; };
			struct { T w, i, j, k; };
		};

		// CONSTRUCTORS

		//! default constructor
		inline Quat()
		{
			w = 0;
			x = 0;
			y = 0;
			z = 0;
		}

		//! initialize quat with one scalar (s) and three complex (i, j, k)
		inline Quat(const T &s, const T &i, const T &j, const T &k)
		{
			w = s;
			x = i;
			y = j;
			z = k;
		}

		//! initialize quat with one scalar (s) and a vec3 of complex (ijk)
		inline Quat(const T &s, const vec<T, 3> &ijk)
		{
			w = s;
			x = ijk.data[0];
			y = ijk.data[1];
			z = ijk.data[2];
		}

		//! initialize quat with vec4 of complex(3)scalar(1)
		//! NOTE: w becomes first element!
		inline Quat(const vec<T, 4> &xyzw)
		{
			w = xyzw.data[3];
			x = xyzw.data[0];
			y = xyzw.data[1];
			z = xyzw.data[2];
		}

		//! Copy constructor
		template< typename U >
		inline Quat(const Quat<U> &copy)
		{
			data[0] = static_cast<T>(copy.data[0]);
			data[1] = static_cast<T>(copy.data[1]);
			data[2] = static_cast<T>(copy.data[2]);
			data[3] = static_cast<T>(copy.data[3]);
		}

		// OPERATORS

		//! returns reference to an element of the given quat, in the order w,x,y,z
		inline T& operator[](const int i) {
			return data[i];
		}

		inline const T& operator[](const int i) const {
			return data[i];
		}

		//!
		inline Quat<T> operator+(const Quat &q) {
			GMTK_QUAT_OPERATOR(data[i] + q.data[i]);
		}

		//!
		inline Quat<T> operator-(const Quat &q) {
			GMTK_QUAT_OPERATOR(data[i] - q.data[i]);
		}

		//!
		inline Quat<T> operator*(const Quat &q) {
			Quat<T> res;
			res.x = x * q.w + y * q.z - z * q.y + w * q.x;
			res.y = -x * q.z + y * q.w + z * q.x + w * q.y;
			res.z = x * q.y - y * q.x + z * q.w + w * q.z;
			res.w = -x * q.x - y * q.y - z * q.z + w * q.w;
			return res;
		}

		//!
		inline Quat<T> operator/(const Quat &q) {
			Quat<T> res;
			res = (*this) * conjugate(q);
			return res;
		}

		//!
		inline Quat<T> operator+=(const Quat &q) {
			GMTK_QUAT_REF_OPERATOR(data[i] += q.data[i]);
		}

		//!
		inline Quat<T> operator-=(const Quat &q) {
			GMTK_QUAT_REF_OPERATOR(data[i] -= q.data[i]);
		}

		//!
		inline vec<T, 3> operator*(const vec<T, 3> &v) const {
			Quat<T> vp = Quat<T>(*this) * Quat<T>(0, v.x, v.y, v.z) * conj(Quat<T>(*this));
			return vec<T, 3>(vp.x, vp.y, vp.z);
		}
		
		//!
		inline vec<T, 3> operator/(const vec<T, 3> &v) const {
			Quat<T> vp = Quat<T>(*this) * Quat<T>(0, -v.x, -v.y, -v.z) * conj(Quat<T>(*this));
			return vec<T, 3>(vp.x, vp.y, vp.z);
		}

		//!
		inline Quat<T> operator+(const T &s) const {
			GMTK_QUAT_OPERATOR(data[i] + s);
		}

		//!
		inline Quat<T> operator-(const T &s) const {
			GMTK_QUAT_OPERATOR(data[i] - s);
		}

		//!
		inline Quat<T> operator*(const T &s) const {
			GMTK_QUAT_OPERATOR(data[i] * s);
		}

		//!
		inline Quat<T> operator/(const T &s) const {
			GMTK_QUAT_OPERATOR(data[i] / s);
		}

		//!
		inline Quat<T> &operator+=(const T &s) {
			GMTK_QUAT_REF_OPERATOR(data[i] += s);
		}

		//!
		inline Quat<T> &operator-=(const T &s) {
			GMTK_QUAT_REF_OPERATOR(data[i] -= s);
		}

		//!
		inline Quat<T> &operator*=(const T &s) {
			GMTK_QUAT_REF_OPERATOR(data[i] *= s);
		}

		//!
		inline Quat<T> &operator/=(const T &s) {
			GMTK_QUAT_REF_OPERATOR(data[i] /= s);
		}

		//!
		inline mat<T, 3, 3> tomat()
		{
			return mat<T, 3, 3>
			{
				1 - 2 * (sq(k) + sq(j)), 
					2 * (i * j + k * w),
					2 * (i * k - j * w),
					//
					2 * (i * j - k * w), 
				1 - 2 * (sq(i) + sq(k)), 
					2 * (j * k + i * w),
					//
					2 * (j * w + i * k), 
					2 * (j * k - i * w), 
				1 - 2 * (sq(j) + sq(i))
			};
		}

		// GENERATORS

		//! creates a rotation quaternion rotated about an axis according to a specified angle
		inline static Quat<T> axisangle(const vec<T, 3> &axis, const Angle<T> &angle)
		{
			float a2 = angle.radians() / 2;
			float sa2 = sin(a2);
			Quat<T> q;
			q.w = cos(a2);
			q.x = axis.x * sa2;
			q.y = axis.y * sa2;
			q.z = axis.z * sa2;
			return q;
		}

		// MISC. STATIC FUNCTIONS

		inline static Quat<T> identity()
		{
			return Quat<T>(1, 0, 0, 0);
		}
				
	};////

	//! Quaternion output operator
	template <typename T>
	inline std::ostream& operator<<(std::ostream& os, const Quat<T>& q)
	{
		os << "< " << std::showpos << q.w << ' ' << q.x << "i " << q.y << "j " << q.z << std::noshowpos << "k >";
		return os;
	}
	
	//! Returns length squared of quaternion
	template <typename T>
	inline T lengthsq(const Quat<T>& v)
	{
		T res = 0;
		GMTK_QUAT_LOOP(res += sq(v.data[i]));
		return res;
	}

	//! Returns length of quaternion, or sqrt(lengthsq)
	template <typename T>
	inline T length(const Quat<T>& v)
	{
		T res = 0;
		GMTK_QUAT_LOOP(res += sq(v.data[i]));
		return sqrt(res);
	}

	template <typename T>
	inline T norm(const Quat<T> &q)
	{
		return length(q);
	}

	//! Normalizes quaternion so it is a unit quaternion
	template <typename T>
	inline Quat<T> normalize(const Quat<T> &q)
	{
		return q / length(q);
	}

	//! Returns the quaternion conjugate. The "negative" of the quaternion.
	template <typename T>
	inline Quat<T> conjugate(const Quat<T> &q)
	{
		Quat<T> res;
		res.x = -q.x;
		res.y = -q.y;
		res.z = -q.z;
		res.w =  q.w;
		return res;
	}

	//! Returns the quaternion conjugate. The "negative" of the quaternion.
	template <typename T>
	inline Quat<T> conj(const Quat<T> &q)
	{
		return conjugate(q);
	}

	//! Returns the quaternion inverse
	template <typename T>
	inline Quat<T> inverse(const Quat<T> &q)
	{
		return q / lengthsq(q);
	}

	//! Calculates the dot or hamiltonian product of two quaternions
	template <typename T>
	inline T dot(const Quat<T> &l, const Quat<T> &r)
	{
		return (l.w * r.w) + (l.x * r.x) + (l.y * r.y) + (l.z * r.z);
	}

	//! Calculates the spherical linear interpolation of two quaternions using a t-value
	template <typename T>
	inline Quat<T> slerp(const Quat<T> &l, const Quat<T> &r, const double &t)
	{
		T dotProduct = dot(l, r);

		if (dotProduct > GMTK_QUAT_SLERP_THRESHOLD) return normalize(l + t*(r - l));

		dot = clamp(dot, -1, 1);

		double tht0 = acos(dot);
		double tht = tht0*t;

		Quaternion v = r - l*dot;
		v = normalize(v);

		return l*cos(tht) + v*sin(tht);
	}

	typedef Quat<float> quat;
	typedef Quat<double> quatd;
	typedef Quat<int> quati;
	typedef Quat<unsigned> quatui;

}

#endif//_GMTK_QUAT_H_