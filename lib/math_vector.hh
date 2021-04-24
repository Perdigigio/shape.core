#ifndef SHAPE_MATH_VECTOR_HH__GUARD
#define SHAPE_MATH_VECTOR_HH__GUARD

#include "type.hh"

namespace shape
{
	template<class T> inline vector2<T> normalize(vector2<T> v) noexcept { return normalize(v, v); }
	template<class T> inline vector3<T> normalize(vector3<T> v) noexcept { return normalize(v, v); }
	template<class T> inline vector4<T> normalize(vector4<T> v) noexcept { return normalize(v, v); }

	template<class T> inline vector2<T> set2(T a) noexcept { return vector2<T>{ a, a      }; }
	template<class T> inline vector3<T> set3(T a) noexcept { return vector3<T>{ a, a, a   }; }
	template<class T> inline vector4<T> set4(T a) noexcept { return vector4<T>{ a, a, a, a}; }

	template<class T> inline vector3<T> cross(vector3<T> a, vector3<T> b) noexcept { return cross(a, a, b); }
	template<class T> inline vector4<T> cross(vector4<T> a, vector4<T> b) noexcept { return cross(a, a, b); }

	template<class T> inline vector2<T> add(vector2<T> a, vector2<T> b) noexcept { return add(a, a, b); }
	template<class T> inline vector3<T> add(vector3<T> a, vector3<T> b) noexcept { return add(a, a, b); }
	template<class T> inline vector4<T> add(vector4<T> a, vector4<T> b) noexcept { return add(a, a, b); }
	template<class T> inline vector2<T> sub(vector2<T> a, vector2<T> b) noexcept { return sub(a, a, b); }
	template<class T> inline vector3<T> sub(vector3<T> a, vector3<T> b) noexcept { return sub(a, a, b); }
	template<class T> inline vector4<T> sub(vector4<T> a, vector4<T> b) noexcept { return sub(a, a, b); }
	template<class T> inline vector2<T> mul(vector2<T> a, vector2<T> b) noexcept { return mul(a, a, b); }
	template<class T> inline vector3<T> mul(vector3<T> a, vector3<T> b) noexcept { return mul(a, a, b); }
	template<class T> inline vector4<T> mul(vector4<T> a, vector4<T> b) noexcept { return mul(a, a, b); }
	template<class T> inline vector2<T> div(vector2<T> a, vector2<T> b) noexcept { return div(a, a, b); }
	template<class T> inline vector3<T> div(vector3<T> a, vector3<T> b) noexcept { return div(a, a, b); }
	template<class T> inline vector4<T> div(vector4<T> a, vector4<T> b) noexcept { return div(a, a, b); }
	template<class T> inline vector2<T> abs(vector2<T> a) noexcept { return abs(a, a); }
	template<class T> inline vector3<T> abs(vector3<T> a) noexcept { return abs(a, a); }
	template<class T> inline vector4<T> abs(vector4<T> a) noexcept { return abs(a, a); }

	//! ----------------------------------------------------------------------------------

	template<class T> inline vector2<T> operator +(vector2<T> a, vector2<T> b) noexcept { return add(a, a, b); }
	template<class T> inline vector3<T> operator +(vector3<T> a, vector3<T> b) noexcept { return add(a, a, b); }
	template<class T> inline vector4<T> operator +(vector4<T> a, vector4<T> b) noexcept { return add(a, a, b); }
	template<class T> inline vector2<T> operator -(vector2<T> a, vector2<T> b) noexcept { return sub(a, a, b); }
	template<class T> inline vector3<T> operator -(vector3<T> a, vector3<T> b) noexcept { return sub(a, a, b); }
	template<class T> inline vector4<T> operator -(vector4<T> a, vector4<T> b) noexcept { return sub(a, a, b); }
	template<class T> inline vector2<T> operator *(vector2<T> a, vector2<T> b) noexcept { return mul(a, a, b); }
	template<class T> inline vector3<T> operator *(vector3<T> a, vector3<T> b) noexcept { return mul(a, a, b); }
	template<class T> inline vector4<T> operator *(vector4<T> a, vector4<T> b) noexcept { return mul(a, a, b); }
	template<class T> inline vector2<T> operator /(vector2<T> a, vector2<T> b) noexcept { return div(a, a, b); }
	template<class T> inline vector3<T> operator /(vector3<T> a, vector3<T> b) noexcept { return div(a, a, b); }
	template<class T> inline vector4<T> operator /(vector4<T> a, vector4<T> b) noexcept { return div(a, a, b); }

	template<class T> inline vector2<T> operator *(vector2<T> a, T b) noexcept { return mul(a, a, set2(b)); }
	template<class T> inline vector3<T> operator *(vector3<T> a, T b) noexcept { return mul(a, a, set3(b)); }
	template<class T> inline vector4<T> operator *(vector4<T> a, T b) noexcept { return mul(a, a, set4(b)); }
	template<class T> inline vector2<T> operator /(vector2<T> a, T b) noexcept { return div(a, a, set2(b)); }
	template<class T> inline vector3<T> operator /(vector3<T> a, T b) noexcept { return div(a, a, set3(b)); }
	template<class T> inline vector4<T> operator /(vector4<T> a, T b) noexcept { return div(a, a, set4(b)); }
	template<class T> inline vector2<T> operator *(T b, vector2<T> a) noexcept { return mul(a, set2(b), a); }
	template<class T> inline vector3<T> operator *(T b, vector3<T> a) noexcept { return mul(a, set3(b), a); }
	template<class T> inline vector4<T> operator *(T b, vector4<T> a) noexcept { return mul(a, set4(b), a); }
	template<class T> inline vector2<T> operator /(T b, vector2<T> a) noexcept { return div(a, set2(b), a); }
	template<class T> inline vector3<T> operator /(T b, vector3<T> a) noexcept { return div(a, set3(b), a); }
	template<class T> inline vector4<T> operator /(T b, vector4<T> a) noexcept { return div(a, set4(b), a); }


	//! ----------------------------------------------------------------------------------

	template<class T> inline vector2<T>& add(vector2<T> &r, vector2<T> a, vector2<T> b) noexcept
	{
		x(r) = x(a) + x(b);
		y(r) = y(a) + y(b); return r;
	}

	template<class T> inline vector3<T>& add(vector3<T> &r, vector3<T> a, vector3<T> b) noexcept
	{
		x(r) = x(a) + x(b);
		y(r) = y(a) + y(b);
		z(r) = z(a) + z(b); return r;
	}

	template<class T> inline vector4<T>& add(vector4<T> &r, vector4<T> a, vector4<T> b) noexcept
	{
		x(r) = x(a) + x(b);
		y(r) = y(a) + y(b);
		z(r) = z(a) + z(b);
		w(r) = w(a) + w(b); return r;
	}

	template<class T> inline vector2<T>& sub(vector2<T> &r, vector2<T> a, vector2<T> b) noexcept
	{
		x(r) = x(a) - x(b);
		y(r) = y(a) - y(b); return r;
	}

	template<class T> inline vector3<T>& sub(vector3<T> &r, vector3<T> a, vector3<T> b) noexcept
	{
		x(r) = x(a) - x(b);
		y(r) = y(a) - y(b);
		z(r) = z(a) - z(b); return r;
	}

	template<class T> inline vector4<T>& sub(vector4<T> &r, vector4<T> a, vector4<T> b) noexcept
	{
		x(r) = x(a) - x(b);
		y(r) = y(a) - y(b);
		z(r) = z(a) - z(b);
		w(r) = w(a) - w(b); return r;
	}

	template<class T> inline vector2<T>& mul(vector2<T> &r, vector2<T> a, vector2<T> b) noexcept
	{
		x(r) = x(a) * x(b);
		y(r) = y(a) * y(b); return r;
	}

	template<class T> inline vector3<T>& mul(vector3<T> &r, vector3<T> a, vector3<T> b) noexcept
	{
		x(r) = x(a) * x(b);
		y(r) = y(a) * y(b);
		z(r) = z(a) * z(b); return r;
	}

	template<class T> inline vector4<T>& mul(vector4<T> &r, vector4<T> a, vector4<T> b) noexcept
	{
		x(r) = x(a) * x(b);
		y(r) = y(a) * y(b);
		z(r) = z(a) * z(b);
		w(r) = w(a) * w(b); return r;
	}

	template<class T> inline vector2<T>& div(vector2<T> &r, vector2<T> a, vector2<T> b) noexcept
	{
		x(r) = x(a) / x(b);
		y(r) = y(a) / y(b); return r;
	}

	template<class T> inline vector3<T>& div(vector3<T> &r, vector3<T> a, vector3<T> b) noexcept
	{
		x(r) = x(a) / x(b);
		y(r) = y(a) / y(b);
		z(r) = z(a) / z(b); return r;
	}

	template<class T> inline vector4<T>& div(vector4<T> &r, vector4<T> a, vector4<T> b) noexcept
	{
		x(r) = x(a) / x(b);
		y(r) = y(a) / y(b);
		z(r) = z(a) / z(b);
		w(r) = w(a) / w(b); return r;
	}

	template<class T> inline vector2<T>& abs(vector2<T> &r, vector2<T> a) noexcept
	{
		x(r) = x(a) < T(0) ? -x(a) : x(a);
		y(r) = y(a) < T(0) ? -y(a) : y(a); return r;
	}

	template<class T> inline vector3<T>& abs(vector3<T> &r, vector3<T> a) noexcept
	{
		x(r) = x(a) < T(0) ? -x(a) : x(a);
		y(r) = y(a) < T(0) ? -y(a) : y(a);
		z(r) = z(a) < T(0) ? -z(a) : z(a); return r;
	}

	template<class T> inline vector4<T>& abs(vector4<T> &r, vector4<T> a) noexcept
	{
		x(r) = x(a) < T(0) ? -x(a) : x(a);
		y(r) = y(a) < T(0) ? -y(a) : y(a);
		z(r) = z(a) < T(0) ? -z(a) : z(a);
		w(r) = w(a) < T(0) ? -w(a) : w(a); return r;
	}

	//! ----------------------------------------------------------------------------------

	template<class T> inline T dot(vector2<T> a, vector2<T> b) noexcept
	{
		return  a.data[0] * b.data[0] + 
			a.data[1] * b.data[1]; 
	}

	template<class T> inline T dot(vector3<T> a, vector3<T> b) noexcept
	{
		return  a.data[0] * b.data[0] + 
			a.data[1] * b.data[1] +
			a.data[2] * b.data[2]; 
	}

	template<class T> inline T dot(vector4<T> a, vector4<T> b) noexcept
	{
		return  a.data[0] * b.data[0] + 
			a.data[1] * b.data[1] +
			a.data[2] * b.data[2] +
			a.data[3] * b.data[3]; 
	}

	template<class T> inline vector3<T> cross(vector3<T> &r, vector3<T> a, vector3<T> b) noexcept
	{
		x(r) = y(a) * z(b) - z(a) * y(b);
		y(r) = z(a) * x(b) - x(a) * z(b);
		z(r) = x(a) * y(b) - y(a) * x(b); return r;
	}

	template<class T> inline vector4<T> cross(vector4<T> &r, vector4<T> a, vector4<T> b) noexcept
	{
		x(r) = y(a) * z(b) - z(a) * y(b);
		y(r) = z(a) * x(b) - x(a) * z(b);
		z(r) = x(a) * y(b) - y(a) * x(b); return r;
	}

	//! ----------------------------------------------------------------------------------

	template<class T> inline T length_sqr(vector2<T> v) noexcept { return dot(v, v); }
	template<class T> inline T length_sqr(vector3<T> v) noexcept { return dot(v, v); }
	template<class T> inline T length_sqr(vector4<T> v) noexcept { return dot(v, v); }

	template<class T> inline T length(vector2<T> v) noexcept { return std::sqrt(length_sqr(v)); }
	template<class T> inline T length(vector3<T> v) noexcept { return std::sqrt(length_sqr(v)); }
	template<class T> inline T length(vector4<T> v) noexcept { return std::sqrt(length_sqr(v)); }

	//! ----------------------------------------------------------------------------------

	template<class T> inline vector2<T>& normalize(vector2<T> &r, vector2<T> v) noexcept { return div(r, v, set2(length(v))); }
	template<class T> inline vector3<T>& normalize(vector3<T> &r, vector3<T> v) noexcept { return div(r, v, set3(length(v))); }
	template<class T> inline vector4<T>& normalize(vector4<T> &r, vector4<T> v) noexcept { return div(r, v, set4(length(v))); }


} //! shape

#ifdef SHAPE_SIMD
#	include SHAPE_SIMD
#endif
#endif