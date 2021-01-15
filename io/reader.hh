#ifndef SHAPE_CORE_STREAM_READER_HH__GUARD
#define SHAPE_CORE_STREAM_READER_HH__GUARD

#include "../type.hh"
#include "../base.hh"

//!
//! TODO MAYBE RETURN std::optional
//!

namespace shape
{
	template<class T> T read(std::istream&) = delete;

	//! ----------------- INTEGER TYPES -----------------------

	template<> uint16_t read<uint16_t>(std::istream&);
	template<> uint32_t read<uint32_t>(std::istream&);
	template<> uint64_t read<uint64_t>(std::istream&);
	template<> sint16_t read<sint16_t>(std::istream&);
	template<> sint32_t read<sint32_t>(std::istream&);
	template<> sint64_t read<sint64_t>(std::istream&);

}

#endif