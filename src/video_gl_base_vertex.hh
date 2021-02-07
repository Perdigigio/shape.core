#ifndef SHAPE_VIDEO_BASE_VERTEX_HH__GUARD
#define SHAPE_VIDEO_BASE_VERTEX_HH__GUARD

#include "video_gl_base.hh"

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

	struct base_vertex
	{
		GLuint layout;

		//! ----------------------------------------------------------------------

		static bool init(base_vertex *) noexcept;

		//! ----------------------------------------------------------------------

		static void enable_nor(base_vertex *) noexcept;
		static void enable_tex(base_vertex *) noexcept;
		static void enable_skn(base_vertex *) noexcept;

		//! ----------------------------------------------------------------------

		static void attach_pos(base_vertex *, GLuint, GLuint) noexcept;
		static void attach_nor(base_vertex *, GLuint, GLuint) noexcept;
		static void attach_tex(base_vertex *, GLuint, GLuint) noexcept;
		static void attach_skn(base_vertex *, GLuint, GLuint) noexcept;

		static void detach_pos(base_vertex *) noexcept;
		static void detach_nor(base_vertex *) noexcept;
		static void detach_tex(base_vertex *) noexcept;
		static void detach_skn(base_vertex *) noexcept;

		//! ----------------------------------------------------------------------

		static void free(base_vertex *) noexcept;

		//! ----------------------------------------------------------------------

		static void bind(base_vertex const*) noexcept;
	};

	class cBaseVertex : private base_vertex
	{
	public:
		inline cBaseVertex() noexcept
		{
			this->layout = {};
		}


		//! -----------------------------------------------------------------------------

		inline bool init() noexcept { return base_vertex::init(this); }

		//! -----------------------------------------------------------------------------

		inline void enable_nor() noexcept { base_vertex::enable_nor(this); }
		inline void enable_tex() noexcept { base_vertex::enable_tex(this); }
		inline void enable_skn() noexcept { base_vertex::enable_skn(this); }

		//! -----------------------------------------------------------------------------

		inline void attach_pos(GLuint p_buffer, GLuint p_offset) noexcept { base_vertex::attach_pos(this, p_buffer, p_offset); }
		inline void attach_nor(GLuint p_buffer, GLuint p_offset) noexcept { base_vertex::attach_nor(this, p_buffer, p_offset); }
		inline void attach_tex(GLuint p_buffer, GLuint p_offset) noexcept { base_vertex::attach_tex(this, p_buffer, p_offset); }
		inline void attach_skn(GLuint p_buffer, GLuint p_offset) noexcept { base_vertex::attach_skn(this, p_buffer, p_offset); }

		inline void detach_pos() noexcept { base_vertex::detach_pos(this); }
		inline void detach_nor() noexcept { base_vertex::detach_nor(this); }
		inline void detach_tex() noexcept { base_vertex::detach_tex(this); }
		inline void detach_skn() noexcept { base_vertex::detach_skn(this); }

		//! -----------------------------------------------------------------------------

		inline void free() noexcept { base_vertex::free(this); }

		//! -----------------------------------------------------------------------------

		inline void bind() const noexcept { base_vertex::bind(this); }
	};

} //! shape::video
} //! shape

#endif