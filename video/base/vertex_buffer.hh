#ifndef SHAPE_VIDEO_BASE_VERTEX_BUFFER_HH__GUARD
#define SHAPE_VIDEO_BASE_VERTEX_BUFFER_HH__GUARD

#include "vertex.hh"

namespace shape {
namespace video {

	struct base_vertex_buffer
	{
		GLuint pos;
		GLuint nor;
		GLuint tex;
		GLuint skn;

		//! --------------------------------------------------------------------------------

		static bool init(base_vertex_buffer *) noexcept;

		//! --------------------------------------------------------------------------------

		static bool allocate_pos(base_vertex_buffer *, GLuint, const void *) noexcept;
		static bool allocate_nor(base_vertex_buffer *, GLuint, const void *) noexcept;
		static bool allocate_tex(base_vertex_buffer *, GLuint, const void *) noexcept;
		static bool allocate_skn(base_vertex_buffer *, GLuint, const void *) noexcept;

		//! --------------------------------------------------------------------------------

		static void update_pos(base_vertex_buffer *, GLuint, GLuint, const void *) noexcept;
		static void update_nor(base_vertex_buffer *, GLuint, GLuint, const void *) noexcept;
		static void update_tex(base_vertex_buffer *, GLuint, GLuint, const void *) noexcept;
		static void update_skn(base_vertex_buffer *, GLuint, GLuint, const void *) noexcept;

		//! --------------------------------------------------------------------------------

		static void dispose_pos(base_vertex_buffer *) noexcept;
		static void dispose_nor(base_vertex_buffer *) noexcept;
		static void dispose_tex(base_vertex_buffer *) noexcept;
		static void dispose_skn(base_vertex_buffer *) noexcept;

		//! --------------------------------------------------------------------------------

		static void free(base_vertex_buffer *) noexcept;
	};



} //! shape::video
} //! shape

#endif