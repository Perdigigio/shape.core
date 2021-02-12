#ifndef SHAPE_ASSET_IMAGE_HH__GUARD
#define SHAPE_ASSET_IMAGE_HH__GUARD

#include "type.hh"
#include "base.hh"

namespace shape
{
	struct asset_image
	{
		uint32_t fmt;
		uint32_t wth;
		uint32_t hth;

		//! ---------------------------------------------------

		static size_t get_stride(asset_image const *) noexcept;
		static size_t get_length(asset_image const *) noexcept;
	};

	class cAssetImage : private asset_image
	{
	public:
		inline cAssetImage(uint32_t p_fmt = {}, uint32_t p_wth = {}, uint32_t p_hth = {}) noexcept
		{
			this->fmt = p_fmt;
			this->wth = p_wth;
			this->hth = p_hth;
		}

		//!
		//! GETTERS
		//!

		inline size_t get_stride() const noexcept { return asset_image::get_stride(this); }
		inline size_t get_length() const noexcept { return asset_image::get_length(this); }

		//! -------------------------------------------------------------------------------

		inline uint32_t get_fmt() const noexcept { return this->fmt; }
		inline uint32_t get_wth() const noexcept { return this->wth; }
		inline uint32_t get_hth() const noexcept { return this->hth; }
	};

	class cAssetImageData : public cAssetImage
	{
	public:
		inline cAssetImageData(uint32_t p_fmt = {}, uint32_t p_wth = {}, uint32_t p_hth = {}) : cAssetImage(p_fmt, p_wth, p_hth)
		{
			//!
			//!

			cAssetImageData::realloc();
		}

		void realloc();
		void dispose();

		//!
		//! GETTERS
		//!

		inline void * get_data() const noexcept { return m_bitmap.get(); }

	private:
		buffer<heap_t>::type_t m_bitmap;
	};
}

#endif
