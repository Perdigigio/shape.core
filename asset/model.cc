#include "model.hh"

//!
//!

namespace shape
{
	static inline size_t get_bytes(const model_buffer *);

	//!
	//!

	size_t cModelBuffer::get_stride() const noexcept
	{
		switch (vec)
		{
			case model_fourcc::VEC1: return 1 * get_bytes(this);
			case model_fourcc::VEC2: return 2 * get_bytes(this);
			case model_fourcc::VEC3: return 3 * get_bytes(this);
			case model_fourcc::VEC4: return 4 * get_bytes(this);
			case model_fourcc::MAT2: return 2 * 2 * get_bytes(this);
			case model_fourcc::MAT3: return 3 * 3 * get_bytes(this);
			case model_fourcc::MAT4: return 4 * 4 * get_bytes(this);
		}

		//!
		//!

		return 0;
	}

	size_t cModelBuffer::get_length() const noexcept
	{
		//!
		//!

		return get_stride() * this->num;
	}

	//!
	//!

	size_t get_bytes(const model_buffer * p_buffer)
	{
		switch (p_buffer->fmt)
		{
			case model_fourcc::U32: return 4;
			case model_fourcc::S32: return 4;
			case model_fourcc::U16: return 2;
			case model_fourcc::S16: return 2;
			case model_fourcc::F16: return 2;
			case model_fourcc::F32: return 4;
		}

		//!
		//!

		return 0;
	}

}