#ifndef SHAPE_VIDEO_BASE_SHADER_TEXTURES_HH__GUARD
#define SHAPE_VIDEO_BASE_SHADER_TEXTURES_HH__GUARD

#include "video_gl_base.hh"

namespace shape {
namespace video {

	struct base_shader_textures
	{
		GLuint albedo;
		GLuint normal;
		GLuint params;
		GLuint ldepth;

		//!
		//!

		static void bind(base_shader_textures const *) noexcept;
	};

	class cBaseTextures : private base_shader_textures
	{
	public:
		inline cBaseTextures() noexcept
		{
			this->albedo = {};
			this->normal = {};
			this->params = {};
			this->ldepth = {};
		}

		inline void set_albedo(GLuint p_handle) noexcept { this->albedo = p_handle; }
		inline void set_normal(GLuint p_handle) noexcept { this->normal = p_handle; }
		inline void set_params(GLuint p_handle) noexcept { this->params = p_handle; }
		inline void set_ldepth(GLuint p_handle) noexcept { this->ldepth = p_handle; }

		//!
		//! GETTERS
		//!

		inline GLuint get_albedo() const noexcept { return this->albedo; }
		inline GLuint get_normal() const noexcept { return this->normal; }
		inline GLuint get_params() const noexcept { return this->params; }
		inline GLuint get_ldepth() const noexcept { return this->ldepth; }

		//!
		//!

		inline void bind() const noexcept { base_shader_textures::bind(this); }
	};

} //! shape::video
} //! shape

#endif