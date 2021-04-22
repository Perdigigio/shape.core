#include "video_gl_base_shader.hh"

//!
//!

namespace shape {
namespace video {

	static GLuint create_shader(GLuint, const char *) noexcept;


	//!
	//!

	bool base_shader::init_vshader(base_shader *p_shader, const char *p_src, GLsizei p_len) noexcept
	{
		#ifdef _DEBUG
		if (!p_shader || glIsShader(p_shader->handle))
		{
			//!
			//!

			return false;
		}
		#endif

		if (p_src)
			p_shader->handle = create_shader(GL_VERTEX_SHADER, p_src);

		//!
		//!

		return glIsShader(p_shader->handle);
	}

	bool base_shader::init_hshader(base_shader *p_shader, const char *p_src, GLsizei p_len) noexcept
	{
		#ifdef _DEBUG
		if (!p_shader || glIsShader(p_shader->handle))
		{
			//!
			//!

			return false;
		}
		#endif

		if (p_src)
			p_shader->handle = create_shader(GL_TESS_CONTROL_SHADER, p_src);

		//!
		//!

		return glIsShader(p_shader->handle);
	}

	bool base_shader::init_dshader(base_shader *p_shader, const char *p_src, GLsizei p_len) noexcept
	{
		#ifdef _DEBUG
		if (!p_shader || glIsShader(p_shader->handle))
		{
			//!
			//!

			return false;
		}
		#endif

		if (p_src)
			p_shader->handle = create_shader(GL_TESS_EVALUATION_SHADER, p_src);

		//!
		//!

		return glIsShader(p_shader->handle);
	}

	bool base_shader::init_gshader(base_shader *p_shader, const char *p_src, GLsizei p_len) noexcept
	{
		#ifdef _DEBUG
		if (!p_shader || glIsShader(p_shader->handle))
		{
			//!
			//!

			return false;
		}
		#endif

		if (p_src)
			p_shader->handle = create_shader(GL_GEOMETRY_SHADER, p_src);

		//!
		//!

		return glIsShader(p_shader->handle);
	}

	bool base_shader::init_fshader(base_shader *p_shader, const char *p_src, GLsizei p_len) noexcept
	{
		#ifdef _DEBUG
		if (!p_shader || glIsShader(p_shader->handle))
		{
			//!
			//!

			return false;
		}
		#endif

		if (p_src)
			p_shader->handle = create_shader(GL_FRAGMENT_SHADER, p_src);

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

	//!
	//!

	const cBaseShader::_VSHADER cBaseShader::VSHADER = {};
	const cBaseShader::_HSHADER cBaseShader::HSHADER = {};
	const cBaseShader::_DSHADER cBaseShader::DSHADER = {};
	const cBaseShader::_GSHADER cBaseShader::GSHADER = {};
	const cBaseShader::_FSHADER cBaseShader::FSHADER = {};

	cBaseShader::cBaseShader(const _VSHADER &, const char *p_src, GLsizei p_len) { if (!base_shader::init_vshader(this, p_src, p_len)) throw failure{}; }
	cBaseShader::cBaseShader(const _HSHADER &, const char *p_src, GLsizei p_len) { if (!base_shader::init_hshader(this, p_src, p_len)) throw failure{}; }
	cBaseShader::cBaseShader(const _DSHADER &, const char *p_src, GLsizei p_len) { if (!base_shader::init_dshader(this, p_src, p_len)) throw failure{}; }
	cBaseShader::cBaseShader(const _GSHADER &, const char *p_src, GLsizei p_len) { if (!base_shader::init_gshader(this, p_src, p_len)) throw failure{}; }
	cBaseShader::cBaseShader(const _FSHADER &, const char *p_src, GLsizei p_len) { if (!base_shader::init_fshader(this, p_src, p_len)) throw failure{}; }

	//!
	//!

	static bool compile_shader(GLuint p_shader, const char *p_src) noexcept
	{
		GLint l_status = GL_FALSE;

		//!
		//! COMPILE SHADER
		//!

		glShaderSource(p_shader, 1, &p_src, NULL);
			glCompileShader(p_shader);

		glGetShaderiv(p_shader, GL_COMPILE_STATUS, &l_status);

		//!
		//!

		return l_status != GL_FALSE;
	}

	GLuint create_shader(GLenum p_shader, const char *p_src) noexcept
	{
		GLuint l_handle = glCreateShader(p_shader);

		//!
		//! CREATE AND COMPILE SHADER
		//!

		if (l_handle)
		{
			if (compile_shader(l_handle, p_src))
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