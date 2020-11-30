#ifndef SHAPE_CORE_VIDEO_D3D11_BASESHADER_HH__GUARD
#define SHAPE_CORE_VIDEO_D3D11_BASESHADER_HH__GUARD

#include "common.hh"

namespace shape
{
	namespace video
	{
		template<class Concrete> class CoreVideoBaseShader : private crtp<Concrete>
		{
		public:
			struct program_t
			{
				std::pair<SIZE_T, const void *> vshader;
				std::pair<SIZE_T, const void *> pshader;
			};

			//!
			//!

			inline CoreVideoBaseShader(D3D11Device p_device, const program_t& p_program, UINT p_length, const D3D11_INPUT_ELEMENT_DESC * p_layout)
			{
				auto l_vshaderLength = std::get<0>(p_program.vshader);
				auto l_pshaderLength = std::get<0>(p_program.pshader);
				auto l_vshader = std::get<1>(p_program.vshader);
				auto l_pshader = std::get<1>(p_program.pshader);

				//!
				//!

				winrt::check_hresult(p_device->CreateInputLayout(p_layout, p_length, l_vshader, l_vshaderLength, m_vlayout.put()));
				winrt::check_hresult(p_device->CreateVertexShader(l_vshader, l_vshaderLength, NULL, m_vshader.put()));
				winrt::check_hresult(p_device->CreatePixelShader(l_pshader, l_pshaderLength, NULL, m_pshader.put()));
			}

			void attach(D3D11DeviceContext);
			void detach(D3D11DeviceContext);

			//!
			//! GETTERS
			//!

			inline D3D11InputLayout getVLayout() const noexcept { return m_vlayout; }
			inline D3D11VertexShader getVShader() const noexcept { return m_vshader; }
			inline D3D11PixelShader getPShader() const noexcept { return m_pshader; }

		private:
			D3D11InputLayout m_vlayout;
			D3D11VertexShader m_vshader;
			D3D11PixelShader m_pshader;
		};

		template<class Concrete> void CoreVideoBaseShader<Concrete>::attach(D3D11DeviceContext p_context)
		{
			p_context->IASetInputLayout(m_vlayout.get());
			p_context->VSSetShader(m_vshader.get(), NULL, 0);
			p_context->PSSetShader(m_pshader.get(), NULL, 0);
		}

		template<class Concrete> void CoreVideoBaseShader<Concrete>::detach(D3D11DeviceContext p_context)
		{
			p_context->IASetInputLayout(NULL);
			p_context->VSSetShader(NULL, NULL, 0);
			p_context->PSSetShader(NULL, NULL, 0);
		}

	}
}

#endif