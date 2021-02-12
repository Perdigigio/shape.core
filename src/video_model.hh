#ifndef SHAPE_VIDEO_MODEL_HH__GUARD
#define SHAPE_VIDEO_MODEL_HH__GUARD

#include "video_gl_base_vertex_buffer.hh"

namespace shape {
namespace video {

	class cVideoModel : private cBaseVertexBuffer
	{
	public:
		static constexpr auto has_nor = (1U << 0);
		static constexpr auto has_tex = (1U << 1);
		static constexpr auto has_skn = (1U << 2);

		static constexpr auto has_all = has_nor | has_tex | has_skn;

		//!
		//!

		inline cVideoModel() noexcept
		{
			this->m_vtx = {};
			this->m_idx = {};
			this->m_fmt = {};
		}

		cVideoModel(uint32_t p_vtx, uint32_t p_idx, uint32_t p_fmt = has_all);

		//!
		//!

		using cBaseVertexBuffer::update_pos;
		using cBaseVertexBuffer::update_nor;
		using cBaseVertexBuffer::update_tex;
		using cBaseVertexBuffer::update_skn;
		using cBaseVertexBuffer::update_idx;

		// void update_pos(uint32_t, uint32_t, const base_model::pos_t *) noexcept;
		// void update_nor(uint32_t, uint32_t, const base_model::nor_t *) noexcept;
		// void update_tex(uint32_t, uint32_t, const base_model::tex_t *) noexcept;
		// void update_skn(uint32_t, uint32_t, const base_model::skn_t *) noexcept;
		// void update_idx(uint32_t, uint32_t, const base_model::idx_t *) noexcept;

		void discard() noexcept;
		void dispose() noexcept;

		//!
		//! GETTERS
		//!

		inline uint32_t get_vtx() const noexcept { return m_vtx; }
		inline uint32_t get_idx() const noexcept { return m_idx; }
		inline uint32_t get_fmt() const noexcept { return m_fmt; }

		inline ~cVideoModel() noexcept
		{
			cBaseVertexBuffer::free();
		}

	private:
		uint32_t m_vtx;
		uint32_t m_idx;
		uint32_t m_fmt;
	};

	//!
	//!

	template<class Source> static void upload(cVideoModel &p_model, const Source &p_source) noexcept
	{
		p_model.update_pos(0, p_source.get_vtx(), p_source.get_pos_data());
		p_model.update_nor(0, p_source.get_vtx(), p_source.get_nor_data());
		p_model.update_tex(0, p_source.get_vtx(), p_source.get_tex_data());
		p_model.update_skn(0, p_source.get_vtx(), p_source.get_skn_data());
		p_model.update_idx(0, p_source.get_idx(), p_source.get_idx_data());
	}

} //! shape::video
} //! shape

#endif