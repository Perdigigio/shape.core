#include "video_gl_base_shader_textures.hh"

namespace shape {
namespace video {

	void base_shader_textures::bind(base_shader_textures const *p_tex) noexcept
	{
		const GLuint l_textures[4] =
		{
			p_tex->albedo,
			p_tex->normal,
			p_tex->params,
			p_tex->ldepth
		};

		//!
		//!

		glBindTextures(0, 4, l_textures);
	}

} //! shape::video
} //! shape