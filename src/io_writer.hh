#ifndef SHAPE_STREAM_WRITER_HH__GUARD
#define SHAPE_STREAM_WRITER_HH__GUARD

#include "type.hh"
#include "base.hh"

//!
//!

namespace shape
{
	struct writer
	{
		template<class T> static std::ostream & write(std::ostream&, const T &);
	};

	//! ----------------- INTEGER TYPES -----------------------

	template<> std::ostream & writer::write(std::ostream&, const uint16_t &);
	template<> std::ostream & writer::write(std::ostream&, const uint32_t &);
	template<> std::ostream & writer::write(std::ostream&, const uint64_t &);
	template<> std::ostream & writer::write(std::ostream&, const sint16_t &);
	template<> std::ostream & writer::write(std::ostream&, const sint32_t &);
	template<> std::ostream & writer::write(std::ostream&, const sint64_t &);

}

#endif