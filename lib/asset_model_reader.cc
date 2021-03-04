#include "asset_model_reader.hh"
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

		static inline bool check_version(uint16_t maj, uint16_t min) noexcept
		{
			//!
			//!

			return maj > details::MAJOR || (maj == details::MAJOR && min >= details::MINOR);
		}

		template<class T> static void read(const file::type &p_stream, uint32_t p_len, T *p_buf) noexcept
		{
			for (uint32_t i = 0; i != p_len; i++)
			{
				if (!reader::read(p_stream, p_buf[i]))
					break;
			}
		}
	}

	//!
	//!

	template<> bool reader::read(const file::type &p_stream, cAssetModelData &p_model)
	{
		uint32_t l_magic;
		uint16_t l_major;
		uint16_t l_minor;

		uint32_t l_model_vtx = 0;
		uint32_t l_model_idx = 0;
		uint32_t l_model_fmt = 0;
		uint32_t l_model_sub = 0;

		if (stream::good(p_stream))
		{
			reader::read(p_stream, l_magic);
			reader::read(p_stream, l_major);
			reader::read(p_stream, l_minor);
		}

		if (stream::good(p_stream))
		{
			if (l_magic == details::MAGIC && details::check_version(l_major, l_minor))
			{
				reader::read(p_stream, l_model_vtx);
				reader::read(p_stream, l_model_idx);
				reader::read(p_stream, l_model_fmt);
				reader::read(p_stream, l_model_sub);
			}
			else
				return false;
		}

		cAssetModelData l_model = { l_model_vtx, l_model_idx, l_model_fmt, l_model_sub };

		uint32_t l_pos;
		uint32_t l_idx;
		uint32_t l_nor;
		uint32_t l_tex;
		uint32_t l_skn;
		uint32_t l_sub;

		const bool l_valid =
			(!l_model.has_pos() || (reader::read(p_stream, l_pos) && l_pos == base_model_fourcc::pos)) &&
			(!l_model.has_idx() || (reader::read(p_stream, l_idx) && l_idx == base_model_fourcc::idx)) &&
			(!l_model.has_nor() || (reader::read(p_stream, l_nor) && l_nor == base_model_fourcc::nor)) &&
			(!l_model.has_tex() || (reader::read(p_stream, l_tex) && l_tex == base_model_fourcc::tex)) &&
			(!l_model.has_skn() || (reader::read(p_stream, l_skn) && l_skn == base_model_fourcc::skn)) &&
			(!l_model.has_sub() || (reader::read(p_stream, l_sub) && l_sub == base_model_fourcc::sub));

		if (!l_valid)
			return false;

		//!
		//!

		if (stream::good(p_stream))
		{
			if (l_model.has_pos()) details::read(p_stream, l_model.get_vtx(), l_model.get_pos_data());
			if (l_model.has_idx()) details::read(p_stream, l_model.get_idx(), l_model.get_idx_data());
			if (l_model.has_nor()) details::read(p_stream, l_model.get_vtx(), l_model.get_nor_data());
			if (l_model.has_tex()) details::read(p_stream, l_model.get_vtx(), l_model.get_tex_data());
			if (l_model.has_skn()) details::read(p_stream, l_model.get_vtx(), l_model.get_skn_data());
			if (l_model.has_sub()) details::read(p_stream, l_model.get_sub(), l_model.get_sub_data());
		}

		if (stream::good(p_stream))
			std::swap(p_model, l_model);

		//!
		//!

		return stream::good(p_stream);
	}

	template<> bool reader::read(const file::type &p_stream, base_model::pos_t &p_data) { for(auto &d : p_data.dummy) reader::read(p_stream, d); return stream::good(p_stream); }
	template<> bool reader::read(const file::type &p_stream, base_model::nor_t &p_data) { for(auto &d : p_data.dummy) reader::read(p_stream, d); return stream::good(p_stream); }
	template<> bool reader::read(const file::type &p_stream, base_model::tex_t &p_data) { for(auto &d : p_data.dummy) reader::read(p_stream, d); return stream::good(p_stream); }
	template<> bool reader::read(const file::type &p_stream, base_model::skn_t &p_data) { for(auto &d : p_data.dummy) reader::read(p_stream, d); return stream::good(p_stream); }
	template<> bool reader::read(const file::type &p_stream, base_model::idx_t &p_data) { for(auto &d : p_data.dummy) reader::read(p_stream, d); return stream::good(p_stream); }

	template<> bool reader::read(const file::type &p_stream, base_model::sub_t &p_data)
	{
		return  reader::read(p_stream, p_data.first) &&
			reader::read(p_stream, p_data.count);
	}


} //! shape