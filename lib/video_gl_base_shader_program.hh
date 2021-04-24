#ifndef SHAPE_VIDEO_BASE_SHADER_PROGRAM_HH__GUARD
#define SHAPE_VIDEO_BASE_SHADER_PROGRAM_HH__GUARD

#include "video_gl_base_shader.hh"

namespace shape {
namespace video {

	struct base_shader_program
	{
		GLuint program;
		GLuint vshader; //! INTROSPECTION ONLY
		GLuint hshader; //! INTROSPECTION ONLY
		GLuint dshader; //! INTROSPECTION ONLY
		GLuint gshader; //! INTROSPECTION ONLY
		GLuint fshader; //! INTROSPECTION ONLY

		//! -------------------------------------------------------------

		static bool init(base_shader_program *) noexcept;

		//! -------------------------------------------------------------

		static void bind_vshader(base_shader_program *, GLuint) noexcept;
		static void bind_hshader(base_shader_program *, GLuint) noexcept;
		static void bind_dshader(base_shader_program *, GLuint) noexcept;
		static void bind_gshader(base_shader_program *, GLuint) noexcept;
		static void bind_fshader(base_shader_program *, GLuint) noexcept;

		//! -------------------------------------------------------------

		static void bind(base_shader_program const *) noexcept;

		//! -------------------------------------------------------------

		static void free(base_shader_program *) noexcept;
		static void grab(base_shader_program *) noexcept;
	};

	//!
	//!

	class cBaseShaderProgram : private base_shader_program
	{
	public:
		static const struct _INIT {} INIT;

		//!
		//!

		inline cBaseShaderProgram() noexcept
		{
			this->program = {};
			this->vshader = {};
			this->hshader = {};
			this->dshader = {};
			this->gshader = {};
			this->fshader = {};
		}
		
		inline cBaseShaderProgram(cBaseShaderProgram && p_other) noexcept : cBaseShaderProgram{}
		{
			std::swap(this->program, p_other.program);
			std::swap(this->vshader, p_other.vshader);
			std::swap(this->hshader, p_other.hshader);
			std::swap(this->dshader, p_other.dshader);
			std::swap(this->gshader, p_other.gshader);
			std::swap(this->fshader, p_other.fshader);
		}

		//!
		//!

		cBaseShaderProgram(const _INIT &);

		//! ---------------------------------------------------------------------------------------

		inline void bind_vshader(GLuint p_shr) noexcept { base_shader_program::bind_vshader(this, p_shr); }
		inline void bind_hshader(GLuint p_shr) noexcept { base_shader_program::bind_hshader(this, p_shr); }
		inline void bind_dshader(GLuint p_shr) noexcept { base_shader_program::bind_dshader(this, p_shr); }
		inline void bind_gshader(GLuint p_shr) noexcept { base_shader_program::bind_gshader(this, p_shr); }
		inline void bind_fshader(GLuint p_shr) noexcept { base_shader_program::bind_fshader(this, p_shr); }

		inline void bind_vshader(const cBaseShader &p_shr) noexcept { base_shader_program::bind_vshader(this, p_shr.get_handle()); }
		inline void bind_hshader(const cBaseShader &p_shr) noexcept { base_shader_program::bind_hshader(this, p_shr.get_handle()); }
		inline void bind_dshader(const cBaseShader &p_shr) noexcept { base_shader_program::bind_dshader(this, p_shr.get_handle()); }
		inline void bind_gshader(const cBaseShader &p_shr) noexcept { base_shader_program::bind_gshader(this, p_shr.get_handle()); }
		inline void bind_fshader(const cBaseShader &p_shr) noexcept { base_shader_program::bind_fshader(this, p_shr.get_handle()); }

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

		//! ---------------------------------------------------------------------------------------

		cBaseShaderProgram& operator=(cBaseShaderProgram p_other) noexcept
		{
			std::swap(this->program, p_other.program);
			std::swap(this->vshader, p_other.vshader);
			std::swap(this->hshader, p_other.hshader);
			std::swap(this->dshader, p_other.dshader);
			std::swap(this->gshader, p_other.gshader);
			std::swap(this->fshader, p_other.fshader); return *this;
		}

		//! ---------------------------------------------------------------------------------------

		inline ~cBaseShaderProgram() noexcept { base_shader_program::free(this); }
	};

} //! shape::video
} //! shape

#endif