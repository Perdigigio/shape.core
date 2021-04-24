#include "video_gl_base_texture_view.hh"

namespace shape {
namespace video {

	bool base_texture_view::init_1d(base_texture_view *p_view, GLuint p_tex, GLenum p_fmt,
		GLuint p_min,
		GLuint p_num,
		GLuint p_off) noexcept
	{
		#ifdef _DEBUG
		if (!p_view || glIsTexture(p_view->handle))
			return false;
		#endif

		glGenTextures(1, &p_view->handle);

		//!
		//!

		if (p_view->handle)
		{
			p_view->format = p_fmt;
			p_view->target = GL_TEXTURE_1D;
			p_view->mipoff = p_min;
			p_view->mipnum = p_num;
			p_view->layoff = p_off;
			p_view->laynum = 1;

			//!
			//!

			glTextureView(p_view->handle, GL_TEXTURE_1D, p_tex, p_fmt, p_min, p_num, p_off, 1);
		}

		//!
		//!

		return glIsTexture(p_view->handle);
	}

	bool base_texture_view::init_2d(base_texture_view *p_view, GLuint p_tex, GLenum p_fmt, GLuint p_min, GLuint p_num, GLuint p_off) noexcept
	{
		#ifdef _DEBUG
		if (!p_view || glIsTexture(p_view->handle))
			return false;
		#endif

		glGenTextures(1, &p_view->handle);

		//!
		//!

		if (p_view->handle)
		{
			p_view->format = p_fmt;
			p_view->target = GL_TEXTURE_2D;
			p_view->mipoff = p_min;
			p_view->mipnum = p_num;
			p_view->layoff = p_off;
			p_view->laynum = 1;

			//!
			//!

			glTextureView(p_view->handle, GL_TEXTURE_2D, p_tex, p_fmt, p_min, p_num, p_off, 1);
		}

		//!
		//!

		return glIsTexture(p_view->handle);
	}

	bool base_texture_view::init_3d(base_texture_view *p_view, GLuint p_tex, GLenum p_fmt, GLuint p_min, GLuint p_num, GLuint p_off) noexcept
	{
		#ifdef _DEBUG
		if (!p_view || glIsTexture(p_view->handle))
			return false;
		#endif

		glGenTextures(1, &p_view->handle);

		//!
		//!

		if (p_view->handle)
		{
			p_view->format = p_fmt;
			p_view->target = GL_TEXTURE_3D;
			p_view->mipoff = p_min;
			p_view->mipnum = p_num;
			p_view->layoff = p_off;
			p_view->laynum = 1;


			//!
			//!

			glTextureView(p_view->handle, GL_TEXTURE_3D, p_tex, p_fmt, p_min, p_num, p_off, 1);
		}

		//!
		//!

		return glIsTexture(p_view->handle);
	}

	bool base_texture_view::init_1d_array(base_texture_view *p_view, GLuint p_tex, GLenum p_fmt, GLuint p_min, GLuint p_num, GLuint p_off, GLuint p_len) noexcept
	{
		#ifdef _DEBUG
		if (!p_view || glIsTexture(p_view->handle))
			return false;
		#endif

		glGenTextures(1, &p_view->handle);

		//!
		//!

		if (p_view->handle)
		{
			p_view->format = p_fmt;
			p_view->target = GL_TEXTURE_1D_ARRAY;
			p_view->mipoff = p_min;
			p_view->mipnum = p_num;
			p_view->layoff = p_off;
			p_view->laynum = p_len;

			//!
			//!

			glTextureView(p_view->handle, GL_TEXTURE_1D_ARRAY, p_tex, p_fmt, p_min, p_num, p_off, p_len);
		}

		//!
		//!

		return glIsTexture(p_view->handle);
	}

	bool base_texture_view::init_2d_array(base_texture_view *p_view, GLuint p_tex, GLenum p_fmt, GLuint p_min, GLuint p_num, GLuint p_off, GLuint p_len) noexcept
	{
		#ifdef _DEBUG
		if (!p_view || glIsTexture(p_view->handle))
			return false;
		#endif

		glGenTextures(1, &p_view->handle);

		//!
		//!

		if (p_view->handle)
		{
			p_view->format = p_fmt;
			p_view->target = GL_TEXTURE_2D_ARRAY;
			p_view->mipoff = p_min;
			p_view->mipnum = p_num;
			p_view->layoff = p_off;
			p_view->laynum = p_len;

			//!
			//!

			glTextureView(p_view->handle, GL_TEXTURE_2D_ARRAY, p_tex, p_fmt, p_min, p_num, p_off, p_len);
		}

		//!
		//!

		return glIsTexture(p_view->handle);
	}

	bool base_texture_view::init_cube(base_texture_view *p_view, GLuint p_tex, GLenum p_fmt, GLuint p_min, GLuint p_num, GLuint p_off) noexcept
	{
		#ifdef _DEBUG
		if (!p_view || glIsTexture(p_view->handle))
			return false;
		#endif

		glGenTextures(1, &p_view->handle);

		//!
		//!

		if (p_view->handle)
		{
			p_view->format = p_fmt;
			p_view->target = GL_TEXTURE_CUBE_MAP;
			p_view->mipoff = p_min;
			p_view->mipnum = p_num;
			p_view->layoff = p_off;
			p_view->laynum = 6;


			//!
			//!

			glTextureView(p_view->handle, GL_TEXTURE_CUBE_MAP, p_tex, p_fmt, p_min, p_num, p_off, 1);
		}

		//!
		//!

		return glIsTexture(p_view->handle);
	}

	//! ---------------------------------------------------------------------------------------------------------------

	void base_texture_view::bind_ro(base_texture_view const *p_view, GLuint p_slot) noexcept
	{
		glBindTextureUnit(p_slot, p_view->handle);
	}

	void base_texture_view::bind_wo(base_texture_view const *p_view, GLuint p_slot) noexcept
	{
		//!
		//!

		glBindImageTexture(p_slot, p_view->handle, 0, (p_view->laynum > 1) ? GL_TRUE : GL_FALSE, p_view->laynum, GL_WRITE_ONLY, p_view->format);
	}

	void base_texture_view::bind_rw(base_texture_view const *p_view, GLuint p_slot) noexcept
	{
		//!
		//!

		glBindImageTexture(p_slot, p_view->handle, 0, (p_view->laynum > 1) ? GL_TRUE : GL_FALSE, p_view->laynum, GL_READ_WRITE, p_view->format);
	}

	//! ---------------------------------------------------------------------------------------------------------------

	void  base_texture_view::free(base_texture_view *p_view) noexcept
	{
		if (p_view)
		{
			glDeleteTextures(1, &p_view->handle);

			//!
			//!

			p_view->format = {};
			p_view->target = {};
			p_view->mipoff = {};
			p_view->mipnum = {};
			p_view->layoff = {};
			p_view->laynum = {};
		}
	}

	//!
	//!

	const cBaseTextureView::_TEXTURE_1D cBaseTextureView::TEXTURE_1D = {};
	const cBaseTextureView::_TEXTURE_2D cBaseTextureView::TEXTURE_2D = {};
	const cBaseTextureView::_TEXTURE_3D cBaseTextureView::TEXTURE_3D = {};
	const cBaseTextureView::_TEXTURE_1D_ARRAY cBaseTextureView::TEXTURE_1D_ARRAY = {};
	const cBaseTextureView::_TEXTURE_2D_ARRAY cBaseTextureView::TEXTURE_2D_ARRAY = {};
	const cBaseTextureView::_CUBEMAP cBaseTextureView::CUBEMAP = {};

	cBaseTextureView::cBaseTextureView(const _TEXTURE_1D &, GLuint p_tex, GLenum p_fmt, GLuint p_mip, GLuint p_num, GLuint p_off) { if (!base_texture_view::init_1d(this, p_tex, p_fmt, p_mip, p_num, p_off)) throw failure{}; }
	cBaseTextureView::cBaseTextureView(const _TEXTURE_2D &, GLuint p_tex, GLenum p_fmt, GLuint p_mip, GLuint p_num, GLuint p_off) { if (!base_texture_view::init_2d(this, p_tex, p_fmt, p_mip, p_num, p_off)) throw failure{}; }
	cBaseTextureView::cBaseTextureView(const _TEXTURE_3D &, GLuint p_tex, GLenum p_fmt, GLuint p_mip, GLuint p_num, GLuint p_off) { if (!base_texture_view::init_3d(this, p_tex, p_fmt, p_mip, p_num, p_off)) throw failure{}; }
	cBaseTextureView::cBaseTextureView(const _TEXTURE_1D_ARRAY &, GLuint p_tex, GLenum p_fmt, GLuint p_mip, GLuint p_num, GLuint p_off, GLuint p_len) { if (!base_texture_view::init_1d_array(this, p_tex, p_fmt, p_mip, p_num, p_off, p_len)) throw failure{}; }
	cBaseTextureView::cBaseTextureView(const _TEXTURE_2D_ARRAY &, GLuint p_tex, GLenum p_fmt, GLuint p_mip, GLuint p_num, GLuint p_off, GLuint p_len) { if (!base_texture_view::init_2d_array(this, p_tex, p_fmt, p_mip, p_num, p_off, p_len)) throw failure{}; }
	cBaseTextureView::cBaseTextureView(const _CUBEMAP &,  GLuint p_tex, GLenum p_fmt, GLuint p_mip, GLuint p_num, GLuint p_off)
	{
		if (!base_texture_view::init_cube(this, p_tex, p_fmt, p_mip, p_num, p_off)) throw failure{};
	}
	
} //! shape::video
} //! shape