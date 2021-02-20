#ifndef SHAPE_CORE_ASSET_MODEL_HH__GUARD
#define SHAPE_CORE_ASSET_MODEL_HH__GUARD

#include "type.hh"
#include "base.hh"

namespace shape
{
	//!
	//! FLAGS
	//!

	struct asset_model_flags
	{
		static constexpr uint32_t has_nor = (1 << 0);
		static constexpr uint32_t has_tex = (1 << 1);
		static constexpr uint32_t has_skn = (1 << 2);
	};

	//!
	//!

	struct asset_model
	{
		uint32_t vtx;
		uint32_t idx;
		uint32_t fmt;

		//!
		//!

		static size_t get_length(asset_model const *, uint32_t) noexcept;
		static size_t get_stride(asset_model const *, uint32_t) noexcept;
	};

	//!
	//!

	class cAssetModel : private asset_model
	{
	public:
		inline cAssetModel(uint32_t p_vtx = {}, uint32_t p_idx = {}, uint32_t p_fmt = {}) noexcept
		{
			this->vtx = p_vtx;
			this->idx = p_idx;
			this->fmt = p_fmt;
		}

		inline bool has_pos() const noexcept { return this->vtx != 0; }
		inline bool has_idx() const noexcept { return this->idx != 0; }
		inline bool has_nor() const noexcept { return this->vtx != 0 && this->fmt & asset_model_flags::has_nor; }
		inline bool has_tex() const noexcept { return this->vtx != 0 && this->fmt & asset_model_flags::has_tex; }
		inline bool has_skn() const noexcept { return this->vtx != 0 && this->fmt & asset_model_flags::has_skn; }

		//!
		//! GETTERS
		//!

		inline size_t get_length(uint32_t p_buf) const noexcept { return asset_model::get_length(this, p_buf); }
		inline size_t get_stride(uint32_t p_buf) const noexcept { return asset_model::get_stride(this, p_buf); }

		//! ----------------------------------------------------------------------------------------------

		inline uint32_t get_vtx() const noexcept { return this->vtx; }
		inline uint32_t get_idx() const noexcept { return this->idx; }
		inline uint32_t get_fmt() const noexcept { return this->fmt; }
	};

	class cAssetModelData : public cAssetModel
	{
	public:
		inline cAssetModelData(uint32_t p_vtx = {}, uint32_t p_idx = {}, uint32_t p_fmt = {}) : cAssetModel(p_vtx, p_idx, p_fmt)
		{
			//!
			//!

			cAssetModelData::realloc();
		}

		void realloc();
		void dispose();

		//!
		//! GETTERS
		//!

		inline base_model::pos_t * get_pos_data() const noexcept { return static_cast<base_model::pos_t *>(m_pos.get()); }
		inline base_model::nor_t * get_nor_data() const noexcept { return static_cast<base_model::nor_t *>(m_nor.get()); }
		inline base_model::tex_t * get_tex_data() const noexcept { return static_cast<base_model::tex_t *>(m_tex.get()); }
		inline base_model::skn_t * get_skn_data() const noexcept { return static_cast<base_model::skn_t *>(m_skn.get()); }
		inline base_model::idx_t * get_idx_data() const noexcept { return static_cast<base_model::idx_t *>(m_idx.get()); }

	private:
		buffer<heap_t>::type_t m_idx;
		buffer<heap_t>::type_t m_pos;
		buffer<heap_t>::type_t m_nor;
		buffer<heap_t>::type_t m_tex;
		buffer<heap_t>::type_t m_skn;
	};

} //! shape

#endif
