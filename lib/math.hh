#ifndef SHAPE_CORE_MATH_HH__GUARD
#define SHAPE_CORE_MATH_HH__GUARD

#include "type.hh"

//! #define SHAPE_SIMD "math_simd_sse.hh"
//! #define SHAPE_SIMD "math_simd_arm.hh"

#ifndef CONFIG_DISABLE_STDMATH
#	include <cmath>
#endif

#include <cstring>

namespace shape
{
	typedef sint32_t IEEEFloat32;
	typedef sint16_t IEEEFloat16;

	static inline IEEEFloat32 as_IEEEFloat32(float p_float) noexcept
	{
		IEEEFloat32 l_float = {};

		//!
		//!

		if (1)
		{
			//!
			//!

			std::memcpy(&l_float, &p_float, sizeof l_float);
		}

		//!
		//!

		return l_float;
	}

	static inline IEEEFloat16 as_IEEEFloat16(IEEEFloat32 p_float) noexcept
	{
		sint32_t s = (p_float & 0x80000000);
		sint32_t e = (p_float & 0x7F800000) ? (p_float & 0x7F800000) - (0x38000000) : 0; //! HANDLE 0
		sint32_t m = (p_float & 0x007FFFFF);

		//!
		//!

		return  (s >> 16) & 0x8000 | (e >> 13) & 0x7C00 | (m >> 13) & 0x03FF;
	}

	static inline IEEEFloat16 as_IEEEFloat16(float p_float) noexcept
	{
		//!
		//!

		return as_IEEEFloat16(as_IEEEFloat32(p_float));
	}

	template<class T> struct vector1 { T data[1]; };
	template<class T> struct vector2 { T data[2]; };
	template<class T> struct vector3 { T data[3]; };
	template<class T> struct vector4 { T data[4]; };

	template<class T> struct matrix2 { vector2<T> data[2]; };
	template<class T> struct matrix3 { vector3<T> data[3]; };
	template<class T> struct matrix4 { vector4<T> data[4]; };

	//! --------------------------------------------------------------------------------------------

	template<class T> inline constexpr T* ptr(vector1<T>& v) noexcept { return v.data; }
	template<class T> inline constexpr T* ptr(vector2<T>& v) noexcept { return v.data; }
	template<class T> inline constexpr T* ptr(vector3<T>& v) noexcept { return v.data; }
	template<class T> inline constexpr T* ptr(vector4<T>& v) noexcept { return v.data; }
	template<class T> inline constexpr T const* ptr(vector1<T> const& v) noexcept { return v.data; }
	template<class T> inline constexpr T const* ptr(vector2<T> const& v) noexcept { return v.data; }
	template<class T> inline constexpr T const* ptr(vector3<T> const& v) noexcept { return v.data; }
	template<class T> inline constexpr T const* ptr(vector4<T> const& v) noexcept { return v.data; }

	template<class T> inline constexpr T* ptr(matrix2<T>& v) noexcept { return ptr(v.data[0]); }
	template<class T> inline constexpr T* ptr(matrix3<T>& v) noexcept { return ptr(v.data[0]); }
	template<class T> inline constexpr T* ptr(matrix4<T>& v) noexcept { return ptr(v.data[0]); }
	template<class T> inline constexpr T const* ptr(matrix2<T> const& v) noexcept { return ptr(v.data[0]); }
	template<class T> inline constexpr T const* ptr(matrix3<T> const& v) noexcept { return ptr(v.data[0]); }
	template<class T> inline constexpr T const* ptr(matrix4<T> const& v) noexcept { return ptr(v.data[0]); }

	//! --------------------------------------------------------------------------------------------

	template<class T> inline constexpr void load(vector2<T>& dst, T const src[2]) noexcept
	{
		dst.data[0] = src[0];
		dst.data[1] = src[1];
	}

	template<class T> inline constexpr void load(vector3<T>& dst, T const src[3]) noexcept
	{
		dst.data[0] = src[0];
		dst.data[1] = src[1];
		dst.data[2] = src[2];
	}

	template<class T> inline constexpr void load(vector4<T>& dst, T const src[4]) noexcept
	{
		dst.data[0] = src[0];
		dst.data[1] = src[1];
		dst.data[2] = src[2];
		dst.data[3] = src[3];
	}

	//! --------------------------------------------------------------------------------------------

	template<class T> inline constexpr void copy(vector2<T>& dst, vector2<T> const &src) noexcept { load(dst, src.data); }
	template<class T> inline constexpr void copy(vector3<T>& dst, vector3<T> const &src) noexcept { load(dst, src.data); }
	template<class T> inline constexpr void copy(vector4<T>& dst, vector4<T> const &src) noexcept { load(dst, src.data); }

	template<class T> inline constexpr void copy(matrix2<T>& dst, matrix2<T> const& src) noexcept
	{
		copy(dst.data[0], src.data[0]);
		copy(dst.data[1], src.data[1]);
	}

	template<class T> inline constexpr void copy(matrix3<T>& dst, matrix3<T> const& src) noexcept
	{
		copy(dst.data[0], src.data[0]);
		copy(dst.data[1], src.data[1]);
		copy(dst.data[2], src.data[2]);
	}

	template<class T> inline constexpr void copy(matrix4<T>& dst, matrix4<T> const& src) noexcept
	{
		copy(dst.data[0], src.data[0]);
		copy(dst.data[1], src.data[1]);
		copy(dst.data[2], src.data[2]);
		copy(dst.data[3], src.data[3]);
	}

	//! --------------------------------------------------------------------------------------------

	template<class T> inline constexpr T& x(vector1<T>& v) noexcept { return v.data[0]; }
	template<class T> inline constexpr T& x(vector2<T>& v) noexcept { return v.data[0]; }
	template<class T> inline constexpr T& x(vector3<T>& v) noexcept { return v.data[0]; }
	template<class T> inline constexpr T& x(vector4<T>& v) noexcept { return v.data[0]; }
	template<class T> inline constexpr T& y(vector2<T>& v) noexcept { return v.data[1]; }
	template<class T> inline constexpr T& y(vector3<T>& v) noexcept { return v.data[1]; }
	template<class T> inline constexpr T& y(vector4<T>& v) noexcept { return v.data[1]; }
	template<class T> inline constexpr T& z(vector3<T>& v) noexcept { return v.data[2]; }
	template<class T> inline constexpr T& z(vector4<T>& v) noexcept { return v.data[2]; }
	template<class T> inline constexpr T& w(vector4<T>& v) noexcept { return v.data[3]; }

	template<class T> inline constexpr T const& x(vector1<T> const& v) noexcept { return v.data[0]; }
	template<class T> inline constexpr T const& x(vector2<T> const& v) noexcept { return v.data[0]; }
	template<class T> inline constexpr T const& x(vector3<T> const& v) noexcept { return v.data[0]; }
	template<class T> inline constexpr T const& x(vector4<T> const& v) noexcept { return v.data[0]; }
	template<class T> inline constexpr T const& y(vector2<T> const& v) noexcept { return v.data[1]; }
	template<class T> inline constexpr T const& y(vector3<T> const& v) noexcept { return v.data[1]; }
	template<class T> inline constexpr T const& y(vector4<T> const& v) noexcept { return v.data[1]; }
	template<class T> inline constexpr T const& z(vector3<T> const& v) noexcept { return v.data[2]; }
	template<class T> inline constexpr T const& z(vector4<T> const& v) noexcept { return v.data[2]; }
	template<class T> inline constexpr T const& w(vector4<T> const& v) noexcept { return v.data[3]; }

	//! --------------------------------------------------------------------------------------------

	template<class T> inline constexpr vector2<T>& r1(matrix2<T>& m) noexcept { return m.data[0]; }
	template<class T> inline constexpr vector3<T>& r1(matrix3<T>& m) noexcept { return m.data[0]; }
	template<class T> inline constexpr vector4<T>& r1(matrix4<T>& m) noexcept { return m.data[0]; }
	template<class T> inline constexpr vector2<T>& r2(matrix2<T>& m) noexcept { return m.data[1]; }
	template<class T> inline constexpr vector3<T>& r2(matrix3<T>& m) noexcept { return m.data[1]; }
	template<class T> inline constexpr vector4<T>& r2(matrix4<T>& m) noexcept { return m.data[1]; }
	template<class T> inline constexpr vector3<T>& r3(matrix3<T>& m) noexcept { return m.data[2]; }
	template<class T> inline constexpr vector4<T>& r3(matrix4<T>& m) noexcept { return m.data[2]; }
	template<class T> inline constexpr vector4<T>& r4(matrix4<T>& m) noexcept { return m.data[3]; }

	template<class T> inline constexpr vector2<T> const& r1(const matrix2<T>& m) noexcept { return m.data[0]; }
	template<class T> inline constexpr vector3<T> const& r1(const matrix3<T>& m) noexcept { return m.data[0]; }
	template<class T> inline constexpr vector4<T> const& r1(const matrix4<T>& m) noexcept { return m.data[0]; }
	template<class T> inline constexpr vector2<T> const& r2(const matrix2<T>& m) noexcept { return m.data[1]; }
	template<class T> inline constexpr vector3<T> const& r2(const matrix3<T>& m) noexcept { return m.data[1]; }
	template<class T> inline constexpr vector4<T> const& r2(const matrix4<T>& m) noexcept { return m.data[1]; }
	template<class T> inline constexpr vector3<T> const& r3(const matrix3<T>& m) noexcept { return m.data[2]; }
	template<class T> inline constexpr vector4<T> const& r3(const matrix4<T>& m) noexcept { return m.data[2]; }
	template<class T> inline constexpr vector4<T> const& r4(const matrix4<T>& m) noexcept { return m.data[3]; }

	//! --------------------------------------------------------------------------------------------

	typedef vector2<float> real2;
	typedef vector3<float> real3;
	typedef vector4<float> real4;
	typedef vector2<uint16_t> half2;
	typedef vector3<uint16_t> half3;
	typedef vector4<uint16_t> half4;
	typedef vector2<unsigned char> byte2;
	typedef vector3<unsigned char> byte3;
	typedef vector4<unsigned char> byte4;
	typedef vector2<char> char2;
	typedef vector3<char> char3;
	typedef vector4<char> char4;

	typedef matrix2<float> real2x2;
	typedef matrix3<float> real3x3;
	typedef matrix4<float> real4x4;
	typedef matrix2<uint16_t> half2x2;
	typedef matrix3<uint16_t> half3x3;
	typedef matrix4<uint16_t> half4x4;
	typedef matrix2<unsigned char> byte2x2;
	typedef matrix3<unsigned char> byte3x3;
	typedef matrix4<unsigned char> byte4x4;
	typedef matrix2<char> char2x2;
	typedef matrix3<char> char3x3;
	typedef matrix4<char> char4x4;

}

#include "math_simd_sse.hh"

#endif
