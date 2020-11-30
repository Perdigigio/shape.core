#ifndef SHAPE_CORE_VIDEO_D3D11_BASEMODELIBUFFER_HH__GUARD
#define SHAPE_CORE_VIDEO_D3D11_BASEMODELVBUFFER_HH__GUARD

#include "common.hh"

namespace shape
{
	namespace video
	{
		template<class Concrete> class CoreVideoBaseModelIBuffer
		{
		public:
			//!
			//!

			inline CoreVideoBaseModelIBuffer(D3D11Device p_device, ULONG p_length)
			{
				const CD3D11_BUFFER_DESC l_idx
				{
					p_length * sizeof(Concrete::idx_t), D3D11_BIND_INDEX_BUFFER
				};


				//!
				//!

				winrt::check_hresult(p_device->CreateBuffer(&l_idx, NULL, m_idx.put()));

			}

			void attach(D3D11DeviceContext);
			void detach(D3D11DeviceContext);

			//!
			//! GETTERS
			//!

			inline const D3D11Buffer& getIdx() const noexcept { return m_idx; }

		private:
			D3D11Buffer m_idx; 
		};

		//!
		//! MEMBER FUNCTIONS
		//!

		template<class Concrete> void CoreVideoBaseModelIBuffer<Concrete>::attach(D3D11DeviceContext p_context)
		{
			//!
			//!

			p_context->IASetIndexBuffer(m_idx.get(), Concrete::getIFormat(), 0);
		}

		template<class Concrete> void CoreVideoBaseModelIBuffer<Concrete>::detach(D3D11DeviceContext p_context)
		{
			//!
			//!

			p_context->IASetIndexBuffer(NULL, DXGI_FORMAT_UNKNOWN, 0);
		}

		

	}
}

#endif