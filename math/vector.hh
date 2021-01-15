#ifndef SHAPE_CORE_MATH_VECTOR_HH__GUARD
#define SHAPE_CORE_MATH_VECTOR_HH__GUARD

namespace shape
{
	template<class T, size_t N> struct vector
	{
		T data[N];
	};

	namespace math
	{
		//!
		//! COORD
		//!

		template<class T> static inline T& x(vector<T, 2>& v) { return v.data[0]; }
		template<class T> static inline T& x(vector<T, 3>& v) { return v.data[0]; }
		template<class T> static inline T& x(vector<T, 4>& v) { return v.data[0]; }
		template<class T> static inline T& y(vector<T, 2>& v) { return v.data[1]; }
		template<class T> static inline T& y(vector<T, 3>& v) { return v.data[1]; }
		template<class T> static inline T& y(vector<T, 4>& v) { return v.data[1]; }
		template<class T> static inline T& z(vector<T, 3>& v) { return v.data[2]; }
		template<class T> static inline T& z(vector<T, 4>& v) { return v.data[2]; }
		template<class T> static inline T& w(vector<T, 4>& v) { return v.data[3]; }

		template<class T> static inline const T& x(const vector<T, 2>& v) { return v.data[0]; }
		template<class T> static inline const T& x(const vector<T, 3>& v) { return v.data[0]; }
		template<class T> static inline const T& x(const vector<T, 4>& v) { return v.data[0]; }
		template<class T> static inline const T& y(const vector<T, 2>& v) { return v.data[1]; }
		template<class T> static inline const T& y(const vector<T, 3>& v) { return v.data[1]; }
		template<class T> static inline const T& y(const vector<T, 4>& v) { return v.data[1]; }
		template<class T> static inline const T& z(const vector<T, 3>& v) { return v.data[2]; }
		template<class T> static inline const T& z(const vector<T, 4>& v) { return v.data[2]; }
		template<class T> static inline const T& w(const vector<T, 4>& v) { return v.data[3]; }

		//!
		//! COLOR
		//!

		template<class T> static inline T& r(vector<T, 3>& v) { return v.data[0]; }
		template<class T> static inline T& r(vector<T, 4>& v) { return v.data[0]; }
		template<class T> static inline T& g(vector<T, 3>& v) { return v.data[1]; }
		template<class T> static inline T& g(vector<T, 4>& v) { return v.data[1]; }
		template<class T> static inline T& b(vector<T, 3>& v) { return v.data[2]; }
		template<class T> static inline T& b(vector<T, 4>& v) { return v.data[2]; }
		template<class T> static inline T& a(vector<T, 4>& v) { return v.data[3]; }

		template<class T> static inline const T& r(const vector<T, 3>& v) { return v.data[0]; }
		template<class T> static inline const T& r(const vector<T, 4>& v) { return v.data[0]; }
		template<class T> static inline const T& g(const vector<T, 3>& v) { return v.data[1]; }
		template<class T> static inline const T& g(const vector<T, 4>& v) { return v.data[1]; }
		template<class T> static inline const T& b(const vector<T, 3>& v) { return v.data[2]; }
		template<class T> static inline const T& b(const vector<T, 4>& v) { return v.data[2]; }
		template<class T> static inline const T& a(const vector<T, 4>& v) { return v.data[3]; }
	}

	//!
	//!

	typedef vector<float, 2> float2;
	typedef vector<float, 3> float3;
	typedef vector<float, 4> float4;

	typedef vector<uint16_t, 2> half2;
	typedef vector<uint16_t, 3> half3;
	typedef vector<uint16_t, 4> half4;
}

#endif