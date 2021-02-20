#ifndef SHAPE_SIMD_SSE_HH__GUARD
#define SHAPE_SIMD_SSE_HH__GUARD

#include <immintrin.h>

namespace shape
{
	namespace simd
	{

		static inline __m128 load(vector4<float> v) noexcept { return _mm_load_ps(ptr(v)); }
		static inline __m128 load(matrix2<float> m) noexcept { return _mm_load_ps(ptr(m)); }

		static inline void store(vector4<float> &v, __m128 r) noexcept { _mm_store_ps(ptr(v), r); }
		static inline void store(matrix2<float> &m, __m128 r) noexcept { _mm_store_ps(ptr(m), r); }

		static inline __m128 yzxw(__m128 v) noexcept { return _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 0, 2, 1)); }
		static inline __m128 zxyw(__m128 v) noexcept { return _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 1, 0, 2)); }
		static inline __m128 yxyx(__m128 v) noexcept { return _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 1, 0, 1)); }
		static inline __m128 xzyw(__m128 v) noexcept { return _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 1, 2, 0)); }
		static inline __m128 zwxy(__m128 v) noexcept { return _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 0, 3, 2)); }
		static inline __m128 xyxy(__m128 v) noexcept { return _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 0, 1, 0)); }
		static inline __m128 xxzz(__m128 v) noexcept { return _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 0, 0)); }
		static inline __m128 yyww(__m128 v) noexcept { return _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 1, 1)); }
		static inline __m128 zwzw(__m128 v) noexcept { return _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 2, 3, 2)); }
		static inline __m128 yzxw(vector4<float> v) noexcept { return yzxw(load(v)); }
		static inline __m128 zxyw(vector4<float> v) noexcept { return zxyw(load(v)); }
		static inline __m128 yxyx(vector4<float> v) noexcept { return yxyx(load(v)); }
		static inline __m128 xzyw(vector4<float> v) noexcept { return xzyw(load(v)); }
		static inline __m128 zwxy(vector4<float> v) noexcept { return zwxy(load(v)); }
		static inline __m128 xyxy(vector4<float> v) noexcept { return xyxy(load(v)); }
		static inline __m128 xxzz(vector4<float> v) noexcept { return xxzz(load(v)); }
		static inline __m128 yyww(vector4<float> v) noexcept { return yyww(load(v)); }
		static inline __m128 zwzw(vector4<float> v) noexcept { return zwzw(load(v)); }

		static inline void add(vector4<float> &a, __m128 b) noexcept { store(a, _mm_add_ps(load(a), b)); }
		static inline void mul(vector4<float> &a, __m128 b) noexcept { store(a, _mm_mul_ps(load(a), b)); }
		static inline void sub(vector4<float> &a, __m128 b) noexcept { store(a, _mm_sub_ps(load(a), b)); }
		static inline void div(vector4<float> &a, __m128 b) noexcept { store(a, _mm_div_ps(load(a), b)); }

		static inline void add(matrix2<float> &a, __m128 b) noexcept { store(a, _mm_add_ps(load(a), b)); }

		static inline __m128 dot(vector4<float> l, __m128 r) noexcept
		{
			auto a = _mm_mul_ps(load(l), r);
			auto b = _mm_add_ps(zwxy(a), a);
			auto c = _mm_add_ps(yxyx(b), b); return c;
		}

		static inline __m128 mmm(__m128 l, __m128 r) noexcept
		{
			auto a = simd::xxzz(l); //! aacc
			auto b = simd::yyww(l); //! bbdd
			auto c = simd::xyxy(r); //! efef
			auto d = simd::zwzw(r); //! ghgh
			auto e = _mm_mul_ps(a, c); //! [ae af ce cf]
			auto f = _mm_mul_ps(b, d); //! [bg bh dg dh]
			auto g = _mm_add_ps(e, f);

			//!
			//!

			return g;
		}

		//!
		//!

		static inline __m128 movelh(vector4<float> a, vector4<float> b) { return _mm_movelh_ps(load(a), load(b)); }
		static inline __m128 movehl(vector4<float> a, vector4<float> b) { return _mm_movehl_ps(load(a), load(b)); }
	} //! shape::simd

	//! ------------------------------------------------------------------------------------------------------------

	static inline void load(vector4<float>& dst, const float src[4]) noexcept { simd::store(dst, _mm_load_ps(src)); }

	//! ------------------------------------------------------------------------------------------------------------

	static inline real4& add(real4 &r, real4 a, real4 b) noexcept { simd::add(a, simd::load(b)); return r = a; }
	static inline real4& mul(real4 &r, real4 a, real4 b) noexcept { simd::mul(a, simd::load(b)); return r = a; }
	static inline real4& sub(real4 &r, real4 a, real4 b) noexcept { simd::sub(a, simd::load(b)); return r = a; }
	static inline real4& div(real4 &r, real4 a, real4 b) noexcept { simd::div(a, simd::load(b)); return r = a; }

	static inline real4& cross(real4 &v, real4 l, real4 r) noexcept
	{
		auto a = simd::yzxw(l);
		auto b = simd::zxyw(l);
		auto c = simd::yzxw(r);
		auto d = simd::zxyw(r);

		auto e = _mm_mul_ps(a, d);
		auto f = _mm_mul_ps(b, c);
		auto g = _mm_sub_ps(e, f);

		//!
		//!

		return simd::store(v, g), v;
	}

	//! ------------------------------------------------------------------------------------------------------------

	static inline float dot(vector4<float> a, vector4<float> b) noexcept
	{
		simd::mul(a, simd::load(b));
		simd::add(a, simd::zwxy(a));
		simd::add(a, simd::yxyx(a));

		//!
		//!

		return x(a);
	}

	//! ------------------------------------------------------------------------------------------------------------

	static inline matrix2<float>& transpose(matrix2<float> &res, matrix2<float> m) noexcept
	{
		auto a = simd::load(m);
		auto b = simd::zwxy(a);

		//!
		//!

		return simd::store(res, b), res;
	}

	static inline matrix4<float>& transpose(matrix4<float> &res, matrix4<float> m) noexcept
	{
		auto a = simd::load(r1(m));
		auto b = simd::load(r2(m));
		auto c = simd::load(r3(m));
		auto d = simd::load(r4(m));
		auto e = _mm_unpacklo_ps(a, b);
		auto f = _mm_unpackhi_ps(a, b);
		auto g = _mm_unpacklo_ps(c, d);
		auto h = _mm_unpackhi_ps(c, d);

		//!
		//!

		simd::store(r1(res), _mm_movelh_ps(e, g));
		simd::store(r2(res), _mm_movehl_ps(g, e));
		simd::store(r3(res), _mm_movelh_ps(f, h));
		simd::store(r4(res), _mm_movehl_ps(h, f)); return res;
	}

	static inline matrix2<float>& transpose(matrix2<float> m) noexcept { return transpose(m, m); }
	static inline matrix4<float>& transpose(matrix4<float> m) noexcept { return transpose(m, m); }

	//! --------------------------------- MATRIX x VECTOR -----------------------------------------------

	static inline vector4<float>& mul(vector4<float> &res, matrix4<float> a, vector4<float> b) noexcept
	{
		auto x = simd::dot(r1(a), simd::load(b));
		auto y = simd::dot(r2(a), simd::load(b));
		auto z = simd::dot(r3(a), simd::load(b));
		auto w = simd::dot(r4(a), simd::load(b));
		auto i = _mm_unpacklo_ps(x, z); //! xzxz
		auto j = _mm_unpacklo_ps(y, w); //! ywyw
		auto k = _mm_unpacklo_ps(i, j); //! xyzw

		//!
		//!

		return simd::store(res, k), res;
	}

	static inline vector4<float> mul(matrix4<float> a, vector4<float> b) noexcept { return mul(b, a, b); }

	//! --------------------------------- MATRIX x MATRIX ----------------------------------------------

	static inline matrix2<float>& mul(matrix2<float> &res, matrix2<float> a, matrix2<float> b) noexcept
	{
		auto _1 = simd::xxzz(simd::load(a)); //! aacc
		auto _2 = simd::yyww(simd::load(a)); //! bbdd
		auto _3 = simd::xyxy(simd::load(b)); //! efef
		auto _4 = simd::zwzw(simd::load(b)); //! ghgh
		auto _5 = _mm_mul_ps(_1, _3); //! [ae af ce cf]
		auto _6 = _mm_mul_ps(_2, _4); //! [bg bh dg dh]
		auto _7 = _mm_add_ps(_5, _6);

		//!
		//!

		return simd::store(res, _7), res;
	}

	static inline matrix4<float>& mul(matrix4<float> &res, matrix4<float> a, matrix4<float> b) noexcept
	{
		auto t = transpose(b);

		//!
		//! ROW x COLUMNS
		//!

		copy(r1(res), mul(t, r1(a)));
		copy(r2(res), mul(t, r2(a)));
		copy(r3(res), mul(t, r3(a)));
		copy(r4(res), mul(t, r4(a))); return res;
	}
} //! shape

#endif
