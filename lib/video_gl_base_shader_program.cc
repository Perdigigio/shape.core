#include "video_gl_base_shader_program.hh"

namespace shape {
namespace video {

	bool base_shader_program::init(base_shader_program *p_program, const base_shader_program_shaders *p_shaders) noexcept
	{
		#ifdef _DEBUG
		if (!p_program || !p_shaders || glIsProgram(p_program->program))
		{
			//!
			//!

			return false;
		}
		#endif

		p_program->program = glCreateProgram();

		//!
		//! LINK PROGRAM
		//!

		if (p_program->program)
		{
			if (p_shaders->vshader) glAttachShader(p_program->program, p_program->vshader = p_shaders->vshader);
			if (p_shaders->hshader) glAttachShader(p_program->program, p_program->hshader = p_shaders->hshader);
			if (p_shaders->dshader) glAttachShader(p_program->program, p_program->dshader = p_shaders->dshader);
			if (p_shaders->gshader) glAttachShader(p_program->program, p_program->gshader = p_shaders->gshader);
			if (p_shaders->fshader) glAttachShader(p_program->program, p_program->fshader = p_shaders->fshader);

			//!
			//!

			glLinkProgram(p_program->program);
		}

		//!
		//!

		return glIsProgram(p_program->program);
	}


	void base_shader_program::detach_vshader(base_shader_program *p_program) noexcept { glDetachShader(p_program->program, p_program->vshader); p_program->vshader = GL_NONE; }
	void base_shader_program::detach_hshader(base_shader_program *p_program) noexcept { glDetachShader(p_program->program, p_program->hshader); p_program->hshader = GL_NONE; }
	void base_shader_program::detach_dshader(base_shader_program *p_program) noexcept { glDetachShader(p_program->program, p_program->dshader); p_program->dshader = GL_NONE; }
	void base_shader_program::detach_gshader(base_shader_program *p_program) noexcept { glDetachShader(p_program->program, p_program->gshader); p_program->gshader = GL_NONE; }
	void base_shader_program::detach_fshader(base_shader_program *p_program) noexcept { glDetachShader(p_program->program, p_program->fshader); p_program->fshader = GL_NONE; }

	void base_shader_program::free(base_shader_program *p_program) noexcept
	{
		if (p_program)
			glDeleteProgramPipelines(1, &p_program->program);
	}
	
	void base_shader_program::grab(base_shader_program *p_program) noexcept
	{
		#ifdef _DEBUG
		if (!p_program || glIsProgramPipeline(p_program->program))
		{
			//!
			//!

			LOG_WARN("p_program is null or p_program->program is already a valid handle (leak)");
		}
		#endif

		//!
		//!

		glGetIntegerv(GL_PROGRAM_PIPELINE_BINDING, (GLint *)&p_program->program);
	}

	void bind_program(const base_shader_program *p_program) noexcept
	{
		glUseProgram(p_program->program);
	}

} //! shape::video
} //! shape