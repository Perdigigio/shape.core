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

	static details::head read_head(std::istream &) noexcept;
	static details::body read_body(std::istream &) noexcept;

	//! ------------------------------------------------------------------

	static details::body_buffer read_body_buffer(std::istream &) noexcept;

	//! ------------------------------------------------------------------

	static inline auto is_pos(const details::body_buffer &p_buf) { return p_buf.fmt == model_buffer_name::pos; }
	static inline auto is_idx(const details::body_buffer &p_buf) { return p_buf.fmt == model_buffer_name::idx; }
	static inline auto is_nor(const details::body_buffer &p_buf) { return p_buf.fmt == model_buffer_name::nor || !p_buf.fmt; }
	static inline auto is_tex(const details::body_buffer &p_buf) { return p_buf.fmt == model_buffer_name::tex || !p_buf.fmt; }
	static inline auto is_skn(const details::body_buffer &p_buf) { return p_buf.fmt == model_buffer_name::skn || !p_buf.fmt; }

	//!
	//!

	template<> cModel read<cModel>(std::istream &p_stream)
	{
		cModel l_model;

		auto l_head = read_head(p_stream);
		auto l_body = read_body(p_stream);

		const auto l_fmt =
			(l_body.nor.fmt != 0) ? cModel::has_nor : 0 |
			(l_body.tex.fmt != 0) ? cModel::has_tex : 0 |
			(l_body.skn.fmt != 0) ? cModel::has_skn : 0;

		if (p_stream)
		{
			bool l_valid = 
				is_pos(l_body.pos) &&
				is_idx(l_body.idx) &&
				is_nor(l_body.nor) &&
				is_tex(l_body.tex) &&
				is_skn(l_body.skn);

			//!
			//!

			if (!l_valid)
				p_stream.setstate(std::ios::failbit);

			//!
			//! INIT
			//!

			l_model = { l_head.vtx_count, l_head.idx_count, l_fmt };
		}

		//!
		//!

		if (p_stream)
		{
			l_model.realloc();

			//!
			//! READ DATA
			//!

			p_stream.seekg(l_body.pos.off).read((char *)l_model.get_pos_data(), l_model.get_pos().get_length());
			p_stream.seekg(l_body.nor.off).read((char *)l_model.get_nor_data(), l_model.get_nor().get_length());
			p_stream.seekg(l_body.tex.off).read((char *)l_model.get_tex_data(), l_model.get_tex().get_length());
			p_stream.seekg(l_body.skn.off).read((char *)l_model.get_skn_data(), l_model.get_skn().get_length());
			p_stream.seekg(l_body.idx.off).read((char *)l_model.get_idx_data(), l_model.get_idx().get_length());
		}

		if (p_stream)
			return l_model;

		//!
		//!

		return {};
	}


	details::head read_head(std::istream &p_stream) noexcept
	{
		details::head l_head;

		if (read<uint32_t>(p_stream) == details::MAGIC)
		{
			l_head.major = read<uint16_t>(p_stream);
			l_head.minor = read<uint16_t>(p_stream);
			l_head.vtx_count = read<uint32_t>(p_stream);
			l_head.idx_count = read<uint32_t>(p_stream);

			//!
			//!

			if (p_stream)
				return l_head;
		}
		else
			p_stream.setstate(std::ios_base::failbit);

		//!
		//!

		return {};
	}

	details::body read_body(std::istream &p_stream) noexcept
	{
		details::body l_body;

		//!
		//!

		l_body.pos = read_body_buffer(p_stream);
		l_body.nor = read_body_buffer(p_stream);
		l_body.tex = read_body_buffer(p_stream);
		l_body.skn = read_body_buffer(p_stream);
		l_body.idx = read_body_buffer(p_stream);

		if (p_stream)
			return l_body;

		//!
		//!

		return {};
	}

	details::body_buffer read_body_buffer(std::istream &p_stream) noexcept
	{
		auto l_fmt = read<uint32_t>(p_stream);
		auto l_pad = read<uint32_t>(p_stream);
		auto l_off = read<uint64_t>(p_stream);

		if (p_stream)
			return { l_fmt, 0, l_off };

		//!
		//!

		return {};
	};

} //! shape