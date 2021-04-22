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

	bool base_stream::open_istream(base_stream *p_stream, const char *p_file) noexcept { return (p_stream->fh = std::fopen(p_file, "rb")) != NULL; }
	bool base_stream::open_ostream(base_stream *p_stream, const char *p_file) noexcept { return (p_stream->fh = std::fopen(p_file, "wb")) != NULL; }
	bool base_stream::open_istream(base_stream *p_stream, int p_fd) noexcept { return (p_stream->fh = fdopen(p_fd, "rb")) != NULL; }
	bool base_stream::open_ostream(base_stream *p_stream, int p_fd) noexcept { return (p_stream->fh = fdopen(p_fd, "wb")) != NULL; }

	//! -----------------------------------------------------------------------------------------------------------------

	bool base_stream::good(base_stream const *p_stream) noexcept { return !base_stream::fail(p_stream) && !std::feof(p_stream->fh); }
	bool base_stream::fail(base_stream const *p_stream) noexcept
	{
		//!
		//!

		 return !p_stream->fh || std::ferror(p_stream->fh);
	}

	//! -----------------------------------------------------------------------------------------------------------------

	void base_stream::free(base_stream *p_stream) noexcept
	{
		if (p_stream)
			std::fclose(p_stream->fh);
	}

	//!
	//!

	const cBaseStream::_ISTREAM cBaseStream::ISTREAM = {};
	const cBaseStream::_OSTREAM cBaseStream::OSTREAM = {};

	cBaseStream::cBaseStream(const _ISTREAM &, const char *p_fn) { if (!base_stream::open_istream(this, p_fn)) throw failure{}; }
	cBaseStream::cBaseStream(const _OSTREAM &, const char *p_fn) { if (!base_stream::open_ostream(this, p_fn)) throw failure{}; }
	cBaseStream::cBaseStream(const _ISTREAM &, int p_fd) { if (!base_stream::open_istream(this, p_fd)) throw failure{}; }
	cBaseStream::cBaseStream(const _OSTREAM &, int p_fd) { if (!base_stream::open_ostream(this, p_fd)) throw failure{}; }

} //! shape

#ifdef _MSC_VER
#	pragma warning( pop )
#endif