#ifndef SHAPE_VIDEO_BASE_TEXTURE_VIEW_HH__GUARD
#define SHAPE_VIDEO_BASE_TEXTURE_VIEW_HH__GUARD

#include "video_gl_base_texture.hh"

namespace shape {
namespace video {

	struct base_texture_view
	{
		GLuint handle;
		GLenum target;
		GLenum format;
		GLuint mipoff;
		GLuint mipnum;
		GLuint layoff;
		GLuint laynum;

		//! ----------------------------------------------------------------------------------------------------------------

		static bool init_1d(base_texture_view *, GLuint, GLenum, GLuint, GLuint, GLuint) noexcept;
		static bool init_2d(base_texture_view *, GLuint, GLenum, GLuint, GLuint, GLuint) noexcept;
		static bool init_3d(base_texture_view *, GLuint, GLenum, GLuint, GLuint, GLuint) noexcept;
		static bool init_1d_array(base_texture_view *, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint) noexcept;
		static bool init_2d_array(base_texture_view *, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint) noexcept;
		static bool init_cube(base_texture_view *, GLuint, GLenum, GLuint, GLuint, GLuint) noexcept;

		//! ----------------------------------------------------------------------------------------------------------------

		static void bind_ro(base_texture_view const *, GLuint) noexcept;
		static void bind_wo(base_texture_view const *, GLuint) noexcept;
		static void bind_rw(base_texture_view const *, GLuint) noexcept;

		//! ----------------------------------------------------------------------------------------------------------------

		static void free(base_texture_view *) noexcept;
	};

	class cBaseTextureView : private base_texture_view
	{
	public:
		static const struct _TEXTURE_1D {} TEXTURE_1D;
		static const struct _TEXTURE_2D {} TEXTURE_2D;
		static const struct _TEXTURE_3D {} TEXTURE_3D;
		static const struct _TEXTURE_1D_ARRAY {} TEXTURE_1D_ARRAY;
		static const struct _TEXTURE_2D_ARRAY {} TEXTURE_2D_ARRAY;
		static const struct _CUBEMAP {} CUBEMAP;

		//!
		//!

		inline cBaseTextureView() noexcept
		{
			this->handle = {};
			this->target = {};
			this->format = {};
			this->mipoff = {};
			this->mipnum = {};
			this->layoff = {};
			this->laynum = {};
		}

		inline cBaseTextureView(cBaseTextureView && p_other) noexcept : cBaseTextureView{}
		{
			std::swap(this->handle, p_other.handle);
			std::swap(this->target, p_other.target);
			std::swap(this->format, p_other.format);
			std::swap(this->mipoff, p_other.mipoff);
			std::swap(this->mipnum, p_other.mipnum);
			std::swap(this->layoff, p_other.layoff);
			std::swap(this->laynum, p_other.laynum);
		}

		//!
		//!

		cBaseTextureView(const _TEXTURE_1D &, GLuint, GLenum, GLuint, GLuint, GLuint);
		cBaseTextureView(const _TEXTURE_2D &, GLuint, GLenum, GLuint, GLuint, GLuint);
		cBaseTextureView(const _TEXTURE_3D &, GLuint, GLenum, GLuint, GLuint, GLuint);
		cBaseTextureView(const _TEXTURE_1D_ARRAY &, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint);
		cBaseTextureView(const _TEXTURE_2D_ARRAY &, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint);
		cBaseTextureView(const _CUBEMAP &, GLuint, GLenum, GLuint, GLuint, GLuint);

		//!
		//! GETTERS
		//!

		inline GLuint get_handle() const noexcept { return this->handle; }
		inline GLenum get_target() const noexcept { return this->target; }
		inline GLenum get_format() const noexcept { return this->format; }
		inline GLuint get_mipoff() const noexcept { return this->mipoff; }
		inline GLuint get_mipnum() const noexcept { return this->mipnum; }
		inline GLuint get_layoff() const noexcept { return this->layoff; }
		inline GLuint get_laynum() const noexcept { return this->laynum; }

		//! ----------------------------------------------------------------------------------------------------------------

		inline cBaseTextureView& operator=(cBaseTextureView p_other) noexcept
		{
			std::swap(this->handle, p_other.handle);
			std::swap(this->target, p_other.target);
			std::swap(this->format, p_other.format);
			std::swap(this->mipoff, p_other.mipoff);
			std::swap(this->mipnum, p_other.mipnum);
			std::swap(this->layoff, p_other.layoff);
			std::swap(this->laynum, p_other.laynum); return *this;
		}

		//! ----------------------------------------------------------------------------------------------------------------

		inline ~cBaseTextureView() noexcept { base_texture_view::free(this); }
	};

} //! shape::video
} //! shape

#endif
