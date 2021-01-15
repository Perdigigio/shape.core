#include "vertex.hh"

//!
//!

namespace shape {
namespace video {

	template<class T, GLuint s> static void buffer_bind(GLuint, GLuint, GLuint);

	//!
	//!

	bool base_vertex::init(base_vertex *p_vertex) noexcept
	{
#		ifndef DEBUG
		if (!p_vertex || glIsVertexArray(p_vertex->layout))
		{
			//!
			//!

			return false;
		}
#		endif

		glCreateVertexArrays(1, &p_vertex->layout);

		//!
		//!

		if (p_vertex->layout)
		{
			glEnableVertexArrayAttrib(p_vertex->layout, 0);

			//!

			glVertexArrayAttribFormat(p_vertex->layout, 0, 3, GL_FLOAT,         GL_FALSE, 0); //! pos
			glVertexArrayAttribFormat(p_vertex->layout, 1, 4, GL_SHORT,         GL_TRUE,  0); //! nor
			glVertexArrayAttribFormat(p_vertex->layout, 2, 4, GL_SHORT,         GL_TRUE,  4); //! nor
			glVertexArrayAttribFormat(p_vertex->layout, 3, 2, GL_HALF_FLOAT,    GL_FALSE, 0); //! tex
			glVertexArrayAttribFormat(p_vertex->layout, 4, 2, GL_HALF_FLOAT,    GL_FALSE, 4); //! tex
			glVertexArrayAttribFormat(p_vertex->layout, 5, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0); //! skn
			glVertexArrayAttribFormat(p_vertex->layout, 6, 4, GL_UNSIGNED_BYTE, GL_TRUE,  4); //! skn

			//!

			glVertexArrayAttribBinding(p_vertex->layout, 0, 0);
			glVertexArrayAttribBinding(p_vertex->layout, 1, 1);
			glVertexArrayAttribBinding(p_vertex->layout, 2, 1);
			glVertexArrayAttribBinding(p_vertex->layout, 3, 2);
			glVertexArrayAttribBinding(p_vertex->layout, 4, 2);
			glVertexArrayAttribBinding(p_vertex->layout, 5, 3);
			glVertexArrayAttribBinding(p_vertex->layout, 6, 3);
		}
		
		//!
		//!

		return glIsVertexArray(p_vertex->layout);
	}
	
	void base_vertex::enable_nor(base_vertex *p_vertex) noexcept
	{
		glEnableVertexArrayAttrib(p_vertex->layout, 1);
		glEnableVertexArrayAttrib(p_vertex->layout, 2);
	}

	void base_vertex::enable_tex(base_vertex *p_vertex) noexcept
	{
		glEnableVertexArrayAttrib(p_vertex->layout, 3);
		glEnableVertexArrayAttrib(p_vertex->layout, 4);
	}

	void base_vertex::enable_skn(base_vertex *p_vertex) noexcept
	{
		glEnableVertexArrayAttrib(p_vertex->layout, 5);
		glEnableVertexArrayAttrib(p_vertex->layout, 6);
	}

	void base_vertex::attach_pos(base_vertex *p_vertex, GLuint p_buffer, GLuint p_offset) noexcept { buffer_bind<base_vtx::pos_t, 0>(p_vertex->layout, p_buffer, p_offset); }
	void base_vertex::attach_nor(base_vertex *p_vertex, GLuint p_buffer, GLuint p_offset) noexcept { buffer_bind<base_vtx::nor_t, 1>(p_vertex->layout, p_buffer, p_offset); }
	void base_vertex::attach_tex(base_vertex *p_vertex, GLuint p_buffer, GLuint p_offset) noexcept { buffer_bind<base_vtx::tex_t, 2>(p_vertex->layout, p_buffer, p_offset); }
	void base_vertex::attach_skn(base_vertex *p_vertex, GLuint p_buffer, GLuint p_offset) noexcept { buffer_bind<base_vtx::skn_t, 3>(p_vertex->layout, p_buffer, p_offset); }

	void base_vertex::detach_pos(base_vertex *p_vertex) noexcept { glVertexArrayVertexBuffer(p_vertex->layout, 0, 0, 0, 0); }
	void base_vertex::detach_nor(base_vertex *p_vertex) noexcept { glVertexArrayVertexBuffer(p_vertex->layout, 1, 0, 0, 0); }
	void base_vertex::detach_tex(base_vertex *p_vertex) noexcept { glVertexArrayVertexBuffer(p_vertex->layout, 2, 0, 0, 0); }
	void base_vertex::detach_skn(base_vertex *p_vertex) noexcept { glVertexArrayVertexBuffer(p_vertex->layout, 3, 0, 0, 0); }

	void base_vertex::bind(base_vertex const *p_vertex) noexcept
	{
		glBindVertexArray(p_vertex->layout);
	}

	void base_vertex::free(base_vertex *p_vertex) noexcept
	{
		if (p_vertex)
			glDeleteVertexArrays(1, &p_vertex->layout);
	}

	//!
	//!

	template<class T, GLuint s> void buffer_bind(GLuint p_handle, GLuint p_buffer, GLuint p_offset)
	{
		//!
		//!

		glVertexArrayVertexBuffer(p_handle, s, p_buffer, p_offset * sizeof(T), sizeof(T));
	}


} //! shape::video
} //! shape