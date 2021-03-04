#include "video_gl_base_shader.hh"

//!
//!

namespace shape {
namespace video {

	static GLuint create_shader(GLuint, const char *) noexcept;


	//!
	//!

	bool base_shader::init_vshader(base_shader *p_shader, const char *p_source) noexcept
	{
		#ifdef _DEBUG
		if (!p_shader || glIsShader(p_shader->handle))
		{
			//!
			//!

			return false;
		}
		#endif

		if (p_source)
			p_shader->handle = create_shader(GL_VERTEX_SHADER, p_source);

		//!
		//!

		return glIsShader(p_shader->handle);
	}

	bool base_shader::init_hshader(base_shader *p_shader, const char *p_source) noexcept
	{
		#ifdef _DEBUG
		if (!p_shader || glIsShader(p_shader->handle))
		{
			//!
			//!

			return false;
		}
		#endif

		if (p_source)
			p_shader->handle = create_shader(GL_TESS_CONTROL_SHADER, p_source);

		//!
		//!

		return glIsShader(p_shader->handle);
	}

	bool base_shader::init_dshader(base_shader *p_shader, const char *p_source) noexcept
	{
		#ifdef _DEBUG
		if (!p_shader || glIsShader(p_shader->handle))
		{
			//!
			//!

			return false;
		}
		#endif

		if (p_source)
			p_shader->handle = create_shader(GL_TESS_EVALUATION_SHADER, p_source);

		//!
		//!

		return glIsShader(p_shader->handle);
	}

	bool base_shader::init_gshader(base_shader *p_shader, const char *p_source) noexcept
	{
		#ifdef _DEBUG
		if (!p_shader || glIsShader(p_shader->handle))
		{
			//!
			//!

			return false;
		}
		#endif

		if (p_source)
			p_shader->handle = create_shader(GL_GEOMETRY_SHADER, p_source);

		//!
		//!

		return glIsShader(p_shader->handle);
	}

	bool base_shader::init_fshader(base_shader *p_shader, const char *p_source) noexcept
	{
		#ifdef _DEBUG
		if (!p_shader || glIsShader(p_shader->handle))
		{
			//!
			//!

			return false;
		}
		#endif

		if (p_source)
			p_shader->handle = create_shader(GL_FRAGMENT_SHADER, p_source);

		//!
		//!

		return glIsShader(p_shader->handle);
	}


	//! -----------------------------------------------------------

	void base_shader::free(base_shader *p_shader) noexcept
	{
		GLuint l_handle = p_shader->handle;

		//!
		//!

		if (p_shader)
		{
			p_shader->handle = 0;

			//!
			//!

			glDeleteProgram(l_handle);
		}
	}

	//! -----------------------------------------------------------

	static bool compile_shader(GLuint p_shader, const char *p_source) noexcept
	{
		GLint l_status = GL_FALSE;

		//!
		//! COMPILE SHADER
		//!

		glShaderSource(p_shader, 1, &p_source, NULL);
			glCompileShader(p_shader);

		glGetShaderiv(p_shader, GL_COMPILE_STATUS, &l_status);

		//!
		//!

		return l_status != GL_FALSE;
	}

	GLuint create_shader(GLenum p_shader, const char *p_source) noexcept
	{
		GLuint l_handle = glCreateShader(p_shader);

		//!
		//! CREATE AND COMPILE SHADER
		//!

		if (l_handle)
		{
			if (compile_shader(l_handle, p_source))
			{
				return l_handle;
			}

			//!
			//!

			glDeleteShader(l_handle);
		}

		//!
		//!

		return GL_NONE;
	}

} //! shape::video
} //! shape