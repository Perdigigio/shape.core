#include "writer.hh"

//!
//!

namespace shape
{
	std::ostream& CoreStreamWriter::setFormat(std::ostream& p_stream, const uuid_t& p_uuid) noexcept
	{
		uint32_t data_1 = p_uuid.data_1;
		uint16_t data_2 = p_uuid.data_2;
		uint16_t data_3 = p_uuid.data_3;
		uint16_t data_4 = p_uuid.data_4;
		uint64_t data_5 = p_uuid.data_5;

		if (p_stream << std::noshowbase << std::hex)
		{
			p_stream << data_1 << char('-')
				 << data_2 << char('-')
				 << data_3 << char('-')
				 << data_4 << char('-')
				 << data_5;
		}

		//!
		//!

		return p_stream << std::ends;
	}

	//!
	//!

	std::ostream& CoreStreamWriter::set(std::ostream& p_stream, uint16_t p_u16) noexcept
	{
		p_stream << char('u')
			 << char('1')
			 << char('6')
			 << char(':') << std::noshowbase << std::hex << p_u16;

		//!
		//!

		return p_stream << std::ends;
	}

	std::ostream& CoreStreamWriter::set(std::ostream& p_stream, uint32_t p_u32) noexcept
	{
		p_stream << char('u')
			 << char('3')
			 << char('2')
			 << char(':') << std::noshowbase << std::hex << p_u32;

		//!
		//!

		return p_stream << std::ends;
	}

	std::ostream& CoreStreamWriter::set(std::ostream& p_stream, uint64_t p_u64) noexcept
	{
		p_stream << char('u')
			 << char('6')
			 << char('4')
			 << char(':') << std::noshowbase << std::hex << p_u64;

		//!
		//!

		return p_stream << std::ends;
	}

	std::ostream& CoreStreamWriter::set(std::ostream& p_stream, sint16_t p_i16) noexcept
	{
		p_stream << char('i')
			 << char('1')
			 << char('6')
			 << char(':') << std::noshowbase << std::hex << p_i16;

		//!
		//!

		return p_stream << std::ends;
	}

	std::ostream& CoreStreamWriter::set(std::ostream& p_stream, sint32_t p_i32) noexcept
	{
		p_stream << char('i')
			 << char('3')
			 << char('2')
			 << char(':') << std::noshowbase << std::hex << p_i32;

		//!
		//!

		return p_stream << std::ends;
	}

	std::ostream& CoreStreamWriter::set(std::ostream& p_stream, sint64_t p_i64) noexcept
	{
		p_stream << char('i')
			 << char('6')
			 << char('4')
			 << char(':') << std::noshowbase << std::hex << p_i64;

		//!
		//!

		return p_stream << std::ends;
	}


	std::ostream& CoreStreamWriter::end(std::ostream& p_stream) noexcept
	{
		return p_stream << std::endl;
	}

}

// vim: ts=8