#ifndef SHAPE_CORE_ASSET_MODEL_HH__GUARD
#define SHAPE_CORE_ASSET_MODEL_HH__GUARD

#include "../type.hh"
#include "../base.hh"

namespace shape
{
	constexpr uuid_t IID_CoreAssetModel = { 0x1cd8ed99, 0x2293, 0x496e, 0xae9d, 0x62e0f6beea3a };

	//!
	//! CORE MODEL
	//!

	class CoreAssetModel
	{
	public:
		inline CoreAssetModel()
		{
			m_vertsCount = uint32_t();
			m_facesCount = uint32_t();
			m_edgesCount = uint32_t();
		}

		/**
		 * @param vertsCount Total model vertex count
		 * @param facesCount Total model faces count
		 * @param edgesCount Per face edge count
		 */
		inline CoreAssetModel(uint32_t p_vertsCount, uint32_t p_facesCount, uint32_t p_edgesCount)
		{
			m_vertsCount = p_vertsCount;
			m_facesCount = p_facesCount;
			m_edgesCount = p_edgesCount;
		}

		template<class Reader, class Output> Output& load(Output&) noexcept;
		template<class Reader, class Output> Output& save(Output&) noexcept;

		//!
		//! GETTERS
		//!

		uint32_t getVertsCount() const noexcept { return m_vertsCount; }
		uint32_t getFacesCount() const noexcept { return m_facesCount; }
		uint32_t getEdgesCount() const noexcept { return m_edgesCount; }

	private:
		uint32_t m_vertsCount;
		uint32_t m_facesCount;
		uint32_t m_edgesCount;
	};

	//!
	//!

	template<class Reader, class Source> Source& CoreAssetModel::load(Source& p_source) noexcept
	{
		if (Reader::getFormat(p_source, IID_CoreAssetModel))
		{
			Reader::get(p_source, m_vertsCount);
			Reader::get(p_source, m_facesCount);
			Reader::get(p_source, m_edgesCount);
		}

		//!
		//!

		return Reader::end(p_source);
	}

	template<class Writer, class Output> Output& CoreAssetModel::save(Output& p_output) noexcept
	{
		if (Writer::setFormat(p_output, IID_CoreAssetModel))
		{
			Writer::set(p_output, m_vertsCount);
			Writer::set(p_output, m_facesCount);
			Writer::set(p_output, m_edgesCount);
		}

		//!
		//!

		return Writer::end(p_output);
	}
}

#endif