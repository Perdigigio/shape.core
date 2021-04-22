#ifndef SHAPE_VIDEO_BASE_SHADER_HH__GUARD
#define SHAPE_VIDEO_BASE_SHADER_HH__GUARD

#include "video_gl_base.hh"

namespace shape {
namespace video {

	struct base_shader
	{
		GLuint handle;

		//! -----------------------------------------------------------

		static bool init_vshader(base_shader *, const char *, GLsizei) noexcept;
		static bool init_hshader(base_shader *, const char *, GLsizei) noexcept;
		static bool init_dshader(base_shader *, const char *, GLsizei) noexcept;
		static bool init_gshader(base_shader *, const char *, GLsizei) noexcept;
		static bool init_fshader(base_shader *, const char *, GLsizei) noexcept;

		//! -----------------------------------------------------------

		static void free(base_shader *) noexcept;
	};

	class cBaseShader : private base_shader
	{
	public:
		static const struct _VSHADER {} VSHADER;
		static const struct _HSHADER {} HSHADER;
		static const struct _DSHADER {} DSHADER;
		static const struct _GSHADER {} GSHADER;
		static const struct _FSHADER {} FSHADER;

		//!
		//!

		inline cBaseShader(cBaseShader && p_other) noexcept
		{
			std::swap(this->handle = {}, p_other.handle);
		}

		//!
		//!

		cBaseShader(const _VSHADER &, const char *, GLsizei = -1);
		cBaseShader(const _HSHADER &, const char *, GLsizei = -1);
		cBaseShader(const _DSHADER &, const char *, GLsizei = -1);
		cBaseShader(const _GSHADER &, const char *, GLsizei = -1);
		cBaseShader(const _FSHADER &, const char *, GLsizei = -1);

		//! ------------------------------------------------------------------------------------------------------------

		void free() noexcept { base_shader::free(this); }

		//! ------------------------------------------------------------------------------------------------------------

		inline GLuint get_handle() const noexcept
		{
			return this->handle;
		}

		//! ------------------------------------------------------------------------------------------------------------

		inline cBaseShader & operator =(cBaseShader p_other) noexcept
		{
			std::swap(this->handle, p_other.handle); return *this;
		}

		inline ~cBaseShader() noexcept { base_shader::free(this); }
	};

} //! shape::video
} //! shape

#endif