#ifndef SHAPE_VIDEO_BASE_TEXTURE_HH__GUARD
#define SHAPE_VIDEO_BASE_TEXTURE_HH__GUARD

#include "video_gl_base.hh"

namespace shape {
namespace video {

	struct base_texture_target
	{
		static constexpr auto TEX_1D = GL_TEXTURE_1D;
		static constexpr auto TEX_2D = GL_TEXTURE_2D;
		static constexpr auto TEX_3D = GL_TEXTURE_3D;
		static constexpr auto TEX_1D_ARRAY = GL_TEXTURE_1D_ARRAY;
		static constexpr auto TEX_2D_ARRAY = GL_TEXTURE_2D_ARRAY;
	};

	//!
	//!

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

		//! --------------------------------------------------------------------------------------------------------

		static void compressed_update_1d(base_texture const*, uint16_t, const void *, uint32_t) noexcept;
		static void compressed_update_2d(base_texture const*, uint16_t, const void *, uint32_t) noexcept;
		static void compressed_update_3d(base_texture const*, uint16_t, const void *, uint32_t) noexcept;
		static void compressed_update_1d(base_texture const*, uint16_t, const void *, uint32_t, GLsizei, const base_region &) noexcept;
		static void compressed_update_2d(base_texture const*, uint16_t, const void *, uint32_t, GLsizei, const base_region &) noexcept;
		static void compressed_update_3d(base_texture const*, uint16_t, const void *, uint32_t, GLsizei, const base_region &) noexcept;

		static void update_1d(base_texture const*, uint16_t, const void *, GLenum, GLenum) noexcept;
		static void update_2d(base_texture const*, uint16_t, const void *, GLenum, GLenum) noexcept;
		static void update_3d(base_texture const*, uint16_t, const void *, GLenum, GLenum) noexcept;
		static void update_1d(base_texture const*, uint16_t, const void *, GLenum, GLenum, const base_region &) noexcept;
		static void update_2d(base_texture const*, uint16_t, const void *, GLenum, GLenum, const base_region &) noexcept;
		static void update_3d(base_texture const*, uint16_t, const void *, GLenum, GLenum, const base_region &) noexcept;

		//! --------------------------------------------------------------------------------------------------------

		static void upload_1d(base_texture const*, uint16_t, const void *, uint32_t) noexcept;
		static void upload_2d(base_texture const*, uint16_t, const void *, uint32_t) noexcept;
		static void upload_3d(base_texture const*, uint16_t, const void *, uint32_t) noexcept;
		static void upload_1d(base_texture const*, uint16_t, const void *, uint32_t, GLsizei, const base_region &) noexcept;
		static void upload_2d(base_texture const*, uint16_t, const void *, uint32_t, GLsizei, const base_region &) noexcept;
		static void upload_3d(base_texture const*, uint16_t, const void *, uint32_t, GLsizei, const base_region &) noexcept;

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
		inline cBaseTexture() noexcept
		{
			this->handle = {};
			this->levels = {};
			this->target = {};
			this->format = {};
		};

		//! ----------------------------------------------------------------------------------------

		inline bool init_1d(uint32_t p_fmt, uint16_t p_lvl, vector1<GLsizei> p_dim) noexcept { return base_texture::init_1d(this, p_fmt, p_lvl, p_dim); }
		inline bool init_2d(uint32_t p_fmt, uint16_t p_lvl, vector2<GLsizei> p_dim) noexcept { return base_texture::init_2d(this, p_fmt, p_lvl, p_dim); }
		inline bool init_3d(uint32_t p_fmt, uint16_t p_lvl, vector3<GLsizei> p_dim) noexcept { return base_texture::init_3d(this, p_fmt, p_lvl, p_dim); }
		inline bool init_1d_array(uint32_t p_fmt, uint16_t p_lvl, uint16_t p_num, vector1<GLsizei> p_dim) noexcept { return base_texture::init_1d_array(this, p_fmt, p_lvl, p_num, p_dim); }
		inline bool init_2d_array(uint32_t p_fmt, uint16_t p_lvl, uint16_t p_num, vector2<GLsizei> p_dim) noexcept { return base_texture::init_2d_array(this, p_fmt, p_lvl, p_num, p_dim); }

		//! ----------------------------------------------------------------------------------------

		inline void compressed_update_1d(uint16_t p_img, const void *p_src, uint32_t p_fmt) const noexcept { base_texture::compressed_update_1d(this, p_img, p_src, p_fmt); }
		inline void compressed_update_2d(uint16_t p_img, const void *p_src, uint32_t p_fmt) const noexcept { base_texture::compressed_update_2d(this, p_img, p_src, p_fmt); }
		inline void compressed_update_3d(uint16_t p_img, const void *p_src, uint32_t p_fmt) const noexcept { base_texture::compressed_update_3d(this, p_img, p_src, p_fmt); }
		inline void compressed_update_1d(uint16_t p_img, const void *p_src, uint32_t p_fmt, GLsizei p_length, const base_region &p_dst) const noexcept { base_texture::compressed_update_1d(this, p_img, p_src, p_fmt, p_length, p_dst); }
		inline void compressed_update_2d(uint16_t p_img, const void *p_src, uint32_t p_fmt, GLsizei p_length, const base_region &p_dst) const noexcept { base_texture::compressed_update_2d(this, p_img, p_src, p_fmt, p_length, p_dst); }
		inline void compressed_update_3d(uint16_t p_img, const void *p_src, uint32_t p_fmt, GLsizei p_length, const base_region &p_dst) const noexcept { base_texture::compressed_update_3d(this, p_img, p_src, p_fmt, p_length, p_dst); }

		inline void update_1d(uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type) const noexcept { base_texture::update_1d(this, p_img, p_src, p_fmt, p_type); }
		inline void update_2d(uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type) const noexcept { base_texture::update_2d(this, p_img, p_src, p_fmt, p_type); }
		inline void update_3d(uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type) const noexcept { base_texture::update_3d(this, p_img, p_src, p_fmt, p_type); }
		inline void update_1d(uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type, const base_region &p_dst) const noexcept { base_texture::update_1d(this, p_img, p_src, p_fmt, p_type, p_dst); }
		inline void update_2d(uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type, const base_region &p_dst) const noexcept { base_texture::update_2d(this, p_img, p_src, p_fmt, p_type, p_dst); }
		inline void update_3d(uint16_t p_img, const void *p_src, GLenum p_fmt, GLenum p_type, const base_region &p_dst) const noexcept { base_texture::update_3d(this, p_img, p_src, p_fmt, p_type, p_dst); }

		//! ----------------------------------------------------------------------------------------

		inline void upload_1d(uint16_t p_img, const void *p_src, uint32_t p_fmt) const noexcept { base_texture::upload_1d(this, p_img, p_src, p_fmt); }
		inline void upload_2d(uint16_t p_img, const void *p_src, uint32_t p_fmt) const noexcept { base_texture::upload_2d(this, p_img, p_src, p_fmt); }
		inline void upload_3d(uint16_t p_img, const void *p_src, uint32_t p_fmt) const noexcept { base_texture::upload_3d(this, p_img, p_src, p_fmt); }
		inline void upload_1d(uint16_t p_img, const void *p_src, uint32_t p_fmt, GLsizei p_len, const base_region &p_dst) const noexcept { base_texture::upload_1d(this, p_img, p_src, p_fmt, p_len, p_dst); }
		inline void upload_2d(uint16_t p_img, const void *p_src, uint32_t p_fmt, GLsizei p_len, const base_region &p_dst) const noexcept { base_texture::upload_2d(this, p_img, p_src, p_fmt, p_len, p_dst); }
		inline void upload_3d(uint16_t p_img, const void *p_src, uint32_t p_fmt, GLsizei p_len, const base_region &p_dst) const noexcept { base_texture::upload_3d(this, p_img, p_src, p_fmt, p_len, p_dst); }

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