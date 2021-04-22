#include "base_model.hh"

namespace shape
{

	constexpr uint32_t base_model_fourcc::pos;
	constexpr uint32_t base_model_fourcc::nor;
	constexpr uint32_t base_model_fourcc::tex;
	constexpr uint32_t base_model_fourcc::skn;
	constexpr uint32_t base_model_fourcc::idx;

	//!
	//!

	size_t base_model::get_length(base_model const *p_obj, uint32_t p_buf) noexcept
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
		}

		//!
		//!

		return 0;
	}

	size_t base_model::get_stride(base_model const *p_obj, uint32_t p_buf) noexcept
	{
		switch (p_buf)
		{
			case base_model_fourcc::pos: return sizeof(base_model_pos);
			case base_model_fourcc::nor: return sizeof(base_model_nor);
			case base_model_fourcc::tex: return sizeof(base_model_tex);
			case base_model_fourcc::skn: return sizeof(base_model_skn);
			case base_model_fourcc::idx: return sizeof(base_model_idx);
		}

		//!
		//!

		return 0;
	}

} //! shape