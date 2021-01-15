#ifndef SHAPE_CORE_STREAM_WRITER_HH__GUARD
#define SHAPE_CORE_STREAM_WRITER_HH__GUARD

#include "../type.hh"
#include "../base.hh"

//!
//!

namespace shape
{
	template<class T> bool write(std::ostream&, T);

	//! ----------------- INTEGER TYPES -----------------------

	template<> bool write<uint16_t>(std::ostream&, uint16_t);
	template<> bool write<uint32_t>(std::ostream&, uint32_t);
	template<> bool write<uint64_t>(std::ostream&, uint64_t);
	template<> bool write<sint16_t>(std::ostream&, sint16_t);
	template<> bool write<sint32_t>(std::ostream&, sint32_t);
	template<> bool write<sint64_t>(std::ostream&, sint64_t);

}

#endif