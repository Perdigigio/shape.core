#include "model.hh"

//!
//!

namespace shape
{
	static const auto g_flags = std::ios_base::xalloc();

	namespace details
	{
		static constexpr auto MAGIC = fourcc('M', 'O', 'D', ' ');

		static constexpr auto MAJOR = uint16_t(1);
		static constexpr auto MINOR = uint16_t(0);

		struct head
		{
			uint32_t magic;
			uint16_t major;
			uint16_t minor;

			uint32_t vtx_count;
			uint32_t idx_count;
		};

		struct body_buffer
		{
			uint32_t fmt;
			uint32_t pad;
			uint64_t off;
		};

		struct body
		{
			body_buffer pos;
			body_buffer nor;
			body_buffer tex;
			body_buffer skn;
			body_buffer idx;
		};
	};


	//! HEAD
	//!
	//! 00 uint32_t magic
	//! 04 uint16_t major
	//! 06 uint16_t minor
	//!
	//! BODY
	//!
	//! 10 * n + 10 uint32_t model_buffer::fmt POS NOR TEX SKN IDX
	//! 10 * n + 14 uint32_t model_buffer::num
	//! 10 * n + 18 uint64_t offset
	//!
	//! DATA

	static void write_head(std::ostream &, const cModel &) noexcept;
	static void write_body(std::ostream &, const cModel &) noexcept;

	//!
	//!

	template<> bool write<cModel>(std::ostream &p_stream, const cModel &p_model)
	{
		write_head(p_stream, p_model);
		write_body(p_stream, p_model);

		//!
		//! WRITE DATA
		//!

		if (p_stream)
		{
			p_stream.write((const char *)p_model.get_pos_data(), p_model.get_pos().get_length());
			p_stream.write((const char *)p_model.get_nor_data(), p_model.get_nor().get_length());
			p_stream.write((const char *)p_model.get_tex_data(), p_model.get_tex().get_length());
			p_stream.write((const char *)p_model.get_skn_data(), p_model.get_skn().get_length());
			p_stream.write((const char *)p_model.get_idx_data(), p_model.get_idx().get_length());
		}

		//!
		//!

		return p_stream.good();
	}

	void write_head(std::ostream &p_stream, const cModel &p_model) noexcept
	{
		write(p_stream, details::MAGIC);
		write(p_stream, details::MAJOR);
		write(p_stream, details::MINOR);

		write(p_stream, p_model.get_pos().get_num());
		write(p_stream, p_model.get_idx().get_num());
	}

	void write_body(std::ostream &p_stream, const cModel &p_model) noexcept
	{
		uint64_t l_offset = sizeof(details::head) + sizeof(details::body);

		//!
		//! WRITE OFFSETS
		//!

		auto l_pos = model_buffer_name::pos;
		auto l_idx = model_buffer_name::idx;
		auto l_nor = p_model.get_nor().get_num() ? model_buffer_name::nor : 0;
		auto l_tex = p_model.get_tex().get_num() ? model_buffer_name::tex : 0;
		auto l_skn = p_model.get_skn().get_num() ? model_buffer_name::skn : 0;

		//!
		//!

		if (p_stream)
		{
			write(p_stream, l_pos) && write<uint32_t>(p_stream, 0) && write(p_stream, l_offset);
			write(p_stream, l_nor) && write<uint32_t>(p_stream, 0) && write(p_stream, l_offset += p_model.get_pos().get_length());
			write(p_stream, l_tex) && write<uint32_t>(p_stream, 0) && write(p_stream, l_offset += p_model.get_nor().get_length());
			write(p_stream, l_skn) && write<uint32_t>(p_stream, 0) && write(p_stream, l_offset += p_model.get_tex().get_length());
			write(p_stream, l_idx) && write<uint32_t>(p_stream, 0) && write(p_stream, l_offset += p_model.get_skn().get_length());
		}
	}


} //! shape