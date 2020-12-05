#ifndef SHAPE_CORE_VIDEO_D3D11_BASEPARAM_HH__GUARD
#define SHAPE_CORE_VIDEO_D3D11_BASEPARAM_HH__GUARD

#include "common.hh"

namespace shape
{
	namespace video
	{
		template<class Concrete> class CoreVideoBaseParam : private crtp<Concrete>
		{
		public:
			typedef typename Concrete::model_t model_t;
			typedef typename Concrete::frame_t frame_t;
			typedef typename Concrete::param_t param_t;

			//!
			//!

			inline CoreVideoBaseParam(D3D11Device p_device)
			{
				const CD3D11_BUFFER_DESC l_model{ sizeof(model_t), D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE };
				const CD3D11_BUFFER_DESC l_frame{ sizeof(frame_t), D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE };
				const CD3D11_BUFFER_DESC l_param{ sizeof(param_t), D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE };

				//!
				//!

				winrt::check_hresult(p_device->CreateBuffer(&l_model, NULL, m_model.put()));
				winrt::check_hresult(p_device->CreateBuffer(&l_frame, NULL, m_frame.put()));
				winrt::check_hresult(p_device->CreateBuffer(&l_param, NULL, m_param.put()));
			}

			void attach(D3D11DeviceContext);
			void detach(D3D11DeviceContext);

			//!
			//! GETTERS
			//!

			inline const D3D11Buffer& getModel() const noexcept { return m_model; }
			inline const D3D11Buffer& getFrame() const noexcept { return m_frame; }
			inline const D3D11Buffer& getParam() const noexcept { return m_param; }

		private:
			D3D11Buffer m_model; 
			D3D11Buffer m_frame;
			D3D11Buffer m_param;
		};

		template<class Concrete> void CoreVideoBaseParam<Concrete>::attach(D3D11DeviceContext p_context)
		{
			ID3D11Buffer * const l_buffers[] =
			{
				m_model.get(),
				m_frame.get(),
				m_param.get()
			};

			//!
			//!

			p_context->VSSetConstantBuffers(0, 3, l_buffers);
			p_context->PSSetConstantBuffers(0, 3, l_buffers);
		}

		template<class Concrete> void CoreVideoBaseParam<Concrete>::detach(D3D11DeviceContext p_context)
		{
			ID3D11Buffer * const l_buffers[] =
			{
				nullptr,
				nullptr,
				nullptr
			};

			//!
			//!

			p_context->VSSetConstantBuffers(0, 3, l_buffers);
			p_context->PSSetConstantBuffers(0, 3, l_buffers);
		}

	}
}

#endif