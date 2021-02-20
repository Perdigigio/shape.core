#include "base_reader.hh"

//!
//!

namespace shape
{

	template<> bool reader::read(const file::type &p_stream, uint16_t &p_data)
	{
		p_data = uint16_t(std::fgetc(p_stream.get()) & 0xFF) << 010 |
			 uint16_t(std::fgetc(p_stream.get()) & 0xFF) << 000;

		//!
		//!

		return stream::good(p_stream);
	}

	template<> bool reader::read(const file::type &p_stream, uint32_t &p_data)
	{
		p_data = uint32_t(std::fgetc(p_stream.get()) & 0xFF) << 030 |
			 uint32_t(std::fgetc(p_stream.get()) & 0xFF) << 020 |
			 uint32_t(std::fgetc(p_stream.get()) & 0xFF) << 010 |
			 uint32_t(std::fgetc(p_stream.get()) & 0xFF) << 000;

		//!
		//!

		return stream::good(p_stream);
	}

	template<> bool reader::read(const file::type &p_stream, uint64_t &p_data)
	{
		p_data = uint64_t(std::fgetc(p_stream.get()) & 0xFF) << 070 |
			 uint64_t(std::fgetc(p_stream.get()) & 0xFF) << 060 |
			 uint64_t(std::fgetc(p_stream.get()) & 0xFF) << 050 |
			 uint64_t(std::fgetc(p_stream.get()) & 0xFF) << 040 |
			 uint64_t(std::fgetc(p_stream.get()) & 0xFF) << 030 |
			 uint64_t(std::fgetc(p_stream.get()) & 0xFF) << 020 |
			 uint64_t(std::fgetc(p_stream.get()) & 0xFF) << 010 |
			 uint64_t(std::fgetc(p_stream.get()) & 0xFF) << 000;

		//!
		//!

		return stream::good(p_stream);
	}

	template<> bool reader::read(const file::type &p_stream, sint16_t &p_data) { return read(p_stream, reinterpret_cast<uint16_t &>(p_data)); }
	template<> bool reader::read(const file::type &p_stream, sint32_t &p_data) { return read(p_stream, reinterpret_cast<uint32_t &>(p_data)); }
	template<> bool reader::read(const file::type &p_stream, sint64_t &p_data) { return read(p_stream, reinterpret_cast<uint64_t &>(p_data)); }

}