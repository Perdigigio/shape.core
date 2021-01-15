#ifndef SHAPE_VIDEO_BASE_SHADER_HH__GUARD
#define SHAPE_VIDEO_BASE_SHADER_HH__GUARD

#include "../base.hh"

namespace shape {
namespace video {



	struct base_shader
	{
		static GLuint init_vshader(const char *, GLint * = NULL) noexcept;
		static GLuint init_hshader(const char *, GLint * = NULL) noexcept;
		static GLuint init_dshader(const char *, GLint * = NULL) noexcept;
		static GLuint init_gshader(const char *, GLint * = NULL) noexcept;
		static GLuint init_fshader(const char *, GLint * = NULL) noexcept;

		//! -----------------------------------------------------------

		static void free(GLuint) noexcept;
		
	};

} //! shape::video
} //! shape

#endif