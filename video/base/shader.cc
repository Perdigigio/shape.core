#include "shader.hh"

//!
//!

namespace shape {
namespace video {


	static bool create_program(GLuint &, GLenum, const char *) noexcept;

	//!
	//!

	bool base_shader::init_vshader(base_shader *p_shader, const char *p_source) noexcept
	{
		if (!p_shader || p_shader->vshader != GLuint{})
		{
			//!
			//!

			return false;
		}

		//!
		//!

		return create_program(p_shader->vshader, GL_VERTEX_SHADER, p_source);
	}

	bool base_shader::init_gshader(base_shader *p_shader, const char *p_source) noexcept
	{
		if (!p_shader || p_shader->gshader != GLuint{})
		{
			//!
			//!

			return false;
		}

		//!
		//!

		return create_program(p_shader->gshader, GL_GEOMETRY_SHADER, p_source);
	}

	bool base_shader::init_fshader(base_shader *p_shader, const char *p_source) noexcept
	{
		if (!p_shader || p_shader->fshader != GLuint{})
		{
			//!
			//!

			return false;
		}

		//!
		//!

		return create_program(p_shader->gshader, GL_GEOMETRY_SHADER, p_source);
	}

	//! -----------------------------------------------------------

	void base_shader::free(base_shader *p_shader) noexcept
	{
		glDeleteProgram(std::exchange(p_shader->vshader, {}));
		glDeleteProgram(std::exchange(p_shader->gshader, {}));
		glDeleteProgram(std::exchange(p_shader->fshader, {}));
	}

	//! -----------------------------------------------------------

	bool create_program(GLuint &p_shader, GLenum p_stage, const char *p_source) noexcept
	{
		auto l_status = GL_TRUE;
		auto l_shader = glCreateShaderProgramv(p_stage, 1, &p_source);

		//!
		//!

		if (l_shader)
		{
			//!
			//!

			glGetProgramiv(l_shader, GL_LINK_STATUS, &l_status);
		}

		//!
		//!

		return (l_shader = p_shader, glIsProgram(l_shader));
	}


} //! shape::video
} //! shape