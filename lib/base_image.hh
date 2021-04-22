#ifndef SHAPE_ASSET_IMAGE_HH__GUARD
#define SHAPE_ASSET_IMAGE_HH__GUARD

#include "type.hh"
#include "base.hh"

namespace shape
{
	struct base_image
	{
		uint32_t fmt;
		uint32_t wth;
		uint32_t hth;

		//! -------------------------------------------------------------------

		static size_t get_stride(base_image const *) noexcept;
		static size_t get_length(base_image const *) noexcept;
	};

	class cBaseImage : private base_image
	{
	public:
		inline cBaseImage() noexcept
		{
			this->fmt = {};
			this->wth = {};
			this->hth = {};
		}

		inline cBaseImage(uint32_t p_fmt, uint32_t p_wth, uint32_t p_hth) noexcept
		{
			this->fmt = p_fmt;
			this->wth = p_wth;
			this->hth = p_hth;
		}

		inline buffer<heap_t>::type_t heap_alloc() const noexcept { return buffer_alloc<heap_t>(base_image::get_length(this)); }
		inline buffer<temp_t>::type_t temp_alloc() const noexcept { return buffer_alloc<temp_t>(base_image::get_length(this)); }
		inline buffer<page_t>::type_t page_alloc() const noexcept { return buffer_alloc<page_t>(base_image::get_length(this)); }

		//!
		//! GETTERS
		//!

		inline size_t get_stride() const noexcept { return base_image::get_stride(this); }
		inline size_t get_length() const noexcept { return base_image::get_length(this); }

		//! -------------------------------------------------------------------------------

		inline uint32_t get_fmt() const noexcept { return this->fmt; }
		inline uint32_t get_wth() const noexcept { return this->wth; }
		inline uint32_t get_hth() const noexcept { return this->hth; }
	};

	template<class mtag> class cBaseImageData : public cBaseImage
	{
	public:
		inline cBaseImageData(const cBaseImage &p_img) : cBaseImage{ p_img }
		{
			//!
			//!

			m_bitmap = buffer_alloc<mtag>(cBaseImage::get_length());
		}

		//!
		//! GETTERS
		//!

		inline void * get_bitmap() const noexcept { return m_bitmap.get(); }

	private:
		typename buffer<mtag>::type_t m_bitmap;
	};
}

#endif
