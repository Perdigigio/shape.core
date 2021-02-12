#ifndef SHAPE_CORE_TYPE_HH__GUARD
#define SHAPE_CORE_TYPE_HH__GUARD

#include "base.hh"

typedef int16_t sint16_t;
typedef int32_t sint32_t;
typedef int64_t sint64_t;

namespace shape
{
	struct base_model
	{
		struct pos_t { uint32_t dummy[3]; }; //! 3 * 32-bit [FLOAT IEEE-754]
		struct nor_t { uint16_t dummy[8]; }; //! 8 * 16-bit [SNORM]
		struct tex_t { uint16_t dummy[4]; }; //! 4 * 16-bit [FLOAT IEEE-754]
		struct skn_t { uint32_t dummy[2]; }; //! 2 * 32-bit
		struct idx_t { uint32_t dummy[1]; }; //! 1 * 32-bit
	};
	
	struct base_model_buffer
	{
		static constexpr auto pos = fourcc('p', 'o', 's', ' ');
		static constexpr auto nor = fourcc('n', 'o', 'r', ' ');
		static constexpr auto tex = fourcc('t', 'e', 'x', ' ');
		static constexpr auto skn = fourcc('s', 'k', 'n', ' ');
		static constexpr auto idx = fourcc('i', 'd', 'x', ' ');
	};

	struct handle
	{
		uint32_t l : 20;
		uint32_t h : 12;
	};
}

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
