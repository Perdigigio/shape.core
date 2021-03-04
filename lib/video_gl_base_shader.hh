#ifndef SHAPE_VIDEO_BASE_SHADER_HH__GUARD
#define SHAPE_VIDEO_BASE_SHADER_HH__GUARD

#include "video_gl_base.hh"

namespace shape {
namespace video {

	struct base_shader
	{
		GLuint handle;

		//! -----------------------------------------------------------

		static bool init_vshader(base_shader *, const char *) noexcept;
		static bool init_hshader(base_shader *, const char *) noexcept;
		static bool init_dshader(base_shader *, const char *) noexcept;
		static bool init_gshader(base_shader *, const char *) noexcept;
		static bool init_fshader(base_shader *, const char *) noexcept;

		//! -----------------------------------------------------------

		static void free(base_shader *) noexcept;
	};

	class cBaseShader
	{
	public:
		inline cBaseShader() : m_object{ std::make_unique<base_shader>() }
		{
			m_object->handle = {};
		}

		//! ------------------------------------------------------------------------------------------------------------

		bool init_vshader(const char *p_source) noexcept { return base_shader::init_vshader(m_object.get(), p_source); }
		bool init_hshader(const char *p_source) noexcept { return base_shader::init_hshader(m_object.get(), p_source); }
		bool init_dshader(const char *p_source) noexcept { return base_shader::init_dshader(m_object.get(), p_source); }
		bool init_gshader(const char *p_source) noexcept { return base_shader::init_gshader(m_object.get(), p_source); }
		bool init_fshader(const char *p_source) noexcept { return base_shader::init_fshader(m_object.get(), p_source); }

		//! ------------------------------------------------------------------------------------------------------------

		void free() { base_shader::free(m_object.get()); }

		//! ------------------------------------------------------------------------------------------------------------

		inline GLuint get_handle() const noexcept { return m_object->handle; }

		//! ------------------------------------------------------------------------------------------------------------

		~cBaseShader() noexcept
		{
			cBaseShader::free();
		}

	private:
		std::unique_ptr<base_shader> m_object;
	};

} //! shape::video
} //! shape

#endif