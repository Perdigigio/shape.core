#include "type.hh"

//!
//! C++11 WORKAROUND
//!

namespace shape
{

	constexpr uint32_t base_model_buffer::pos;
	constexpr uint32_t base_model_buffer::nor;
	constexpr uint32_t base_model_buffer::tex;
	constexpr uint32_t base_model_buffer::skn;
	constexpr uint32_t base_model_buffer::idx;

} //! shape

namespace shape {
namespace video {

	constexpr uint32_t pixel::LUMA;
	constexpr uint32_t pixel::BM16;
	constexpr uint32_t pixel::BM24;
	constexpr uint32_t pixel::BM32;
	constexpr uint32_t pixel::DXT1;
	constexpr uint32_t pixel::DXT3;
	constexpr uint32_t pixel::DXT5;
	constexpr uint32_t pixel::ATI1;
	constexpr uint32_t pixel::ATI2;
	constexpr uint32_t pixel::ETC1;
	constexpr uint32_t pixel::ETC2;
	constexpr uint32_t pixel::HD32;
	constexpr uint32_t pixel::HD64;

} //! shape::video
} //! shape