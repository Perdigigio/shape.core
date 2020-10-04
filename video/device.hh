#ifndef SHAPE_CORE_VIDEO_DEVICE_HH__GUARD
#define SHAPE_CORE_VIDEO_DEVICE_HH__GUARD

#include "buffer.hh"
#include "source.hh"
#include "shader.hh"

namespace shape
{

	//!
	//! @brief Generic video device adapter
	//!
	template<class Device> class CoreVideoDevice
	{
		/**
		 * @param lhs
		 * @param rhs
		 */
		template<class T> friend void swap(CoreVideoDevice<T>&,  CoreVideoDevice<T>&);

	public:
		typedef typename Device::handle_t handle_t;
		typedef typename Device::offset_t offset_t;
		typedef typename Device::length_t length_t;
		typedef typename Device::bitset_t bitset_t;

		//!
		//!

		inline CoreVideoDevice() noexcept
		{
			m_handle = handle_t();
		}

		inline CoreVideoDevice(const CoreVideoDevice& p_other)
		{
			if (!Device::grab(p_other.m_handle))
			{
				CoreError::error("called Device::grab on invalid handle");
			}

			//!
			//!

			m_handle = p_other.m_handle;
		}

		inline CoreVideoDevice(handle_t p_handle) noexcept
		{
			m_handle = p_handle;
		}

		//!
		//!

		/**
		 * @param length
		 * @param bitset
		 * @param buffer
		 */
		template<class Buffer> CoreVideoBuffer<Buffer> createBuffer(length_t, bitset_t, const void *) noexcept;
		
		/**
		 * @param source
		 * @param format
		 * @param bitset
		 * @param source-data
		 */
		template<class Source> CoreVideoSource<Source> createSource(const source1D_t&, const uuid_t&, bitset_t, const subresource_t *) noexcept;
		template<class Source> CoreVideoSource<Source> createSource(const source2D_t&, const uuid_t&, bitset_t, const subresource_t *) noexcept;
		template<class Source> CoreVideoSource<Source> createSource(const source3D_t&, const uuid_t&, bitset_t, const subresource_t *) noexcept;

		/**
		 * @param source-length
		 * @param source
		 */
		template<class Shader> CoreVideoShader<Shader> createShader(length_t, typename Shader::source_t);

		//!
		//!

		inline CoreVideoDevice& operator=(CoreVideoDevice p_other)
		{
			//!
			//! COPY-SWAP
			//!

			return swap(*this, p_other), *this;
		}

		//!
		//!

		~CoreVideoDevice()
		{
			Device::drop(m_handle);
		}

	private:
		handle_t m_handle;
	};

	//!
	//!

	template<class Device> void swap(CoreVideoDevice<Device>& lhs, CoreVideoDevice<Device>& rhs)
	{
		std::swap(lhs.m_handle, rhs.m_handle);
	}

	//!
	//!

	template<class Device>
	template<class Buffer>
	CoreVideoBuffer<Buffer> CoreVideoDevice<Device>::createBuffer(length_t p_length, bitset_t p_bitset, const void * p_buffer) noexcept
	{
		typename Buffer::handle_t l_handle = Buffer::open(m_handle, p_length, p_bitset, p_buffer);

		//!
		//! CHECK IF HANDLE IS VALID
		//!

		if (l_handle == Buffer::handle_t())
		{
			//!
			//! NOTIFY FAILURE
			//!

			CoreError::error("failed creating buffer"); //! TODO formatter
		}

		//!
		//!

		return CoreVideoBuffer<Buffer>{l_handle, p_length, p_bitset};
	}

	template<class Device>
	template<class Source>
	CoreVideoSource<Source> CoreVideoDevice<Device>::createSource(const source1D_t& p_source, const uuid_t& p_format, bitset_t p_bitset, const subresource_t * p_buffer) noexcept
	{
		typename Source::format_t l_format = Source::cast(p_format);
		typename Source::handle_t l_handle = Source::open(m_handle, p_source, l_format, p_bitset, p_buffer);

		//!
		//! CHECK IF HANDLE IS VALID
		//!

		if (l_handle == Source::handle_t())
		{
			//!
			//! NOTIFY FAILURE
			//!

			CoreError::error("failed creating 1D source"); //! TODO formatter
		}

		//!
		//!

		return CoreVideoSource<Source>{l_handle, l_format, p_bitset};
	}

	template<class Device>
	template<class Source>
	CoreVideoSource<Source> CoreVideoDevice<Device>::createSource(const source2D_t& p_source, const uuid_t& p_format, bitset_t p_bitset, const subresource_t * p_buffer) noexcept
	{
		typename Source::format_t l_format = Source::cast(p_format);
		typename Source::handle_t l_handle = Source::open(m_handle, p_source, l_format, p_bitset, p_buffer);

		//!
		//! CHECK IF HANDLE IS VALID
		//!

		if (l_handle == Source::handle_t())
		{
			//!
			//! NOTIFY FAILURE
			//!

			CoreError::error("failed creating 2D source"); //! TODO formatter
		}

		//!
		//!

		return CoreVideoSource<Source>{l_handle, l_format, p_bitset};
	}

	template<class Device>
	template<class Source>
	CoreVideoSource<Source> CoreVideoDevice<Device>::createSource(const source3D_t& p_source, const uuid_t& p_format, bitset_t p_bitset, const subresource_t * p_buffer) noexcept
	{
		typename Source::format_t l_format = Source::cast(p_format);
		typename Source::handle_t l_handle = Source::open(m_handle, p_source, l_format, p_bitset, p_buffer);

		//!
		//! CHECK IF HANDLE IS VALID
		//!

		if (l_handle == Source::handle_t())
		{
			//!
			//! NOTIFY FAILURE
			//!

			CoreError::error("failed creating 3D source"); //! TODO formatter
		}

		//!
		//!

		return CoreVideoSource<Source>{l_handle, l_format, p_bitset};
	}

	template<class Device>
	template<class Shader>
	CoreVideoShader<Shader> CoreVideoDevice<Device>::createShader(length_t p_length, typename Shader::source_t p_source)
	{
		typename Shader::handle_t l_handle = Shader::open(m_handle, p_length, p_source);

		//!
		//! CHECK IF HANDLE IS VALID
		//!

		if (l_handle == Shader::handle_t())
		{
			//!
			//! NOTIFY FAILURE
			//!

			CoreError::error("failed creating shader"); //! TODO formatter
		}

		//!
		//!

		return CoreVideoShader<Shader>{l_handle, p_length, p_source};
	}
}

#endif