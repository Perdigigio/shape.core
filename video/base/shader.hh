#ifndef SHAPE_VIDEO_BASE_SHADER_HH__GUARD
#define SHAPE_VIDEO_BASE_SHADER_HH__GUARD

#include "../base.hh"

namespace shape {
namespace video {

	struct base_shader
	{
		GLuint vshader;
		GLuint gshader;
		GLuint fshader;

		//! -----------------------------------------------------------

		static bool init_vshader(base_shader *, const char *) noexcept;
		static bool init_gshader(base_shader *, const char *) noexcept;
		static bool init_fshader(base_shader *, const char *) noexcept;

		//! -----------------------------------------------------------

		static void free(base_shader *) noexcept;
	};

	class cBaseShader : private base_shader
	{
	public:
		inline cBaseShader() noexcept
		{
			this->vshader = {};
			this->gshader = {};
			this->fshader = {};
		}

		//! -------------------------------------------------------------------------------------

		bool init_vshader(const char * s) noexcept { return base_shader::init_vshader(this, s); }
		bool init_fshader(const char * s) noexcept { return base_shader::init_vshader(this, s); }
		bool init_gshader(const char * s) noexcept { return base_shader::init_vshader(this, s); }

		//! -------------------------------------------------------------------------------------

		inline void free() noexcept { base_shader::free(this); }

		//!
		//! GETTERS
		//!

		inline GLuint get_vshader() const noexcept { return this->vshader; }
		inline GLuint get_gshader() const noexcept { return this->gshader; }
		inline GLuint get_fshader() const noexcept { return this->fshader; }
	};


} //! shape::video
} //! shape

#endif