#ifndef SHAPE_STREAM_WRITER_HH__GUARD
#define SHAPE_STREAM_WRITER_HH__GUARD

#include "type.hh"
#include "base_stream.hh"

//!
//!

namespace shape
{
	struct writer
	{
		template<class T> static bool write(const file::type &, const T &);
	};

	//! ----------------- INTEGER TYPES -----------------------

	template<> bool writer::write(const file::type &, const uint16_t &);
	template<> bool writer::write(const file::type &, const uint32_t &);
	template<> bool writer::write(const file::type &, const uint64_t &);
	template<> bool writer::write(const file::type &, const sint16_t &);
	template<> bool writer::write(const file::type &, const sint32_t &);
	template<> bool writer::write(const file::type &, const sint64_t &);

}

#endif