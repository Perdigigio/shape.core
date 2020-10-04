#include "base.hh"

//!
//! STD
//!

#include <iostream>

//!
//!

namespace shape
{

	void CoreError::error(const char * p_message)
	{
		std::cerr << "[EE] " << p_message << std::endl;
	}

	void CoreError::raise(const char *  p_message)
	{

	}
}