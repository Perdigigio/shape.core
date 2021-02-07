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

		static bool init(base_texture *, GLenum, uint16_t, vector1<GLsizei>) noexcept; //! GL_TEXTURE_1D
		static bool init(base_texture *, GLenum, uint16_t, vector2<GLsizei>) noexcept; //! GL_TEXTURE_2D
		static bool init(base_texture *, GLenum, uint16_t, vector3<GLsizei>) noexcept; //! GL_TEXTURE_3D
		static bool init_array(base_texture *, GLenum, uint16_t, uint16_t, vector1<GLsizei>) noexcept; //! GL_TEXTURE_2D_ARRAY
		static bool init_array(base_texture *, GLenum, uint16_t, uint16_t, vector2<GLsizei>) noexcept; //! GL_TEXTURE_3D_ARRAY

		//! --------------------------------------------------------------------------------------------------------

		static void compressed_upload_1d(base_texture const*, uint16_t, const void *) noexcept;
		static void compressed_upload_2d(base_texture const*, uint16_t, const void *) noexcept;
		static void compressed_upload_3d(base_texture const*, uint16_t, const void *) noexcept;
		static void compressed_upload_1d(base_texture const*, uint16_t, const void *, const base_region &) noexcept;
		static void compressed_upload_2d(base_texture const*, uint16_t, const void *, const base_region &) noexcept;
		static void compressed_upload_3d(base_texture const*, uint16_t, const void *, const base_region &) noexcept;

		static void upload_1d(base_texture const*, uint16_t, const void *, GLenum, GLenum) noexcept;
		static void upload_2d(base_texture const*, uint16_t, const void *, GLenum, GLenum) noexcept;
		static void upload_3d(base_texture const*, uint16_t, const void *, GLenum, GLenum) noexcept;
		static void upload_1d(base_texture const*, uint16_t, const void *, GLenum, GLenum, const base_region &) noexcept;
		static void upload_2d(base_texture const*, uint16_t, const void *, GLenum, GLenum, const base_region &) noexcept;
		static void upload_3d(base_texture const*, uint16_t, const void *, GLenum, GLenum, const base_region &) noexcept;

		//! --------------------------------------------------------------------------------------------------------

		static void free(base_texture *) noexcept;
	};

	//!
	//!

	class cBaseTexture : private base_texture
	{
	public:
		inline cBaseTexture() noexcept
		{
			this->handle = {};
			this->levels = {};
			this->target = {};
			this->format = {};
		};

		//! ----------------------------------------------------------------------------------------

		inline bool init(GLenum p_fmt, uint16_t p_lvl, vector1<GLsizei> p_dim) noexcept { return base_texture::init(this, p_fmt, p_lvl, p_dim); }
		inline bool init(GLenum p_fmt, uint16_t p_lvl, vector2<GLsizei> p_dim) noexcept { return base_texture::init(this, p_fmt, p_lvl, p_dim); }
		inline bool init(GLenum p_fmt, uint16_t p_lvl, vector3<GLsizei> p_dim) noexcept { return base_texture::init(this, p_fmt, p_lvl, p_dim); }
		inline bool init_array(GLenum p_fmt, uint16_t p_lvl, uint16_t p_num, vector1<GLsizei> p_dim) noexcept { return base_texture::init_array(this, p_fmt, p_lvl, p_num, p_dim); }
		inline bool init_array(GLenum p_fmt, uint16_t p_lvl, uint16_t p_num, vector2<GLsizei> p_dim) noexcept { return base_texture::init_array(this, p_fmt, p_lvl, p_num, p_dim); }

		//! ----------------------------------------------------------------------------------------

		inline void compressed_upload_1d(uint16_t p_img, const void *p_src) const noexcept { base_texture::compressed_upload_1d(this, p_img, p_src); }
		inline void compressed_upload_2d(uint16_t p_img, const void *p_src) const noexcept { base_texture::compressed_upload_2d(this, p_img, p_src); }
		inline void compressed_upload_3d(uint16_t p_img, const void *p_src) const noexcept { base_texture::compressed_upload_3d(this, p_img, p_src); }
		inline void compressed_upload_1d(uint16_t p_img, const void *p_src, const base_region &p_dst) const noexcept { base_texture::compressed_upload_1d(this, p_img, p_src, p_dst); }
		inline void compressed_upload_2d(uint16_t p_img, const void *p_src, const base_region &p_dst) const noexcept { base_texture::compressed_upload_2d(this, p_img, p_src, p_dst); }
		inline void compressed_upload_3d(uint16_t p_img, const void *p_src, const base_region &p_dst) const noexcept { base_texture::compressed_upload_3d(this, p_img, p_src, p_dst); }

		inline void upload_1d(uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type) const noexcept { base_texture::upload_1d(this, p_img, p_src, p_fmt, p_type); }
		inline void upload_2d(uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type) const noexcept { base_texture::upload_2d(this, p_img, p_src, p_fmt, p_type); }
		inline void upload_3d(uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type) const noexcept { base_texture::upload_3d(this, p_img, p_src, p_fmt, p_type); }
		inline void upload_1d(uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type, const base_region &p_dst) const noexcept { base_texture::upload_1d(this, p_img, p_src, p_fmt, p_type, p_dst); }
		inline void upload_2d(uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type, const base_region &p_dst) const noexcept { base_texture::upload_2d(this, p_img, p_src, p_fmt, p_type, p_dst); }
		inline void upload_3d(uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type, const base_region &p_dst) const noexcept { base_texture::upload_3d(this, p_img, p_src, p_fmt, p_type, p_dst); }

		//! ----------------------------------------------------------------------------------------

		inline void free() noexcept { base_texture::free(this); }

		//! ----------------------------------------------------------------------------------------

		inline GLuint get_handle() const noexcept { return this->handle; }
		inline GLuint get_levels() const noexcept { return this->levels; }
		inline GLenum get_target() const noexcept { return this->target; }
		inline GLenum get_format() const noexcept { return this->format; }
	};

} //! shape::video
} //! shape

#endif