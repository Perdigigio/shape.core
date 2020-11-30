#ifndef SHAPE_CORE_VIDEO_D3D11_COMMON_HH__GUARD
#define SHAPE_CORE_VIDEO_D3D11_COMMON_HH__GUARD


#include <d3d11_1.h>
#include <dxgi1_2.h>

#include <winrt/base.h>

namespace shape
{
	namespace video
	{

		typedef winrt::com_ptr<ID3D11Device> D3D11Device;
		typedef winrt::com_ptr<ID3D11DeviceChild> D3D11DeviceChild;
		typedef winrt::com_ptr<ID3D11DeviceContext> D3D11DeviceContext;
		typedef winrt::com_ptr<ID3D11Resource> D3D11Resource;
		typedef winrt::com_ptr<ID3D11Buffer> D3D11Buffer;
		typedef winrt::com_ptr<ID3D11Texture1D> D3D11Texture1D;
		typedef winrt::com_ptr<ID3D11Texture2D> D3D11Texture2D;
		typedef winrt::com_ptr<ID3D11Texture3D> D3D11Texture3D;
		typedef winrt::com_ptr<ID3D11RenderTargetView> D3D11RenderTargetView;
		typedef winrt::com_ptr<ID3D11DepthStencilView> D3D11DepthStencilView;
		typedef winrt::com_ptr<ID3D11VertexShader> D3D11VertexShader;
		typedef winrt::com_ptr<ID3D11PixelShader> D3D11PixelShader;
		typedef winrt::com_ptr<ID3D11GeometryShader> D3D11GeometryShader;
		typedef winrt::com_ptr<ID3D11HullShader> D3D11HullShader;
		typedef winrt::com_ptr<ID3D11DomainShader> D3D11DomainShader;
		typedef winrt::com_ptr<ID3D11BlendState> D3D11BlendState;
		typedef winrt::com_ptr<ID3D11DepthStencilState> D3D11DepthStencilState;
		typedef winrt::com_ptr<ID3D11RasterizerState> D3D11RasterizerState;








		typedef winrt::com_ptr<IDXGIFactory> D3D11Factory;
		typedef winrt::com_ptr<IDXGIAdapter> D3D11Adapter;

		//!
		//! HELPER CLASS
		//!

		template<class T> struct crtp
		{
			inline T * parent() noexcept { return static_cast<T *>(this); }
		};

		/**
		 * @param offset
		 * @param length
		 */
		static inline D3D11_BOX make_range(UINT p_offset, UINT p_length) noexcept
		{
			//!
			//!

			return CD3D11_BOX(p_offset, 0, 0, p_offset + p_length, 1, 1);
		}

		static inline D3D11Device device(D3D11DeviceChild p_child)
		{
			D3D11Device l_device;

			if (p_child)
			{
				p_child->GetDevice(l_device.put());
			}

			//!
			//!

			return l_device;
		}

		/**
		 * @param ctx
		 * @param res
		 * @param sub
		 * @param map
		 * @param src
		 */
		static inline void* map(D3D11DeviceContext p_ctx, D3D11Resource p_res, D3D11_MAP p_map)
		{
			D3D11_MAPPED_SUBRESOURCE l_mapped;
			{
				//!
				//! CHECKED MAP
				//!

				winrt::check_hresult(p_ctx->Map(p_res.get(), 0, p_map, 0, &l_mapped));
			}

			//!
			//!

			return l_mapped.pData;
		}

		//!
		//!

	}
}

#endif