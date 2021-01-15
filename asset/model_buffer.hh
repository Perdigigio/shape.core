#ifndef SHAPE_CORE_ASSET_MODEL_BUFFER_HH__GUARD
#define SHAPE_CORE_ASSET_MODEL_BUFFER_HH__GUARD

#include "../type.hh"
#include "../base.hh"

namespace shape
{

	struct model_buffer_name
	{
		static constexpr uint32_t pos = fourcc('p', 'o', 's', ' ');
		static constexpr uint32_t nor = fourcc('n', 'o', 'r', ' ');
		static constexpr uint32_t tex = fourcc('t', 'e', 'x', ' ');
		static constexpr uint32_t skn = fourcc('s', 'k', 'n', ' ');
		static constexpr uint32_t idx = fourcc('i', 'd', 'x', ' ');
	};

	struct model_buffer
	{
		uint32_t fmt;
		uint32_t num;
	};

	class cModelBuffer : private model_buffer
	{
	public:
		inline cModelBuffer(const model_buffer &p_desc = {}) noexcept : model_buffer(p_desc) {}

		inline cModelBuffer(uint32_t fmt, uint32_t num) noexcept
		{
			this->fmt = fmt;
			this->num = num;
		}

		//!
		//!
		//!

		inline uint32_t get_fmt() const noexcept { return this->fmt; }
		inline uint32_t get_num() const noexcept { return this->num; }

		//!
		//!

		size_t get_stride() const noexcept;
		size_t get_length() const noexcept;
	};

	//!
	//!

	template<class tag> typename buffer<tag>::type_t model_buffer_alloc(const cModelBuffer & p_buffer)
	{
		//!
		//!

		return buffer_alloc<tag>(p_buffer.get_length());
	}

	//!
	//!

	template<class T> static constexpr uint32_t model_buffer_fmt() noexcept { return 0; }

	//!
	//! FOURCC-TYPE ASSOC
	//!

	template<> constexpr uint32_t model_buffer_fmt<base_vtx::pos_t>() noexcept { return model_buffer_name::pos; }
	template<> constexpr uint32_t model_buffer_fmt<base_vtx::nor_t>() noexcept { return model_buffer_name::nor; }
	template<> constexpr uint32_t model_buffer_fmt<base_vtx::tex_t>() noexcept { return model_buffer_name::tex; }
	template<> constexpr uint32_t model_buffer_fmt<base_vtx::skn_t>() noexcept { return model_buffer_name::skn; }

	template<> constexpr uint32_t model_buffer_fmt<uint32_t>() noexcept { return model_buffer_name::idx; }


} //! shape

#endif
