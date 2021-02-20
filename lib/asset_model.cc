#include "asset_model.hh"

namespace shape
{

	size_t asset_model::get_length(asset_model const *p_obj, uint32_t p_buf) noexcept
	{
		const size_t l_stride = get_stride(p_obj, p_buf);

		//!
		//! CALCULATE TOTAL BUFFER LENGTH
		//!

		switch (p_buf)
		{
			case base_model_buffer::pos: return p_obj->vtx * l_stride;
			case base_model_buffer::nor: return p_obj->vtx * l_stride;
			case base_model_buffer::tex: return p_obj->vtx * l_stride;
			case base_model_buffer::skn: return p_obj->vtx * l_stride;
			case base_model_buffer::idx: return p_obj->idx * l_stride;
		}

		//!
		//!

		return 0;
	}

	size_t asset_model::get_stride(asset_model const *p_obj, uint32_t p_buf) noexcept
	{
		switch (p_buf)
		{
			case base_model_buffer::pos: return sizeof(base_model::pos_t);
			case base_model_buffer::nor: return sizeof(base_model::nor_t);
			case base_model_buffer::tex: return sizeof(base_model::tex_t);
			case base_model_buffer::skn: return sizeof(base_model::skn_t);
			case base_model_buffer::idx: return sizeof(base_model::idx_t);
		}

		//!
		//!

		return 0;
	}

	void cAssetModelData::realloc()
	{
		if (has_pos() && !m_pos) m_pos = buffer_alloc<heap_t>(get_length(base_model_buffer::pos));
		if (has_idx() && !m_idx) m_idx = buffer_alloc<heap_t>(get_length(base_model_buffer::idx));
		if (has_nor() && !m_nor) m_nor = buffer_alloc<heap_t>(get_length(base_model_buffer::nor));
		if (has_tex() && !m_tex) m_tex = buffer_alloc<heap_t>(get_length(base_model_buffer::tex));
		if (has_skn() && !m_skn) m_skn = buffer_alloc<heap_t>(get_length(base_model_buffer::skn));
	}

	void cAssetModelData::dispose()
	{
		m_idx = {};
		m_skn = {};
		m_tex = {};
		m_nor = {};
		m_pos = {};
	}

} //! shape