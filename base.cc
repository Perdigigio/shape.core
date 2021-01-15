#include "base.hh"

//!
//! STD
//!

#include <iostream>

//!
//!

namespace shape
{
	//!
	//!

	template<> void * memory_alloc<temp_t>(size_t p_length) { return ::operator new(p_length); }
	template<> void * memory_alloc<heap_t>(size_t p_length) { return ::operator new(p_length); }
	template<> void * memory_alloc<page_t>(size_t p_length) { return ::operator new(p_length); }

	//!
	//!

	template<> void memory_free<temp_t>(void * p_memory) { ::operator delete(p_memory); }
	template<> void memory_free<heap_t>(void * p_memory) { ::operator delete(p_memory); }
	template<> void memory_free<page_t>(void * p_memory) { ::operator delete(p_memory); }

	//!
	//!

	std::ostream& log_fail(const char * p_file, int p_line) { return std::cerr << "\033[31m[EE] "; }
	std::ostream& log_warn(const char * p_file, int p_line) { return std::cerr << "\033[35m[WW] "; }
	std::ostream& log_info(const char * p_file, int p_line) { return std::clog << "\033[36m[II] "; }
}