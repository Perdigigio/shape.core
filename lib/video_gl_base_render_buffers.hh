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

	class cBaseRenderBuffers : private base_render_buffers
	{
	public:
		inline cBaseRenderBuffers()
		{
			this->handle = {};
			this->albedo = {};
			this->normal = {};
			this->params = {};
			this->fdepth = {};
			this->tdepth = {};
		}

		inline cBaseRenderBuffers(cBaseRenderBuffers && p_other) noexcept : cBaseRenderBuffers{}
		{
			std::swap(this->handle, p_other.handle);
			std::swap(this->albedo, p_other.albedo);
			std::swap(this->normal, p_other.normal);
			std::swap(this->params, p_other.params);
			std::swap(this->fdepth, p_other.fdepth);
			std::swap(this->tdepth, p_other.tdepth);
		}

		/**
		 * @param wth
		 * @param hth
		 * @param num
		 */
		cBaseRenderBuffers(GLsizei, GLsizei, GLsizei = 1);

		//! -----------------------------------------------------------------------------------------------------------------------

		inline void clear_albedo(float r, float g, float b, float a) noexcept { base_render_buffers::clear_albedo(this, r, g, b, a); }
		inline void clear_normal(float r, float g, float b, float a) noexcept { base_render_buffers::clear_normal(this, r, g, b, a); }
		inline void clear_params(float r, float g, float b, float a) noexcept { base_render_buffers::clear_params(this, r, g, b, a); }		
		inline void clear_tdepth(float d) noexcept { base_render_buffers::clear_tdepth(this, d); }
		inline void clear_fdepth(float d) noexcept { base_render_buffers::clear_fdepth(this, d); }

		//! -----------------------------------------------------------------------------------------------------------------------

		inline void discard_albedo() noexcept { base_render_buffers::discard_albedo(this); }
		inline void discard_normal() noexcept { base_render_buffers::discard_normal(this); }
		inline void discard_params() noexcept { base_render_buffers::discard_params(this); }
		inline void discard_fdepth() noexcept { base_render_buffers::discard_fdepth(this); }
		inline void discard_tdepth() noexcept { base_render_buffers::discard_tdepth(this); }

		//! -----------------------------------------------------------------------------------------------------------------------

		inline void free() noexcept { base_render_buffers::free(this); }

		//! -----------------------------------------------------------------------------------------------------------------------

		inline void bind_for_draw() const noexcept { video::bind_for_draw(this); }
		inline void bind_for_read() const noexcept { video::bind_for_read(this); }

		//! -----------------------------------------------------------------------------------------------------------------------

		inline ~cBaseRenderBuffers() noexcept { base_render_buffers::free(this); }
	};

} //! shape::video
} //! shape

#endif