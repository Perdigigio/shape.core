#ifndef SHAPE_CORE_BASE_HH__GUARD
#define SHAPE_CORE_BASE_HH__GUARD

#include <cstdint>

namespace shape
{
	//!
	//! UUID
	//!

	struct uuid_t
	{
		uint64_t data_1 : 32;
		uint64_t data_2 : 16;
		uint64_t data_3 : 16;
		uint64_t data_4 : 16;
		uint64_t data_5 : 48;
	};

	inline bool operator ==(const uuid_t&, const uuid_t&) noexcept;
	inline bool operator !=(const uuid_t&, const uuid_t&) noexcept;

	//!
	//!

	inline bool operator ==(const uuid_t& l, const uuid_t& r) noexcept
	{
		return  l.data_1 == r.data_1 &&
			l.data_2 == r.data_2 &&
			l.data_3 == r.data_3 &&
			l.data_4 == r.data_4 &&
			l.data_5 == r.data_5;
	}

	inline bool operator !=(const uuid_t& l, const uuid_t& r) noexcept
	{
		return  l.data_1 != r.data_1 ||
			l.data_2 != r.data_2 ||
			l.data_3 != r.data_3 ||
			l.data_4 != r.data_4 ||
			l.data_5 != r.data_5;
	}



} // namespace shape

#endif