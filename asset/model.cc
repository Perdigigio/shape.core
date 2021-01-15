#include "model.hh"

namespace shape
{

	void cModel::realloc()
	{
		m_pos = model_buffer_alloc<heap_t>(this->pos);
		m_nor = model_buffer_alloc<heap_t>(this->nor);
		m_tex = model_buffer_alloc<heap_t>(this->tex);
		m_skn = model_buffer_alloc<heap_t>(this->skn);
		m_idx = model_buffer_alloc<heap_t>(this->idx);
	}

	void cModel::dispose()
	{
		m_idx.release();
		m_skn.release();
		m_tex.release();
		m_nor.release();
		m_pos.release();
	}

} //! shape