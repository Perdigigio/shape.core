#ifndef SHAPE_VIDEO_BASE_SHADER_BUFFERS_HH__GUARD
#define SHAPE_VIDEO_BASE_SHADER_BUFFERS_HH__GUARD

#include "video_gl_base.hh"

namespace shape {
namespace video {

	struct base_shader_buffers
	{
		GLuint model, model_stride;
		GLuint frame, frame_stride;
		GLuint blend, blend_stride;
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

		static GLsizeiptr offset_model(base_shader_buffers const *, GLuint) noexcept;
		static GLsizeiptr offset_frame(base_shader_buffers const *, GLuint) noexcept;
		static GLsizeiptr offset_blend(base_shader_buffers const *, GLuint) noexcept;

		//! --------------------------------------------------------------------------

		static void free(base_shader_buffers *) noexcept;
		static void grab(base_shader_buffers *) noexcept;
	};

	//!
	//! BIND
	//!

	void bind_model_ubuffer(base_shader_buffers const *, GLuint) noexcept;
	void bind_frame_ubuffer(base_shader_buffers const *, GLuint) noexcept;
	void bind_blend_ubuffer(base_shader_buffers const *, GLuint) noexcept;

	//!
	//!

	class cBaseShaderBuffers
	{
	public:
		inline cBaseShaderBuffers() : m_object{ std::make_unique<base_shader_buffers>() }
		{
			m_object->model = {};
			m_object->frame = {};
			m_object->blend = {};
			m_object->model_stride = {};
			m_object->frame_stride = {};
			m_object->blend_stride = {};
			m_object->count = {};
			m_object->align = {};
		}

		//! -------------------------------------------------------------------------------------------------------------------

		inline bool init(GLuint p_count) noexcept { return base_shader_buffers::init(m_object.get(), p_count); }

		//! -------------------------------------------------------------------------------------------------------------------

		inline void discard_model() noexcept { base_shader_buffers::discard_model(m_object.get()); }
		inline void discard_frame() noexcept { base_shader_buffers::discard_frame(m_object.get()); }
		inline void discard_blend() noexcept { base_shader_buffers::discard_blend(m_object.get()); }

		//! -------------------------------------------------------------------------------------------------------------------

		inline GLsizeiptr offset_model(GLuint p_which) const noexcept { return base_shader_buffers::offset_model(m_object.get(), p_which); }
		inline GLsizeiptr offset_frame(GLuint p_which) const noexcept { return base_shader_buffers::offset_frame(m_object.get(), p_which); }
		inline GLsizeiptr offset_blend(GLuint p_which) const noexcept { return base_shader_buffers::offset_blend(m_object.get(), p_which); }

		//! -------------------------------------------------------------------------------------------------------------------

		inline void free() noexcept { base_shader_buffers::free(m_object.get()); }
		inline void grab() noexcept { base_shader_buffers::grab(m_object.get()); }

		//!
		//! GETTERS
		//!

		inline GLuint get_model() const noexcept { return m_object->model; }
		inline GLuint get_frame() const noexcept { return m_object->frame; }
		inline GLuint get_blend() const noexcept { return m_object->blend; }
		inline GLuint get_count() const noexcept { return m_object->count; }
		inline GLuint get_align() const noexcept { return m_object->align; }
		inline GLuint get_model_stride() const noexcept { return m_object->model_stride; }
		inline GLuint get_frame_stride() const noexcept { return m_object->frame_stride; }
		inline GLuint get_blend_stride() const noexcept { return m_object->blend_stride; }

		//!
		//!

		inline base_model_buffer * get_lpmodel(GLuint p_which = 0) const noexcept { return cast_offset<base_model_buffer>(m_object->lpmodel, offset_model(p_which)); }
		inline base_frame_buffer * get_lpframe(GLuint p_which = 0) const noexcept { return cast_offset<base_frame_buffer>(m_object->lpframe, offset_frame(p_which)); }
		inline base_blend_buffer * get_lpblend(GLuint p_which = 0) const noexcept { return cast_offset<base_blend_buffer>(m_object->lpblend, offset_blend(p_which)); }

		//! -------------------------------------------------------------------------------------------------------------------

		inline void bind_model(GLuint p_which) noexcept { bind_model_ubuffer(m_object.get(), p_which); }
		inline void bind_frame(GLuint p_which) noexcept { bind_frame_ubuffer(m_object.get(), p_which); }
		inline void bind_blend(GLuint p_which) noexcept { bind_blend_ubuffer(m_object.get(), p_which); }

		//! -------------------------------------------------------------------------------------------------------------------

		inline ~cBaseShaderBuffers() noexcept
		{
			cBaseShaderBuffers::free();
		}
	private:
		std::unique_ptr<base_shader_buffers> m_object;
	};

} //! shape::video
} //! shape

#endif
