#ifndef SHAPE_VIDEO_BASE_SHADER_PROGRAM_HH__GUARD
#define SHAPE_VIDEO_BASE_SHADER_PROGRAM_HH__GUARD

#include "video_gl_base.hh"

namespace shape {
namespace video {

	struct base_shader_program_shaders
	{
		GLuint vshader;
		GLuint hshader;
		GLuint dshader;
		GLuint gshader;
		GLuint fshader;
	};

	struct base_shader_program
	{
		GLuint program;
		GLuint vshader; //! ref only
		GLuint hshader; //! ref only
		GLuint dshader; //! ref only
		GLuint gshader; //! ref only
		GLuint fshader; //! ref only

		//! -------------------------------------------------------------

		static bool init(base_shader_program *, const base_shader_program_shaders *) noexcept;

		//! -------------------------------------------------------------

		/**
		 * @param program
		 * @param uniform
		 * @param uniform-len
		 * @param uniform-buf
		 */
		static void set_uniform2f(const base_shader_program *, const char *, GLuint, const real2 *);
		static void set_uniform3f(const base_shader_program *, const char *, GLuint, const real3 *);
		static void set_uniform4f(const base_shader_program *, const char *, GLuint, const real4 *);
		static void set_uniform2i(const base_shader_program *, const char *, GLuint, const sint2 *);
		static void set_uniform3i(const base_shader_program *, const char *, GLuint, const sint3 *);
		static void set_uniform4i(const base_shader_program *, const char *, GLuint, const sint4 *);
		static void set_uniform2u(const base_shader_program *, const char *, GLuint, const uint2 *);
		static void set_uniform3u(const base_shader_program *, const char *, GLuint, const uint3 *);
		static void set_uniform4u(const base_shader_program *, const char *, GLuint, const uint4 *);

		//! -------------------------------------------------------------

		static void detach_vshader(base_shader_program *) noexcept;
		static void detach_hshader(base_shader_program *) noexcept;
		static void detach_dshader(base_shader_program *) noexcept;
		static void detach_gshader(base_shader_program *) noexcept;
		static void detach_fshader(base_shader_program *) noexcept;

		//! -------------------------------------------------------------

		static void free(base_shader_program *) noexcept;
		static void grab(base_shader_program *) noexcept;
	};

	//!
	//!
	//!

	void bind_program(const base_shader_program *) noexcept;

	//!
	//!

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

		inline bool init(const base_shader_program_shaders &p_program) noexcept { return base_shader_program::init(this, &p_program); }

		//! ---------------------------------------------------------------------------------------

		inline void detach_vshader() noexcept { base_shader_program::detach_vshader(this); }
		inline void detach_hshader() noexcept { base_shader_program::detach_hshader(this); }
		inline void detach_dshader() noexcept { base_shader_program::detach_dshader(this); }
		inline void detach_gshader() noexcept { base_shader_program::detach_gshader(this); }
		inline void detach_fshader() noexcept { base_shader_program::detach_fshader(this); }

		//! ---------------------------------------------------------------------------------------

		inline void free() noexcept { base_shader_program::free(this); }
		inline void grab() noexcept { base_shader_program::grab(this); }

		//! ---------------------------------------------------------------------------------------

		inline void bind() const noexcept { video::bind_program(this); }


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