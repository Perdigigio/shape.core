#include "video_gl_base_shader.hh"

//!
//!

namespace shape {
namespace video {

	bool base_shader::init_vshader(base_shader *p_shader, const char *p_src, GLsizei p_len) noexcept
	{
		#ifdef _DEBUG
		if (!p_shader || glIsProgram(p_shader->handle))
		{
			//!
			//!

			return false;
		}
		#endif

		if (p_src)
		{
			//!
			//!

			p_shader->handle = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &p_src);
		}

		//!
		//!

		return glIsProgram(p_shader->handle);
	}

	bool base_shader::init_hshader(base_shader *p_shader, const char *p_src, GLsizei p_len) noexcept
	{
		#ifdef _DEBUG
		if (!p_shader || glIsProgram(p_shader->handle))
		{
			//!
			//!

			return false;
		}
		#endif

		if (p_src)
		{
			//!
			//!

			p_shader->handle = glCreateShaderProgramv(GL_TESS_CONTROL_SHADER, 1, &p_src);
		}

		//!
		//!

		return glIsProgram(p_shader->handle);
	}

	bool base_shader::init_dshader(base_shader *p_shader, const char *p_src, GLsizei p_len) noexcept
	{
		#ifdef _DEBUG
		if (!p_shader || glIsProgram(p_shader->handle))
		{
			//!
			//!

			return false;
		}
		#endif

		if (p_src)
		{
			//!
			//!

			p_shader->handle = glCreateShaderProgramv(GL_TESS_EVALUATION_SHADER, 1, &p_src);
		}

		//!
		//!

		return glIsProgram(p_shader->handle);
	}

	bool base_shader::init_gshader(base_shader *p_shader, const char *p_src, GLsizei p_len) noexcept
	{
		#ifdef _DEBUG
		if (!p_shader || glIsProgram(p_shader->handle))
		{
			//!
			//!

			return false;
		}
		#endif

		if (p_src)
		{
			//!
			//!

			p_shader->handle = glCreateShaderProgramv(GL_GEOMETRY_SHADER, 1, &p_src);
		}

		//!
		//!

		return glIsProgram(p_shader->handle);
	}

	bool base_shader::init_fshader(base_shader *p_shader, const char *p_src, GLsizei p_len) noexcept
	{
		#ifdef _DEBUG
		if (!p_shader || glIsProgram(p_shader->handle))
		{
			//!
			//!

			return false;
		}
		#endif

		if (p_src)
		{
			//!
			//!

			p_shader->handle = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &p_src);
		}

		//!
		//!

		return glIsProgram(p_shader->handle);
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

} //! shape::video
} //! shape