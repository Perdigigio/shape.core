#include "video_image.hh"

namespace shape {
namespace video {

	static base_region adjust_dst(cBaseTexture const &, uint32_t, base_region) noexcept;

	//!
	//!

	void upload(cBaseTexture const & p_tex, uint16_t p_img, const void *p_src, uint32_t p_fmt, uint32_t p_len, const base_region &p_dst) noexcept
	{
		const uint16_t l_lvl = uint16_t(p_img & p_tex.get_levels());

		//!
		//!

		switch (p_tex.get_target())
		{
			case base_texture_target::TEX_1D: return p_tex.upload_1d(l_lvl, p_src, p_fmt, p_len, p_dst);
			case base_texture_target::TEX_2D: return p_tex.upload_2d(l_lvl, p_src, p_fmt, p_len, p_dst);
			case base_texture_target::TEX_3D: return p_tex.upload_3d(l_lvl, p_src, p_fmt, p_len, p_dst);
			case base_texture_target::TEX_1D_ARRAY: return p_tex.upload_2d(l_lvl, p_src, p_fmt, p_len, adjust_dst(p_tex, p_img, p_dst));
			case base_texture_target::TEX_2D_ARRAY: return p_tex.upload_3d(l_lvl, p_src, p_fmt, p_len, adjust_dst(p_tex, p_img, p_dst));
		}

		//!
		//!

		LOG_FAIL("Should never be reached");
	}

	cBaseTexture create_texture_1d(uint16_t p_lvl, uint32_t p_fmt, vector1<int> p_dim, const void **p_src) noexcept
	{
		cBaseTexture l_tex;

		//!
		//!

		if (l_tex.init_1d(p_fmt, p_lvl, p_dim))
		{
			for (uint16_t i = 0; i != p_lvl; i++)
			{
				if (!p_src[i])
					LOG_WARN("p_src[" << i << "] is null");

				//!
				//!

				l_tex.upload_1d(i, p_src[i], p_fmt);
			}
		}
		else
			LOG_FAIL("Cannot create texture_1d");

		//!
		//!

		return l_tex;
	}

	cBaseTexture create_texture_2d(uint16_t p_lvl, uint32_t p_fmt, vector2<int> p_dim, const void **p_src) noexcept
	{
		cBaseTexture l_tex;

		//!
		//!

		if (l_tex.init_2d(p_fmt, p_lvl, p_dim))
		{
			for (uint16_t i = 0; i != p_lvl; i++)
			{
				if (!p_src[i])
					LOG_WARN("p_src[" << i << "] is null");

				//!
				//!

				l_tex.upload_2d(i, p_src[i], p_fmt);
			}
		}
		else
			LOG_FAIL("Cannot create texture_1d");

		//!
		//!

		return l_tex;
	}

	cBaseTexture create_texture_3d(uint16_t p_lvl, uint32_t p_fmt, vector3<int> p_dim, const void **p_src) noexcept
	{
		cBaseTexture l_tex;

		//!
		//!

		if (l_tex.init_3d(p_fmt, p_lvl, p_dim))
		{
			for (uint16_t i = 0; i != p_lvl; i++)
			{
				if (!p_src[i])
					LOG_WARN("p_src[" << i << "] is null");

				//!
				//!

				l_tex.upload_3d(i, p_src[i], p_fmt);
			}
		}
		else
			LOG_FAIL("Cannot create texture_1d");

		//!
		//!

		return l_tex;
	}


	//!
	//!

	static base_region adjust_dst(cBaseTexture const & p_tex, uint32_t p_img, base_region p_dst) noexcept
	{
		switch (p_tex.get_target())
		{
			case base_texture_target::TEX_1D_ARRAY:
				p_dst.y0 = uint16_t(p_img / p_tex.get_levels()) + 0;
				p_dst.y1 = uint16_t(p_img / p_tex.get_levels()) + 1;
				break;
			case base_texture_target::TEX_2D_ARRAY:
				p_dst.z0 = uint16_t(p_img / p_tex.get_levels()) + 0;
				p_dst.z1 = uint16_t(p_img / p_tex.get_levels()) + 1;
				break;
		}

		//!
		//!

		return p_dst;
	}

} //! shape::video  
} //! shape 