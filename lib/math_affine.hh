#ifndef SHAPE_MATH_AFFINE_HH__GUARD
#define SHAPE_MATH_AFFINE_HH__GUARD

#include "math_matrix.hh"

namespace shape
{
	namespace details
	{
		template<class T> static T constexpr eps() noexcept { return static_cast<T>(1.e-11); }

		//!
		//!

		template<class T> inline bool is_almost(T a, T b) noexcept
		{
			//!
			//! | a - b | < epsilon
			//!

			return std::abs(a - b) < eps<T>();
		} 
	}

	template<class T> inline matrix2<T>& transpose(matrix2<T> m) noexcept { return transpose(m, m); }
	template<class T> inline matrix3<T>& transpose(matrix3<T> m) noexcept { return transpose(m, m); }
	template<class T> inline matrix4<T>& transpose(matrix4<T> m) noexcept { return transpose(m, m); }

	template<class T> inline matrix2<T>& invert(matrix2<T> m) noexcept { return invert(m, m); }
	template<class T> inline matrix3<T>& invert(matrix3<T> m) noexcept { return invert(m, m); }
	template<class T> inline matrix4<T>& invert(matrix4<T> m) noexcept { return invert(m, m); }

	//!
	//!

	template<class T> inline matrix2<T>& transpose(matrix2<T>& ret, matrix2<T> m) noexcept
	{
		r1(ret).data[0] = r1(m).data[0];
		r1(ret).data[1] = r2(m).data[0];
		r2(ret).data[0] = r1(m).data[1];
		r2(ret).data[1] = r2(m).data[1]; return ret;
	}

	template<class T> inline matrix3<T>& transpose(matrix3<T>& ret, matrix3<T> m) noexcept
	{
		r1(ret).data[0] = r1(m).data[0];
		r1(ret).data[1] = r2(m).data[0];
		r1(ret).data[2] = r3(m).data[0];
		r2(ret).data[0] = r1(m).data[1];
		r2(ret).data[1] = r2(m).data[1];
		r2(ret).data[2] = r3(m).data[1];
		r3(ret).data[0] = r1(m).data[2];
		r3(ret).data[1] = r2(m).data[2];
		r3(ret).data[2] = r3(m).data[2]; return ret;
	}

	template<class T> inline matrix4<T>& transpose(matrix4<T>& ret, matrix4<T> m) noexcept
	{
		r1(ret).data[0] = r1(m).data[0];
		r1(ret).data[1] = r2(m).data[0];
		r1(ret).data[2] = r3(m).data[0];
		r1(ret).data[3] = r4(m).data[0];
		r2(ret).data[0] = r1(m).data[1];
		r2(ret).data[1] = r2(m).data[1];
		r2(ret).data[2] = r3(m).data[1];
		r2(ret).data[3] = r4(m).data[1];
		r3(ret).data[0] = r1(m).data[2];
		r3(ret).data[1] = r2(m).data[2];
		r3(ret).data[2] = r3(m).data[2];
		r3(ret).data[3] = r4(m).data[2];
		r4(ret).data[0] = r1(m).data[3];
		r4(ret).data[1] = r2(m).data[3];
		r4(ret).data[2] = r3(m).data[3];
		r4(ret).data[3] = r4(m).data[3]; return ret;
	}

	//! ------------------------------------------------------------------------------------------

	template<class T> inline matrix2<T>& invert(matrix2<T>& ret, matrix2<T> m) noexcept
	{
		const T d = det(m);

		//!
		//! CHECK DETERMINANT != 0
		//!

		if (!details::is_almost(d, T{}))
		{
			r1(ret).data[0] = +r2(m).data[1] / d;
			r1(ret).data[1] = -r2(m).data[0] / d;
			r2(ret).data[0] = -r1(m).data[1] / d;
			r2(ret).data[1] = +r1(m).data[0] / d;
		}

		//!
		//!

		return ret;
	}

	template<class T> inline matrix3<T>& invert(matrix3<T>& ret, matrix3<T> m) noexcept
	{
		const T d = det(m);

		//!
		//! CHECK DETERMINANT != 0
		//!

		if (!details::is_almost(d, T{}))
		{
			r1(ret).data[0] = +(r2(m).data[1] * r3(m).data[2] - r2(m).data[2] * r3(m).data[1]) / d;
			r1(ret).data[1] = -(r2(m).data[0] * r3(m).data[2] - r2(m).data[2] * r3(m).data[0]) / d;
			r1(ret).data[2] = +(r2(m).data[0] * r3(m).data[1] - r2(m).data[1] * r3(m).data[0]) / d;
			r2(ret).data[0] = -(r1(m).data[1] * r3(m).data[2] - r1(m).data[2] * r3(m).data[1]) / d;
			r2(ret).data[1] = +(r1(m).data[0] * r3(m).data[2] - r1(m).data[2] * r3(m).data[0]) / d;
			r2(ret).data[2] = -(r1(m).data[0] * r3(m).data[1] - r1(m).data[1] * r3(m).data[0]) / d;
			r3(ret).data[0] = +(r1(m).data[1] * r2(m).data[2] - r1(m).data[2] * r2(m).data[1]) / d;
			r3(ret).data[1] = -(r1(m).data[0] * r2(m).data[2] - r1(m).data[2] * r2(m).data[0]) / d;
			r3(ret).data[2] = +(r1(m).data[0] * r2(m).data[1] - r1(m).data[1] * r2(m).data[0]) / d;
		}

		//!
		//!

		return transpose(ret);
	}

	template<class T> inline matrix4<T>& invert(matrix4<T>& ret, matrix4<T> src) noexcept
	{
		const T q = det(src);

		//!
		//! CHECK DETERMINANT != 0 (HUGE)
		//!

		if (!details::is_almost(q, T{}))
		{
			T a =   r2(src).data[1] * r3(src).data[2] * r4(src).data[3] + r2(src).data[2] * r3(src).data[3] * r4(src).data[1] + r2(src).data[3] * r3(src).data[1] * r4(src).data[2] -
				r2(src).data[2] * r3(src).data[1] * r4(src).data[3] - r2(src).data[1] * r3(src).data[3] * r4(src).data[2] - r2(src).data[3] * r3(src).data[2] * r4(src).data[1];
			T b =   r2(src).data[0] * r3(src).data[2] * r4(src).data[3] + r2(src).data[2] * r3(src).data[3] * r4(src).data[0] + r2(src).data[3] * r3(src).data[0] * r4(src).data[2] -
				r2(src).data[2] * r3(src).data[0] * r4(src).data[3] - r2(src).data[0] * r3(src).data[3] * r4(src).data[2] - r2(src).data[3] * r3(src).data[2] * r4(src).data[0];
			T c =   r2(src).data[0] * r3(src).data[1] * r4(src).data[3] + r2(src).data[1] * r3(src).data[3] * r4(src).data[0] + r2(src).data[3] * r3(src).data[0] * r4(src).data[1] -
				r2(src).data[1] * r3(src).data[0] * r4(src).data[3] - r2(src).data[0] * r3(src).data[3] * r4(src).data[1] - r2(src).data[3] * r3(src).data[1] * r4(src).data[0];
			T d =   r2(src).data[0] * r3(src).data[1] * r4(src).data[2] + r2(src).data[1] * r3(src).data[2] * r4(src).data[0] + r2(src).data[2] * r3(src).data[0] * r4(src).data[1] -
				r2(src).data[1] * r3(src).data[0] * r4(src).data[2] - r2(src).data[0] * r3(src).data[2] * r4(src).data[1] - r2(src).data[2] * r3(src).data[1] * r4(src).data[0];
			T e =   r1(src).data[1] * r3(src).data[2] * r4(src).data[3] + r1(src).data[2] * r3(src).data[3] * r4(src).data[1] + r1(src).data[3] * r3(src).data[1] * r4(src).data[2] -
				r1(src).data[2] * r3(src).data[1] * r4(src).data[3] - r1(src).data[1] * r3(src).data[3] * r4(src).data[2] - r1(src).data[3] * r3(src).data[2] * r4(src).data[1];
			T f =   r1(src).data[0] * r3(src).data[2] * r4(src).data[3] + r1(src).data[2] * r3(src).data[3] * r4(src).data[0] + r1(src).data[3] * r3(src).data[0] * r4(src).data[2] -
				r1(src).data[2] * r3(src).data[0] * r4(src).data[3] - r1(src).data[0] * r3(src).data[3] * r4(src).data[2] - r1(src).data[3] * r3(src).data[2] * r4(src).data[0];
			T g =   r1(src).data[0] * r3(src).data[1] * r4(src).data[3] + r1(src).data[1] * r3(src).data[3] * r4(src).data[0] + r1(src).data[3] * r3(src).data[0] * r4(src).data[1] -
				r1(src).data[1] * r3(src).data[0] * r4(src).data[3] - r1(src).data[0] * r3(src).data[3] * r4(src).data[1] - r1(src).data[3] * r3(src).data[1] * r4(src).data[0];
			T h =   r1(src).data[0] * r3(src).data[1] * r4(src).data[2] + r1(src).data[1] * r3(src).data[2] * r4(src).data[0] + r1(src).data[2] * r3(src).data[0] * r4(src).data[1] -
				r1(src).data[1] * r3(src).data[0] * r4(src).data[2] - r1(src).data[0] * r3(src).data[2] * r4(src).data[1] - r1(src).data[2] * r3(src).data[1] * r4(src).data[0];
			T i =   r1(src).data[1] * r2(src).data[2] * r4(src).data[3] + r1(src).data[2] * r2(src).data[3] * r4(src).data[1] + r1(src).data[3] * r2(src).data[1] * r4(src).data[2] -
				r1(src).data[2] * r2(src).data[1] * r4(src).data[3] - r1(src).data[1] * r2(src).data[3] * r4(src).data[2] - r1(src).data[3] * r2(src).data[2] * r4(src).data[1];
			T j =   r1(src).data[0] * r2(src).data[2] * r4(src).data[3] + r1(src).data[2] * r2(src).data[3] * r4(src).data[0] + r1(src).data[3] * r2(src).data[0] * r4(src).data[2] -
				r1(src).data[2] * r2(src).data[0] * r4(src).data[3] - r1(src).data[0] * r2(src).data[3] * r4(src).data[2] - r1(src).data[3] * r2(src).data[2] * r4(src).data[0];
			T k =   r1(src).data[0] * r2(src).data[1] * r4(src).data[3] + r1(src).data[1] * r2(src).data[3] * r4(src).data[0] + r1(src).data[3] * r2(src).data[0] * r4(src).data[1] -
				r1(src).data[1] * r2(src).data[0] * r4(src).data[3] - r1(src).data[0] * r2(src).data[3] * r4(src).data[1] - r1(src).data[3] * r2(src).data[1] * r4(src).data[0];
			T l =   r1(src).data[0] * r2(src).data[1] * r4(src).data[2] + r1(src).data[1] * r2(src).data[2] * r4(src).data[0] + r1(src).data[2] * r2(src).data[0] * r4(src).data[1] -
				r1(src).data[1] * r2(src).data[0] * r4(src).data[2] - r1(src).data[0] * r2(src).data[2] * r4(src).data[1] - r1(src).data[2] * r2(src).data[1] * r4(src).data[0];
			T m =   r1(src).data[1] * r2(src).data[2] * r3(src).data[3] + r1(src).data[2] * r2(src).data[3] * r3(src).data[1] + r1(src).data[3] * r2(src).data[1] * r3(src).data[2] -
				r1(src).data[2] * r2(src).data[1] * r3(src).data[3] - r1(src).data[1] * r2(src).data[3] * r3(src).data[2] - r1(src).data[3] * r2(src).data[2] * r3(src).data[1];
			T n =   r1(src).data[0] * r2(src).data[2] * r3(src).data[3] + r1(src).data[2] * r2(src).data[3] * r3(src).data[0] + r1(src).data[3] * r2(src).data[0] * r3(src).data[2] -
				r1(src).data[2] * r2(src).data[0] * r3(src).data[3] - r1(src).data[0] * r2(src).data[3] * r3(src).data[2] - r1(src).data[3] * r2(src).data[2] * r3(src).data[0];
			T o =   r1(src).data[0] * r2(src).data[1] * r3(src).data[3] + r1(src).data[1] * r2(src).data[3] * r3(src).data[0] + r1(src).data[3] * r2(src).data[0] * r3(src).data[1] -
				r1(src).data[1] * r2(src).data[0] * r3(src).data[3] - r1(src).data[0] * r2(src).data[3] * r3(src).data[1] - r1(src).data[3] * r2(src).data[1] * r3(src).data[0];
			T p =   r1(src).data[0] * r2(src).data[1] * r3(src).data[2] + r1(src).data[1] * r2(src).data[2] * r3(src).data[0] + r1(src).data[2] * r2(src).data[0] * r3(src).data[1] -
				r1(src).data[1] * r2(src).data[0] * r3(src).data[2] - r1(src).data[0] * r2(src).data[2] * r3(src).data[1] - r1(src).data[2] * r2(src).data[1] * r3(src).data[0];

			//!
			//! STORE TRANSPOSED
			//!

			copy(r1(ret), { +a / q, -e / q, +i / q, -m / q });
			copy(r2(ret), { -b / q, +f / q, -j / q, +n / q });
			copy(r3(ret), { +c / q, -g / q, +k / q, -o / q });
			copy(r4(ret), { -d / q, +h / q, -l / q, +p / q });
		}

		//!
		//!

		return ret;
	}

	//! ------------------------------------------------------------------------------------------

	template<class T> inline matrix3<T>& load_translate(matrix3<T>& m, vector2<T> t) noexcept
	{
		r3(m).data[0] = t.data[0];
		r3(m).data[1] = t.data[1]; return m;
	}

	template<class T> inline matrix4<T>& load_translate(matrix4<T>& m, vector3<T> t) noexcept
	{
		r4(m).data[0] = t.data[0];
		r4(m).data[1] = t.data[1];
		r4(m).data[2] = t.data[2]; return m;
	}

	//! ------------------------------------------------------------------------------------------

	template<class T> inline matrix3<T>& load_rotate_x(matrix3<T> &m, float angle) noexcept
	{
		const T s = std::sin(angle);
		const T c = std::cos(angle);

		//!
		//!

		copy(m.data[0], vector3<T>{ 1, 0,  0 });
		copy(m.data[1], vector3<T>{ 0, c, -s });
		copy(m.data[2], vector3<T>{ 0, s,  c }); return m;
	}

	template<class T> inline matrix3<T>& load_rotate_y(matrix3<T> &m, float angle) noexcept
	{
		const T s = std::sin(angle);
		const T c = std::cos(angle);

		//!
		//!

		copy(m.data[0], vector3<T>{ c, 0, -s });
		copy(m.data[1], vector3<T>{ 0, 1,  0 });
		copy(m.data[2], vector3<T>{ s, 0,  c }); return m;
	}

	template<class T> inline matrix3<T>& load_rotate_z(matrix3<T> &m, float angle) noexcept
	{
		const T s = std::sin(angle);
		const T c = std::cos(angle);

		//!
		//!

		copy(m.data[0], vector3<T>{ c, -s, 0 });
		copy(m.data[1], vector3<T>{ s,  c, 0 });
		copy(m.data[2], vector3<T>{ 0,  0, 1 }); return m;
	}

	template<class T> inline matrix4<T>& load_rotate_x(matrix4<T> &m, T angle) noexcept
	{
		const T s = std::sin(angle);
		const T c = std::cos(angle);

		//!
		//!

		copy(m.data[0], vector4<T>{ 1, 0,  0, 0 });
		copy(m.data[1], vector4<T>{ 0, c, -s, 0 });
		copy(m.data[2], vector4<T>{ 0, s,  c, 0 });
		copy(m.data[3], vector4<T>{ 0, 0,  0, 1 }); return m;
	}

	template<class T> inline matrix4<T>& load_rotate_y(matrix4<T> &m, T angle) noexcept
	{
		const T s = std::sin(angle);
		const T c = std::cos(angle);

		//!
		//!

		copy(m.data[0], vector4<T>{ c, 0, -s, 0 });
		copy(m.data[1], vector4<T>{ 0, 1,  0, 0 });
		copy(m.data[2], vector4<T>{ s, 0,  c, 0 });
		copy(m.data[3], vector4<T>{ 0, 0,  0, 1 }); return m;
	}

	template<class T> inline matrix4<T>& load_rotate_z(matrix4<T> &m, T angle) noexcept
	{
		const T s = std::sin(angle);
		const T c = std::cos(angle);

		//!
		//!

		copy(m.data[0], vector4<T>{ c, -s, 0, 0 });
		copy(m.data[1], vector4<T>{ s,  c, 0, 0 });
		copy(m.data[2], vector4<T>{ 0,  0, 1, 0 });
		copy(m.data[3], vector4<T>{ 0,  0, 0, 1 }); return m;
	}
}

#endif
