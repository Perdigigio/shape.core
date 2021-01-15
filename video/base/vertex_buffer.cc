#include "vertex_buffer.hh"

namespace shape {
namespace video {

	bool base_vertex_buffer::init(base_vertex_buffer *p_vertex) noexcept
	{
		if (	glIsBuffer(p_vertex->pos) ||
			glIsBuffer(p_vertex->nor) ||
			glIsBuffer(p_vertex->tex) ||
			glIsBuffer(p_vertex->skn))
		{
			//!
			//!

			return false;
		}

		glGenBuffers(1, &p_vertex->pos);
		glGenBuffers(1, &p_vertex->nor);
		glGenBuffers(1, &p_vertex->tex);
		glGenBuffers(1, &p_vertex->skn);

		//!
		//!

		return true;
	}

	bool base_vertex_buffer::allocate_pos(base_vertex_buffer *p_vertex, GLuint p_length, const void * p_buffer) noexcept
	{
		glNamedBufferData(p_vertex->pos, p_length * sizeof(base_vertex_pos), p_buffer, GL_STATIC_DRAW);
	}

	bool base_vertex_buffer::allocate_nor(base_vertex_buffer *, GLuint, const void *) noexcept;
	bool base_vertex_buffer::allocate_tex(base_vertex_buffer *, GLuint, const void *) noexcept;
	bool base_vertex_buffer::allocate_skn(base_vertex_buffer *, GLuint, const void *) noexcept;

		//! --------------------------------------------------------------------------------

		static void  base_vertex_buffer::update_pos(base_vertex_buffer *, GLuint, GLuint, const void *) noexcept;
		static void  base_vertex_buffer::update_nor(base_vertex_buffer *, GLuint, GLuint, const void *) noexcept;
		static void  base_vertex_buffer::update_tex(base_vertex_buffer *, GLuint, GLuint, const void *) noexcept;
		static void  base_vertex_buffer::update_skn(base_vertex_buffer *, GLuint, GLuint, const void *) noexcept;

		//! --------------------------------------------------------------------------------

		static void dispose_pos(base_vertex_buffer *) noexcept;
		static void dispose_nor(base_vertex_buffer *) noexcept;
		static void dispose_tex(base_vertex_buffer *) noexcept;
		static void dispose_skn(base_vertex_buffer *) noexcept;

		//! --------------------------------------------------------------------------------

		static void free(base_vertex_buffer *) noexcept;

} //! shape::video
} //! shape