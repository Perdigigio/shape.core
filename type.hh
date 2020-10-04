#ifndef SHAPE_CORE_TYPE_HH__GUARD
#define SHAPE_CORE_TYPE_HH__GUARD

#include <cstdint>
#include <cstddef>
#include <utility>

namespace shape
{

	typedef int16_t sint16_t;
	typedef int32_t sint32_t;
	typedef int64_t sint64_t;

	typedef struct uuid uuid_t;


	//!
	//! UUID
	//!

	struct uuid
	{
		uint64_t data_1 : 32;
		uint64_t data_2 : 16;
		uint64_t data_3 : 16;
		uint64_t data_4 : 16;
		uint64_t data_5 : 48;
	};

	inline bool operator ==(const uuid&, const uuid&) noexcept;
	inline bool operator !=(const uuid&, const uuid&) noexcept;

	//!
	//!

	inline bool operator ==(const uuid& l, const uuid& r) noexcept
	{
		return  l.data_1 == r.data_1 &&
			l.data_2 == r.data_2 &&
			l.data_3 == r.data_3 &&
			l.data_4 == r.data_4 &&
			l.data_5 == r.data_5;
	}

	inline bool operator !=(const uuid& l, const uuid& r) noexcept
	{
		return  l.data_1 != r.data_1 ||
			l.data_2 != r.data_2 ||
			l.data_3 != r.data_3 ||
			l.data_4 != r.data_4 ||
			l.data_5 != r.data_5;
	}

} // namespace shape

#endif