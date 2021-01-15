#include "framebuffer.hh"

namespace shape {
namespace video {

	inline constexpr real4 make_color(float r, float g, float b, float a)
	{
		//!
		//!

		return { r, g, b, a };
	}

	static bool create_color(GLuint &, GLenum, GLsizei, GLsizei, GLsizei) noexcept;
	static bool create_depth(GLuint &, GLenum, GLsizei, GLsizei, GLsizei) noexcept;

	static constexpr GLenum s_buffers[] =
	{
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3,
	};

	//!
	//!

	bool base_framebuffer::init(base_framebuffer *p_frame, GLsizei w, GLsizei h, GLsizei n) noexcept
	{
		#ifdef DEBUG
		if (!p_frame || glIsFramebuffer(p_frame->handle) ||
			glIsTexture(p_frame->albedo) ||
			glIsTexture(p_frame->normal) ||
			glIsTexture(p_frame->params) ||
			glIsTexture(p_frame->fdepth) || glIsRenderbuffer(p_frame->tdepth))
		{
			//!
			//!

			return false;
		}
		#endif

		glCreateFramebuffers(1, &p_frame->handle);

		//!
		//!

		if (p_frame->handle)
		{
			bool l_result = 
				create_color(p_frame->albedo, GL_RGB10_A2,         w, h, n) &&
				create_color(p_frame->normal, GL_RGB10_A2,         w, h, n) &&
				create_color(p_frame->params, GL_RGB10_A2,         w, h, n) &&
				create_color(p_frame->fdepth, GL_R32F,             w, h, n) &&
				create_depth(p_frame->tdepth, GL_DEPTH24_STENCIL8, w, h, n);

			if (!l_result)
				return false;

			glNamedFramebufferDrawBuffers(p_frame->handle, 4, s_buffers);

			//!
			//! COLOR
			//!

			glNamedFramebufferTexture(p_frame->handle, GL_COLOR_ATTACHMENT0, p_frame->albedo, 0);
			glNamedFramebufferTexture(p_frame->handle, GL_COLOR_ATTACHMENT1, p_frame->normal, 0);
			glNamedFramebufferTexture(p_frame->handle, GL_COLOR_ATTACHMENT2, p_frame->params, 0);
			glNamedFramebufferTexture(p_frame->handle, GL_COLOR_ATTACHMENT3, p_frame->fdepth, 0);

			//!
			//! DEPTH
			//!

			glNamedFramebufferRenderbuffer(p_frame->handle, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, p_frame->tdepth);			
		}

		//!
		//!

		return glIsFramebuffer(p_frame->handle);
	}

	void base_framebuffer::clear_albedo(base_framebuffer *p_frame, float r, float g, float b, float a) noexcept { glClearTexImage(p_frame->albedo, 0, GL_RGBA, GL_FLOAT, make_color(r, g, b, a).data); }
	void base_framebuffer::clear_normal(base_framebuffer *p_frame, float r, float g, float b, float a) noexcept { glClearTexImage(p_frame->normal, 0, GL_RGBA, GL_FLOAT, make_color(r, g, b, a).data); }
	void base_framebuffer::clear_params(base_framebuffer *p_frame, float r, float g, float b, float a) noexcept { glClearTexImage(p_frame->params, 0, GL_RGBA, GL_FLOAT, make_color(r, g, b, a).data); }
	void base_framebuffer::clear_fdepth(base_framebuffer *p_frame, float d) noexcept { glClearTexImage(p_frame->fdepth, 0, GL_RED, GL_FLOAT, &d); }

	void base_framebuffer::clear_tdepth(base_framebuffer *p_frame, float d) noexcept
	{
		//!
		//! CLEAR DEPTH_STENCIL BUFFER
		//!

		glClearNamedFramebufferfi(p_frame->handle, GL_DEPTH_STENCIL, 0, d, 0);
	}
	
	void base_framebuffer::discard_albedo(base_framebuffer *p_frame) noexcept { glInvalidateTexImage(p_frame->albedo, 0); }
	void base_framebuffer::discard_normal(base_framebuffer *p_frame) noexcept { glInvalidateTexImage(p_frame->normal, 0); }
	void base_framebuffer::discard_params(base_framebuffer *p_frame) noexcept { glInvalidateTexImage(p_frame->params, 0); }
	void base_framebuffer::discard_fdepth(base_framebuffer *p_frame) noexcept { glInvalidateTexImage(p_frame->fdepth, 0); }

	void base_framebuffer::discard_tdepth(base_framebuffer *p_frame) noexcept
	{
		static constexpr GLenum l_attachments[] =
		{
			GL_DEPTH_STENCIL_ATTACHMENT
		};

		//!
		//!

		glInvalidateNamedFramebufferData(p_frame->handle, 1, l_attachments);
	}

	void base_framebuffer::bind_for_draw(base_framebuffer const *p_frame) noexcept { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, p_frame->handle); }
	void base_framebuffer::bind_for_read(base_framebuffer const *p_frame) noexcept { glBindFramebuffer(GL_READ_FRAMEBUFFER, p_frame->handle); }
	void base_framebuffer::bind_for_both(base_framebuffer const *p_frame) noexcept { glBindFramebuffer(GL_FRAMEBUFFER, p_frame->handle); }

	void base_framebuffer::free(base_framebuffer *p_frame) noexcept
	{
		if (p_frame)
		{
			GLuint l_handle = std::exchange(p_frame->handle, {});
			GLuint l_albedo = std::exchange(p_frame->albedo, {});
			GLuint l_normal = std::exchange(p_frame->normal, {});
			GLuint l_params = std::exchange(p_frame->params, {});
			GLuint l_fdepth = std::exchange(p_frame->fdepth, {});
			GLuint l_tdepth = std::exchange(p_frame->tdepth, {});

			glDeleteRenderbuffers(1, &l_tdepth);

			//!
			//!

			glDeleteTextures(1, &l_fdepth);
			glDeleteTextures(1, &l_params);
			glDeleteTextures(1, &l_normal);
			glDeleteTextures(1, &l_albedo);

			//!
			//!

			glDeleteFramebuffers(1, &l_handle);
		}
	}

	//!
	//!

	bool create_color(GLuint &p_color, GLenum p_format, GLsizei p_w, GLsizei p_h, GLsizei p_n) noexcept
	{
		glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &p_color);

		//!
		//!

		if (p_color)
		{
			//!
			//! ALLOCATE STORAGE
			//!

			glTextureStorage2DMultisample(p_color, p_n, p_format, p_w, p_h, GL_TRUE);
		}

		//!
		//!

		return glIsTexture(p_color);
	}


	bool create_depth(GLuint &p_depth, GLenum p_format, GLsizei p_w, GLsizei p_h, GLsizei p_n) noexcept
	{
		glCreateRenderbuffers(1, &p_depth);

		//!
		//!

		if (p_depth)
		{
			//!
			//! ALLOCATE STORAGE
			//!

			glNamedRenderbufferStorageMultisample(p_depth, p_n, p_format, p_w, p_h);
		}

		//!
		//!

		return glIsRenderbuffer(p_depth);
	}

} //! shape::video
} //! shape
