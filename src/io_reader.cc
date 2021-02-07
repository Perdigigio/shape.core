#include "io_reader.hh"

//!
//!

namespace shape
{

	template<> uint16_t read<uint16_t>(std::istream& p_stream)
	{
		return  uint16_t(p_stream.get() & 0xFF) << 010 |
			uint16_t(p_stream.get() & 0xFF) << 000;
	}

	template<> uint32_t read<uint32_t>(std::istream& p_stream)
	{
		return  uint32_t(p_stream.get() & 0xFF) << 030 |
			uint32_t(p_stream.get() & 0xFF) << 020 |
			uint32_t(p_stream.get() & 0xFF) << 010 |
			uint32_t(p_stream.get() & 0xFF) << 000;
	}

	template<> uint64_t read<uint64_t>(std::istream& p_stream)
	{
		return  uint64_t(p_stream.get() & 0xFF) << 070 |
			uint64_t(p_stream.get() & 0xFF) << 060 |
			uint64_t(p_stream.get() & 0xFF) << 050 |
			uint64_t(p_stream.get() & 0xFF) << 040 |
			uint64_t(p_stream.get() & 0xFF) << 030 |
			uint64_t(p_stream.get() & 0xFF) << 020 |
			uint64_t(p_stream.get() & 0xFF) << 010 |
			uint64_t(p_stream.get() & 0xFF) << 000;
	}

	template<> sint16_t read<sint16_t>(std::istream& p_stream)
	{
		return  uint16_t(p_stream.get() & 0xFF) << 010 |
			uint16_t(p_stream.get() & 0xFF) << 000;
	}

	template<> sint32_t read<sint32_t>(std::istream& p_stream)
	{
		return  uint32_t(p_stream.get() & 0xFF) << 030 |
			uint32_t(p_stream.get() & 0xFF) << 020 |
			uint32_t(p_stream.get() & 0xFF) << 010 |
			uint32_t(p_stream.get() & 0xFF) << 000;
	}

	template<> sint64_t read<sint64_t>(std::istream& p_stream)
	{
		return  uint64_t(p_stream.get() & 0xFF) << 070 |
			uint64_t(p_stream.get() & 0xFF) << 060 |
			uint64_t(p_stream.get() & 0xFF) << 050 |
			uint64_t(p_stream.get() & 0xFF) << 040 |
			uint64_t(p_stream.get() & 0xFF) << 030 |
			uint64_t(p_stream.get() & 0xFF) << 020 |
			uint64_t(p_stream.get() & 0xFF) << 010 |
			uint64_t(p_stream.get() & 0xFF) << 000;
	}

}