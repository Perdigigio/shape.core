#include "base_image.hh"

namespace shape
{
	static inline size_t get_stride_bm1(const base_image*) noexcept;
	static inline size_t get_stride_bm2(const base_image*) noexcept;
	static inline size_t get_stride_bm3(const base_image*) noexcept;
	static inline size_t get_length_bc1(const base_image*) noexcept;
	static inline size_t get_length_bc2(const base_image*) noexcept;

	//!
	//!

	size_t base_image::get_stride(base_image const *p_img) noexcept
	{
		switch (p_img->fmt)
		{
			case video::pixel::BM16: return get_stride_bm1(p_img);
			case video::pixel::BM24: return get_stride_bm2(p_img);
			case video::pixel::BM32: return get_stride_bm3(p_img);
		}

		//!
		//! DEFAULT TO 0
		//!

		return 0;
	}

	size_t base_image::get_length(base_image const *p_img) noexcept
	{
		switch (p_img->fmt)
		{
			case video::pixel::BM16: return get_stride_bm1(p_img) * p_img->hth;
			case video::pixel::BM24: return get_stride_bm2(p_img) * p_img->hth;
			case video::pixel::BM32: return get_stride_bm3(p_img) * p_img->hth;
			case video::pixel::DXT1: return get_length_bc1(p_img);
			case video::pixel::DXT3: return get_length_bc2(p_img);
			case video::pixel::DXT5: return get_length_bc2(p_img);
			case video::pixel::ATI1: return get_length_bc1(p_img);
			case video::pixel::ATI2: return get_length_bc2(p_img);
		}

		//!
		//! DEFAULT TO 0
		//!

		return 0;
	}

	//!
	//!

	size_t get_stride_bm1(const base_image *p_img) noexcept { return (p_img->wth * 2 + 3) & ~3; }
	size_t get_stride_bm2(const base_image *p_img) noexcept { return (p_img->wth * 3 + 3) & ~3; }
	size_t get_stride_bm3(const base_image *p_img) noexcept { return (p_img->wth * 4); }
	size_t get_length_bc1(const base_image *p_img) noexcept { return (p_img->wth * p_img->hth) / 16 * 010; }
	size_t get_length_bc2(const base_image *p_img) noexcept { return (p_img->wth * p_img->hth) / 16 * 020; }

}