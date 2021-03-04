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
			case base_model_fourcc::pos: return p_obj->vtx * l_stride;
			case base_model_fourcc::nor: return p_obj->vtx * l_stride;
			case base_model_fourcc::tex: return p_obj->vtx * l_stride;
			case base_model_fourcc::skn: return p_obj->vtx * l_stride;
			case base_model_fourcc::idx: return p_obj->idx * l_stride;
			case base_model_fourcc::sub: return p_obj->sub * l_stride;
		}

		//!
		//!

		return 0;
	}

	size_t asset_model::get_stride(asset_model const *p_obj, uint32_t p_buf) noexcept
	{
		switch (p_buf)
		{
			case base_model_fourcc::pos: return sizeof(base_model::pos_t);
			case base_model_fourcc::nor: return sizeof(base_model::nor_t);
			case base_model_fourcc::tex: return sizeof(base_model::tex_t);
			case base_model_fourcc::skn: return sizeof(base_model::skn_t);
			case base_model_fourcc::idx: return sizeof(base_model::idx_t);
			case base_model_fourcc::sub: return sizeof(base_model::sub_t);
		}

		//!
		//!

		return 0;
	}

	cAssetModelData::cAssetModelData() = default;

	cAssetModelData::cAssetModelData(uint32_t p_vtx, uint32_t p_idx, uint32_t p_fmt, uint32_t p_sub) : cAssetModel{ p_vtx, p_idx, p_fmt, p_sub }
	{
		if (has_pos()) m_pos = buffer_alloc<heap_t>(get_length(base_model_fourcc::pos));
		if (has_idx()) m_idx = buffer_alloc<heap_t>(get_length(base_model_fourcc::idx));
		if (has_nor()) m_nor = buffer_alloc<heap_t>(get_length(base_model_fourcc::nor));
		if (has_tex()) m_tex = buffer_alloc<heap_t>(get_length(base_model_fourcc::tex));
		if (has_skn()) m_skn = buffer_alloc<heap_t>(get_length(base_model_fourcc::skn));
		if (has_sub()) m_sub = buffer_alloc<heap_t>(get_length(base_model_fourcc::sub));
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