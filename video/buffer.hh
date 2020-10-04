#ifndef SHAPE_CORE_VIDEO_BUFFER_HH__GUARD
#define SHAPE_CORE_VIDEO_BUFFER_HH__GUARD

#include "../base.hh"
#include "../type.hh"

namespace shape
{
	template<class Buffer> class CoreVideoBuffer
	{
		/**
		 * @param lhs
		 * @param rhs
		 */
		friend void swap(CoreVideoBuffer&,  CoreVideoBuffer&);

	public:
		typedef typename Buffer::handle_t handle_t;
		typedef typename Buffer::offset_t offset_t;
		typedef typename Buffer::length_t length_t;
		typedef typename Buffer::bitset_t bitset_t;

		//!
		//!

		inline CoreVideoBuffer()  noexcept
		{
			m_handle = handle_t();
			m_length = length_t();
			m_bitset = bitset_t();
		}

		inline CoreVideoBuffer(const CoreVideoBuffer& p_other) noexcept
		{
			if (!Buffer::grab(p_other.m_handle))
			{
				CoreError::error("called Buffer::grab on invalid handle");
			}

			//!
			//!

			m_handle = p_other.m_handle;
			m_length = p_other.m_length;
			m_bitset = p_other.m_bitset;
		}

		/**
		 * @brief Helper constructor for Device
		 * 
		 * @param handle
		 * @param length
		 * @param bitset
		 */
		inline CoreVideoBuffer(handle_t p_handle, length_t p_length, bitset_t p_bitset) noexcept
		{
			m_handle = p_handle;
			m_length = p_length;
			m_bitset = p_bitset;
		}

		//!
		//! GETTERS
		//!

		inline handle_t getHandle() const noexcept { return m_handle; }
		inline length_t getLength() const noexcept { return m_length; }
		inline bitset_t getBitset() const noexcept { return m_bitset; }

		//!
		//!

		~CoreVideoBuffer()
		{
			Buffer::drop(m_handle);
		}

	private:
		handle_t m_handle;
		length_t m_length;
		bitset_t m_bitset;
	};

	//!
	//!

	template<class Buffer> void swap(CoreVideoBuffer<Buffer>& lhs,  CoreVideoBuffer<Buffer>& rhs) noexcept
	{
		std::swap(lhs.m_handle, rhs.m_handle);
		std::swap(lhs.m_length, rhs.m_length);
		std::swap(lhs.m_bitset, rhs.m_bitset);
	}

	//!
	//!

	/**
	 * @param buffer
	 * @param bitset
	 * @param offset offset + length should not exceed CoreVideoBuffer length
	 * @param length offset + length should not exceed CoreVideoBuffer length
	 */
	template<class Buffer> void * grabMap(const CoreVideoBuffer<Buffer>& p_buffer,
		typename Buffer::bitset_t p_bitset,
		typename Buffer::offset_t p_offset,
		typename Buffer::length_t p_length) noexcept
	{
		void * l_address = nullptr;

		//!
		//!

		if (!Buffer::grabAddress(p_buffer.getHandle(), p_offset, p_length, &l_address))
		{
			//!
			//! HANDLE ERROR
			//!

			CoreError::error("failure while Buffer::grabAddress");
		}

		//!
		//!

		return l_address;
	}

	template<class Buffer> void dropMap(const CoreVideoBuffer<Buffer>& p_buffer) noexcept
	{
		Buffer::dropAddress(p_buffer.getHandle());
	}
}

#endif