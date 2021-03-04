#include "video_gl_base_texture.hh"

namespace shape {
namespace video {

	/**
	 * @param target 
	 * @param handle
	 * @param subimg
	 */
	static base_region get_region(const base_texture *, GLsizei) noexcept;

	static GLenum get_fmt_enum(uint32_t) noexcept;
	static GLenum get_fmt_type(uint32_t) noexcept;
	static GLenum get_fmt_size(uint32_t) noexcept;

	static GLsizei get_length(const base_texture *, GLsizei) noexcept;

	//!
	//!

	bool base_texture::init_1d(base_texture *p_tex, uint32_t p_fmt, uint16_t p_lvl, vector1<GLsizei> p_dim) noexcept
	{
		#ifdef DEBUG
		if (!p_tex || glIsTexture(p_tex->handle)) return false;
		#endif

		glCreateTextures(GL_TEXTURE_1D, 1, &p_tex->handle);

		//!
		//!

		if (p_tex)
		{
			p_tex->target = GL_TEXTURE_1D;
			p_tex->format = p_fmt;
			p_tex->levels = p_lvl;

			//!
			//!

			glTextureStorage1D(p_tex->handle, p_lvl, get_fmt_enum(p_fmt), x(p_dim));
		}

		//!
		//!

		return glIsTexture(p_tex->handle);
	}

	bool base_texture::init_2d(base_texture *p_tex, uint32_t p_fmt, uint16_t p_lvl, vector2<GLsizei> p_dim) noexcept
	{
		#ifdef DEBUG
		if (!p_tex || glIsTexture(p_tex->handle)) return false;
		#endif

		glCreateTextures(GL_TEXTURE_2D, 1, &p_tex->handle);

		//!
		//!

		if (p_tex->handle)
		{
			p_tex->target = GL_TEXTURE_2D;
			p_tex->format = p_fmt;
			p_tex->levels = p_lvl;

			//!
			//!

			glTextureStorage2D(p_tex->handle, p_lvl, get_fmt_enum(p_fmt), x(p_dim), y(p_dim));
		}

		//!
		//!

		return glIsTexture(p_tex->handle);
	}
	bool base_texture::init_3d(base_texture *p_tex, uint32_t p_fmt, uint16_t p_lvl, vector3<GLsizei> p_dim) noexcept
	{
		#ifdef DEBUG
		if (!p_tex || glIsTexture(p_tex->handle)) return false;
		#endif

		glCreateTextures(GL_TEXTURE_3D, 1, &p_tex->handle);

		//!
		//!

		if (p_tex->handle)
		{
			p_tex->target = GL_TEXTURE_3D;
			p_tex->format = p_fmt;
			p_tex->levels = p_lvl;

			//!
			//!

			glTextureStorage3D(p_tex->handle, p_lvl, get_fmt_enum(p_fmt), x(p_dim), y(p_dim), z(p_dim));
		}

		//!
		//!

		return glIsTexture(p_tex->handle);
	}

	bool base_texture::init_1d_array(base_texture *p_tex, uint32_t p_fmt, uint16_t p_lvl, uint16_t p_num, vector1<GLsizei> p_dim) noexcept
	{
		#ifdef DEBUG
		if (!p_tex || glIsTexture(p_tex->handle)) return false;
		#endif

		glCreateTextures(GL_TEXTURE_1D_ARRAY, 1, &p_tex->handle);

		//!
		//!

		if (p_tex->handle)
		{
			p_tex->target = GL_TEXTURE_1D_ARRAY;
			p_tex->format = p_fmt;
			p_tex->levels = p_lvl;

			//!
			//!

			glTextureStorage2D(p_tex->handle, p_lvl, get_fmt_enum(p_fmt), x(p_dim), p_num);
		}

		//!
		//!

		return glIsTexture(p_tex->handle);
	}

	bool base_texture::init_2d_array(base_texture *p_tex, uint32_t p_fmt, uint16_t p_lvl, uint16_t p_num, vector2<GLsizei> p_dim) noexcept
	{
		#ifdef DEBUG
		if (!p_tex || glIsTexture(p_tex->handle)) return false;
		#endif

		glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &p_tex->handle);

		//!
		//!

		if (p_tex->handle)
		{
			p_tex->target = GL_TEXTURE_2D_ARRAY;
			p_tex->format = p_fmt;
			p_tex->levels = p_lvl;

			//!
			//!

			glTextureStorage3D(p_tex->handle, p_lvl, get_fmt_enum(p_fmt), x(p_dim), y(p_dim), p_num);
		}

		//!
		//!

		return glIsTexture(p_tex->handle);
	}

	bool base_texture::init_cube(base_texture *p_tex, uint32_t p_fmt, uint16_t p_lvl, vector2<GLsizei> p_dim) noexcept
	{
		#ifdef DEBUG
		if (!p_tex || glIsTexture(p_tex->handle)) return false;
		#endif

		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &p_tex->handle);

		//!
		//!

		if (p_tex->handle)
		{
			p_tex->target = GL_TEXTURE_2D;
			p_tex->format = p_fmt;
			p_tex->levels = p_lvl;

			//!
			//!

			glTextureStorage2D(p_tex->handle, p_lvl, get_fmt_enum(p_fmt), x(p_dim), y(p_dim));
		}

		//!
		//!

		return glIsTexture(p_tex->handle);
	}

	void base_texture::compressed_update_1d(base_texture const *p_tex, uint16_t p_img, const void *p_src, uint32_t p_fmt) noexcept { base_texture::compressed_update_1d(p_tex, p_img, p_src, p_fmt, get_length(p_tex, p_img), get_region(p_tex, p_img)); }
	void base_texture::compressed_update_2d(base_texture const *p_tex, uint16_t p_img, const void *p_src, uint32_t p_fmt) noexcept { base_texture::compressed_update_2d(p_tex, p_img, p_src, p_fmt, get_length(p_tex, p_img), get_region(p_tex, p_img)); }
	void base_texture::compressed_update_3d(base_texture const *p_tex, uint16_t p_img, const void *p_src, uint32_t p_fmt) noexcept { base_texture::compressed_update_3d(p_tex, p_img, p_src, p_fmt, get_length(p_tex, p_img), get_region(p_tex, p_img)); }

	void base_texture::compressed_update_1d(base_texture const *p_tex, uint16_t p_img, const void *p_src, uint32_t p_fmt, GLsizei p_length, const base_region &p_dst) noexcept
	{
		GLsizei x = video::x(p_dst);
		GLsizei w = video::w(p_dst);

		//!
		//! EMPTY RESULTS IN NOOP
		//!

		if (x >= 0 && w > 0 && p_src)
		{
			//!
			//!

			glCompressedTextureSubImage1D(p_tex->handle, p_img, x, w, get_fmt_enum(p_fmt), p_length, p_src);
		}
	}

	void base_texture::compressed_update_2d(base_texture const *p_tex, uint16_t p_img, const void *p_src, uint32_t p_fmt, GLsizei p_length, const base_region &p_dst) noexcept
	{
		GLsizei x = video::x(p_dst);
		GLsizei y = video::y(p_dst);
		GLsizei w = video::w(p_dst);
		GLsizei h = video::h(p_dst);


		//!
		//! EMPTY RESULTS IN NOOP
		//!

		if (p_length && x >= 0 && w > 0 
			     && y >= 0 && h > 0 && p_src)
		{
			//!
			//!

			glCompressedTextureSubImage2D(p_tex->handle, p_img, x, y, w, h, get_fmt_enum(p_fmt), p_length, p_src);
		}
	}

	void base_texture::compressed_update_3d(base_texture const *p_tex, uint16_t p_img, const void *p_src, uint32_t p_fmt, GLsizei p_length, const base_region &p_dst) noexcept
	{
		GLsizei x = video::x(p_dst);
		GLsizei y = video::y(p_dst);
		GLsizei z = video::z(p_dst);
		GLsizei w = video::w(p_dst);
		GLsizei h = video::h(p_dst);
		GLsizei d = video::d(p_dst);

		//!
		//! EMPTY RESULTS IN NOOP
		//!

		if (p_length && x >= 0 && w > 0 
			     && y >= 0 && h > 0
			     && z >= 0 && d > 0 && p_src)
		{
			//!
			//!

			glCompressedTextureSubImage2D(p_tex->handle, p_img, x, y, w, h, get_fmt_enum(p_fmt), p_length, p_src);
		}
	}

	void base_texture::update_1d(base_texture const *p_tex, uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type) noexcept { base_texture::update_1d(p_tex, p_img, p_src, p_fmt, p_type, get_region(p_tex, p_img)); }
	void base_texture::update_2d(base_texture const *p_tex, uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type) noexcept { base_texture::update_2d(p_tex, p_img, p_src, p_fmt, p_type, get_region(p_tex, p_img)); }
	void base_texture::update_3d(base_texture const *p_tex, uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type) noexcept { base_texture::update_3d(p_tex, p_img, p_src, p_fmt, p_type, get_region(p_tex, p_img)); }

	void base_texture::update_1d(base_texture const *p_tex, uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type, const base_region &p_dst) noexcept
	{
		GLsizei x = video::x(p_dst);
		GLsizei w = video::w(p_dst);

		//!
		//! EMPTY RESULTS IN NOOP
		//!

		if (p_src && x >= 0 && w > 0)
		{
			//!
			//!

			glTextureSubImage1D(p_tex->handle, p_img, x, w, p_fmt, p_type, p_src);
		}
	}

	void base_texture::update_2d(base_texture const *p_tex, uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type, const base_region &p_dst) noexcept
	{
		GLsizei x = video::x(p_dst);
		GLsizei y = video::y(p_dst);
		GLsizei w = video::w(p_dst);
		GLsizei h = video::h(p_dst);

		//!
		//! EMPTY RESULTS IN NOOP
		//!

		if (p_src && x >= 0 && w > 0)
		{
			//!
			//!

			glTextureSubImage2D(p_tex->handle, p_img, x, y, w, h, p_fmt, p_type, p_src);
		}
	}

	void base_texture::update_3d(base_texture const *p_tex, uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type, const base_region &p_dst) noexcept
	{
		GLsizei x = video::x(p_dst);
		GLsizei y = video::y(p_dst);
		GLsizei z = video::z(p_dst);
		GLsizei w = video::w(p_dst);
		GLsizei h = video::h(p_dst);
		GLsizei d = video::d(p_dst);

		//!
		//! EMPTY RESULTS IN NOOP
		//!

		if (p_src && x >= 0 && w > 0)
		{
			//!
			//!

			glTextureSubImage3D(p_tex->handle, p_img, x, y, z, w, h, d, p_fmt, p_type, p_src);
		}
	}

	void base_texture::upload_1d(base_texture const *p_tex, uint16_t p_img, const void *p_src, uint32_t p_fmt) noexcept
	{
		const GLenum l_size = get_fmt_size(p_fmt);
		const GLenum l_type = get_fmt_type(p_fmt);

		//!
		//!

		is_compressed(p_fmt) ?
			base_texture::compressed_update_1d(p_tex, p_img, p_src, p_fmt) : base_texture::update_1d(p_tex, p_img, p_src, l_size, l_type);
	}

	void base_texture::upload_2d(base_texture const *p_tex, uint16_t p_img, const void *p_src, uint32_t p_fmt) noexcept
	{
		const GLenum l_size = get_fmt_size(p_fmt);
		const GLenum l_type = get_fmt_type(p_fmt);

		//!
		//!

		is_compressed(p_fmt) ?
			base_texture::compressed_update_2d(p_tex, p_img, p_src, p_fmt) : base_texture::update_2d(p_tex, p_img, p_src, l_size, l_type);
	}

	void base_texture::upload_3d(base_texture const *p_tex, uint16_t p_img, const void *p_src, uint32_t p_fmt) noexcept
	{
		const GLenum l_size = get_fmt_size(p_fmt);
		const GLenum l_type = get_fmt_type(p_fmt);

		//!
		//!

		is_compressed(p_fmt) ?
			base_texture::compressed_update_3d(p_tex, p_img, p_src, p_fmt) : base_texture::update_3d(p_tex, p_img, p_src, l_size, l_type);
	}

	void base_texture::upload_1d(base_texture const *p_tex, uint16_t p_img, const void *p_src, uint32_t p_fmt, GLsizei p_len, const base_region &p_dst) noexcept
	{
		const GLenum l_size = get_fmt_size(p_fmt);
		const GLenum l_type = get_fmt_type(p_fmt);

		//!
		//!

		is_compressed(p_fmt) ?
			base_texture::compressed_update_1d(p_tex, p_img, p_src, p_fmt, p_len, p_dst) : base_texture::update_1d(p_tex, p_img, p_src, l_size, l_type, p_dst);
	}

	void base_texture::upload_2d(base_texture const *p_tex, uint16_t p_img, const void *p_src, uint32_t p_fmt, GLsizei p_len, const base_region &p_dst) noexcept
	{
		const GLenum l_size = get_fmt_size(p_fmt);
		const GLenum l_type = get_fmt_type(p_fmt);

		//!
		//!

		is_compressed(p_fmt) ?
			base_texture::compressed_update_2d(p_tex, p_img, p_src, p_fmt, p_len, p_dst) : base_texture::update_2d(p_tex, p_img, p_src, l_size, l_type, p_dst);
	}

	void base_texture::upload_3d(base_texture const *p_tex, uint16_t p_img, const void *p_src, uint32_t p_fmt, GLsizei p_len, const base_region &p_dst) noexcept
	{
		const GLenum l_size = get_fmt_size(p_fmt);
		const GLenum l_type = get_fmt_type(p_fmt);

		//!
		//!

		is_compressed(p_fmt) ?
			base_texture::compressed_update_3d(p_tex, p_img, p_src, p_fmt, p_len, p_dst) : base_texture::update_3d(p_tex, p_img, p_src, l_size, l_type, p_dst);
	}


	void base_texture::free(base_texture *p_tex) noexcept
	{
		if (p_tex)
			glDeleteTextures(1, &p_tex->handle);
	}

	//!
	//!

	base_region get_region(const base_texture *p_tex, GLsizei p_level) noexcept
	{
		GLsizei x1 = 1;
		GLsizei y1 = 1;
		GLsizei z1 = 1;

		switch (p_tex->target)
		{
			case GL_TEXTURE_3D:       glGetTextureLevelParameteriv(p_tex->handle, p_level, GL_TEXTURE_DEPTH,  &z1);
			case GL_TEXTURE_2D:       glGetTextureLevelParameteriv(p_tex->handle, p_level, GL_TEXTURE_HEIGHT, &y1);
			case GL_TEXTURE_1D:       glGetTextureLevelParameteriv(p_tex->handle, p_level, GL_TEXTURE_WIDTH,  &x1); break;
			case GL_TEXTURE_2D_ARRAY: glGetTextureLevelParameteriv(p_tex->handle, p_level, GL_TEXTURE_HEIGHT, &y1);
			case GL_TEXTURE_1D_ARRAY: glGetTextureLevelParameteriv(p_tex->handle, p_level, GL_TEXTURE_WIDTH,  &x1); break;
		}

		//!
		//!

		return { 0, x1, 0, y1, 0, z1 };
	}

	GLsizei get_length(const base_texture *p_tex, GLsizei p_level) noexcept
	{
		GLsizei l_length = 0;

		//!
		//! GET FULL LEVEL SIZE
		//!

		if (is_compressed(p_tex->format))
			glGetTextureLevelParameteriv(p_tex->handle, p_level, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &p_level);

		//!
		//!

		return l_length;
	}

	GLenum get_fmt_enum(GLenum p_format) noexcept
	{
		switch (p_format)
		{
			case pixel::LUMA: return GL_R8;
			case pixel::BM16: return GL_RGB565;
			case pixel::BM24: return GL_SRGB8;
			case pixel::BM32: return GL_SRGB8_ALPHA8;
			case pixel::DXT1: return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
			case pixel::DXT3: return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT;
			case pixel::DXT5: return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT;
			case pixel::ATI1: return GL_COMPRESSED_RED_RGTC1;
			case pixel::ATI2: return GL_COMPRESSED_RG_RGTC2;
			case pixel::ETC1: return GL_COMPRESSED_SRGB8_ETC2;
			case pixel::ETC2: return GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC;
			case pixel::HD32: return GL_R11F_G11F_B10F;
			case pixel::HD64: return GL_RGBA16F;
			case pixel::FLT1: return GL_R32F;
		}

		//!
		//!

		return GL_NONE;
	}

	GLenum get_fmt_type(uint32_t p_fmt) noexcept
	{
		switch (p_fmt)
		{
			case pixel::LUMA: return GL_UNSIGNED_BYTE;
			case pixel::BM16: return GL_UNSIGNED_SHORT_5_6_5_REV;
			case pixel::BM24: return GL_UNSIGNED_BYTE;
			case pixel::BM32: return GL_UNSIGNED_INT_8_8_8_8_REV;
		}

		//!
		//!

		return GL_NONE;
	}

	GLenum get_fmt_size(uint32_t p_fmt) noexcept
	{
		switch (p_fmt)
		{
			case pixel::LUMA: return GL_RED;
			case pixel::BM16: return GL_BGR;
			case pixel::BM24: return GL_BGR;
			case pixel::BM32: return GL_BGRA;
		}

		//!
		//!

		return GL_NONE;
	}


} //! shape::video
} //! shape