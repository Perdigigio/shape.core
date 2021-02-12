#ifndef SHAPE_VIDEO_IMAGE_HH__GUARD
#define SHAPE_VIDEO_IMAGE_HH__GUARD

#include "video_gl_base_texture.hh"

namespace shape {
namespace video {

	struct texture_flg
	{
		static constexpr uint32_t mipmap = 1;
	};

	/**
	 * @param tex
	 * @param img
	 * @param src
	 * @param fmt
	 * @param len
	 * @param dst
	 */
	void upload(cBaseTexture const &, uint16_t, const void *, uint32_t, uint32_t, const base_region &) noexcept;

	/**
	 * @brief create a texture_nd object from source
	 * 
	 * @param lvl
	 * @param fmt
	 * @param dim
	 * @param src
	 */
	cBaseTexture create_texture_1d(uint16_t, uint32_t, vector1<int>, const void **) noexcept;
	cBaseTexture create_texture_2d(uint16_t, uint32_t, vector2<int>, const void **) noexcept;
	cBaseTexture create_texture_3d(uint16_t, uint32_t, vector3<int>, const void **) noexcept;

} //! shape::video
} //! shape

#include "asset_image.hh"

namespace shape {
namespace video {

	static inline void upload(cBaseTexture const &p_tex, uint16_t p_lvl, const cAssetImageData & p_img) noexcept
	{
		const int l_length = (p_img.get_length() <= 0x7FFFFFFF) ? (int)p_img.get_length() : -1;

		const base_region l_dst =
		{
			0, (p_img.get_wth() <= 0x7FFFFFFF) ? (int)p_img.get_wth() : -1,
			0, (p_img.get_hth() <= 0x7FFFFFFF) ? (int)p_img.get_hth() : -1,
			0, 1
		};

		//!
		//!

		upload(p_tex, p_lvl, p_img.get_data(), p_img.get_fmt(), l_length, l_dst);
	}

} //! shape::video
} //! shape

#endif