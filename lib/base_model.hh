#ifndef SHAPE_BASE_MODEL_HH__GUARD
#define SHAPE_BASE_MODEL_HH__GUARD

#include "type.hh"
#include "base.hh"

namespace shape
{
	//!
	//! FLAGS
	//!

	struct base_model_flag
	{
		static constexpr uint32_t has_nor = (1 << 0);
		static constexpr uint32_t has_tex = (1 << 1);
		static constexpr uint32_t has_skn = (1 << 2);
	};

	struct base_model_pos { uint32_t dummy[3]; }; //! 3x REAL
	struct base_model_nor { uint16_t dummy[8]; }; //! 4x WORD NORM, 4x WORD NORM
	struct base_model_tex { uint16_t dummy[4]; }; //! 2x HALF, 2x HALF
	struct base_model_skn { uint32_t dummy[2]; }; //! 4x BYTE, 4x BYTE NORM
	struct base_model_idx { uint32_t dummy[1]; }; //! 1x UINT

	struct base_model_fourcc
	{
		static constexpr auto pos = fourcc('p', 'o', 's', ' ');
		static constexpr auto nor = fourcc('n', 'o', 'r', ' ');
		static constexpr auto tex = fourcc('t', 'e', 'x', ' ');
		static constexpr auto skn = fourcc('s', 'k', 'n', ' ');
		static constexpr auto idx = fourcc('i', 'd', 'x', ' ');
	};

	//!
	//!

	struct base_model
	{
		uint32_t vtx;
		uint32_t idx;
		uint32_t fmt;

		//!
		//!

		static size_t get_length(base_model const *, uint32_t) noexcept;
		static size_t get_stride(base_model const *, uint32_t) noexcept;
	};

	//!
	//!

	class cBaseModel : private base_model
	{
	public:
		inline cBaseModel() noexcept
		{
			this->vtx = {};
			this->idx = {};
			this->fmt = {};
		}

		inline cBaseModel(uint32_t p_vtx, uint32_t p_idx, uint32_t p_fmt) noexcept
		{
			this->vtx = p_vtx;
			this->idx = p_idx;
			this->fmt = p_fmt;
		}

		inline bool has_pos() const noexcept { return this->vtx != 0; }
		inline bool has_idx() const noexcept { return this->idx != 0; }
		inline bool has_nor() const noexcept { return this->vtx != 0 && this->fmt & base_model_flag::has_nor; }
		inline bool has_tex() const noexcept { return this->vtx != 0 && this->fmt & base_model_flag::has_tex; }
		inline bool has_skn() const noexcept { return this->vtx != 0 && this->fmt & base_model_flag::has_skn; }

		//!
		//! GETTERS
		//!

		inline size_t get_length(uint32_t p_buf) const noexcept { return base_model::get_length(this, p_buf); }
		inline size_t get_stride(uint32_t p_buf) const noexcept { return base_model::get_stride(this, p_buf); }

		//! ----------------------------------------------------------------------------------------------

		inline uint32_t get_vtx() const noexcept { return this->vtx; }
		inline uint32_t get_idx() const noexcept { return this->idx; }
		inline uint32_t get_fmt() const noexcept { return this->fmt; }
	};

	template<class mtag> class cBaseModelData : public cBaseModel
	{
	public:
		cBaseModelData(const cBaseModel &p_mod) : cBaseModel{ p_mod }
		{
			m_pos = buffer_alloc<mtag>(cBaseModel::get_length(base_model_fourcc::pos));
			m_idx = buffer_alloc<mtag>(cBaseModel::get_length(base_model_fourcc::idx));

			//!
			//! EXTRA BUFFERS
			//!

			if (has_nor()) m_nor = buffer_alloc<mtag>(cBaseModel::get_length(base_model_fourcc::nor));
			if (has_tex()) m_tex = buffer_alloc<mtag>(cBaseModel::get_length(base_model_fourcc::tex));
			if (has_skn()) m_skn = buffer_alloc<mtag>(cBaseModel::get_length(base_model_fourcc::skn));
		}

		//! --------------------------------------------------------------------------------------------------------------

		inline base_model_pos * get_pos_buffer() const noexcept { return static_cast<base_model_pos *>(m_pos.get()); }
		inline base_model_nor * get_nor_buffer() const noexcept { return static_cast<base_model_nor *>(m_nor.get()); }
		inline base_model_tex * get_tex_buffer() const noexcept { return static_cast<base_model_tex *>(m_tex.get()); }
		inline base_model_skn * get_skn_buffer() const noexcept { return static_cast<base_model_skn *>(m_skn.get()); }
		inline base_model_idx * get_idx_buffer() const noexcept { return static_cast<base_model_idx *>(m_idx.get()); }

	private:
		typename buffer<mtag>::type_t m_pos;
		typename buffer<mtag>::type_t m_idx;
		typename buffer<mtag>::type_t m_nor;
		typename buffer<mtag>::type_t m_tex;
		typename buffer<mtag>::type_t m_skn;
	};

} //! shape

#endif
