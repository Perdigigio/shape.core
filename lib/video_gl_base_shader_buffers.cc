#include "video_gl_base_shader_buffers.hh"

//!
//!
//!

#define SHADER_BUFFER_FLAGS GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT

//!
//!

namespace shape {
namespace video {

	static bool buffer_create(GLuint &, GLuint &, GLuint &, GLuint, GLuint);

		//!
		//!

	bool base_shader_buffers::init(base_shader_buffers *p_buffers, GLuint p_count) noexcept
	{
		const GLuint l_align = (GLuint) gl_getter<GLsizei, GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT>{}.value; //! must be > 0

		#ifdef _DEBUG
		if (!p_buffers || glIsBuffer(p_buffers->model) ||
				  glIsBuffer(p_buffers->frame) ||
				  glIsBuffer(p_buffers->blend)) return false;

		//!
		//!

		if (!p_count) return false;
		#endif

		GLuint l_model = sizeof(base_model_buffer);
		GLuint l_frame = sizeof(base_frame_buffer);
		GLuint l_blend = sizeof(base_blend_buffer);

		bool l_result =
			buffer_create(p_buffers->model, p_buffers->model_stride, l_model, p_count, l_align) &&
			buffer_create(p_buffers->frame, p_buffers->frame_stride, l_frame, p_count, l_align) &&
			buffer_create(p_buffers->blend, p_buffers->blend_stride, l_blend, p_count, l_align);

		//!
		//!

		if (l_result)
		{
			p_buffers->lpmodel = glMapNamedBufferRange(p_buffers->model, 0, l_model, SHADER_BUFFER_FLAGS);
			p_buffers->lpframe = glMapNamedBufferRange(p_buffers->frame, 0, l_frame, SHADER_BUFFER_FLAGS);
			p_buffers->lpblend = glMapNamedBufferRange(p_buffers->blend, 0, l_blend, SHADER_BUFFER_FLAGS);
		}

		p_buffers->count = p_count;
		p_buffers->align = l_align;

		//!
		//!

		return l_result;
	}

	//! ---------------------------------------------------------------------------

	void base_shader_buffers::discard_model(base_shader_buffers *p_buffer) noexcept { glInvalidateBufferData(p_buffer->model); }
	void base_shader_buffers::discard_frame(base_shader_buffers *p_buffer) noexcept { glInvalidateBufferData(p_buffer->frame); }
	void base_shader_buffers::discard_blend(base_shader_buffers *p_buffer) noexcept { glInvalidateBufferData(p_buffer->blend); }

	//! ---------------------------------------------------------------------------

	GLsizeiptr base_shader_buffers::offset_model(base_shader_buffers const *p_buffer, GLuint p_which) noexcept { return (p_which % p_buffer->count) * p_buffer->model_stride; }
	GLsizeiptr base_shader_buffers::offset_frame(base_shader_buffers const *p_buffer, GLuint p_which) noexcept { return (p_which % p_buffer->count) * p_buffer->frame_stride; }
	GLsizeiptr base_shader_buffers::offset_blend(base_shader_buffers const *p_buffer, GLuint p_which) noexcept { return (p_which % p_buffer->count) * p_buffer->blend_stride; }

	//! ---------------------------------------------------------------------------

	void base_shader_buffers::free(base_shader_buffers *p_buffer) noexcept
	{
		GLuint l_model = GL_NONE;
		GLuint l_frame = GL_NONE;
		GLuint l_blend = GL_NONE;

		//!
		//!

		if (p_buffer)
		{
			std::swap(p_buffer->model, l_model);
			std::swap(p_buffer->frame, l_frame);
			std::swap(p_buffer->blend, l_blend);

			//!
			//!

			glDeleteBuffers(1, &l_blend);
			glDeleteBuffers(1, &l_frame);
			glDeleteBuffers(1, &l_model);
		}
	}

	void base_shader_buffers::grab(base_shader_buffers *p_buffer) noexcept
	{
		
	}


	//!
	//!

	bool buffer_create(GLuint &p_handle, GLuint &p_stride, GLuint &p_length, GLuint p_count, GLuint p_align)
	{
		glCreateBuffers(1, &p_handle);

		//!
		//!

		p_stride = align(p_length, p_align);
		p_length = align(p_length, p_align) * p_count;

		if (p_handle)
		{
			//!
			//!

			glNamedBufferStorage(p_handle, p_length, NULL, SHADER_BUFFER_FLAGS);
		}

		//!
		//!

		return glIsBuffer(p_handle);
	}

	//!
	//! BIND
	//!

	void bind_model_ubuffer(base_shader_buffers const *p_buffer, GLuint p_which) noexcept { glBindBufferRange(GL_UNIFORM_BUFFER, 0, p_buffer->model, base_shader_buffers::offset_model(p_buffer, p_which), p_buffer->model_stride); }
	void bind_frame_ubuffer(base_shader_buffers const *p_buffer, GLuint p_which) noexcept { glBindBufferRange(GL_UNIFORM_BUFFER, 1, p_buffer->frame, base_shader_buffers::offset_frame(p_buffer, p_which), p_buffer->frame_stride); }
	void bind_blend_ubuffer(base_shader_buffers const *p_buffer, GLuint p_which) noexcept { glBindBufferRange(GL_UNIFORM_BUFFER, 2, p_buffer->blend, base_shader_buffers::offset_blend(p_buffer, p_which), p_buffer->blend_stride); }

} //! shape::video
} //! shape