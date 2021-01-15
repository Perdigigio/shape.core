#ifndef SHAPE_CORE_ASSET_MODEL_HH__GUARD
#define SHAPE_CORE_ASSET_MODEL_HH__GUARD

#include "model_buffer.hh"

namespace shape
{
	struct model
	{
		model_buffer pos;
		model_buffer nor;
		model_buffer tex;
		model_buffer skn;
		model_buffer idx;
	};

	//!
	//!

	class cModel : private model
	{
	public:
		static constexpr auto has_nor = (1U << 0);
		static constexpr auto has_tex = (1U << 1);
		static constexpr auto has_skn = (1U << 2);
		static constexpr auto has_all = has_nor | has_tex | has_skn;

		//!
		//!

		inline cModel() noexcept
		{
			this->pos = {};
			this->nor = {};
			this->tex = {};
			this->skn = {};
			this->idx = {};
		}

		inline cModel(uint32_t p_vtx, uint32_t p_idx, uint32_t p_fmt = has_all) noexcept
		{
			this->pos = { model_buffer_name::pos, p_vtx };
			this->nor = { model_buffer_name::nor, p_fmt & has_nor ? p_vtx : 0 };
			this->tex = { model_buffer_name::tex, p_fmt & has_tex ? p_vtx : 0 };
			this->skn = { model_buffer_name::skn, p_fmt & has_skn ? p_vtx : 0 };
			this->idx = { model_buffer_name::idx, p_idx };
		}

		void realloc();
		void dispose();

		//!
		//! GETTERS
		//!

		inline void * get_pos_data() const noexcept { return m_pos.get(); }
		inline void * get_nor_data() const noexcept { return m_nor.get(); }
		inline void * get_tex_data() const noexcept { return m_tex.get(); }
		inline void * get_skn_data() const noexcept { return m_skn.get(); }
		inline void * get_idx_data() const noexcept { return m_idx.get(); }

		//! ------------------------------------------------------------

		inline cModelBuffer get_pos() const noexcept { return this->pos; }
		inline cModelBuffer get_nor() const noexcept { return this->nor; }
		inline cModelBuffer get_tex() const noexcept { return this->tex; }
		inline cModelBuffer get_skn() const noexcept { return this->skn; }
		inline cModelBuffer get_idx() const noexcept { return this->idx; }

	private:
		buffer<heap_t>::type_t m_idx;
		buffer<heap_t>::type_t m_pos;
		buffer<heap_t>::type_t m_nor;
		buffer<heap_t>::type_t m_tex;
		buffer<heap_t>::type_t m_skn;
	};

} //! shape

#endif
