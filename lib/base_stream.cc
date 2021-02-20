#include "base_stream.hh"

//!
//! MSVC deprecation warning suppress workaround
//!

#ifdef _MSC_VER
#	pragma warning( push )
#	pragma warning( disable : 4996 )
#endif

namespace shape
{

	file::type stream::open_istream(const char *p_file) noexcept { return { std::fopen(p_file, "rb"), file::deleter{} }; }
	file::type stream::open_ostream(const char *p_file) noexcept { return { std::fopen(p_file, "wb"), file::deleter{} }; }
	file::type stream::open_istream(int p_fd) noexcept { return { fdopen(p_fd, "rb"), file::deleter{} }; }
	file::type stream::open_ostream(int p_fd) noexcept { return { fdopen(p_fd, "wb"), file::deleter{} }; }

	//! -----------------------------------------------------------------------------------------------------------------

	bool stream::good(const file::type &p_fh) noexcept { return !fail(p_fh); }
	bool stream::fail(const file::type &p_fh) noexcept
	{
		//!
		//!

		 return !p_fh || std::ferror(p_fh.get());
	}

	//! -----------------------------------------------------------------------------------------------------------------

	void file::deleter::operator()(FILE *p_fh) const noexcept
	{
		std::fclose(p_fh);
	}

} //! shape

#ifdef _MSC_VER
#	pragma warning( pop )
#endif