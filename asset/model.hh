#ifndef SHAPE_CORE_ASSET_MODEL_HH__GUARD
#define SHAPE_CORE_ASSET_MODEL_HH__GUARD

#include "../type.hh"
#include "../base.hh"

namespace shape
{

	struct model_fourcc
	{
		static constexpr uint32_t U16 = fourcc('U', '1', '6', ' ');
		static constexpr uint32_t U32 = fourcc('U', '3', '2', ' ');
		static constexpr uint32_t S16 = fourcc('S', '1', '6', ' ');
		static constexpr uint32_t S32 = fourcc('S', '3', '2', ' ');
		static constexpr uint32_t F16 = fourcc('F', '1', '6', ' ');
		static constexpr uint32_t F32 = fourcc('F', '3', '2', ' ');

		//! ------------------ VECTOR TYPES -----------------------

		static constexpr uint32_t VEC1 = fourcc('V', 'E', 'C', '1');
		static constexpr uint32_t VEC2 = fourcc('V', 'E', 'C', '2');
		static constexpr uint32_t VEC3 = fourcc('V', 'E', 'C', '3');
		static constexpr uint32_t VEC4 = fourcc('V', 'E', 'C', '4');
		static constexpr uint32_t MAT2 = fourcc('M', 'A', 'T', '2');
		static constexpr uint32_t MAT3 = fourcc('M', 'A', 'T', '3');
		static constexpr uint32_t MAT4 = fourcc('M', 'A', 'T', '4');
	};

	struct model_buffer
	{
		uint32_t fmt;
		uint32_t vec;
		uint32_t num;
	};

	class cModelBuffer : private model_buffer
	{
	public:
		inline cModelBuffer(uint32_t fmt, uint32_t vec, uint32_t num) noexcept
		{
			this->fmt = fmt;
			this->vec = vec;
			this->num = num;
		}

		//!
		//!
		//!

		inline uint32_t get_fmt() const noexcept { return this->fmt; }
		inline uint32_t get_vec() const noexcept { return this->vec; }
		inline uint32_t get_num() const noexcept { return this->num; }

		//!
		//!

		size_t get_stride() const noexcept;
		size_t get_length() const noexcept;
	};

	//!
	//!

	template<class tag> buffer_t model_buffer_alloc(const cModelBuffer & p_buffer)
	{
		//!
		//!

		return buffer_alloc<tag>(p_buffer.get_length());
	}

}

#endif