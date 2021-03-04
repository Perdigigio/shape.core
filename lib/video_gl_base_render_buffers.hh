#ifndef SHAPE_VIDEO_BASE_RENDER_BUFFERS_HH__GUARD
#define SHAPE_VIDEO_BASE_RENDER_BUFFERS_HH__GUARD

#include "video_gl_base.hh"

namespace shape {
namespace video {

	struct base_render_buffers
	{
		GLuint handle;

		GLuint albedo; //! r:10 g:10 b:10 a:2
		GLuint normal; //! x:10 y:10 r:10 s:2
		GLuint params; //! s:10 l:10 m:10 x:2
		GLuint fdepth; //! d:24 s:8
		GLuint tdepth; //! d:24 s:8

		//! ---------------------------------------------------------------------

		static bool init(base_render_buffers *, GLsizei, GLsizei, GLsizei) noexcept;

		//! ---------------------------------------------------------------------

		static void clear_albedo(base_render_buffers *, float, float, float, float) noexcept;
		static void clear_normal(base_render_buffers *, float, float, float, float) noexcept;
		static void clear_params(base_render_buffers *, float, float, float, float) noexcept;
		static void clear_fdepth(base_render_buffers *, float) noexcept;
		static void clear_tdepth(base_render_buffers *, float) noexcept;

		//! ---------------------------------------------------------------------

		static void discard_albedo(base_render_buffers *) noexcept;
		static void discard_normal(base_render_buffers *) noexcept;
		static void discard_params(base_render_buffers *) noexcept;
		static void discard_fdepth(base_render_buffers *) noexcept;
		static void discard_tdepth(base_render_buffers *) noexcept;


		//! ---------------------------------------------------------------------

		static void free(base_render_buffers *) noexcept;
	};

	//!
	//! BIND
	//!

	void bind_for_draw(base_render_buffers const *) noexcept;
	void bind_for_read(base_render_buffers const *) noexcept;

	//!
	//!

	class cBaseRenderBuffers
	{
	public:
		inline cBaseRenderBuffers() : m_object{ std::make_unique<base_render_buffers>() }
		{
			m_object->handle = {};
			m_object->albedo = {};
			m_object->normal = {};
			m_object->params = {};
			m_object->fdepth = {};
			m_object->tdepth = {};
		}

		//! -----------------------------------------------------------------------------------------------------------------------

		inline bool init(GLsizei w, GLsizei h, GLsizei n = 1) noexcept { return base_render_buffers::init(m_object.get(), w, h, n); }

		//! -----------------------------------------------------------------------------------------------------------------------

		inline void clear_albedo(float r, float g, float b, float a) noexcept { base_render_buffers::clear_albedo(m_object.get(), r, g, b, a); }
		inline void clear_normal(float r, float g, float b, float a) noexcept { base_render_buffers::clear_normal(m_object.get(), r, g, b, a); }
		inline void clear_params(float r, float g, float b, float a) noexcept { base_render_buffers::clear_params(m_object.get(), r, g, b, a); }		
		inline void clear_tdepth(float d) noexcept { base_render_buffers::clear_tdepth(m_object.get(), d); }
		inline void clear_fdepth(float d) noexcept { base_render_buffers::clear_fdepth(m_object.get(), d); }

		//! -----------------------------------------------------------------------------------------------------------------------

		inline void discard_albedo() noexcept { base_render_buffers::discard_albedo(m_object.get()); }
		inline void discard_normal() noexcept { base_render_buffers::discard_normal(m_object.get()); }
		inline void discard_params() noexcept { base_render_buffers::discard_params(m_object.get()); }
		inline void discard_fdepth() noexcept { base_render_buffers::discard_fdepth(m_object.get()); }
		inline void discard_tdepth() noexcept { base_render_buffers::discard_tdepth(m_object.get()); }

		//! -----------------------------------------------------------------------------------------------------------------------

		inline void free() noexcept { base_render_buffers::free(m_object.get()); }

		//! -----------------------------------------------------------------------------------------------------------------------

		inline void bind_for_draw() const noexcept { video::bind_for_draw(m_object.get()); }
		inline void bind_for_read() const noexcept { video::bind_for_read(m_object.get()); }

		//! -----------------------------------------------------------------------------------------------------------------------

		inline operator const base_render_buffers*() const noexcept { return m_object.get(); }

		//! -----------------------------------------------------------------------------------------------------------------------

		inline ~cBaseRenderBuffers() noexcept
		{
			cBaseRenderBuffers::free();
		}

	private:
		std::unique_ptr<base_render_buffers> m_object;
	};

} //! shape::video
} //! shape

#endif