#include "video_gl_base_texture.hh"

namespace shape {
namespace video {

	/**
	 * @param target 
	 * @param handle
	 * @param subimg
	 */
	static base_region get_region(const base_texture *, GLsizei) noexcept;

	static GLenum get_fmt_enum(GLenum) noexcept;
//	static GLenum get_fmt_type(GLenum) noexcept;
//	static GLenum get_fmt_size(GLenum) noexcept;

	//!
	//!

	bool base_texture::init(base_texture *p_tex, GLenum p_fmt, uint16_t p_lvl, vector1<GLsizei> p_dim) noexcept
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

	bool base_texture::init(base_texture *p_tex, GLenum p_fmt, uint16_t p_lvl, vector2<GLsizei> p_dim) noexcept
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
	bool base_texture::init(base_texture *p_tex, GLenum p_fmt, uint16_t p_lvl, vector3<GLsizei> p_dim) noexcept
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

	bool base_texture::init_array(base_texture *p_tex, GLenum p_fmt, uint16_t p_lvl, uint16_t p_num, vector1<GLsizei> p_dim) noexcept
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

	bool base_texture::init_array(base_texture *p_tex, GLenum p_fmt, uint16_t p_lvl, uint16_t p_num, vector2<GLsizei> p_dim) noexcept
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

	void base_texture::compressed_upload_1d(base_texture const *p_tex, uint16_t p_img, const void *p_src) noexcept { base_texture::compressed_upload_1d(p_tex, p_img, p_src, get_region(p_tex, p_img)); }
	void base_texture::compressed_upload_2d(base_texture const *p_tex, uint16_t p_img, const void *p_src) noexcept { base_texture::compressed_upload_2d(p_tex, p_img, p_src, get_region(p_tex, p_img)); }
	void base_texture::compressed_upload_3d(base_texture const *p_tex, uint16_t p_img, const void *p_src) noexcept { base_texture::compressed_upload_3d(p_tex, p_img, p_src, get_region(p_tex, p_img)); }

	void base_texture::compressed_upload_1d(base_texture const *p_tex, uint16_t p_img, const void *p_src, const base_region &p_dst) noexcept
	{
		GLsizei l_length = 0;

		GLsizei x = video::x(p_dst);
		GLsizei w = video::w(p_dst);

		glGetTextureLevelParameteriv(p_tex->handle, p_img, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &l_length);

		//!
		//! EMPTY RESULTS IN NOOP
		//!

		if (l_length && x >= 0 && w > 0 && p_src)
		{
			//!
			//!

			glCompressedTextureSubImage1D(p_tex->handle, p_img, x, w, get_fmt_enum(p_tex->format), l_length, p_src);
		}
	}

	void base_texture::compressed_upload_2d(base_texture const *p_tex, uint16_t p_img, const void *p_src, const base_region &p_dst) noexcept
	{
		GLsizei l_length = 0;

		GLsizei x = video::x(p_dst);
		GLsizei y = video::y(p_dst);
		GLsizei w = video::w(p_dst);
		GLsizei h = video::h(p_dst);

		glGetTextureLevelParameteriv(p_tex->handle, p_img, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &l_length);

		//!
		//! EMPTY RESULTS IN NOOP
		//!

		if (l_length && x >= 0 && w > 0 
			     && y >= 0 && h > 0 && p_src)
		{
			//!
			//!

			glCompressedTextureSubImage2D(p_tex->handle, p_img, x, y, w, h, get_fmt_enum(p_tex->format), l_length, p_src);
		}
	}

	void base_texture::compressed_upload_3d(base_texture const *p_tex, uint16_t p_img, const void *p_src, const base_region &p_dst) noexcept
	{
		GLsizei l_length = 0;

		GLsizei x = video::x(p_dst);
		GLsizei y = video::y(p_dst);
		GLsizei z = video::z(p_dst);
		GLsizei w = video::w(p_dst);
		GLsizei h = video::h(p_dst);
		GLsizei d = video::d(p_dst);

		glGetTextureLevelParameteriv(p_tex->handle, p_img, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &l_length);

		//!
		//! EMPTY RESULTS IN NOOP
		//!

		if (l_length && x >= 0 && w > 0 
			     && y >= 0 && h > 0
			     && z >= 0 && d > 0 && p_src)
		{
			//!
			//!

			glCompressedTextureSubImage2D(p_tex->handle, p_img, x, y, w, h, get_fmt_enum(p_tex->format), l_length, p_src);
		}
	}

	void base_texture::upload_1d(base_texture const *p_tex, uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type) noexcept { base_texture::upload_1d(p_tex, p_img, p_src, p_fmt, p_type, get_region(p_tex, p_img)); }
	void base_texture::upload_2d(base_texture const *p_tex, uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type) noexcept { base_texture::upload_2d(p_tex, p_img, p_src, p_fmt, p_type, get_region(p_tex, p_img)); }
	void base_texture::upload_3d(base_texture const *p_tex, uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type) noexcept { base_texture::upload_3d(p_tex, p_img, p_src, p_fmt, p_type, get_region(p_tex, p_img)); }
	
	void base_texture::upload_1d(base_texture const *p_tex, uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type, const base_region &p_dst) noexcept
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

	void base_texture::upload_2d(base_texture const *p_tex, uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type, const base_region &p_dst) noexcept
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
	void base_texture::upload_3d(base_texture const *p_tex, uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type, const base_region &p_dst) noexcept
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
		}

		//!
		//!

		return GL_NONE;
	}

} //! shape::video
} //! shape