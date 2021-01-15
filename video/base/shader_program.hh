#ifndef SHAPE_VIDEO_BASE_SHADER_PROGRAM_HH__GUARD
#define SHAPE_VIDEO_BASE_SHADER_PROGRAM_HH__GUARD

#include "../base.hh"

namespace shape {
namespace video {

	struct base_shader_program
	{
		GLuint program;
		GLuint vshader; //! ref only
		GLuint hshader; //! ref only
		GLuint dshader; //! ref only
		GLuint gshader; //! ref only
		GLuint fshader; //! ref only

		//! -------------------------------------------------------------

		static bool init(base_shader_program *) noexcept;

		//! -------------------------------------------------------------

		static void bind_vshader(base_shader_program *, GLuint) noexcept;
		static void bind_hshader(base_shader_program *, GLuint) noexcept;
		static void bind_dshader(base_shader_program *, GLuint) noexcept;
		static void bind_gshader(base_shader_program *, GLuint) noexcept;
		static void bind_fshader(base_shader_program *, GLuint) noexcept;

		//! -------------------------------------------------------------

		static void free(base_shader_program *) noexcept;
		static void grab(base_shader_program *) noexcept;

		//! -------------------------------------------------------------

		static void bind(const base_shader_program *) noexcept;
	};

	class cBaseShaderProgram : private base_shader_program
	{
	public:
		inline cBaseShaderProgram() noexcept
		{
			this->program = {};
			this->vshader = {};
			this->hshader = {};
			this->dshader = {};
			this->gshader = {};
			this->fshader = {};
		}

		//! ---------------------------------------------------------------------------------------

		inline bool init() noexcept { return base_shader_program::init(this); }

		//! ---------------------------------------------------------------------------------------

		inline void bind_vshader(GLuint s) noexcept { base_shader_program::bind_vshader(this, s); }
		inline void bind_hshader(GLuint s) noexcept { base_shader_program::bind_hshader(this, s); }
		inline void bind_dshader(GLuint s) noexcept { base_shader_program::bind_dshader(this, s); }
		inline void bind_gshader(GLuint s) noexcept { base_shader_program::bind_gshader(this, s); }
		inline void bind_fshader(GLuint s) noexcept { base_shader_program::bind_fshader(this, s); }

		//! ---------------------------------------------------------------------------------------

		inline void free() noexcept { base_shader_program::free(this); }
		inline void grab() noexcept { base_shader_program::grab(this); }

		//! ---------------------------------------------------------------------------------------

		inline void bind() const noexcept { base_shader_program::bind(this); }


		//!
		//! GETTERS
		//!

		inline GLuint get_program() const noexcept { return this->program; }
		inline GLuint get_vshader() const noexcept { return this->vshader; }
		inline GLuint get_hshader() const noexcept { return this->hshader; }
		inline GLuint get_dshader() const noexcept { return this->dshader; }
		inline GLuint get_gshader() const noexcept { return this->gshader; }
		inline GLuint get_fshader() const noexcept { return this->fshader; }
	};

} //! shape::video
} //! shape

#endif