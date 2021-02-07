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

		template<GLuint slot> static inline void buffer_bind(const GLuint p_buffer[2], GLuint p_which)
		{
			//!
			//!

			glBindBufferRange(GL_UNIFORM_BUFFER, slot, p_buffer[0], p_which * p_buffer[1], p_buffer[1]);
		}

		//!
		//!

		bool base_shader_buffers::init(base_shader_buffers *p_buffers, GLuint p_count) noexcept
		{
			const GLuint l_align = (GLuint) gl_getter<GLsizei, GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT>{}.value; //! must be > 0

			#ifdef DEBUG
			if (!p_buffers || glIsBuffer(p_buffers->model[0]) ||
					  glIsBuffer(p_buffers->frame[0]) ||
					  glIsBuffer(p_buffers->blend[0])) return false;

			//!
			//!

			if (!p_count) return false;
			#endif

			GLuint l_model = sizeof(base_model_buffer);
			GLuint l_frame = sizeof(base_frame_buffer);
			GLuint l_blend = sizeof(base_blend_buffer);

			bool l_result =
				buffer_create(p_buffers->model[0], p_buffers->model[1], l_model, p_count, l_align) &&
				buffer_create(p_buffers->frame[0], p_buffers->frame[1], l_frame, p_count, l_align) &&
				buffer_create(p_buffers->blend[0], p_buffers->blend[1], l_blend, p_count, l_align);

			//!
			//!

			if (l_result)
			{
				p_buffers->lpmodel = glMapNamedBufferRange(p_buffers->model[0], 0, l_model, SHADER_BUFFER_FLAGS);
				p_buffers->lpframe = glMapNamedBufferRange(p_buffers->frame[0], 0, l_frame, SHADER_BUFFER_FLAGS);
				p_buffers->lpblend = glMapNamedBufferRange(p_buffers->blend[0], 0, l_blend, SHADER_BUFFER_FLAGS);
			}

			p_buffers->count = p_count;
			p_buffers->align = l_align;

			//!
			//!

			return l_result;
		}

		//! ---------------------------------------------------------------------------

		void base_shader_buffers::discard_model(base_shader_buffers *p_buffer) noexcept { glInvalidateBufferData(p_buffer->model[0]); }
		void base_shader_buffers::discard_frame(base_shader_buffers *p_buffer) noexcept { glInvalidateBufferData(p_buffer->frame[0]); }
		void base_shader_buffers::discard_blend(base_shader_buffers *p_buffer) noexcept { glInvalidateBufferData(p_buffer->blend[0]); }

		//! ---------------------------------------------------------------------------

		GLvoid* base_shader_buffers::offset_model(base_shader_buffers const *p_buffer, GLuint p_which) noexcept { return offset(p_buffer->lpmodel, (p_which % p_buffer->count) * p_buffer->model[1]); }
		GLvoid* base_shader_buffers::offset_frame(base_shader_buffers const *p_buffer, GLuint p_which) noexcept { return offset(p_buffer->lpframe, (p_which % p_buffer->count) * p_buffer->frame[1]); }
		GLvoid* base_shader_buffers::offset_blend(base_shader_buffers const *p_buffer, GLuint p_which) noexcept { return offset(p_buffer->lpblend, (p_which % p_buffer->count) * p_buffer->blend[1]); }

		//! ---------------------------------------------------------------------------

		void base_shader_buffers::bind_model(base_shader_buffers const *p_buffer, GLuint p_which) noexcept { buffer_bind<0>(p_buffer->model, p_which % p_buffer->count); }
		void base_shader_buffers::bind_frame(base_shader_buffers const *p_buffer, GLuint p_which) noexcept { buffer_bind<1>(p_buffer->model, p_which % p_buffer->count); }
		void base_shader_buffers::bind_blend(base_shader_buffers const *p_buffer, GLuint p_which) noexcept { buffer_bind<2>(p_buffer->model, p_which % p_buffer->count); }

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
				std::swap(p_buffer->model[0], l_model);
				std::swap(p_buffer->frame[0], l_frame);
				std::swap(p_buffer->blend[0], l_blend);

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



} //! shape::video
} //! shape