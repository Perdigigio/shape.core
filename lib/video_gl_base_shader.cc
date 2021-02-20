#include "video_gl_base_shader.hh"

//!
//!

namespace shape {
namespace video {


	static GLuint create_program(GLenum, const char *, GLint *) noexcept;

	//!
	//!

	GLuint base_shader::init_vshader(const char *p_source, GLint *p_status) noexcept { return create_program(GL_VERTEX_SHADER,          p_source, p_status); }
	GLuint base_shader::init_hshader(const char *p_source, GLint *p_status) noexcept { return create_program(GL_TESS_CONTROL_SHADER,    p_source, p_status); }
	GLuint base_shader::init_dshader(const char *p_source, GLint *p_status) noexcept { return create_program(GL_TESS_EVALUATION_SHADER, p_source, p_status); }
	GLuint base_shader::init_gshader(const char *p_source, GLint *p_status) noexcept { return create_program(GL_GEOMETRY_SHADER,        p_source, p_status); }
	GLuint base_shader::init_fshader(const char *p_source, GLint *p_status) noexcept { return create_program(GL_FRAGMENT_SHADER,        p_source, p_status); }

	//! -----------------------------------------------------------

	void base_shader::free(GLuint p_shader) noexcept
	{
		glDeleteProgram(p_shader);
	}

	//! -----------------------------------------------------------

	GLuint create_program(GLenum p_target, const char *p_source, GLint *p_status) noexcept
	{
		auto l_shader = glCreateShaderProgramv(p_target, 1, &p_source);

		//!
		//!

		if (l_shader && p_status)
		{
			//!
			//! ALLOCATE LOG BUFFER
			//!

			glGetProgramiv(l_shader, GL_LINK_STATUS, p_status);
		}

		//!
		//!

		return l_shader;
	}


} //! shape::video
} //! shape