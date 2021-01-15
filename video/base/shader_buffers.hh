#ifndef SHAPE_VIDEO_BASE_SHADER_BUFFERS_HH__GUARD
#define SHAPE_VIDEO_BASE_SHADER_BUFFERS_HH__GUARD

#include "../base.hh"

namespace shape {
namespace video {

	struct base_shader_buffers
	{
		GLuint model[2]; //! [0] handle, [2] stride
		GLuint frame[2]; //! [0] handle, [2] stride
		GLuint blend[2]; //! [0] handle, [2] stride
		GLuint count;
		GLuint align;

		GLvoid *lpmodel;
		GLvoid *lpframe;
		GLvoid *lpblend;

		//! --------------------------------------------------------------------------

		static bool init(base_shader_buffers *, GLuint) noexcept;

		//! --------------------------------------------------------------------------

		static void discard_model(base_shader_buffers *) noexcept;
		static void discard_frame(base_shader_buffers *) noexcept;
		static void discard_blend(base_shader_buffers *) noexcept;

		//! --------------------------------------------------------------------------

		static GLvoid* offset_model(base_shader_buffers const *, GLuint) noexcept;
		static GLvoid* offset_frame(base_shader_buffers const *, GLuint) noexcept;
		static GLvoid* offset_blend(base_shader_buffers const *, GLuint) noexcept;

		//! --------------------------------------------------------------------------

		static void bind_model(base_shader_buffers const *, GLuint) noexcept;
		static void bind_frame(base_shader_buffers const *, GLuint) noexcept;
		static void bind_blend(base_shader_buffers const *, GLuint) noexcept;

		//! --------------------------------------------------------------------------

		static void free(base_shader_buffers *) noexcept;
		static void grab(base_shader_buffers *) noexcept;
	};

	//!
	//!

	class cBaseShaderBuffers : private base_shader_buffers
	{
	public:
		inline cBaseShaderBuffers() noexcept
		{
			this->model[0] = {};
			this->model[1] = {};
			this->frame[0] = {};
                        this->frame[1] = {};
			this->blend[0] = {};
                        this->blend[1] = {};

			this->count = {};
			this->align = {};

			this->lpmodel = nullptr;
			this->lpframe = nullptr;
			this->lpblend = nullptr;
		}

		//! -------------------------------------------------------------------------------------------------------------------

		inline bool init(GLuint p_count) noexcept { return base_shader_buffers::init(this, p_count); }

		//! -------------------------------------------------------------------------------------------------------------------

		inline void discard_model() noexcept { base_shader_buffers::discard_model(this); }
		inline void discard_frame() noexcept { base_shader_buffers::discard_frame(this); }
		inline void discard_blend() noexcept { base_shader_buffers::discard_blend(this); }

		//! -------------------------------------------------------------------------------------------------------------------

		inline GLvoid* offset_model(GLuint p_which) const noexcept { return base_shader_buffers::offset_model(this, p_which); }
		inline GLvoid* offset_frame(GLuint p_which) const noexcept { return base_shader_buffers::offset_frame(this, p_which); }
		inline GLvoid* offset_blend(GLuint p_which) const noexcept { return base_shader_buffers::offset_blend(this, p_which); }

		//! -------------------------------------------------------------------------------------------------------------------

		inline void bind_model(GLuint p_which) noexcept { base_shader_buffers::bind_model(this, p_which); }
		inline void bind_frame(GLuint p_which) noexcept { base_shader_buffers::bind_frame(this, p_which); }
		inline void bind_blend(GLuint p_which) noexcept { base_shader_buffers::bind_blend(this, p_which); }

		//! -------------------------------------------------------------------------------------------------------------------

		inline void free() noexcept { base_shader_buffers::free(this); }
		inline void grab() noexcept { base_shader_buffers::grab(this); }

		//!
		//! GETTERS
		//!

		inline GLuint get_model() const noexcept { return this->model[0]; }
		inline GLuint get_frame() const noexcept { return this->frame[0]; }
		inline GLuint get_blend() const noexcept { return this->blend[0]; }
		inline GLuint get_count() const noexcept { return this->count; }
		inline GLuint get_align() const noexcept { return this->align; }

		inline GLuint get_model_stride() const noexcept { return this->model[1]; }
		inline GLuint get_frame_stride() const noexcept { return this->frame[1]; }
		inline GLuint get_blend_stride() const noexcept { return this->blend[1]; }

		//!
		//!

		inline base_model_buffer * get_lpmodel(GLuint p_which = 0) const noexcept { return static_cast<base_model_buffer*>(offset_model(p_which)); }
		inline base_frame_buffer * get_lpframe(GLuint p_which = 0) const noexcept { return static_cast<base_frame_buffer*>(offset_frame(p_which)); }
		inline base_blend_buffer * get_lpblend(GLuint p_which = 0) const noexcept { return static_cast<base_blend_buffer*>(offset_blend(p_which)); }
	};

} //! shape::video
} //! shape

#endif
