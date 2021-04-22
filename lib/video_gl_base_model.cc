#include "video_gl_base_model.hh"

namespace shape {
namespace video {

	static bool buffer_alloc(GLuint &, GLuint, GLuint) noexcept;

	//!
	//!

	bool base_model::init(base_model *p_model, GLuint p_vtx, GLuint p_idx, GLuint p_fmt) noexcept
	{
		GLuint l_pos_buffer = {};
		GLuint l_nor_buffer = {};
		GLuint l_tex_buffer = {};
		GLuint l_skn_buffer = {};
		GLuint l_idx_buffer = {};

		#ifdef DEBUG
		if (!p_model ||  glIsBuffer(p_model->pos_buffer) ||
				 glIsBuffer(p_model->nor_buffer) ||
				 glIsBuffer(p_model->tex_buffer) ||
				 glIsBuffer(p_model->skn_buffer) ||
				 glIsBuffer(p_model->idx_buffer))
		{
			//!
			//!

			return false;
		}
		#endif

		bool l_status =
			buffer_alloc(l_pos_buffer, p_vtx, sizeof(base_model_pos)) &&
			buffer_alloc(l_idx_buffer, p_idx, sizeof(base_model_idx));

		//!
		//! EXTRA BUFFERS
		//!

		if (p_fmt & base_model_flag::has_nor) l_status = l_status && buffer_alloc(l_nor_buffer, p_vtx, sizeof(base_model_nor));
		if (p_fmt & base_model_flag::has_tex) l_status = l_status && buffer_alloc(l_tex_buffer, p_vtx, sizeof(base_model_tex));
		if (p_fmt & base_model_flag::has_skn) l_status = l_status && buffer_alloc(l_skn_buffer, p_vtx, sizeof(base_model_skn));

		if (!l_status)
		{
			glDeleteBuffers(1, &l_pos_buffer);
			glDeleteBuffers(1, &l_nor_buffer);
			glDeleteBuffers(1, &l_tex_buffer);
			glDeleteBuffers(1, &l_skn_buffer);
			glDeleteBuffers(1, &l_idx_buffer);
		}
		else
		{
			p_model->vtx = p_vtx;
			p_model->idx = p_idx;
			p_model->fmt = p_fmt;
			p_model->pos_buffer = l_pos_buffer;
			p_model->nor_buffer = l_nor_buffer;
			p_model->tex_buffer = l_tex_buffer;
			p_model->skn_buffer = l_skn_buffer;
			p_model->idx_buffer = l_idx_buffer;
		}

		//!
		//!

		return l_status;
	}

	//! --------------------------------------------------------------------------------

	void base_model::discard_pos(base_model const *p_model) noexcept { glInvalidateBufferData(p_model->pos_buffer); }
	void base_model::discard_nor(base_model const *p_model) noexcept { glInvalidateBufferData(p_model->nor_buffer); }
	void base_model::discard_tex(base_model const *p_model) noexcept { glInvalidateBufferData(p_model->tex_buffer); }
	void base_model::discard_skn(base_model const *p_model) noexcept { glInvalidateBufferData(p_model->skn_buffer); }
	void base_model::discard_idx(base_model const *p_model) noexcept { glInvalidateBufferData(p_model->idx_buffer); }

	//! --------------------------------------------------------------------------------

	void base_model::update_pos(base_model const *p_model, GLuint p_off, GLuint p_len, const void *p_buf) noexcept { glNamedBufferSubData(p_model->pos_buffer, p_off * sizeof(base_model_pos), p_len * sizeof(base_model_pos), p_buf); }
	void base_model::update_nor(base_model const *p_model, GLuint p_off, GLuint p_len, const void *p_buf) noexcept { glNamedBufferSubData(p_model->nor_buffer, p_off * sizeof(base_model_nor), p_len * sizeof(base_model_nor), p_buf); }
	void base_model::update_tex(base_model const *p_model, GLuint p_off, GLuint p_len, const void *p_buf) noexcept { glNamedBufferSubData(p_model->tex_buffer, p_off * sizeof(base_model_tex), p_len * sizeof(base_model_tex), p_buf); }
	void base_model::update_skn(base_model const *p_model, GLuint p_off, GLuint p_len, const void *p_buf) noexcept { glNamedBufferSubData(p_model->skn_buffer, p_off * sizeof(base_model_skn), p_len * sizeof(base_model_skn), p_buf); }
	void base_model::update_idx(base_model const *p_model, GLuint p_off, GLuint p_len, const void *p_buf) noexcept { glNamedBufferSubData(p_model->idx_buffer, p_off * sizeof(base_model_idx), p_len * sizeof(base_model_idx), p_buf); }

	void base_model::copy_pos(base_model const *p_dst, GLuint p_doff, base_model const *p_src, GLuint p_soff, GLuint p_len) noexcept { glCopyNamedBufferSubData(p_src->pos_buffer, p_dst->pos_buffer, p_soff * sizeof(base_model_pos), p_doff * sizeof(base_model_pos), p_len * sizeof(base_model_pos)); }
	void base_model::copy_nor(base_model const *p_dst, GLuint p_doff, base_model const *p_src, GLuint p_soff, GLuint p_len) noexcept { glCopyNamedBufferSubData(p_src->nor_buffer, p_dst->nor_buffer, p_soff * sizeof(base_model_nor), p_doff * sizeof(base_model_nor), p_len * sizeof(base_model_nor)); }
	void base_model::copy_tex(base_model const *p_dst, GLuint p_doff, base_model const *p_src, GLuint p_soff, GLuint p_len) noexcept { glCopyNamedBufferSubData(p_src->tex_buffer, p_dst->tex_buffer, p_soff * sizeof(base_model_tex), p_doff * sizeof(base_model_tex), p_len * sizeof(base_model_tex)); }
	void base_model::copy_skn(base_model const *p_dst, GLuint p_doff, base_model const *p_src, GLuint p_soff, GLuint p_len) noexcept { glCopyNamedBufferSubData(p_src->skn_buffer, p_dst->skn_buffer, p_soff * sizeof(base_model_skn), p_doff * sizeof(base_model_skn), p_len * sizeof(base_model_skn)); }
	void base_model::copy_idx(base_model const *p_dst, GLuint p_doff, base_model const *p_src, GLuint p_soff, GLuint p_len) noexcept { glCopyNamedBufferSubData(p_src->idx_buffer, p_dst->idx_buffer, p_soff * sizeof(base_model_idx), p_doff * sizeof(base_model_idx), p_len * sizeof(base_model_idx)); }

	//! --------------------------------------------------------------------------------

	void base_model::free(base_model *p_model) noexcept
	{
		GLuint l_skn = GL_NONE;
		GLuint l_tex = GL_NONE;
		GLuint l_nor = GL_NONE;
		GLuint l_pos = GL_NONE;
		GLuint l_idx = GL_NONE;

		//!
		//!

		if (p_model)
		{
			std::swap(p_model->skn_buffer, l_skn);
			std::swap(p_model->tex_buffer, l_tex);
			std::swap(p_model->nor_buffer, l_nor);
			std::swap(p_model->pos_buffer, l_pos);
			std::swap(p_model->idx_buffer, l_idx);


			//!
			//!

			glDeleteBuffers(1, &l_pos);
			glDeleteBuffers(1, &l_nor);
			glDeleteBuffers(1, &l_tex);
			glDeleteBuffers(1, &l_skn);
			glDeleteBuffers(1, &l_idx);
		}
	}

	//!
	//!

	cBaseModel::cBaseModel(GLuint p_vtx, GLuint p_idx, GLuint p_fmt)
	{
		if (!base_model::init(this, p_vtx, p_idx, p_fmt)) throw failure{};
	}

	//!
	//!

	bool buffer_alloc(GLuint & p_handle, GLuint p_length, GLuint p_stride) noexcept
	{
		glCreateBuffers(1, &p_handle);

		if (p_handle)
		{
			//!
			//!

			glNamedBufferStorage(p_handle, GLsizeiptr(p_length) * p_stride, NULL, GL_DYNAMIC_STORAGE_BIT);
		}

		//!
		//!

		return glIsBuffer(p_handle);
	}

} //! shape::video
} //! shape