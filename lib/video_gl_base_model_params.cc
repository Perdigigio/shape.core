#include "video_gl_base_model_params.hh"

//!
//!

namespace shape {
namespace video {

	static const GLbitfield SHADER_BUFFER_FLAGS = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;

	//!
	//!

	inline void * offset(void *p_mem, GLuint p_off) noexcept
	{
		//!
		//!

		return reinterpret_cast<char *>(p_mem) + p_off;
	}

	//!
	//!

	bool base_model_params::init(base_model_params *p_buf, GLuint p_model, GLuint p_frame, GLuint p_blend) noexcept
	{
		const GLuint l_align = (GLuint) gl_getter<GLsizei, GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT>{}.value; //! must be > 0

		#ifdef _DEBUG
		if (!p_buf ||   glIsBuffer(p_buf->model_handle) ||
				glIsBuffer(p_buf->frame_handle) ||
				glIsBuffer(p_buf->blend_handle)) return false;
		#endif

		GLuint l_model_buffer = GL_NONE;
		GLuint l_frame_buffer = GL_NONE;
		GLuint l_blend_buffer = GL_NONE;
		GLuint l_model_stride = ((GLuint)sizeof(base_model_buffer) + l_align - 1UL) & ~(l_align - 1);
		GLuint l_frame_stride = ((GLuint)sizeof(base_frame_buffer) + l_align - 1UL) & ~(l_align - 1);
		GLuint l_blend_stride = ((GLuint)sizeof(base_blend_buffer) + l_align - 1UL) & ~(l_align - 1);
		GLuint l_model_length = l_model_stride * p_model;
		GLuint l_frame_length = l_frame_stride * p_frame;
		GLuint l_blend_length = l_blend_stride * p_blend;

		glCreateBuffers(1, &l_model_buffer);
		glCreateBuffers(1, &l_frame_buffer);
		glCreateBuffers(1, &l_blend_buffer);

		//!
		//!

		if (l_model_buffer && l_frame_buffer && l_blend_buffer)
		{
			if(l_model_length) glNamedBufferStorage(l_model_buffer, l_model_length, NULL, SHADER_BUFFER_FLAGS);
			if(l_frame_length) glNamedBufferStorage(l_frame_buffer, l_frame_length, NULL, SHADER_BUFFER_FLAGS);
			if(l_blend_length) glNamedBufferStorage(l_blend_buffer, l_blend_length, NULL, SHADER_BUFFER_FLAGS);

			p_buf->model_handle = l_model_buffer;
			p_buf->model_stride = l_model_stride;
			p_buf->model_length = l_model_length;
			p_buf->model_offset = 0;
			p_buf->frame_handle = l_frame_buffer;
			p_buf->frame_stride = l_frame_stride;
			p_buf->frame_length = l_frame_length;
			p_buf->frame_offset = 0;
			p_buf->blend_handle = l_blend_buffer;
			p_buf->blend_stride = l_blend_stride;
			p_buf->blend_length = l_blend_length;
			p_buf->blend_offset = 0;

			if(l_model_length) p_buf->model_buffer = glMapNamedBufferRange(l_model_buffer, 0, l_model_length, SHADER_BUFFER_FLAGS);
			if(l_frame_length) p_buf->frame_buffer = glMapNamedBufferRange(l_frame_buffer, 0, l_frame_length, SHADER_BUFFER_FLAGS);
			if(l_blend_length) p_buf->blend_buffer = glMapNamedBufferRange(l_blend_buffer, 0, l_blend_length, SHADER_BUFFER_FLAGS);
		}
		else
		{
			glDeleteBuffers(1, &l_model_buffer);
			glDeleteBuffers(1, &l_frame_buffer);
			glDeleteBuffers(1, &l_blend_buffer);
		}

		//!
		//!

		return glIsBuffer(l_model_buffer) && glIsBuffer(l_frame_buffer) && glIsBuffer(l_blend_buffer);
	}

	//! ---------------------------------------------------------------------------

	void base_model_params::discard_model(base_model_params *p_buf) noexcept { glInvalidateBufferData(p_buf->model_handle); }
	void base_model_params::discard_frame(base_model_params *p_buf) noexcept { glInvalidateBufferData(p_buf->frame_handle); }
	void base_model_params::discard_blend(base_model_params *p_buf) noexcept { glInvalidateBufferData(p_buf->blend_handle); }

	//! ---------------------------------------------------------------------------

	void base_model_params::next_model(base_model_params *p_buf) noexcept { p_buf->model_offset = (p_buf->model_offset + p_buf->model_stride) % p_buf->model_length; }
	void base_model_params::next_frame(base_model_params *p_buf) noexcept { p_buf->frame_offset = (p_buf->frame_offset + p_buf->frame_stride) % p_buf->frame_length; }
	void base_model_params::next_blend(base_model_params *p_buf) noexcept { p_buf->blend_offset = (p_buf->blend_offset + p_buf->blend_stride) % p_buf->blend_length; }

	void base_model_params::copy_model(base_model_params const *p_buf, base_model_buffer const *p_src) noexcept { std::memcpy(offset(p_buf->model_buffer, p_buf->model_offset), p_src, sizeof(base_model_buffer)); }
	void base_model_params::copy_frame(base_model_params const *p_buf, base_frame_buffer const *p_src) noexcept { std::memcpy(offset(p_buf->frame_buffer, p_buf->frame_offset), p_src, sizeof(base_frame_buffer)); }
	void base_model_params::copy_blend(base_model_params const *p_buf, base_blend_buffer const *p_src) noexcept { std::memcpy(offset(p_buf->blend_buffer, p_buf->blend_offset), p_src, sizeof(base_blend_buffer)); }
	void base_model_params::bind_model(base_model_params const *p_buf, GLuint p_slot) noexcept { glBindBufferRange(GL_UNIFORM_BUFFER, p_slot, p_buf->model_handle, p_buf->model_offset, p_buf->model_stride); }
	void base_model_params::bind_frame(base_model_params const *p_buf, GLuint p_slot) noexcept { glBindBufferRange(GL_UNIFORM_BUFFER, p_slot, p_buf->frame_handle, p_buf->frame_offset, p_buf->frame_stride); }
	void base_model_params::bind_blend(base_model_params const *p_buf, GLuint p_slot) noexcept { glBindBufferRange(GL_UNIFORM_BUFFER, p_slot, p_buf->blend_handle, p_buf->blend_offset, p_buf->blend_stride); }

	//! ---------------------------------------------------------------------------

	void base_model_params::free(base_model_params *p_buf) noexcept
	{
		GLuint l_model = GL_NONE;
		GLuint l_frame = GL_NONE;
		GLuint l_blend = GL_NONE;

		//!
		//!

		if (p_buf)
		{
			std::swap(p_buf->model_handle, l_model);
			std::swap(p_buf->frame_handle, l_frame);
			std::swap(p_buf->blend_handle, l_blend);

			//!
			//!

			glDeleteBuffers(1, &l_blend);
			glDeleteBuffers(1, &l_frame);
			glDeleteBuffers(1, &l_model);
		}
	}

	//!
	//!

	cBaseModelParams::cBaseModelParams(GLuint p_model, GLuint p_frame, GLuint p_blend)
	{
		if (!base_model_params::init(this, p_model, p_frame, p_blend)) throw failure{};
	}

} //! shape::video
} //! shape