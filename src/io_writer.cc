#include "io_writer.hh"

//!
//!

namespace shape
{

	template<> std::ostream & writer::write(std::ostream &p_stream, const uint16_t &p_data)
	{
		return  p_stream.put(char((p_data >> 010) & 0xFF))
				.put(char((p_data >> 000) & 0xFF));
	}

	template<> std::ostream & writer::write(std::ostream &p_stream, const uint32_t &p_data)
	{
		return  p_stream.put(char((p_data >> 030) & 0xFF))
				.put(char((p_data >> 020) & 0xFF))
				.put(char((p_data >> 010) & 0xFF))
				.put(char((p_data >> 000) & 0xFF));
	}

	template<> std::ostream & writer::write(std::ostream &p_stream, const uint64_t &p_data)
	{
		return  p_stream.put(char((p_data >> 070) & 0xFF))
				.put(char((p_data >> 060) & 0xFF))
				.put(char((p_data >> 050) & 0xFF))
				.put(char((p_data >> 040) & 0xFF))
				.put(char((p_data >> 030) & 0xFF))
				.put(char((p_data >> 020) & 0xFF))
				.put(char((p_data >> 010) & 0xFF))
				.put(char((p_data >> 000) & 0xFF));
	}

	template<> std::ostream & writer::write(std::ostream &p_stream, const sint16_t &p_data) { return write(p_stream, reinterpret_cast<const uint16_t &>(p_data)); }
	template<> std::ostream & writer::write(std::ostream &p_stream, const sint32_t &p_data) { return write(p_stream, reinterpret_cast<const uint32_t &>(p_data)); }
	template<> std::ostream & writer::write(std::ostream &p_stream, const sint64_t &p_data) { return write(p_stream, reinterpret_cast<const uint64_t &>(p_data)); }
}