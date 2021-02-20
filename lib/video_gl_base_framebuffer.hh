#ifndef SHAPE_VIDEO_BASE_FRAMEBUFFER_HH__GUARD
#define SHAPE_VIDEO_BASE_FRAMEBUFFER_HH__GUARD

#include "video_gl_base.hh"

namespace shape {
namespace video {

	struct base_framebuffer
	{
		GLuint handle;

		GLuint albedo; //! r:10 g:10 b:10 a:2
		GLuint normal; //! x:10 y:10 r:10 s:2
		GLuint params; //! s:10 l:10 m:10 x:2
		GLuint fdepth; //! d:24 s:8
		GLuint tdepth; //! d:24 s:8

		//! ---------------------------------------------------------------------

		static bool init(base_framebuffer *, GLsizei, GLsizei, GLsizei) noexcept;

		//! ---------------------------------------------------------------------

		static void clear_albedo(base_framebuffer *, float, float, float, float) noexcept;
		static void clear_normal(base_framebuffer *, float, float, float, float) noexcept;
		static void clear_params(base_framebuffer *, float, float, float, float) noexcept;
		static void clear_fdepth(base_framebuffer *, float) noexcept;
		static void clear_tdepth(base_framebuffer *, float) noexcept;

		//! ---------------------------------------------------------------------

		static void discard_albedo(base_framebuffer *) noexcept;
		static void discard_normal(base_framebuffer *) noexcept;
		static void discard_params(base_framebuffer *) noexcept;
		static void discard_fdepth(base_framebuffer *) noexcept;
		static void discard_tdepth(base_framebuffer *) noexcept;


		//! ---------------------------------------------------------------------

		static void free(base_framebuffer *) noexcept;

		//! ---------------------------------------------------------------------

		static void bind_for_draw(base_framebuffer const *) noexcept;
		static void bind_for_read(base_framebuffer const *) noexcept;
		static void bind_for_both(base_framebuffer const *) noexcept;
	};

	class cBaseFramebuffer : private base_framebuffer
	{
	public:
		inline cBaseFramebuffer() noexcept
		{
			this->handle = {};
			this->albedo = {};
			this->normal = {};
			this->params = {};
			this->fdepth = {};
			this->tdepth = {};
		}

		//! -----------------------------------------------------------------------------------------------------------------------

		inline bool init(GLsizei w, GLsizei h, GLsizei n = 1) noexcept { return base_framebuffer::init(this, w, h, n); }

		//! -----------------------------------------------------------------------------------------------------------------------

		inline void clear_albedo(float r, float g, float b, float a) noexcept { base_framebuffer::clear_albedo(this, r, g, b, a); }
		inline void clear_normal(float r, float g, float b, float a) noexcept { base_framebuffer::clear_normal(this, r, g, b, a); }
		inline void clear_params(float r, float g, float b, float a) noexcept { base_framebuffer::clear_params(this, r, g, b, a); }		
		inline void clear_tdepth(float d) noexcept { base_framebuffer::clear_tdepth(this, d); }
		inline void clear_fdepth(float d) noexcept { base_framebuffer::clear_fdepth(this, d); }

		//! -----------------------------------------------------------------------------------------------------------------------

		inline void discard_albedo() noexcept { base_framebuffer::discard_albedo(this); }
		inline void discard_normal() noexcept { base_framebuffer::discard_normal(this); }
		inline void discard_params() noexcept { base_framebuffer::discard_params(this); }
		inline void discard_fdepth() noexcept { base_framebuffer::discard_fdepth(this); }
		inline void discard_tdepth() noexcept { base_framebuffer::discard_tdepth(this); }

		//! -----------------------------------------------------------------------------------------------------------------------

		inline void free() noexcept { base_framebuffer::free(this); }

		//! -----------------------------------------------------------------------------------------------------------------------

		inline void bind_for_draw() const noexcept { base_framebuffer::bind_for_draw(this); }
		inline void bind_for_read() const noexcept { base_framebuffer::bind_for_read(this); }
		inline void bind_for_both() const noexcept { base_framebuffer::bind_for_both(this); }
	};

} //! shape::video
} //! shape

#endif