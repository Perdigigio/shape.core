#ifndef SHAPE_CORE_IO_STREAM_HH__GUARD
#define SHAPE_CORE_IO_STREAM_HH__GUARD

#include <cstdio>
#include <memory>

//!
//! TODO MAYBE RETURN std::optional
//!

namespace shape
{
	struct file
	{
		struct deleter
		{
			void operator()(FILE *) const noexcept;
		};

		//!
		//!

		typedef std::unique_ptr<FILE, deleter> type;
	};

	//!
	//!

	struct stream
	{
		static file::type open_istream(const char *) noexcept;
		static file::type open_ostream(const char *) noexcept;
		static file::type open_istream(int) noexcept;
		static file::type open_ostream(int) noexcept;

		//! --------------------------------------------------

		static bool good(const file::type &) noexcept;
		static bool fail(const file::type &) noexcept;
	};

}

#endif