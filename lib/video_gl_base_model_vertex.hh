#ifndef SHAPE_VIDEO_BASE_VERTEX_HH__GUARD
#define SHAPE_VIDEO_BASE_VERTEX_HH__GUARD

#include "video_gl_base_model.hh"

namespace shape {
namespace video {

	/**
	 * slot | type | name | components
	 * 
	 *  (0) | real |  pos | [3]
	 *  (1) | word |  nor | [0][4]
	 *  (1) | word |  nor | [1][4]
	 *  (2) | word |  tex | [0][2]
	 *  (2) | word |  tex | [1][2]
	 *  (3) | byte |  skn | [0][4]
	 *  (3) | byte |  skn | [1][4] 
	 * 
	 */

	struct base_model_vertex
	{
		GLuint vao;
		GLuint fmt;

		//! ----------------------------------------------------------------------

		static bool init(base_model_vertex *) noexcept;

		//! ----------------------------------------------------------------------

		static void enable_nor(base_model_vertex const *) noexcept;
		static void enable_tex(base_model_vertex const *) noexcept;
		static void enable_skn(base_model_vertex const *) noexcept;

		//! ----------------------------------------------------------------------

		static void attach_pos(base_model_vertex const *, GLuint, GLuint) noexcept;
		static void attach_nor(base_model_vertex const *, GLuint, GLuint) noexcept;
		static void attach_tex(base_model_vertex const *, GLuint, GLuint) noexcept;
		static void attach_skn(base_model_vertex const *, GLuint, GLuint) noexcept;

		//! ----------------------------------------------------------------------

		static void attach_idx(base_model_vertex const *, GLuint) noexcept;

		//! ----------------------------------------------------------------------

		static void detach_pos(base_model_vertex const *) noexcept;
		static void detach_nor(base_model_vertex const *) noexcept;
		static void detach_tex(base_model_vertex const *) noexcept;
		static void detach_skn(base_model_vertex const *) noexcept;
		static void detach_idx(base_model_vertex const *) noexcept;

		//! ----------------------------------------------------------------------

		static void free(base_model_vertex *) noexcept;

		//! ----------------------------------------------------------------------

		static void bind(base_model_vertex const*) noexcept;
	};

	class cBaseModelVertex : private base_model_vertex
	{
	public:
		inline cBaseModelVertex() noexcept
		{
			this->vao = {};
			this->fmt = {};
		}

		inline cBaseModelVertex(cBaseModelVertex && p_other) noexcept : cBaseModelVertex{}
		{
			std::swap(this->vao, p_other.vao);
			std::swap(this->fmt, p_other.fmt);
		}

		/**
		 * @param fmt
		 */
		cBaseModelVertex(uint32_t);

		//!
		//!

		inline void attach_pos(GLuint p_buffer, GLuint p_offset) const noexcept { base_model_vertex::attach_pos(this, p_buffer, p_offset); }
		inline void attach_nor(GLuint p_buffer, GLuint p_offset) const noexcept { base_model_vertex::attach_nor(this, p_buffer, p_offset); }
		inline void attach_tex(GLuint p_buffer, GLuint p_offset) const noexcept { base_model_vertex::attach_tex(this, p_buffer, p_offset); }
		inline void attach_skn(GLuint p_buffer, GLuint p_offset) const noexcept { base_model_vertex::attach_skn(this, p_buffer, p_offset); }

		//! -----------------------------------------------------------------------------

		inline void attach_idx(GLuint p_buffer) const noexcept { base_model_vertex::attach_idx(this, p_buffer); }

		//! -----------------------------------------------------------------------------

		inline void detach_pos() const noexcept { base_model_vertex::detach_pos(this); }
		inline void detach_nor() const noexcept { base_model_vertex::detach_nor(this); }
		inline void detach_tex() const noexcept { base_model_vertex::detach_tex(this); }
		inline void detach_skn() const noexcept { base_model_vertex::detach_skn(this); }
		inline void detach_idx() const noexcept { base_model_vertex::detach_idx(this); }

		//! -----------------------------------------------------------------------------

		inline void free() noexcept { base_model_vertex::free(this); }

		//! -----------------------------------------------------------------------------

		inline void bind() const noexcept { base_model_vertex::bind(this); }
	};

} //! shape::video
} //! shape

#endif