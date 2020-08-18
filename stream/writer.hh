#ifndef SHAPE_CORE_STREAM_WRITER_HH__GUARD
#define SHAPE_CORE_STREAM_WRITER_HH__GUARD

#include "../type.hh"
#include "../base.hh"

//!
//! STD
//!

#include <ostream>

//!
//!

namespace shape
{

	struct CoreStreamWriter
	{
		static bool setFormat(std::ostream&, const uuid_t&) noexcept;

		//!
		//!

		static void set(std::ostream&, uint16_t) noexcept;
		static void set(std::ostream&, uint32_t) noexcept;
		static void set(std::ostream&, uint64_t) noexcept;
		static void set(std::ostream&, sint16_t) noexcept;
		static void set(std::ostream&, sint32_t) noexcept;
		static void set(std::ostream&, sint64_t) noexcept;
	};

	//!
	//!

}

#endif