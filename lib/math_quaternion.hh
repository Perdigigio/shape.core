#ifndef SHAPE_MATH_QUATERNION_HH__GUARD
#define SHAPE_MATH_QUATERNION_HH__GUARD

#include "math_vector.hh"

namespace shape
{

	//! ---------------------------------------------------------------------------------------------------------------------------

	template<class T> inline vector4<T> q_invert(vector4<T> a) noexcept { return q_invert(a, a); }

	template<class T> inline vector4<T> q_mul(vector4<T> a, vector4<T> b) noexcept { return q_mul(a, a, b); }
	template<class T> inline vector4<T> q_add(vector4<T> a, vector4<T> b) noexcept { return q_add(a, a, b); }
	template<class T> inline vector4<T> q_sub(vector4<T> a, vector4<T> b) noexcept { return q_sub(a, a, b); }

	template<class T> inline vector4<T> q_normalize(vector4<T> a) noexcept { return q_normalize(a, a); }
	template<class T> inline vector4<T> q_conjugate(vector4<T> a) noexcept { return q_conjugate(a, a); }

	//! ---------------------------------------------------------------------------------------------------------------------------

	template<class T> inline vector4<T>& q_mul(vector4<T> & r, vector4<T> a, vector4<T> b) noexcept
	{
		x(r) = x(a) * w(b) + w(a) * x(b) + z(a) * y(b) - y(a) * z(b);
		y(r) = y(a) * w(b) + w(a) * y(b) + x(a) * z(b) - z(a) * x(b);
		z(r) = z(a) * w(b) + w(a) * z(b) + y(a) * x(b) - x(a) * y(b);
		w(r) = w(a) * w(b) - x(a) * x(b) - y(a) * y(b) - z(a) * z(b); return r;
	}

	template<class T> inline vector4<T>& q_add(vector4<T> & r, vector4<T> a, vector4<T> b) noexcept { return add(r, a, b); }
	template<class T> inline vector4<T>& q_sub(vector4<T> & r, vector4<T> a, vector4<T> b) noexcept { return sub(r, a, b); }

	//! ---------------------------------------------------------------------------------------------------------------------------

	template<class T> inline vector4<T>& q_normalize(vector4<T> &r, vector4<T> a) noexcept { return normalize(r, a); }
	template<class T> inline vector4<T>& q_conjugate(vector4<T> &r, vector4<T> a) noexcept
	{
		x(r) = -x(a);
		y(r) = -y(a);
		z(r) = -z(a);
		w(r) = +w(a); return r;
	}

	template<class T> inline vector4<T>& q_invert(vector4<T> &r, vector4<T> a) noexcept
	{
		return q_normalize(r, q_conjugate(a));
	}

	//! ---------------------------------------------------------------------------------------------------------------------------

	template<class T> inline vector4<T>& q_load_rotate(vector4<T>& r, vector3<T> axis, float angle) noexcept
	{
		const T c = std::cos(-angle / 2.f); //! minus adjust rotation
		const T s = std::sin(-angle / 2.f); //! minus adjust rotation

		//!
		//! ROTATION AROUND ARBITRARY AXIS, axis SHOULD BE NORMALIZED
		//!

		w(r) = c;
		x(r) = s * x(axis);
		y(r) = s * y(axis);
		z(r) = s * z(axis); return r;
	}

	template<class T> inline vector4<T>& q_load_rotate_x(vector4<T>& r, float angle) noexcept { return q_load_rotate(r, vector3<T>{ 1, 0, 0 }, angle); }
	template<class T> inline vector4<T>& q_load_rotate_y(vector4<T>& r, float angle) noexcept { return q_load_rotate(r, vector3<T>{ 0, 1, 0 }, angle); }
	template<class T> inline vector4<T>& q_load_rotate_z(vector4<T>& r, float angle) noexcept { return q_load_rotate(r, vector3<T>{ 0, 0, 1 }, angle); }

	//! ---------------------------------------------------------------------------------------------------------------------------

	template<class T> inline vector4<T>& q_apply(vector4<T>& r, vector4<T> q, vector4<T> v) noexcept
	{
		//!
		//! APPLY q TO v
		//!

		return q_mul(r, q_mul(q, v), q_conjugate(q)); //! r = qvq*
	}

	template<class T> inline vector3<T>& q_apply(vector3<T>& r, vector4<T> q, vector3<T> v) noexcept
	{
		const vector4<T> t = q_mul(q_mul(q, { x(v), y(v), z(v), T(0) }), q_conjugate(q));

		x(r) = x(t);
		y(r) = y(t);
		z(r) = z(t);

		return r; //! r = qvq*
	}

	//! ---------------------------------------------------------------------------------------------------------------------------

	template<class T> inline vector4<T>& q_rotate(vector4<T>& r, vector3<T> a, float angle, vector4<T> v) noexcept { vector4<T> q; return q_apply(r, q_load_rotate(q, a, angle), v); }
	template<class T> inline vector3<T>& q_rotate(vector3<T>& r, vector3<T> a, float angle, vector3<T> v) noexcept { vector4<T> q; return q_apply(r, q_load_rotate(q, a, angle), v); }

	template<class T> inline vector4<T>& q_rotate_x(vector4<T>& r, float angle, vector4<T> v) noexcept { return q_rotate(r, { 1, 0, 0 }, angle, v); }
	template<class T> inline vector4<T>& q_rotate_y(vector4<T>& r, float angle, vector4<T> v) noexcept { return q_rotate(r, { 0, 1, 0 }, angle, v); }
	template<class T> inline vector4<T>& q_rotate_z(vector4<T>& r, float angle, vector4<T> v) noexcept { return q_rotate(r, { 0, 0, 1 }, angle, v); }
	template<class T> inline vector3<T>& q_rotate_x(vector3<T>& r, float angle, vector3<T> v) noexcept { return q_rotate(r, { 1, 0, 0 }, angle, v); }
	template<class T> inline vector3<T>& q_rotate_y(vector3<T>& r, float angle, vector3<T> v) noexcept { return q_rotate(r, { 0, 1, 0 }, angle, v); }
	template<class T> inline vector3<T>& q_rotate_z(vector3<T>& r, float angle, vector3<T> v) noexcept { return q_rotate(r, { 0, 0, 1 }, angle, v); }
}

#endif