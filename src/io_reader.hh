#ifndef SHAPE_CORE_STREAM_READER_HH__GUARD
#define SHAPE_CORE_STREAM_READER_HH__GUARD

#include "type.hh"
#include "base.hh"

//!
//! TODO MAYBE RETURN std::optional
//!

namespace shape
{
	struct reader
	{
		template<class T> static std::istream & read(std::istream&, T &);
	};


	//! ----------------- INTEGER TYPES -----------------------

	template<> std::istream & reader::read(std::istream &, uint16_t &);
	template<> std::istream & reader::read(std::istream &, uint32_t &);
	template<> std::istream & reader::read(std::istream &, uint64_t &);
	template<> std::istream & reader::read(std::istream &, sint16_t &);
	template<> std::istream & reader::read(std::istream &, sint32_t &);
	template<> std::istream & reader::read(std::istream &, sint64_t &);

}

#endif