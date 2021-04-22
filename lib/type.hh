#ifndef SHAPE_CORE_TYPE_HH__GUARD
#define SHAPE_CORE_TYPE_HH__GUARD

#include "base.hh"

typedef int16_t sint16_t;
typedef int32_t sint32_t;
typedef int64_t sint64_t;

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

} //! shape

namespace shape {
namespace video {

	struct pixel
	{
		static constexpr auto LUMA = fourcc('L', 'U', 'M', 'A'); //! r:8
		static constexpr auto BM16 = fourcc('B', 'M', '1', '6'); //! b:5 g:6 r:5
		static constexpr auto BM24 = fourcc('B', 'M', '2', '4'); //! b:8 g:8 r:8
		static constexpr auto BM32 = fourcc('B', 'M', '3', '2'); //! b:8 g:8 r:8 a:8
		static constexpr auto DXT1 = fourcc('D', 'X', 'T', '1'); //! b:5 g:6 r:5
		static constexpr auto DXT3 = fourcc('D', 'X', 'T', '3'); //! b:5 g:6 r:5 a:4
		static constexpr auto DXT5 = fourcc('D', 'X', 'T', '5'); //! b:5 g:6 r:5 a:8
		static constexpr auto ATI1 = fourcc('A', 'T', 'I', '1'); //! r:8
		static constexpr auto ATI2 = fourcc('A', 'T', 'I', '2'); //! r:8 g:8
		static constexpr auto ETC1 = fourcc('E', 'T', 'C', '1'); //!
		static constexpr auto ETC2 = fourcc('E', 'T', 'C', '2'); //!
		static constexpr auto HD32 = fourcc('H', 'D', '3', '2'); //! r:11 g:11 b:10
		static constexpr auto HD64 = fourcc('H', 'D', '6', '4'); //! r:16 g:16 b:16 a:16
		static constexpr auto FLT1 = fourcc('F', 'L', 'T', '1'); //! r:32
	};

	//!
	//!

	static inline bool is_compressed(uint32_t p_format) noexcept
	{
		return  p_format == pixel::DXT1 ||
			p_format == pixel::DXT3 ||
			p_format == pixel::DXT5 ||
			p_format == pixel::ATI1 ||
			p_format == pixel::ATI2 ||
			p_format == pixel::ETC1 ||
			p_format == pixel::ETC2;
	}

} //! shape::video
} //! shape

#endif
