#include "reader.hh"

//!
//!

namespace shape
{
	//!
	//! STREAM HELPERS
	//!

	template<char A> std::istream& mandate(std::istream& p_stream)
	{
		std::istream::sentry l_sentry(p_stream);

		//!
		//! CHECK THAT LAST EXTRACTED CHAR IS p_mandatory
		//!

		if (!l_sentry || p_stream.get() != A)
		{
			//!
			//! SET ERROR STATE ON STREAM
			//!

			p_stream.setstate(p_stream.rdstate() | std::istream::failbit);
		}

		//!
		//!

		return p_stream;
	}

	//!
	//!

	bool CoreStreamReader::getFormat(std::istream& p_stream, const uuid_t& p_uuid) noexcept
	{
		uint32_t data_1 = 0;
		uint16_t data_2 = 0;
		uint16_t data_3 = 0;
		uint16_t data_4 = 0;
		uint64_t data_5 = 0;

		if (p_stream >> std::hex)
		{
			p_stream >> data_1 >> mandate<'-'>
				 >> data_2 >> mandate<'-'>
				 >> data_3 >> mandate<'-'>
				 >> data_4 >> mandate<'-'>
				 >> data_5;
		}

		if (p_stream >> mandate<0>)
		{
			//!
			//! CHECK UUID EQUIVALENCE
			//!

			return uuid_t{ data_1, data_2, data_3, data_4, data_5 } == p_uuid;
		}

		//!
		//!

		return p_stream.good();
	}

	//!
	//!

	std::istream& CoreStreamReader::get(std::istream& p_stream, uint16_t& p_u16) noexcept
	{
		p_stream >> mandate<'u'>
			 >> mandate<'1'>
			 >> mandate<'6'>
			 >> mandate<':'> >> std::hex >> p_u16;

		//!
		//!

		return p_stream >> mandate<0>;
	}

	std::istream& CoreStreamReader::get(std::istream& p_stream, uint32_t& p_u32) noexcept
	{
		p_stream >> mandate<'u'>
			 >> mandate<'3'>
			 >> mandate<'2'>
			 >> mandate<':'> >> std::hex >> p_u32;

		//!
		//!

		return p_stream >> mandate<0>;
	}

	std::istream& CoreStreamReader::get(std::istream& p_stream, uint64_t& p_u64) noexcept
	{
		p_stream >> mandate<'u'>
			 >> mandate<'6'>
			 >> mandate<'4'>
			 >> mandate<':'> >> std::hex >> p_u64;

		//!
		//!

		return p_stream >> mandate<0>;
	}

	std::istream& CoreStreamReader::get(std::istream& p_stream, sint16_t& p_i16) noexcept
	{
		p_stream >> mandate<'i'>
			 >> mandate<'1'>
			 >> mandate<'6'>
			 >> mandate<':'> >> std::hex >> p_i16;

		//!
		//!

		return p_stream >> mandate<0>;
	}

	std::istream& CoreStreamReader::get(std::istream& p_stream, sint32_t& p_i32) noexcept
	{
		p_stream >> mandate<'i'>
			 >> mandate<'3'>
			 >> mandate<'2'>
			 >> mandate<':'> >> std::hex >> p_i32;

		//!
		//!

		return p_stream >> mandate<0>;
	}

	std::istream& CoreStreamReader::get(std::istream& p_stream, sint64_t& p_i64) noexcept
	{
		p_stream >> mandate<'i'>
			 >> mandate<'6'>
			 >> mandate<'4'>
			 >> mandate<':'> >> std::hex >> p_i64;

		//!
		//!

		return p_stream >> mandate<0>;
	}

}

// vim: ts=8