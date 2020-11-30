#ifndef SHAPE_CORE_VIDEO_D3D11_BASEPIPELINE_HH__GUARD
#define SHAPE_CORE_VIDEO_D3D11_BASEPIPELINE_HH__GUARD

#include "common.hh"

namespace shape
{
	namespace video
	{


		template<class Concrete> class CoreVideoBaseState : private crtp<Concrete>
		{
		public:
			//!
			//!

			inline CoreVideoBaseState(D3D11Device p_device)
			{
				winrt::check_hresult(p_device->CreateRasterizerState(Concrete::getRasterizerDesc(), m_rasterizer.put()));
				winrt::check_hresult(p_device->CreateDepthStencilState(Concrete::getDepthStencilDesc(), m_depthStencil.put()));
				winrt::check_hresult(p_device->CreateBlendState(Concrete::getBlendDesc(), m_blend.put()));
			}

			void attach(D3D11DeviceContext);
			void detach(D3D11DeviceContext);

			//!
			//! GETTERS
			//!

			inline D3D11RasterizerState getRasterizer() const noexcept { return m_rasterizer; }
			inline D3D11DepthStencilState getDepthStencil() const noexcept { return m_depthStencil; }
			inline D3D11BlendState getBlend() const noexcept { return m_blend; }

		private:
			D3D11RasterizerState m_rasterizer;
			D3D11DepthStencilState m_depthStencil;
			D3D11BlendState m_blend;
		};

		template<class Concrete> void CoreVideoBaseState<Concrete>::attach(D3D11DeviceContext p_context)
		{
			p_context->RSSetState(m_rasterizer.get());
			p_context->OMSetDepthStencilState(m_depthStencil.get(), parent()->getStencilRef());
			p_context->OMSetBlendState(m_blend.get(), parent()->getBlendFactor(), parent()->getSampleMask());
		}

		template<class Concrete> void CoreVideoBaseState<Concrete>::detach(D3D11DeviceContext p_context)
		{
			p_context->RSSetState(NULL));
			p_context->OMSetDepthStencilState(NULL, 0);
			p_context->OMSetBlendState(NULL, NULL, 0xFFFFFFFF);
		}

	}
}

#endif