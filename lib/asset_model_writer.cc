#include "asset_model_writer.hh"
#include "asset_model.hh"

//!
//!

namespace shape
{
	namespace details
	{
		static constexpr auto MAGIC = fourcc('M', 'O', 'D', ' ');

		static constexpr auto MAJOR = uint16_t(1);
		static constexpr auto MINOR = uint16_t(0);

		template<class T> static void write(const file::type &p_stream, uint32_t p_len, const T *p_buf) noexcept
		{
			for (uint32_t i = 0; i != p_len; i++)
			{
				if (!writer::write(p_stream, p_buf[i]))
					break;
			}
		}
	}




	//!
	//!

	template<> bool writer::write(const file::type &p_stream, const cAssetModelData &p_model)
	{
		writer::write(p_stream, details::MAGIC);
		writer::write(p_stream, details::MAJOR);
		writer::write(p_stream, details::MINOR);

		//!
		//!

		if (stream::good(p_stream))
		{
			writer::write(p_stream, p_model.get_vtx());
			writer::write(p_stream, p_model.get_idx());
			writer::write(p_stream, p_model.get_fmt());
		}

		//!
		//!

		if (p_model.has_pos()) writer::write(p_stream, base_model_buffer::pos);
		if (p_model.has_idx()) writer::write(p_stream, base_model_buffer::idx);
		if (p_model.has_nor()) writer::write(p_stream, base_model_buffer::nor);
		if (p_model.has_tex()) writer::write(p_stream, base_model_buffer::tex);
		if (p_model.has_skn()) writer::write(p_stream, base_model_buffer::skn);

		if (stream::good(p_stream))
		{
			if (p_model.has_pos()) details::write(p_stream, p_model.get_vtx(), p_model.get_pos_data());
			if (p_model.has_idx()) details::write(p_stream, p_model.get_idx(), p_model.get_idx_data());
			if (p_model.has_nor()) details::write(p_stream, p_model.get_vtx(), p_model.get_nor_data());
			if (p_model.has_tex()) details::write(p_stream, p_model.get_vtx(), p_model.get_tex_data());
			if (p_model.has_skn()) details::write(p_stream, p_model.get_vtx(), p_model.get_skn_data());
		}

		//!
		//!

		return stream::good(p_stream);
	}

	//!
	//!

	template<> bool writer::write(const file::type &p_stream, const base_model::pos_t &p_data) { for(auto d : p_data.dummy) writer::write(p_stream, d); return stream::good(p_stream); }
	template<> bool writer::write(const file::type &p_stream, const base_model::nor_t &p_data) { for(auto d : p_data.dummy) writer::write(p_stream, d); return stream::good(p_stream); }
	template<> bool writer::write(const file::type &p_stream, const base_model::tex_t &p_data) { for(auto d : p_data.dummy) writer::write(p_stream, d); return stream::good(p_stream); }
	template<> bool writer::write(const file::type &p_stream, const base_model::skn_t &p_data) { for(auto d : p_data.dummy) writer::write(p_stream, d); return stream::good(p_stream); }
	template<> bool writer::write(const file::type &p_stream, const base_model::idx_t &p_data) { for(auto d : p_data.dummy) writer::write(p_stream, d); return stream::good(p_stream); }

} //! shape