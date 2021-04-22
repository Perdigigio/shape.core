#ifndef SHAPE_CORE_IO_STREAM_HH__GUARD
#define SHAPE_CORE_IO_STREAM_HH__GUARD

#include "base.hh"

//!
//!

#include <cstdio>

//!
//!

namespace shape
{
	struct base_stream
	{
		FILE *fh;

		//!
		//!

		static bool open_istream(base_stream *, const char *) noexcept;
		static bool open_ostream(base_stream *, const char *) noexcept;
		static bool open_istream(base_stream *, int) noexcept;
		static bool open_ostream(base_stream *, int) noexcept;

		//! --------------------------------------------------

		static bool good(base_stream const *) noexcept;
		static bool fail(base_stream const *) noexcept;

		//! --------------------------------------------------

		static void free(base_stream *) noexcept;
	};

	class cBaseStream : private base_stream
	{
	public:
		static const struct _ISTREAM {} ISTREAM;
		static const struct _OSTREAM {} OSTREAM;

		//!
		//!

		inline cBaseStream(cBaseStream && p_other) noexcept
		{
			std::swap(this->fh = {}, p_other.fh);
		}

		//!
		//!

		cBaseStream(const _ISTREAM &, const char *);
		cBaseStream(const _OSTREAM &, const char *);
		cBaseStream(const _ISTREAM &, int);
		cBaseStream(const _OSTREAM &, int);

		//! -----------------------------------------------------------------

		inline bool good() const noexcept { return base_stream::good(this); }
		inline bool fail() const noexcept { return base_stream::fail(this); }

		//! -----------------------------------------------------------------

		inline FILE * get_handle() const noexcept
		{
			return this->fh;
		}

		//! -----------------------------------------------------------------

		inline cBaseStream & operator =(cBaseStream p_other) noexcept
		{
			std::swap(this->fh, p_other.fh); return *this; 
		}

		//! ------------------------------------------------------------------

		inline ~cBaseStream() noexcept { base_stream::free(this); }
	};


}

#endif