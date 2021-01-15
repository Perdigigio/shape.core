#include "image.hh"

namespace shape
{
	static inline size_t get_stride_bm1(const image*) noexcept;
	static inline size_t get_stride_bm2(const image*) noexcept;
	static inline size_t get_stride_bm3(const image*) noexcept;
	static inline size_t get_length_bc1(const image*) noexcept;
	static inline size_t get_length_bc2(const image*) noexcept;

	//!
	//!

	size_t cImage::get_stride() const noexcept
	{
		switch (fmt)
		{
			case image_fourcc::BM16: return get_stride_bm1(this);
			case image_fourcc::BM24: return get_stride_bm2(this);
			case image_fourcc::BM32: return get_stride_bm3(this);
		}

		//!
		//! DEFAULT TO 0
		//!

		return 0;
	}

	size_t cImage::get_length() const noexcept
	{
		switch (fmt)
		{
			case image_fourcc::BM16: return get_stride_bm1(this) * this->hth;
			case image_fourcc::BM24: return get_stride_bm2(this) * this->hth;
			case image_fourcc::BM32: return get_stride_bm3(this) * this->hth;
			case image_fourcc::DXT1: return get_length_bc1(this);
			case image_fourcc::DXT3: return get_length_bc2(this);
			case image_fourcc::DXT5: return get_length_bc2(this);
			case image_fourcc::ATI1: return get_length_bc1(this);
			case image_fourcc::ATI2: return get_length_bc2(this);
		}

		//!
		//! DEFAULT TO 0
		//!

		return 0;
	}

	//!
	//!

	size_t get_stride_bm1(const image* p_img) noexcept { return (p_img->wth * 2 + 3) & ~3; }
	size_t get_stride_bm2(const image* p_img) noexcept { return (p_img->wth * 3 + 3) & ~3; }
	size_t get_stride_bm3(const image* p_img) noexcept { return (p_img->wth * 4); }
	size_t get_length_bc1(const image* p_img) noexcept { return (p_img->wth * p_img->hth) / 16 * 010; }
	size_t get_length_bc2(const image* p_img) noexcept { return (p_img->wth * p_img->hth) / 16 * 020; }

}