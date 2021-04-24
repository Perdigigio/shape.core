#ifndef SHAPE_VIDEO_BASE_TEXTURE_HH__GUARD
#define SHAPE_VIDEO_BASE_TEXTURE_HH__GUARD

#include "video_gl_base.hh"

namespace shape {
namespace video {

	struct base_texture
	{
		GLuint handle;
		GLuint levels;
		GLenum target;
		GLenum format;

		//! --------------------------------------------------------------------------------------------------------

		static bool init_1d(base_texture *, uint32_t, uint16_t, vector1<GLsizei>) noexcept; //! GL_TEXTURE_1D
		static bool init_2d(base_texture *, uint32_t, uint16_t, vector2<GLsizei>) noexcept; //! GL_TEXTURE_2D
		static bool init_3d(base_texture *, uint32_t, uint16_t, vector3<GLsizei>) noexcept; //! GL_TEXTURE_3D
		static bool init_1d_array(base_texture *, uint32_t, uint16_t, uint16_t, vector1<GLsizei>) noexcept; //! GL_TEXTURE_2D_ARRAY
		static bool init_2d_array(base_texture *, uint32_t, uint16_t, uint16_t, vector2<GLsizei>) noexcept; //! GL_TEXTURE_3D_ARRAY

		static bool init_cube(base_texture *, uint32_t, uint16_t, vector2<GLsizei>) noexcept;

		//! --------------------------------------------------------------------------------------------------------

		static void compressed_update_1d(base_texture const*, uint16_t, const void *, uint32_t) noexcept;
		static void compressed_update_2d(base_texture const*, uint16_t, const void *, uint32_t) noexcept;
		static void compressed_update_3d(base_texture const*, uint16_t, const void *, uint32_t) noexcept;
		static void compressed_update_1d(base_texture const*, uint16_t, const void *, uint32_t, GLsizei, const base_region &) noexcept;
		static void compressed_update_2d(base_texture const*, uint16_t, const void *, uint32_t, GLsizei, const base_region &) noexcept;
		static void compressed_update_3d(base_texture const*, uint16_t, const void *, uint32_t, GLsizei, const base_region &) noexcept;

		static void update_1d(base_texture const*, uint16_t, const void *, uint32_t) noexcept;
		static void update_2d(base_texture const*, uint16_t, const void *, uint32_t) noexcept;
		static void update_3d(base_texture const*, uint16_t, const void *, uint32_t) noexcept;
		static void update_1d(base_texture const*, uint16_t, const void *, uint32_t, const base_region &) noexcept;
		static void update_2d(base_texture const*, uint16_t, const void *, uint32_t, const base_region &) noexcept;
		static void update_3d(base_texture const*, uint16_t, const void *, uint32_t, const base_region &) noexcept;

		//! --------------------------------------------------------------------------------------------------------

		static void discard(base_texture const *, uint16_t);

		//! --------------------------------------------------------------------------------------------------------

		static void free(base_texture *) noexcept;
	};

	//!
	//!

	class cBaseTexture : private base_texture
	{
	public:
		static const struct _TEXTURE_1D {} TEXTURE_1D;
		static const struct _TEXTURE_2D {} TEXTURE_2D;
		static const struct _TEXTURE_3D {} TEXTURE_3D;
		static const struct _CUBEMAP {} CUBEMAP;

		//!
		//!

		inline cBaseTexture() noexcept
		{
			this->handle = {};
			this->levels = {};
			this->target = {};
			this->format = {};
		}

		inline cBaseTexture(cBaseTexture && p_other) noexcept : cBaseTexture{}
		{
			std::swap(this->handle, p_other.handle);
			std::swap(this->levels, p_other.levels);
			std::swap(this->target, p_other.target);
			std::swap(this->format, p_other.format);
		}

		//! ----------------------------------------------------------------------------------------

		cBaseTexture(const _TEXTURE_1D &, uint32_t, uint16_t, vector1<GLsizei>);
		cBaseTexture(const _TEXTURE_2D &, uint32_t, uint16_t, vector2<GLsizei>);
		cBaseTexture(const _TEXTURE_3D &, uint32_t, uint16_t, vector3<GLsizei>);
		cBaseTexture(const _TEXTURE_1D &, uint32_t, uint16_t, uint16_t, vector1<GLsizei>);
		cBaseTexture(const _TEXTURE_2D &, uint32_t, uint16_t, uint16_t, vector2<GLsizei>);

		cBaseTexture(const _CUBEMAP &, uint32_t, uint16_t, vector2<GLsizei>);

		//! ----------------------------------------------------------------------------------------

		inline void compressed_update_1d(uint16_t p_img, const void *p_src, uint32_t p_fmt) const noexcept { base_texture::compressed_update_1d(this, p_img, p_src, p_fmt); }
		inline void compressed_update_2d(uint16_t p_img, const void *p_src, uint32_t p_fmt) const noexcept { base_texture::compressed_update_2d(this, p_img, p_src, p_fmt); }
		inline void compressed_update_3d(uint16_t p_img, const void *p_src, uint32_t p_fmt) const noexcept { base_texture::compressed_update_3d(this, p_img, p_src, p_fmt); }
		inline void compressed_update_1d(uint16_t p_img, const void *p_src, uint32_t p_fmt, GLsizei p_length, const base_region &p_dst) const noexcept { base_texture::compressed_update_1d(this, p_img, p_src, p_fmt, p_length, p_dst); }
		inline void compressed_update_2d(uint16_t p_img, const void *p_src, uint32_t p_fmt, GLsizei p_length, const base_region &p_dst) const noexcept { base_texture::compressed_update_2d(this, p_img, p_src, p_fmt, p_length, p_dst); }
		inline void compressed_update_3d(uint16_t p_img, const void *p_src, uint32_t p_fmt, GLsizei p_length, const base_region &p_dst) const noexcept { base_texture::compressed_update_3d(this, p_img, p_src, p_fmt, p_length, p_dst); }

		inline void update_1d(uint16_t p_img, const void *p_src, uint32_t p_fmt) const noexcept { base_texture::update_1d(this, p_img, p_src, p_fmt); }
		inline void update_2d(uint16_t p_img, const void *p_src, uint32_t p_fmt) const noexcept { base_texture::update_2d(this, p_img, p_src, p_fmt); }
		inline void update_3d(uint16_t p_img, const void *p_src, uint32_t p_fmt) const noexcept { base_texture::update_3d(this, p_img, p_src, p_fmt); }
		inline void update_1d(uint16_t p_img, const void *p_src, uint32_t p_fmt, const base_region &p_dst) const noexcept { base_texture::update_1d(this, p_img, p_src, p_fmt, p_dst); }
		inline void update_2d(uint16_t p_img, const void *p_src, uint32_t p_fmt, const base_region &p_dst) const noexcept { base_texture::update_2d(this, p_img, p_src, p_fmt, p_dst); }
		inline void update_3d(uint16_t p_img, const void *p_src, uint32_t p_fmt, const base_region &p_dst) const noexcept { base_texture::update_3d(this, p_img, p_src, p_fmt, p_dst); }

		//! ----------------------------------------------------------------------------------------

		inline void free() noexcept { base_texture::free(this); }

		//! ----------------------------------------------------------------------------------------

		inline GLuint get_handle() const noexcept { return this->handle; }
		inline GLuint get_levels() const noexcept { return this->levels; }
		inline GLenum get_target() const noexcept { return this->target; }
		inline GLenum get_format() const noexcept { return this->format; }

		//! ----------------------------------------------------------------------------------------

		inline cBaseTexture & operator =(cBaseTexture p_other) noexcept
		{
			std::swap(this->handle, p_other.handle);
			std::swap(this->levels, p_other.levels);
			std::swap(this->target, p_other.target);
			std::swap(this->format, p_other.format); return *this;
		}

		//! ----------------------------------------------------------------------------------------

		inline ~cBaseTexture() noexcept { cBaseTexture::free(); }
	};

} //! shape::video
} //! shape

#endif