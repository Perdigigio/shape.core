#ifndef SHAPE_CORE_ASSET_IMAGE_HH__GUARD
#define SHAPE_CORE_ASSET_IMAGE_HH__GUARD

#include "../type.hh"
#include "../base.hh"

namespace shape
{
	struct image_fourcc
	{
		static constexpr auto BM16 = fourcc('B', 'M', '1', '6'); //! b:5 g:6 r:5
		static constexpr auto BM24 = fourcc('B', 'M', '2', '4'); //! b:8 g:8 r:8
		static constexpr auto BM32 = fourcc('B', 'M', '3', '2'); //! b:8 g:8 r:8 a:8
		static constexpr auto DXT1 = fourcc('D', 'X', 'T', '1'); //! b:5 g:6 r:5
		static constexpr auto DXT3 = fourcc('D', 'X', 'T', '3'); //! b:5 g:6 r:5 a:4
		static constexpr auto DXT5 = fourcc('D', 'X', 'T', '5'); //! b:5 g:6 r:5 a:8
		static constexpr auto ATI1 = fourcc('A', 'T', 'I', '1'); //! r:8
		static constexpr auto ATI2 = fourcc('A', 'T', 'I', '2'); //! r:8 g:8
	};

	struct image
	{
		uint32_t fmt;
		uint32_t wth;
		uint32_t hth;
	};

	class cImage : private image
	{
	public:
		/**
		 * @param fmt
		 * @param wth
		 * @param hth
		 */
		inline cImage(uint32_t fmt, uint32_t wth, uint32_t hth) noexcept
		{
			this->fmt = fmt;
			this->wth = wth;
			this->hth = hth;
		}

		//!
		//!

		inline uint32_t get_fmt() const noexcept { return this->fmt; }
		inline uint32_t get_wth() const noexcept { return this->wth; }
		inline uint32_t get_hth() const noexcept { return this->hth; }

		//!
		//!

		size_t get_stride() const noexcept;
		size_t get_length() const noexcept;
	};

	//!
	//!

	template<class tag> inline typename buffer<tag>::type_t image_alloc(const cImage& p_image)
	{
		//!
		//!

		return buffer_alloc<tag>(p_image.get_length());
	}
}

#endif
