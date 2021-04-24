#include "video_gl_base_shader_program.hh"

namespace shape {
namespace video {

	const cBaseShaderProgram::_INIT cBaseShaderProgram::INIT = {};

	//!
	//!

	bool base_shader_program::init(base_shader_program *p_program) noexcept
	{
		#ifdef _DEBUG
		if (!p_program || glIsProgramPipeline(p_program->program))
		{
			//!
			//!

			return false;
		}
		#endif

		glCreateProgramPipelines(1, &p_program->program);

		//!
		//! LINK PROGRAM
		//!

		if (p_program->program)
		{
			p_program->vshader = {};
			p_program->hshader = {};
			p_program->dshader = {};
			p_program->gshader = {};
			p_program->fshader = {};
		}

		//!
		//!

		return glIsProgramPipeline(p_program->program);
	}


	void base_shader_program::bind_vshader(base_shader_program *p_program, GLuint p_shr) noexcept { glUseProgramStages(p_program->program, GL_VERTEX_SHADER_BIT,          p_program->vshader = p_shr); }
	void base_shader_program::bind_hshader(base_shader_program *p_program, GLuint p_shr) noexcept { glUseProgramStages(p_program->program, GL_TESS_CONTROL_SHADER_BIT,    p_program->hshader = p_shr); }
	void base_shader_program::bind_dshader(base_shader_program *p_program, GLuint p_shr) noexcept { glUseProgramStages(p_program->program, GL_TESS_EVALUATION_SHADER_BIT, p_program->dshader = p_shr); }
	void base_shader_program::bind_gshader(base_shader_program *p_program, GLuint p_shr) noexcept { glUseProgramStages(p_program->program, GL_GEOMETRY_SHADER_BIT,        p_program->gshader = p_shr); }
	void base_shader_program::bind_fshader(base_shader_program *p_program, GLuint p_shr) noexcept { glUseProgramStages(p_program->program, GL_FRAGMENT_SHADER_BIT,        p_program->fshader = p_shr); }

	void base_shader_program::bind(base_shader_program const *p_program) noexcept { glBindProgramPipeline(p_program->program); }

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

	//!
	//!

	cBaseShaderProgram::cBaseShaderProgram(const _INIT &)
	{
		if (!base_shader_program::init(this)) throw failure{};
	}

} //! shape::video
} //! shape