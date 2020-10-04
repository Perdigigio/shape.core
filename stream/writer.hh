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
		static std::ostream& setFormat(std::ostream&, const uuid_t&) noexcept;

		//!
		//! SCALAR
		//!

		static std::ostream& set(std::ostream&, uint16_t) noexcept;
		static std::ostream& set(std::ostream&, uint32_t) noexcept;
		static std::ostream& set(std::ostream&, uint64_t) noexcept;
		static std::ostream& set(std::ostream&, sint16_t) noexcept;
		static std::ostream& set(std::ostream&, sint32_t) noexcept;
		static std::ostream& set(std::ostream&, sint64_t) noexcept;

		static std::ostream& end(std::ostream&) noexcept;
	};

	//!
	//!

}

#endif