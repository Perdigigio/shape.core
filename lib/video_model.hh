#ifndef SHAPE_VIDEO_MODEL_HH__GUARD
#define SHAPE_VIDEO_MODEL_HH__GUARD

#include "video_gl_base_vertex.hh"
#include "video_gl_base_vertex_buffers.hh"

#include "asset_model.hh"

namespace shape {
namespace video {

	class cVideoModel : public cAssetModel
	{
	public:
		cVideoModel();
		cVideoModel(const cAssetModel &);
		cVideoModel(const cAssetModelData &);

		//! -------------------------------------------------------

		inline const cBaseVertexBuffers * operator->() const noexcept
		{
			return &m_buffer;
		}

		//! -------------------------------------------------------

		void discard();
		void dispose();

	private:
		cBaseVertexBuffers m_buffer;
	};

	//!
	//!

	template<class Source> static void upload(cVideoModel &p_model, const Source &p_source) noexcept
	{
		// p_model.update_pos(0, p_source.get_vtx(), p_source.get_pos_data());
		// p_model.update_nor(0, p_source.get_vtx(), p_source.get_nor_data());
		// p_model.update_tex(0, p_source.get_vtx(), p_source.get_tex_data());
		// p_model.update_skn(0, p_source.get_vtx(), p_source.get_skn_data());
		// p_model.update_idx(0, p_source.get_idx(), p_source.get_idx_data());
	}

} //! shape::video
} //! shape

#endif