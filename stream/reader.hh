#ifndef SHAPE_CORE_STREAM_READER_HH__GUARD
#define SHAPE_CORE_STREAM_READER_HH__GUARD

#include "../type.hh"
#include "../base.hh"

//!
//! STD
//!

#include <istream>

//!
//!

namespace shape
{

	struct CoreStreamReader
	{
		static bool getFormat(std::istream&, const uuid_t&) noexcept;

		//!
		//!

		static std::istream& get(std::istream&, uint16_t&) noexcept;
		static std::istream& get(std::istream&, uint32_t&) noexcept;
		static std::istream& get(std::istream&, uint64_t&) noexcept;
		static std::istream& get(std::istream&, sint16_t&) noexcept;
		static std::istream& get(std::istream&, sint32_t&) noexcept;
		static std::istream& get(std::istream&, sint64_t&) noexcept;
	};

	//!
	//!

}

#endif