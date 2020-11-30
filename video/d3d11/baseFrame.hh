#ifndef SHAPE_CORE_VIDEO_D3D11_BASEFRAME_HH__GUARD
#define SHAPE_CORE_VIDEO_D3D11_BASEFRAME_HH__GUARD

#include "common.hh"

namespace shape
{
	namespace video
	{
		template<class Concrete> class CoreVideoBaseFrame
		{
		public:
			//!
			//!

			inline CoreVideoBaseFrame(D3D11Device p_device, UINT p_w, UINT p_h, UINT p_msaa = 1)
			{
				const CD3D11_TEXTURE2D_DESC l_color{ Concrete::getColorFmt(), p_w, p_h, 1, 1, D3D11_BIND_RENDER_TARGET, D3D11_USAGE_DEFAULT, 0, p_msaa };
				const CD3D11_TEXTURE2D_DESC l_depth{ Concrete::getDepthFmt(), p_w, p_h, 1, 1, D3D11_BIND_DEPTH_STENCIL, D3D11_USAGE_DEFAULT, 0, p_msaa };

				//!
				//!

				winrt::check_hresult(p_device->CreateTexture2D(&l_color, NULL, m_color.put()));
				winrt::check_hresult(p_device->CreateTexture2D(&l_depth, NULL, m_depth.put()));
				winrt::check_hresult(p_device->CreateRenderTargetView(m_color.get(), NULL, m_colorView.put()));
				winrt::check_hresult(p_device->CreateDepthStencilView(m_depth.get(), NULL, m_depthView.put()));
			}

			void attach(D3D11DeviceContext);
			void detach(D3D11DeviceContext);

			//!
			//! GETTERS
			//!

			inline D3D11Texture2D getColor() const noexcept { return m_color; }
			inline D3D11Texture2D getDepth() const noexcept { return m_depth; }
			inline D3D11RenderTargetView getColorView() const noexcept { return m_colorView; }
			inline D3D11DepthStencilView getDepthView() const noexcept { return m_depthView; }

		private:
			D3D11Texture2D m_color;
			D3D11Texture2D m_depth;
			D3D11RenderTargetView m_colorView;
			D3D11DepthStencilView m_depthView;
		};

		template<class Concrete> void CoreVideoBaseFrame<Concrete>::attach(D3D11DeviceContext p_context)
		{
			ID3D11RenderTargetView * const l_colorView[] =
			{
				m_colorView.get()
			};

			//!
			//!

			p_context->OMSetRenderTargets(1, l_colorView, m_depthView.get());
		}

		template<class Concrete> void CoreVideoBaseFrame<Concrete>::detach(D3D11DeviceContext p_context)
		{
			//!
			//!

			p_context->OMSetRenderTargets(0, NULL, NULL);
		}

	}
}

#endif