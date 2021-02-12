#include "video_gl_base_vertex_buffer.hh"

namespace shape {
namespace video {

	template<class T> void buffer_malloc(GLuint, GLuint, const void *);
	template<class T> void buffer_update(GLuint, GLuint, GLuint, const void *);

	//!
	//!

	bool base_vertex_buffer::init(base_vertex_buffer *p_vertex) noexcept
	{
		#ifdef DEBUG
		if (!p_vertex || glIsBuffer(p_vertex->pos) ||
				 glIsBuffer(p_vertex->nor) ||
				 glIsBuffer(p_vertex->tex) ||
				 glIsBuffer(p_vertex->skn) ||
				 glIsBuffer(p_vertex->idx))
		{
			//!
			//!

			return false;
		}
		#endif

		glCreateBuffers(1, &p_vertex->pos);
		glCreateBuffers(1, &p_vertex->nor);
		glCreateBuffers(1, &p_vertex->tex);
		glCreateBuffers(1, &p_vertex->skn);
		glCreateBuffers(1, &p_vertex->idx);

		//!
		//!

		return true;
	}

	//! --------------------------------------------------------------------------------

	void base_vertex_buffer::realloc_pos(base_vertex_buffer *p_vertex, GLuint p_length, const void *p_buffer) noexcept { buffer_malloc<base_model::pos_t>(p_vertex->pos, p_length, p_buffer); }
	void base_vertex_buffer::realloc_nor(base_vertex_buffer *p_vertex, GLuint p_length, const void *p_buffer) noexcept { buffer_malloc<base_model::nor_t>(p_vertex->nor, p_length, p_buffer); }
	void base_vertex_buffer::realloc_tex(base_vertex_buffer *p_vertex, GLuint p_length, const void *p_buffer) noexcept { buffer_malloc<base_model::tex_t>(p_vertex->tex, p_length, p_buffer); }
	void base_vertex_buffer::realloc_skn(base_vertex_buffer *p_vertex, GLuint p_length, const void *p_buffer) noexcept { buffer_malloc<base_model::skn_t>(p_vertex->skn, p_length, p_buffer); }
	void base_vertex_buffer::realloc_idx(base_vertex_buffer *p_vertex, GLuint p_length, const void *p_buffer) noexcept { buffer_malloc<base_model::idx_t>(p_vertex->idx, p_length, p_buffer); }

	void base_vertex_buffer::discard_pos(base_vertex_buffer *p_vertex) noexcept { glInvalidateBufferData(p_vertex->pos); }
	void base_vertex_buffer::discard_nor(base_vertex_buffer *p_vertex) noexcept { glInvalidateBufferData(p_vertex->nor); }
	void base_vertex_buffer::discard_tex(base_vertex_buffer *p_vertex) noexcept { glInvalidateBufferData(p_vertex->tex); }
	void base_vertex_buffer::discard_skn(base_vertex_buffer *p_vertex) noexcept { glInvalidateBufferData(p_vertex->skn); }
	void base_vertex_buffer::discard_idx(base_vertex_buffer *p_vertex) noexcept { glInvalidateBufferData(p_vertex->idx); }

	void base_vertex_buffer::dispose_pos(base_vertex_buffer *p_vertex) noexcept { glNamedBufferData(p_vertex->pos, 0, NULL, GL_STATIC_DRAW); }
	void base_vertex_buffer::dispose_nor(base_vertex_buffer *p_vertex) noexcept { glNamedBufferData(p_vertex->nor, 0, NULL, GL_STATIC_DRAW); }
	void base_vertex_buffer::dispose_tex(base_vertex_buffer *p_vertex) noexcept { glNamedBufferData(p_vertex->tex, 0, NULL, GL_STATIC_DRAW); }
	void base_vertex_buffer::dispose_skn(base_vertex_buffer *p_vertex) noexcept { glNamedBufferData(p_vertex->skn, 0, NULL, GL_STATIC_DRAW); }
	void base_vertex_buffer::dispose_idx(base_vertex_buffer *p_vertex) noexcept { glNamedBufferData(p_vertex->idx, 0, NULL, GL_STATIC_DRAW); }

	//! --------------------------------------------------------------------------------

	void base_vertex_buffer::update_pos(base_vertex_buffer *p_vertex, GLuint p_offset, GLuint p_length, const void *p_buffer) noexcept { buffer_update<base_model::pos_t>(p_vertex->pos, p_offset, p_length, p_buffer); }
	void base_vertex_buffer::update_nor(base_vertex_buffer *p_vertex, GLuint p_offset, GLuint p_length, const void *p_buffer) noexcept { buffer_update<base_model::nor_t>(p_vertex->nor, p_offset, p_length, p_buffer); }
	void base_vertex_buffer::update_tex(base_vertex_buffer *p_vertex, GLuint p_offset, GLuint p_length, const void *p_buffer) noexcept { buffer_update<base_model::tex_t>(p_vertex->tex, p_offset, p_length, p_buffer); }
	void base_vertex_buffer::update_skn(base_vertex_buffer *p_vertex, GLuint p_offset, GLuint p_length, const void *p_buffer) noexcept { buffer_update<base_model::skn_t>(p_vertex->skn, p_offset, p_length, p_buffer); }
	void base_vertex_buffer::update_idx(base_vertex_buffer *p_vertex, GLuint p_offset, GLuint p_length, const void *p_buffer) noexcept { buffer_update<base_model::idx_t>(p_vertex->idx, p_offset, p_length, p_buffer); }

	//! --------------------------------------------------------------------------------

	void base_vertex_buffer::free(base_vertex_buffer *p_vertex) noexcept
	{
		GLuint l_skn = GL_NONE;
		GLuint l_tex = GL_NONE;
		GLuint l_nor = GL_NONE;
		GLuint l_pos = GL_NONE;
		GLuint l_idx = GL_NONE;

		//!
		//!

		if (p_vertex)
		{
			std::swap(p_vertex->skn, l_skn);
			std::swap(p_vertex->tex, l_tex);
			std::swap(p_vertex->nor, l_nor);
			std::swap(p_vertex->pos, l_pos);
			std::swap(p_vertex->idx, l_idx);


			//!
			//!

			glDeleteBuffers(1, &l_pos);
			glDeleteBuffers(1, &l_nor);
			glDeleteBuffers(1, &l_tex);
			glDeleteBuffers(1, &l_skn);
			glDeleteBuffers(1, &l_idx);
		}
	}

	//! --------------------------------------------------------------------------------

	template<class T> void buffer_malloc(GLuint p_handle, GLuint p_length, const void *p_buffer)
	{
		if (glIsBuffer(p_handle))
			glNamedBufferData(p_handle, p_length * sizeof(T), p_buffer, GL_STATIC_DRAW);
	}

	template<class T> void buffer_update(GLuint p_handle, GLuint p_offset, GLuint p_length, const void *p_buffer)
	{
		const GLintptr l_offset = p_offset * sizeof(T);
		const GLintptr l_length = p_length * sizeof(T);

		//!
		//!

		if (glIsBuffer(p_handle) && p_buffer)
			glNamedBufferSubData(p_handle, l_offset, l_length, p_buffer);
	}


} //! shape::video
} //! shape