#ifndef SHAPE_VIDEO_BASE_VERTEX_BUFFERS_HH__GUARD
#define SHAPE_VIDEO_BASE_VERTEX_BUFFERS_HH__GUARD

#include "video_gl_base_vertex.hh"

namespace shape {
namespace video {

	struct base_vertex_buffers
	{
		GLuint pos;
		GLuint nor;
		GLuint tex;
		GLuint skn;
		GLuint idx;


		//! --------------------------------------------------------------------------------

		static bool init(base_vertex_buffers *) noexcept;

		//! --------------------------------------------------------------------------------

		static void realloc_pos(base_vertex_buffers *, GLuint, const void *) noexcept;
		static void realloc_nor(base_vertex_buffers *, GLuint, const void *) noexcept;
		static void realloc_tex(base_vertex_buffers *, GLuint, const void *) noexcept;
		static void realloc_skn(base_vertex_buffers *, GLuint, const void *) noexcept;
		static void realloc_idx(base_vertex_buffers *, GLuint, const void *) noexcept;

		static void discard_pos(base_vertex_buffers *) noexcept;
		static void discard_nor(base_vertex_buffers *) noexcept;
		static void discard_tex(base_vertex_buffers *) noexcept;
		static void discard_skn(base_vertex_buffers *) noexcept;
		static void discard_idx(base_vertex_buffers *) noexcept;

		static void dispose_pos(base_vertex_buffers *) noexcept;
		static void dispose_nor(base_vertex_buffers *) noexcept;
		static void dispose_tex(base_vertex_buffers *) noexcept;
		static void dispose_skn(base_vertex_buffers *) noexcept;
		static void dispose_idx(base_vertex_buffers *) noexcept;

		//! --------------------------------------------------------------------------------

		static void update_pos(base_vertex_buffers *, GLuint, GLuint, const void *) noexcept;
		static void update_nor(base_vertex_buffers *, GLuint, GLuint, const void *) noexcept;
		static void update_tex(base_vertex_buffers *, GLuint, GLuint, const void *) noexcept;
		static void update_skn(base_vertex_buffers *, GLuint, GLuint, const void *) noexcept;
		static void update_idx(base_vertex_buffers *, GLuint, GLuint, const void *) noexcept;

		//! --------------------------------------------------------------------------------

		static void free(base_vertex_buffers *) noexcept;
	};

	class cBaseVertexBuffers
	{
	public:
		inline cBaseVertexBuffers() : m_object{ std::make_unique<base_vertex_buffers>() }
		{
			m_object->pos = {};
			m_object->nor = {};
			m_object->tex = {};
			m_object->skn = {};
			m_object->idx = {};
		}

		cBaseVertexBuffers(cBaseVertexBuffers &&) noexcept = default;

		//! -----------------------------------------------------------------------------------

		inline bool init() noexcept { return base_vertex_buffers::init(m_object.get()); }

		//! -----------------------------------------------------------------------------------

		inline void realloc_pos(GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffers::realloc_pos(m_object.get(), p_length, p_buffer); }
		inline void realloc_nor(GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffers::realloc_nor(m_object.get(), p_length, p_buffer); }
		inline void realloc_tex(GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffers::realloc_tex(m_object.get(), p_length, p_buffer); }
		inline void realloc_skn(GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffers::realloc_skn(m_object.get(), p_length, p_buffer); }
		inline void realloc_idx(GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffers::realloc_idx(m_object.get(), p_length, p_buffer); }

		inline void discard_pos() noexcept { base_vertex_buffers::discard_pos(m_object.get()); }
		inline void discard_nor() noexcept { base_vertex_buffers::discard_nor(m_object.get()); }
		inline void discard_tex() noexcept { base_vertex_buffers::discard_tex(m_object.get()); }
		inline void discard_skn() noexcept { base_vertex_buffers::discard_skn(m_object.get()); }
		inline void discard_idx() noexcept { base_vertex_buffers::discard_idx(m_object.get()); }

		inline void dispose_pos() noexcept { base_vertex_buffers::dispose_pos(m_object.get()); }
		inline void dispose_nor() noexcept { base_vertex_buffers::dispose_nor(m_object.get()); }
		inline void dispose_tex() noexcept { base_vertex_buffers::dispose_tex(m_object.get()); }
		inline void dispose_skn() noexcept { base_vertex_buffers::dispose_skn(m_object.get()); }
		inline void dispose_idx() noexcept { base_vertex_buffers::dispose_idx(m_object.get()); }

		//! -----------------------------------------------------------------------------------

		inline void update_pos(GLuint p_offset, GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffers::update_pos(m_object.get(), p_offset, p_length, p_buffer); }
		inline void update_nor(GLuint p_offset, GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffers::update_nor(m_object.get(), p_offset, p_length, p_buffer); }
		inline void update_tex(GLuint p_offset, GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffers::update_tex(m_object.get(), p_offset, p_length, p_buffer); }
		inline void update_skn(GLuint p_offset, GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffers::update_skn(m_object.get(), p_offset, p_length, p_buffer); }
		inline void update_idx(GLuint p_offset, GLuint p_length, const void *p_buffer) noexcept { base_vertex_buffers::update_idx(m_object.get(), p_offset, p_length, p_buffer); }

		//! -----------------------------------------------------------------------------------

		inline void free() noexcept { base_vertex_buffers::free(m_object.get()); }

		//!
		//! GETTERS
		//!

		inline GLuint get_pos() const noexcept { return m_object->pos; }
		inline GLuint get_nor() const noexcept { return m_object->nor; }
		inline GLuint get_tex() const noexcept { return m_object->tex; }
		inline GLuint get_skn() const noexcept { return m_object->skn; }
		inline GLuint get_idx() const noexcept { return m_object->idx; }

		//! -----------------------------------------------------------------------------------

		inline ~cBaseVertexBuffers() noexcept
		{
			cBaseVertexBuffers::free();
		}

	private:
		std::unique_ptr<base_vertex_buffers> m_object;
	};


} //! shape::video
} //! shape

#endif