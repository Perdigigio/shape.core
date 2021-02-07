#ifndef SHAPE_MATH_MATRIX_HH__GUARD
#define SHAPE_MATH_MATRIX_HH__GUARD

#include "math_vector.hh"

namespace shape
{

	template<class T> static inline vector2<T>& mul(matrix2<T> a, vector2<T> b) noexcept { return mul(b, a, b); }
	template<class T> static inline vector3<T>& mul(matrix3<T> a, vector3<T> b) noexcept { return mul(b, a, b); }
	template<class T> static inline vector4<T>& mul(matrix4<T> a, vector4<T> b) noexcept { return mul(b, a, b); }
	template<class T> static inline matrix2<T>& mul(matrix2<T> a, matrix2<T> b) noexcept { return mul(a, a, b); }
	template<class T> static inline matrix3<T>& mul(matrix3<T> a, matrix3<T> b) noexcept { return mul(a, a, b); }
	template<class T> static inline matrix4<T>& mul(matrix4<T> a, matrix4<T> b) noexcept { return mul(a, a, b); }

	//! --------------------------------- MATRIX x VECTOR -----------------------------------------------

	template<class T> static inline vector2<T>& mul(vector2<T> &res, matrix2<T> a, vector2<T> b) noexcept
	{
		x(res) = dot(r1(a), b);
		y(res) = dot(r2(a), b); return res;
	}

	template<class T> static inline vector3<T>& mul(vector3<T> &res, matrix3<T> a, vector3<T> b) noexcept
	{
		x(res) = dot(r1(a), b);
		y(res) = dot(r2(a), b);
		z(res) = dot(r3(a), b);	return res;
	}

	template<class T> static inline vector4<T>& mul(vector4<T> &res, matrix4<T> a, vector4<T> b) noexcept
	{
		x(res) = dot(r1(a), b);
		y(res) = dot(r2(a), b);
		z(res) = dot(r3(a), b);
		w(res) = dot(r4(a), b); return res;
	}

	//! --------------------------------- MATRIX x MATRIX ----------------------------------------------

	template<class T> static inline matrix2<T>& mul(matrix2<T> &ret, matrix2<T> a, matrix2<T> b) noexcept
	{
		const vector2<T> c1 { r1(b).data[0], r2(b).data[0] };
		const vector2<T> c2 { r1(b).data[1], r2(b).data[1] };

		r1(ret).data[0] = dot(r1(a), c1);
		r1(ret).data[1] = dot(r1(a), c2);
		r2(ret).data[0] = dot(r2(a), c1);
		r2(ret).data[1] = dot(r2(a), c2); return ret;
	}

	template<class T> static inline matrix3<T>& mul(matrix3<T> &ret, matrix3<T> a, matrix3<T> b) noexcept
	{
		const vector3<T> c1 { r1(b).data[0], r2(b).data[0], r3(b).data[0] };
		const vector3<T> c2 { r1(b).data[1], r2(b).data[1], r3(b).data[1] };
		const vector3<T> c3 { r1(b).data[2], r2(b).data[2], r3(b).data[2] };

		r1(ret).data[0] = dot(r1(a), c1);
		r1(ret).data[1] = dot(r1(a), c2);
		r1(ret).data[2] = dot(r1(a), c3);
		r2(ret).data[0] = dot(r2(a), c1);
		r2(ret).data[1] = dot(r2(a), c2);
		r2(ret).data[2] = dot(r2(a), c3);
		r3(ret).data[0] = dot(r3(a), c1);
		r3(ret).data[1] = dot(r3(a), c2);
		r3(ret).data[2] = dot(r3(a), c3); return ret;
	}

	template<class T> static inline matrix4<T>& mul(matrix4<T> &ret, matrix4<T> a, matrix4<T> b) noexcept
	{
		const vector4<T> c1 { r1(b).data[0], r2(b).data[0], r3(b).data[0], r4(b).data[0] };
		const vector4<T> c2 { r1(b).data[1], r2(b).data[1], r3(b).data[1], r4(b).data[1] };
		const vector4<T> c3 { r1(b).data[2], r2(b).data[2], r3(b).data[2], r4(b).data[2] };
		const vector4<T> c4 { r1(b).data[3], r2(b).data[3], r3(b).data[3], r4(b).data[3] };

		r1(ret).data[0] = dot(r1(a), c1);
		r1(ret).data[1] = dot(r1(a), c2);
		r1(ret).data[2] = dot(r1(a), c3);
		r1(ret).data[3] = dot(r1(a), c4);
		r2(ret).data[0] = dot(r2(a), c1);
		r2(ret).data[1] = dot(r2(a), c2);
		r2(ret).data[2] = dot(r2(a), c3);
		r2(ret).data[3] = dot(r2(a), c4);
		r3(ret).data[0] = dot(r3(a), c1);
		r3(ret).data[1] = dot(r3(a), c2);
		r3(ret).data[2] = dot(r3(a), c3);
		r3(ret).data[3] = dot(r3(a), c4);
		r4(ret).data[0] = dot(r4(a), c1);
		r4(ret).data[1] = dot(r4(a), c2);
		r4(ret).data[2] = dot(r4(a), c3);
		r4(ret).data[3] = dot(r4(a), c4); return ret;
	}

	//! ------------------------------------------------------------------------------------------------

	template<class T> static inline float det(matrix2<T> m)
	{
		return  r1(m).data[0] * r2(m).data[1] -
			r1(m).data[1] * r2(m).data[0];
	}

	template<class T> static inline float det(matrix3<T> m)
	{
		return  r1(m).data[0] * r2(m).data[1] * r3(m).data[2] +
			r1(m).data[1] * r2(m).data[2] * r3(m).data[0] +
			r1(m).data[2] * r2(m).data[0] * r3(m).data[1] -
			r1(m).data[1] * r2(m).data[0] * r3(m).data[2] -
			r1(m).data[0] * r2(m).data[2] * r3(m).data[1] -
			r1(m).data[2] * r2(m).data[1] * r3(m).data[0];
	}

	template<class T> static inline float det(matrix4<T> m)
	{
		auto a = det(matrix2<T>{ r1(m).data[0], r1(m).data[1], r2(m).data[0], r2(m).data[1] });
		auto b = det(matrix2<T>{ r1(m).data[2], r1(m).data[3], r2(m).data[2], r2(m).data[3] });
		auto c = det(matrix2<T>{ r3(m).data[0], r3(m).data[1], r4(m).data[0], r4(m).data[1] });
		auto d = det(matrix2<T>{ r3(m).data[2], r3(m).data[3], r4(m).data[2], r4(m).data[3] });

		//!
		//!

		return a * d - b * c;
	}

} //! shape

#endif