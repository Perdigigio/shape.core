#ifndef SHAPE_BASE_HH__GUARD
#define SHAPE_BASE_HH__GUARD

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
	struct temp_t {};
	struct heap_t {};
	struct page_t {};

	//!
	//! FOURCC
	//!

	static inline constexpr uint32_t fourcc(int f, int o, int u, int r) noexcept
	{
		return  (uint32_t(f) << 030) | (uint32_t(o) << 020) |
			(uint32_t(u) << 010) | (uint32_t(r) << 000);
	}

	//!
	//!

	template<class T> static inline constexpr T align(T size, T base) noexcept
	{
		//!
		//!

		return (size + base - 1) & ~(base - 1);
	}

	template<class T> static inline constexpr T * cast_offset(void * p_addr, intptr_t p_base)
	{
		return  reinterpret_cast<T *>(
				reinterpret_cast<intptr_t>(p_addr) + p_base);
	}

	template<class T> static inline constexpr const T * cast_offset(const void * p_addr, intptr_t p_base)
	{
		return  reinterpret_cast<const T *>(
				reinterpret_cast<intptr_t>(p_addr) + p_base);
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

	template<class tag> struct buffer
	{
		struct deleter
		{
			inline void operator()(void * p) const noexcept { memory_free<tag>(p); }
		};

		//!
		//!

		typedef std::unique_ptr<void, deleter> type_t;
	};

	//! -------------------------------------------------------------

	template<class tag> static typename buffer<tag>::type_t buffer_alloc(size_t p_length)
	{
		//!
		//! buffer_t FACILITY
		//!

		return  typename buffer<tag>::type_t{ memory_alloc<tag>(p_length) };
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
		const char * what() const noexcept override { return "shape::failure"; }
	};

} // namespace shape

#endif
