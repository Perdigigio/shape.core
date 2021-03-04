#include "video_model.hh"

namespace shape {
namespace video {

	cVideoModel::cVideoModel() {}

	cVideoModel::cVideoModel(const cAssetModel &p_asset) : cAssetModel{ p_asset }
	{
		if (m_buffer.init())
		{
			if (p_asset.has_pos()) m_buffer.realloc_pos(p_asset.get_vtx(), nullptr);
			if (p_asset.has_nor()) m_buffer.realloc_nor(p_asset.get_vtx(), nullptr);
			if (p_asset.has_tex()) m_buffer.realloc_tex(p_asset.get_vtx(), nullptr);
			if (p_asset.has_skn()) m_buffer.realloc_skn(p_asset.get_vtx(), nullptr);
			if (p_asset.has_idx()) m_buffer.realloc_idx(p_asset.get_idx(), nullptr);
		}
		else
			throw failure{};
	}

	cVideoModel::cVideoModel(const cAssetModelData &p_asset) : cAssetModel{ p_asset }
	{
		if (m_buffer.init())
		{
			if (p_asset.has_pos()) m_buffer.realloc_pos(p_asset.get_vtx(), p_asset.get_pos_data());
			if (p_asset.has_nor()) m_buffer.realloc_nor(p_asset.get_vtx(), p_asset.get_nor_data());
			if (p_asset.has_tex()) m_buffer.realloc_tex(p_asset.get_vtx(), p_asset.get_tex_data());
			if (p_asset.has_skn()) m_buffer.realloc_skn(p_asset.get_vtx(), p_asset.get_skn_data());
			if (p_asset.has_idx()) m_buffer.realloc_idx(p_asset.get_idx(), p_asset.get_idx_data());
		}
		else
			throw failure{};
	}


} //! shape::video
} //! shape