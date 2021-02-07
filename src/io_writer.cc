#include "io_writer.hh"

//!
//!

namespace shape
{

	template<> bool write(std::ostream& p_stream, uint16_t const &p_data)
	{
		return  p_stream.put(char((p_data >> 010) & 0xFF)) &&
			p_stream.put(char((p_data >> 000) & 0xFF));
	}

	template<> bool write(std::ostream& p_stream, uint32_t const &p_data)
	{
		return  p_stream.put(char((p_data >> 030) & 0xFF)) &&
			p_stream.put(char((p_data >> 020) & 0xFF)) &&
			p_stream.put(char((p_data >> 010) & 0xFF)) &&
			p_stream.put(char((p_data >> 000) & 0xFF));
	}

	template<> bool write(std::ostream& p_stream, uint64_t const &p_data)
	{
		return  p_stream.put(char((p_data >> 070) & 0xFF)) &&
			p_stream.put(char((p_data >> 060) & 0xFF)) &&
			p_stream.put(char((p_data >> 050) & 0xFF)) &&
			p_stream.put(char((p_data >> 040) & 0xFF)) &&
			p_stream.put(char((p_data >> 030) & 0xFF)) &&
			p_stream.put(char((p_data >> 020) & 0xFF)) &&
			p_stream.put(char((p_data >> 010) & 0xFF)) &&
			p_stream.put(char((p_data >> 000) & 0xFF));
	}

	template<> bool write(std::ostream& p_stream, sint16_t const &p_data)
	{
		return  p_stream.put(char((p_data >> 010) & 0xFF)) &&
			p_stream.put(char((p_data >> 000) & 0xFF));
	}

	template<> bool write(std::ostream& p_stream, sint32_t const &p_data)
	{
		return  p_stream.put(char((p_data >> 030) & 0xFF)) &&
			p_stream.put(char((p_data >> 020) & 0xFF)) &&
			p_stream.put(char((p_data >> 010) & 0xFF)) &&
			p_stream.put(char((p_data >> 000) & 0xFF));
	}

	template<> bool write(std::ostream& p_stream, sint64_t const &p_data)
	{
		return  p_stream.put(char((p_data >> 070) & 0xFF)) &&
			p_stream.put(char((p_data >> 060) & 0xFF)) &&
			p_stream.put(char((p_data >> 050) & 0xFF)) &&
			p_stream.put(char((p_data >> 040) & 0xFF)) &&
			p_stream.put(char((p_data >> 030) & 0xFF)) &&
			p_stream.put(char((p_data >> 020) & 0xFF)) &&
			p_stream.put(char((p_data >> 010) & 0xFF)) &&
			p_stream.put(char((p_data >> 000) & 0xFF));
	}

}