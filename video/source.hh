#ifndef SHAPE_CORE_VIDEO_SOURCE_HH__GUARD
#define SHAPE_CORE_VIDEO_SOURCE_HH__GUARD

#include "../base.hh"
#include "../type.hh"

namespace shape
{
	typedef struct subresource subresource_t;

	typedef struct source1D source1D_t;
	typedef struct source2D source2D_t;
	typedef struct source3D source3D_t;

	//!
	//!

	template<class Source> class CoreVideoSource
	{
		/**
		 * @param lhs
		 * @param rhs
		 */
		template<class T> friend void swap(CoreVideoSource<T>&,  CoreVideoSource<T>&);

	public:
		typedef typename Source::handle_t handle_t;
		typedef typename Source::bitset_t bitset_t;
		typedef typename Source::format_t format_t;
		typedef typename Source::offset_t offset_t;

		//!
		//!

		inline CoreVideoSource() noexcept
		{
			m_handle = handle_t();
			m_format = format_t();
			m_bitset = bitset_t();
		}

		inline CoreVideoSource(const CoreVideoSource& p_other) noexcept
		{
			if (!Source::grab(p_other.m_handle))
			{
				CoreError::error("called Source::grab on invalid handle");
			}

			//!
			//!

			m_handle = p_other.m_handle;
			m_format = p_other.m_format;
			m_bitset = p_other.m_bitset;
		}

		/**
		 * @brief Helper constructor for Device
		 * 
		 * @param handle
		 * @param length
		 * @param bitset
		 */
		inline CoreVideoSource(handle_t p_handle, format_t p_format, bitset_t p_bitset) noexcept
		{
			m_handle = p_handle;
			m_format = p_format;
			m_bitset = p_bitset;
		}

		//!
		//! GETTERS
		//!

		inline handle_t getHandle() const { return m_handle; }
		inline format_t getFormat() const { return m_format; }
		inline bitset_t getBitset() const { return m_bitset; }

		//!
		//!

		~CoreVideoSource()
		{
			Source::drop(m_handle);
		}

	private:
		handle_t m_handle;
		format_t m_format;
		bitset_t m_bitset;
	};

	//!
	//!

	template<class Source> void swap(CoreVideoSource<Source>& lhs,  CoreVideoSource<Source>& rhs)
	{
		std::swap(lhs.m_handle, rhs.m_handle);
		std::swap(lhs.m_format, rhs.m_format);
		std::swap(lhs.m_bitset, rhs.m_bitset);
	}

	//!
	//!

	/**
	 * @brief Enqueue an update request on device, do not block
	 * 
	 * @param source 
	 * @param buffer
	 * @param offset-base
	 * @param offset-stop
	 */
	template<class Source> void update(const CoreVideoSource<Source>& p_source, const subresource_t& p_buffer,
		typename Source::offset_t p_offsetBase,
		typename Source::offset_t p_offsetStop) noexcept
	{
		typename Source::offset_t l_range =
		{
			p_offsetBase,
			p_offsetStop
		};

		//!
		//!

		Source::update(p_source.getHandle(), p_subresorce, l_range);
	}

	//!
	//!

	struct subresource
	{
		uint16_t level;
		uint16_t layer;
		uint32_t pitchLength;
		uint32_t sliceLength;

		//!
		//!

		const void * data;
	};

	struct source1D
	{
		uint16_t levels;
		uint16_t layers;
		uint16_t w;
	};

	struct source2D
	{
		uint16_t levels;
		uint16_t layers;
		uint16_t w;
		uint16_t h;
	};

	struct source3D
	{
		uint16_t levels;
		uint16_t w;
		uint16_t h;
		uint16_t d;
	};
}

#endif