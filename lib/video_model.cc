#include "video_model.hh"

namespace shape {
namespace video {

	cVideoModel::cVideoModel(uint32_t p_vtx, uint32_t p_idx, uint32_t p_fmt) :
		m_vtx(p_vtx),
		m_idx(p_idx),
		m_fmt(p_fmt)
	{
		if (!cBaseVertexBuffer::init())
			throw failure{};

		//!
		//! INIT MANDATORY BUFFERS
		//!

		cBaseVertexBuffer::realloc_pos(p_vtx, nullptr);
		cBaseVertexBuffer::realloc_idx(p_idx, nullptr);

		//! ----------------------------------------------------------------

		if (p_fmt & has_nor) cBaseVertexBuffer::realloc_nor(p_vtx, nullptr);
		if (p_fmt & has_tex) cBaseVertexBuffer::realloc_tex(p_vtx, nullptr);
		if (p_fmt & has_skn) cBaseVertexBuffer::realloc_skn(p_vtx, nullptr);
	}

	void cVideoModel::discard() noexcept
	{
		cBaseVertexBuffer::discard_pos();
		cBaseVertexBuffer::discard_idx();

		//! --------------------------------------------------

		if (m_fmt & has_nor) cBaseVertexBuffer::discard_nor();
		if (m_fmt & has_tex) cBaseVertexBuffer::discard_tex();
		if (m_fmt & has_skn) cBaseVertexBuffer::discard_skn();
	}

	void cVideoModel::dispose() noexcept
	{
		cBaseVertexBuffer::free();
	}

} //! shape::video
} //! shape