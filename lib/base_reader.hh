#ifndef SHAPE_CORE_STREAM_READER_HH__GUARD
#define SHAPE_CORE_STREAM_READER_HH__GUARD

#include "type.hh"
#include "base_stream.hh"

//!
//!

namespace shape
{
	struct reader
	{
		template<class T> static bool read(const file::type&, T &);
	};


	//! ----------------- INTEGER TYPES -----------------------

	template<> bool reader::read(const file::type &, uint16_t &);
	template<> bool reader::read(const file::type &, uint32_t &);
	template<> bool reader::read(const file::type &, uint64_t &);
	template<> bool reader::read(const file::type &, sint16_t &);
	template<> bool reader::read(const file::type &, sint32_t &);
	template<> bool reader::read(const file::type &, sint64_t &);

}

#endif