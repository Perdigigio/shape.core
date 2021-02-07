#include "asset_model_buffer.hh"

//!
//!

namespace shape
{

	size_t cModelBuffer::get_stride() const noexcept
	{
		switch (fmt)
		{
			case model_buffer_name::pos: return sizeof(base_vtx::pos_t);
			case model_buffer_name::nor: return sizeof(base_vtx::nor_t);
			case model_buffer_name::tex: return sizeof(base_vtx::tex_t);
			case model_buffer_name::skn: return sizeof(base_vtx::skn_t);
			case model_buffer_name::idx: return sizeof(uint32_t);
		}

		//!
		//!

		return 0;
	}

	size_t cModelBuffer::get_length() const noexcept
	{
		//!
		//!

		return get_stride() * this->num;
	}
}