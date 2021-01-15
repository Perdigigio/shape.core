#ifndef SHAPE_CORE_BASE_HH__GUARD
#define SHAPE_CORE_BASE_HH__GUARD

#include <ostream>
#include <istream>
#include <cstdint>
#include <utility>

#include <exception>
#include <memory>

#define LOG_FAIL(msg) (shape::log_fail(__FILE__, __LINE__) << msg << "\033[0m" << std::endl)
#define LOG_WARN(msg) (shape::log_warn(__FILE__, __LINE__) << msg << "\033[0m" << std::endl)
#define LOG_INFO(msg) (shape::log_info(__FILE__, __LINE__) << msg << "\033[0m" << std::endl)

namespace shape
{
	typedef std::unique_ptr<void, void (*)(void*)> buffer_t;

	struct temp_t {};
	struct heap_t {};
	struct page_t {};

	static inline constexpr uint32_t fourcc(int f, int o, int u, int r) noexcept
	{
		return  (uint32_t(f) << 000) | (uint32_t(o) << 010) |
			(uint32_t(u) << 020) | (uint32_t(r) << 030);
	}

	//!
	//! MEMORY ACQUISITION
	//!

	template<class T> void * memory_alloc(size_t) = delete;

	//! -------------------------------------------------------

	template<> void * memory_alloc<temp_t>(size_t);
	template<> void * memory_alloc<heap_t>(size_t);
	template<> void * memory_alloc<page_t>(size_t);

	//!
	//! MEMORY RELEASE
	//!

	template<class T> void memory_free(void *) = delete;

	//! -------------------------------------------------------

	template<> void memory_free<temp_t>(void *);
	template<> void memory_free<heap_t>(void *);
	template<> void memory_free<page_t>(void *);

	//!
	//! BUFFER
	//!

	template<class tag> buffer_t buffer_alloc(size_t p_length)
	{
		//!
		//! buffer_t FACILITY
		//!

		return { memory_alloc<tag>(p_length), memory_free<tag> };
	}

	//!
	//! LOGGER
	//!

	std::ostream& log_fail(const char *, int);
	std::ostream& log_warn(const char *, int);
	std::ostream& log_info(const char *, int);

	//!
	//! EXCEPTIONS
	//!

	struct failure : std::exception
	{
		const char * what() const override { return "shape::failure"; }
	};

} // namespace shape

#endif