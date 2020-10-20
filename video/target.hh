#ifndef SHAPE_CORE_VIDEO_TARGET_HH__GUARD
#define SHAPE_CORE_VIDEO_TARGET_HH__GUARD

#include "../base.hh"
#include "../type.hh"

namespace shape
{
	typedef struct target1D target1D_t;
	typedef struct target2D target2D_t;
	typedef struct target3D target3D_t;

	//!
	//! FLAGS
	//!

	struct CoreVideoTargetFlags
	{
		static constexpr uint32_t IsArray = 1 << 0;
		static constexpr uint32_t IsCubic = 1 << 1;
		static constexpr uint32_t IsMultisampled = 1 << 2;
		static constexpr uint32_t IsBindable = 1 << 3;
	};

	//!
	//!

	template<class Target> class CoreVideoTarget
	{
		/**
		 * @param lhs
		 * @param rhs
		 */
		template<class T> friend void swap(CoreVideoTarget<T>&,  CoreVideoTarget<T>&);

	public:
		typedef typename Target::handle_t handle_t;
		typedef typename Target::bitset_t bitset_t;
		typedef typename Target::format_t format_t;

		//!
		//!

		inline CoreVideoSource() noexcept
		{
			m_handle = handle_t();
			m_format = format_t();
			m_bitset = bitset_t();
		}

		inline CoreVideoTarget(const CoreVideoTarget& p_other) noexcept
		{
			if (!Target::grab(p_other.m_handle))
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
		inline CoreVideoTarget(handle_t p_handle, format_t p_format, bitset_t p_bitset) noexcept
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

		~CoreVideoTarget()
		{
			Target::drop(m_handle);
		}

	private:
		handle_t m_handle;
		format_t m_format;
		bitset_t m_bitset;
	};

	//!
	//!

	template<class Target> void swap(CoreVideoTarget<Target>& lhs,  CoreVideoTarget<Target>& rhs)
	{
		std::swap(lhs.m_handle, rhs.m_handle);
		std::swap(lhs.m_format, rhs.m_format);
		std::swap(lhs.m_bitset, rhs.m_bitset);
	}

	//!
	//!


	struct target1D
	{
		uint16_t levels;
		uint16_t layers;
		uint16_t w;
	};

	struct target2D
	{
		uint16_t levels;
		uint16_t layers;
		uint16_t w;
		uint16_t h;
	};

	struct target3D
	{
		uint16_t levels;
		uint16_t w;
		uint16_t h;
		uint16_t d;
	};
}

#endif