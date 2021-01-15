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

	template<class T, class O, T N> static inline constexpr T arraysize(const O(&)[N])
	{
		return N;
	}

	template<class T> static inline constexpr T align(T size, T base) noexcept
	{
		//!
		//!

		return (size + base - 1) & ~(base - 1);
	}

	template<class T> static inline constexpr T * offset(T * p_addr, intptr_t p_base)
	{
		return reinterpret_cast<T *>(reinterpret_cast<intptr_t>(p_addr) + p_base);
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

	//!
	//!
	//!

	template<class T> struct on_scope_exit_t
	{
		inline on_scope_exit_t() = delete;
		inline on_scope_exit_t(const on_scope_exit_t &) = delete;
		inline on_scope_exit_t(on_scope_exit_t && p_other) = default;
		inline on_scope_exit_t(T && p_callable) noexcept : m_callable(p_callable) {}

		on_scope_exit_t& operator=(const on_scope_exit_t &) noexcept = delete;
		on_scope_exit_t& operator=(on_scope_exit_t &&) noexcept = default;

		inline ~on_scope_exit_t() noexcept
		{
			m_callable();
		}

		T m_callable;
	};

	template<class T> static inline on_scope_exit_t<T> on_scope_exit(T && p_callable) noexcept
	{
		//!
		//!

		return on_scope_exit_t<T>{ std::forward<T>(p_callable) };
	}

} // namespace shape

#endif
