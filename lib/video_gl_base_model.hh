#ifndef SHAPE_VIDEO_BASE_VERTEX_BUFFERS_HH__GUARD
#define SHAPE_VIDEO_BASE_VERTEX_BUFFERS_HH__GUARD

#include "video_gl_base.hh"

namespace shape {
namespace video {

	struct base_model_pos { uint32_t dummy[3]; }; //! 3x REAL
	struct base_model_nor { uint16_t dummy[8]; }; //! 4x WORD NORM, 4x WORD NORM
	struct base_model_tex { uint16_t dummy[4]; }; //! 2x HALF, 2x HALF
	struct base_model_skn { uint32_t dummy[2]; }; //! 4x BYTE, 4x BYTE NORM
	struct base_model_idx { uint32_t dummy[1]; }; //! 1x UINT

	//!
	//!

	struct base_model_flag
	{
		static constexpr uint32_t has_nor = (1 << 0);
		static constexpr uint32_t has_tex = (1 << 1);
		static constexpr uint32_t has_skn = (1 << 2);
	};

	//!
	//!

	struct base_model
	{
		GLuint vtx;
		GLuint idx;
		GLuint fmt;
		GLuint pos_buffer;
		GLuint nor_buffer;
		GLuint tex_buffer;
		GLuint skn_buffer;
		GLuint idx_buffer;

		//! --------------------------------------------------------------------------------

		static bool init(base_model *, GLuint, GLuint, GLuint) noexcept;

		//! --------------------------------------------------------------------------------

		static void discard_pos(base_model const *) noexcept;
		static void discard_nor(base_model const *) noexcept;
		static void discard_tex(base_model const *) noexcept;
		static void discard_skn(base_model const *) noexcept;
		static void discard_idx(base_model const *) noexcept;

		//! --------------------------------------------------------------------------------

		static void update_pos(base_model const *, GLuint, GLuint, const void *) noexcept;
		static void update_nor(base_model const *, GLuint, GLuint, const void *) noexcept;
		static void update_tex(base_model const *, GLuint, GLuint, const void *) noexcept;
		static void update_skn(base_model const *, GLuint, GLuint, const void *) noexcept;
		static void update_idx(base_model const *, GLuint, GLuint, const void *) noexcept;

		static void copy_pos(base_model const *, GLuint, base_model const *, GLuint, GLuint) noexcept;
		static void copy_nor(base_model const *, GLuint, base_model const *, GLuint, GLuint) noexcept;
		static void copy_tex(base_model const *, GLuint, base_model const *, GLuint, GLuint) noexcept;
		static void copy_skn(base_model const *, GLuint, base_model const *, GLuint, GLuint) noexcept;
		static void copy_idx(base_model const *, GLuint, base_model const *, GLuint, GLuint) noexcept;

		//! --------------------------------------------------------------------------------

		static void free(base_model *) noexcept;
	};

	class cBaseModel : private base_model
	{
	public:
		static const struct _COPY {} COPY;

		//!
		//!

		inline cBaseModel() noexcept
		{
			this->vtx = {};
			this->idx = {};
			this->fmt = {};
			this->pos_buffer = {};
			this->nor_buffer = {};
			this->tex_buffer = {};
			this->skn_buffer = {};
			this->idx_buffer = {};
		}

		inline cBaseModel(cBaseModel && p_other) noexcept : cBaseModel{}
		{
			std::swap(this->vtx, p_other.vtx);
			std::swap(this->idx, p_other.idx);
			std::swap(this->fmt, p_other.fmt);
			std::swap(this->pos_buffer, p_other.pos_buffer);
			std::swap(this->nor_buffer, p_other.nor_buffer);
			std::swap(this->tex_buffer, p_other.tex_buffer);
			std::swap(this->skn_buffer, p_other.skn_buffer);
			std::swap(this->idx_buffer, p_other.idx_buffer);
		}

		inline cBaseModel(const _COPY&, const cBaseModel &p_other) : cBaseModel{ p_other.get_vtx(), p_other.get_idx(), p_other.get_fmt() }
		{
			if (p_other.has_pos()) this->copy_pos(0, p_other, 0, p_other.get_vtx());
			if (p_other.has_idx()) this->copy_idx(0, p_other, 0, p_other.get_idx());
			if (p_other.has_nor()) this->copy_nor(0, p_other, 0, p_other.get_vtx());
			if (p_other.has_tex()) this->copy_tex(0, p_other, 0, p_other.get_vtx());
			if (p_other.has_skn()) this->copy_skn(0, p_other, 0, p_other.get_vtx());
		}

		/**
		 * @param vtx
		 * @param idx
		 * @param fmt
		 */
		cBaseModel(GLuint, GLuint, GLuint);

		//! ---------------------------------------------------------------------------------------------------

		inline bool has_pos() const noexcept { return this->vtx != 0; }
		inline bool has_idx() const noexcept { return this->idx != 0; }
		inline bool has_nor() const noexcept { return this->vtx != 0 && this->fmt & base_model_flag::has_nor; }
		inline bool has_tex() const noexcept { return this->vtx != 0 && this->fmt & base_model_flag::has_tex; }
		inline bool has_skn() const noexcept { return this->vtx != 0 && this->fmt & base_model_flag::has_skn; }

		//! ---------------------------------------------------------------------------------------------------

		inline void discard_pos() const noexcept { base_model::discard_pos(this); }
		inline void discard_nor() const noexcept { base_model::discard_nor(this); }
		inline void discard_tex() const noexcept { base_model::discard_tex(this); }
		inline void discard_skn() const noexcept { base_model::discard_skn(this); }
		inline void discard_idx() const noexcept { base_model::discard_idx(this); }

		inline void update_pos(GLuint p_off, GLuint p_len, const void *p_buf) const noexcept { base_model::update_pos(this, p_off, p_len, p_buf); }
		inline void update_nor(GLuint p_off, GLuint p_len, const void *p_buf) const noexcept { base_model::update_nor(this, p_off, p_len, p_buf); }
		inline void update_tex(GLuint p_off, GLuint p_len, const void *p_buf) const noexcept { base_model::update_tex(this, p_off, p_len, p_buf); }
		inline void update_skn(GLuint p_off, GLuint p_len, const void *p_buf) const noexcept { base_model::update_skn(this, p_off, p_len, p_buf); }
		inline void update_idx(GLuint p_off, GLuint p_len, const void *p_buf) const noexcept { base_model::update_idx(this, p_off, p_len, p_buf); }

		//! ----------------------------------------------------------------------------------------------------

		inline void copy_pos(GLuint p_doff, base_model const *p_src, GLuint p_soff, GLuint p_len) const noexcept { base_model::copy_pos(this, p_soff, p_src, p_doff, p_len); }
		inline void copy_nor(GLuint p_doff, base_model const *p_src, GLuint p_soff, GLuint p_len) const noexcept { base_model::copy_nor(this, p_soff, p_src, p_doff, p_len); }
		inline void copy_tex(GLuint p_doff, base_model const *p_src, GLuint p_soff, GLuint p_len) const noexcept { base_model::copy_tex(this, p_soff, p_src, p_doff, p_len); }
		inline void copy_skn(GLuint p_doff, base_model const *p_src, GLuint p_soff, GLuint p_len) const noexcept { base_model::copy_skn(this, p_soff, p_src, p_doff, p_len); }
		inline void copy_idx(GLuint p_doff, base_model const *p_src, GLuint p_soff, GLuint p_len) const noexcept { base_model::copy_idx(this, p_soff, p_src, p_doff, p_len); }

		inline void copy_pos(GLuint p_doff, cBaseModel const &p_src, GLuint p_soff, GLuint p_len) const noexcept { base_model::copy_pos(this, p_soff, &p_src, p_doff, p_len); }
		inline void copy_nor(GLuint p_doff, cBaseModel const &p_src, GLuint p_soff, GLuint p_len) const noexcept { base_model::copy_nor(this, p_soff, &p_src, p_doff, p_len); }
		inline void copy_tex(GLuint p_doff, cBaseModel const &p_src, GLuint p_soff, GLuint p_len) const noexcept { base_model::copy_tex(this, p_soff, &p_src, p_doff, p_len); }
		inline void copy_skn(GLuint p_doff, cBaseModel const &p_src, GLuint p_soff, GLuint p_len) const noexcept { base_model::copy_skn(this, p_soff, &p_src, p_doff, p_len); }
		inline void copy_idx(GLuint p_doff, cBaseModel const &p_src, GLuint p_soff, GLuint p_len) const noexcept { base_model::copy_idx(this, p_soff, &p_src, p_doff, p_len); }

		//! ----------------------------------------------------------------------------------------------------

		inline void free() noexcept { base_model::free(this); }

		//!
		//! GETTERS
		//!

		inline GLuint get_vtx() const noexcept { return this->vtx; }
		inline GLuint get_idx() const noexcept { return this->idx; }
		inline GLuint get_fmt() const noexcept { return this->fmt; }

		inline GLuint get_pos_buffer() const noexcept { return this->pos_buffer; }
		inline GLuint get_nor_buffer() const noexcept { return this->nor_buffer; }
		inline GLuint get_tex_buffer() const noexcept { return this->tex_buffer; }
		inline GLuint get_skn_buffer() const noexcept { return this->skn_buffer; }
		inline GLuint get_idx_buffer() const noexcept { return this->idx_buffer; }

		//! ----------------------------------------------------------------------------------------------------

		cBaseModel& operator=(cBaseModel p_other) noexcept
		{
			std::swap(this->vtx, p_other.vtx);
			std::swap(this->idx, p_other.idx);
			std::swap(this->fmt, p_other.fmt);
			std::swap(this->pos_buffer, p_other.pos_buffer);
			std::swap(this->nor_buffer, p_other.nor_buffer);
			std::swap(this->tex_buffer, p_other.tex_buffer);
			std::swap(this->skn_buffer, p_other.skn_buffer);
			std::swap(this->idx_buffer, p_other.idx_buffer); return *this;
		}

		//! ----------------------------------------------------------------------------------------------------

		inline ~cBaseModel() noexcept { base_model::free(this); }
	};

} //! shape::video
} //! shape

#endif