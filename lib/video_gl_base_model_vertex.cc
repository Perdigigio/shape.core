#include "video_gl_base_model_vertex.hh"

//!
//!

namespace shape {
namespace video {

	bool base_model_vertex::init(base_model_vertex *p_vtx) noexcept
	{
		#ifndef DEBUG
		if (!p_vtx || glIsVertexArray(p_vtx->vao))
		{
			//!
			//!

			return false;
		}
		#endif

		glCreateVertexArrays(1, &p_vtx->vao);

		//!
		//!

		if (p_vtx->vao)
		{
			glEnableVertexArrayAttrib(p_vtx->vao, 0);

			//!

			glVertexArrayAttribFormat(p_vtx->vao, 0, 3, GL_FLOAT,          GL_FALSE, 0); //! pos
			glVertexArrayAttribFormat(p_vtx->vao, 1, 4, GL_UNSIGNED_SHORT, GL_TRUE,  0); //! nor
			glVertexArrayAttribFormat(p_vtx->vao, 2, 4, GL_UNSIGNED_SHORT, GL_TRUE,  8); //! nor
			glVertexArrayAttribFormat(p_vtx->vao, 3, 2, GL_HALF_FLOAT,     GL_FALSE, 0); //! tex
			glVertexArrayAttribFormat(p_vtx->vao, 4, 2, GL_HALF_FLOAT,     GL_FALSE, 4); //! tex
			glVertexArrayAttribFormat(p_vtx->vao, 5, 4, GL_UNSIGNED_BYTE,  GL_FALSE, 0); //! skn
			glVertexArrayAttribFormat(p_vtx->vao, 6, 4, GL_UNSIGNED_BYTE,  GL_TRUE,  4); //! skn

			//!

			glVertexArrayAttribBinding(p_vtx->vao, 0, 0);
			glVertexArrayAttribBinding(p_vtx->vao, 1, 1);
			glVertexArrayAttribBinding(p_vtx->vao, 2, 1);
			glVertexArrayAttribBinding(p_vtx->vao, 3, 2);
			glVertexArrayAttribBinding(p_vtx->vao, 4, 2);
			glVertexArrayAttribBinding(p_vtx->vao, 5, 3);
			glVertexArrayAttribBinding(p_vtx->vao, 6, 3);
		}
		
		//!
		//!

		return glIsVertexArray(p_vtx->vao);
	}
	
	void base_model_vertex::enable_nor(base_model_vertex const *p_vtx) noexcept
	{
		glEnableVertexArrayAttrib(p_vtx->vao, 1);
		glEnableVertexArrayAttrib(p_vtx->vao, 2);
	}

	void base_model_vertex::enable_tex(base_model_vertex const *p_vtx) noexcept
	{
		glEnableVertexArrayAttrib(p_vtx->vao, 3);
		glEnableVertexArrayAttrib(p_vtx->vao, 4);
	}

	void base_model_vertex::enable_skn(base_model_vertex const *p_vtx) noexcept
	{
		glEnableVertexArrayAttrib(p_vtx->vao, 5);
		glEnableVertexArrayAttrib(p_vtx->vao, 6);
	}

	void base_model_vertex::attach_pos(base_model_vertex const *p_vtx, GLuint p_buf, GLuint p_off) noexcept { glVertexArrayVertexBuffer(p_vtx->vao, 0, p_buf, p_off * sizeof(base_model_pos), sizeof(base_model_pos)); }
	void base_model_vertex::attach_nor(base_model_vertex const *p_vtx, GLuint p_buf, GLuint p_off) noexcept { glVertexArrayVertexBuffer(p_vtx->vao, 1, p_buf, p_off * sizeof(base_model_nor), sizeof(base_model_nor)); }
	void base_model_vertex::attach_tex(base_model_vertex const *p_vtx, GLuint p_buf, GLuint p_off) noexcept { glVertexArrayVertexBuffer(p_vtx->vao, 2, p_buf, p_off * sizeof(base_model_tex), sizeof(base_model_tex)); }
	void base_model_vertex::attach_skn(base_model_vertex const *p_vtx, GLuint p_buf, GLuint p_off) noexcept { glVertexArrayVertexBuffer(p_vtx->vao, 3, p_buf, p_off * sizeof(base_model_skn), sizeof(base_model_skn)); }

	void base_model_vertex::attach_idx(base_model_vertex const *p_vtx, GLuint p_buffer) noexcept { glVertexArrayElementBuffer(p_vtx->vao, p_buffer); }

	void base_model_vertex::detach_pos(base_model_vertex const *p_vtx) noexcept { glVertexArrayVertexBuffer(p_vtx->vao, 0, 0, 0, 0); }
	void base_model_vertex::detach_nor(base_model_vertex const *p_vtx) noexcept { glVertexArrayVertexBuffer(p_vtx->vao, 1, 0, 0, 0); }
	void base_model_vertex::detach_tex(base_model_vertex const *p_vtx) noexcept { glVertexArrayVertexBuffer(p_vtx->vao, 2, 0, 0, 0); }
	void base_model_vertex::detach_skn(base_model_vertex const *p_vtx) noexcept { glVertexArrayVertexBuffer(p_vtx->vao, 3, 0, 0, 0); }
	void base_model_vertex::detach_idx(base_model_vertex const *p_vtx) noexcept
	{
		glVertexArrayElementBuffer(p_vtx->vao, 0);
	}

	void base_model_vertex::bind(base_model_vertex const *p_vtx) noexcept { glBindVertexArray(p_vtx->vao); }

	void base_model_vertex::free(base_model_vertex *p_vtx) noexcept
	{
		if (p_vtx)
			glDeleteVertexArrays(1, &p_vtx->vao);
	}

	//!
	//!

	cBaseModelVertex::cBaseModelVertex(uint32_t p_fmt)
	{
		if (base_model_vertex::init(this))
		{
			if (p_fmt & base_model_flag::has_nor) base_model_vertex::enable_nor(this);
			if (p_fmt & base_model_flag::has_tex) base_model_vertex::enable_tex(this);
			if (p_fmt & base_model_flag::has_skn) base_model_vertex::enable_skn(this);
		}
		else
			throw failure{};

		//!
		//!

		this->fmt = p_fmt;
	}

} //! shape::video
} //! shape