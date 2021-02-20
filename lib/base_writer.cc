#include "base_writer.hh"

//!
//!

namespace shape
{

	template<> bool writer::write(const file::type &p_stream, const uint16_t &p_data)
	{
		return  std::fputc(int(p_data >> 010) & 0xFF, p_stream.get()) != EOF &&
			std::fputc(int(p_data >> 000) & 0xFF, p_stream.get()) != EOF;
	}

	template<> bool writer::write(const file::type &p_stream, const uint32_t &p_data)
	{
		return  std::fputc(int(p_data >> 030) & 0xFF, p_stream.get()) != EOF &&
			std::fputc(int(p_data >> 020) & 0xFF, p_stream.get()) != EOF &&
			std::fputc(int(p_data >> 010) & 0xFF, p_stream.get()) != EOF &&
			std::fputc(int(p_data >> 000) & 0xFF, p_stream.get()) != EOF;
	}

	template<> bool writer::write(const file::type &p_stream, const uint64_t &p_data)
	{
		return  std::fputc(int(p_data >> 070) & 0xFF, p_stream.get()) != EOF &&
			std::fputc(int(p_data >> 060) & 0xFF, p_stream.get()) != EOF &&
			std::fputc(int(p_data >> 050) & 0xFF, p_stream.get()) != EOF &&
			std::fputc(int(p_data >> 040) & 0xFF, p_stream.get()) != EOF &&
			std::fputc(int(p_data >> 030) & 0xFF, p_stream.get()) != EOF &&
			std::fputc(int(p_data >> 020) & 0xFF, p_stream.get()) != EOF &&
			std::fputc(int(p_data >> 010) & 0xFF, p_stream.get()) != EOF &&
			std::fputc(int(p_data >> 000) & 0xFF, p_stream.get()) != EOF;
	}

	template<> bool writer::write(const file::type &p_stream, const sint16_t &p_data) { return write(p_stream, reinterpret_cast<const uint16_t &>(p_data)); }
	template<> bool writer::write(const file::type &p_stream, const sint32_t &p_data) { return write(p_stream, reinterpret_cast<const uint32_t &>(p_data)); }
	template<> bool writer::write(const file::type &p_stream, const sint64_t &p_data) { return write(p_stream, reinterpret_cast<const uint64_t &>(p_data)); }
}