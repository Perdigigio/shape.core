#ifndef SHAPE_VIDEO_BASE_VERTEX_BUFFER_HH__GUARD
#define SHAPE_VIDEO_BASE_VERTEX_BUFFER_HH__GUARD

#include "video_gl_base_vertex.hh"

namespace shape {
namespace video {

	struct base_vertex_buffer
	{
		GLuint pos;
		GLuint nor;
		GLuint tex;
		GLuint skn;
		GLuint idx;


		//! --------------------------------------------------------------------------------

		static bool init(base_vertex_buffer *) noexcept;

		//! --------------------------------------------------------------------------------

		static void realloc_pos(base_vertex_buffer *, GLuint, const void *) noexcept;
		static void realloc_nor(base_vertex_buffer *, GLuint, const void *) noexcept;
		static void realloc_tex(base_vertex_buffer *, GLuint, const void *) noexcept;
		static void realloc_skn(base_vertex_buffer *, GLuint, const void *) noexcept;
		static void realloc_idx(base_vertex_buffer *, GLuint, const void *) noexcept;

		static void discard_pos(base_vertex_buffer *) noexcept;
		static void discard_nor(base_vertex_buffer *) noexcept;
		static void discard_tex(base_vertex_buffer *) noexcept;
		static void discard_skn(base_vertex_buffer *) noexcept;
		static void discard_idx(base_vertex_buffer *) noexcept;

		static void dispose_pos(base_vertex_buffer *) noexcept;
		static void dispose_nor(base_vertex_buffer *) noexcept;
		static void dispose_tex(base_vertex_buffer *) noexcept;
		static void dispose_skn(base_vertex_buffer *) noexcept;
		static void dispose_idx(base_vertex_buffer *) noexcept;

		//! --------------------------------------------------------------------------------

		static void update_pos(base_vertex_buffer *, GLuint, GLuint, const void *) noexcept;
		static void update_nor(base_vertex_buffer *, GLuint, GLuint, const void *) noexcept;
		static void update_tex(base_vertex_buffer *, GLuint, GLuint, const void *) noexcept;
		static void update_skn(base_vertex_buffer *, GLuint, GLuint, const void *) noexcept;
		static void update_idx(base_vertex_buffer *, GLuint, GLuint, const void *) noexcept;

		//! --------------------------------------------------------------------------------

		static void free(base_vertex_buffer *) noexcept;
	};

	class cBaseVertexBuffer : private base_vertex_buffer
	{
	public:
		inline cBaseVertexBuffer() noexcept
		{
			this->pos = {};
			this->nor = {};
			this->tex = {};
			this->skn = {};
		}

		//! -----------------------------------------------------------------------------------

		inline bool init() noexcept { return base_vertex_buffer::init(this); }

		//! -----------------------------------------------------------------------------------

		inline void realloc_pos(GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffer::realloc_pos(this, p_length, p_buffer); }
		inline void realloc_nor(GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffer::realloc_nor(this, p_length, p_buffer); }
		inline void realloc_tex(GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffer::realloc_tex(this, p_length, p_buffer); }
		inline void realloc_skn(GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffer::realloc_skn(this, p_length, p_buffer); }
		inline void realloc_idx(GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffer::realloc_idx(this, p_length, p_buffer); }

		inline void discard_pos() noexcept { base_vertex_buffer::discard_pos(this); }
		inline void discard_nor() noexcept { base_vertex_buffer::discard_nor(this); }
		inline void discard_tex() noexcept { base_vertex_buffer::discard_tex(this); }
		inline void discard_skn() noexcept { base_vertex_buffer::discard_skn(this); }
		inline void discard_idx() noexcept { base_vertex_buffer::discard_idx(this); }

		inline void dispose_pos() noexcept { base_vertex_buffer::dispose_pos(this); }
		inline void dispose_nor() noexcept { base_vertex_buffer::dispose_nor(this); }
		inline void dispose_tex() noexcept { base_vertex_buffer::dispose_tex(this); }
		inline void dispose_skn() noexcept { base_vertex_buffer::dispose_skn(this); }
		inline void dispose_idx() noexcept { base_vertex_buffer::dispose_idx(this); }

		//! -----------------------------------------------------------------------------------

		inline void update_pos(GLuint p_offset, GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffer::update_pos(this, p_offset, p_length, p_buffer); }
		inline void update_nor(GLuint p_offset, GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffer::update_nor(this, p_offset, p_length, p_buffer); }
		inline void update_tex(GLuint p_offset, GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffer::update_tex(this, p_offset, p_length, p_buffer); }
		inline void update_skn(GLuint p_offset, GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffer::update_skn(this, p_offset, p_length, p_buffer); }
		inline void update_idx(GLuint p_offset, GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffer::update_idx(this, p_offset, p_length, p_buffer); }

		//! -----------------------------------------------------------------------------------

		inline void free() noexcept { base_vertex_buffer::free(this); }


		//!
		//! GETTERS
		//!

		inline GLuint get_pos() const noexcept { return this->pos; }
		inline GLuint get_nor() const noexcept { return this->nor; }
		inline GLuint get_tex() const noexcept { return this->tex; }
		inline GLuint get_skn() const noexcept { return this->skn; }
		inline GLuint get_idx() const noexcept { return this->idx; }
	};


} //! shape::video
} //! shape

#endif