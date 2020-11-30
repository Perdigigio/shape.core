#ifndef SHAPE_CORE_VIDEO_D3D11_BASEVERTEXBUFFER_HH__GUARD
#define SHAPE_CORE_VIDEO_D3D11_BASEVERTEXBUFFER_HH__GUARD

#include "common.hh"

namespace shape
{
	namespace video
	{
		template<class Concrete> class CoreVideoBaseModelVBuffer
		{
		public:
			typedef typename Concrete::pos_t pos_t;
			typedef typename Concrete::nor_t nor_t;
			typedef typename Concrete::tex_t tex_t;

			//!
			//!

			inline CoreVideoBaseModelVBuffer(D3D11Device p_device, ULONG p_length)
			{
				const CD3D11_BUFFER_DESC l_pos { p_length * sizeof(pos_t), D3D11_BIND_VERTEX_BUFFER };
				const CD3D11_BUFFER_DESC l_nor { p_length * sizeof(nor_t), D3D11_BIND_VERTEX_BUFFER };
				const CD3D11_BUFFER_DESC l_tex { p_length * sizeof(tex_t), D3D11_BIND_VERTEX_BUFFER };


				//!
				//!

				winrt::check_hresult(p_device->CreateBuffer(&l_pos, NULL, m_pos.put()));
				winrt::check_hresult(p_device->CreateBuffer(&l_nor, NULL, m_nor.put()));
				winrt::check_hresult(p_device->CreateBuffer(&l_tex, NULL, m_tex.put()));

			}

			void upload(D3D11DeviceContext);
			void attach(D3D11DeviceContext);
			void detach(D3D11DeviceContext);

			//!
			//! GETTERS
			//!

			inline const D3D11Buffer& getPos() const noexcept { return m_pos; }
			inline const D3D11Buffer& getNor() const noexcept { return m_nor; }
			inline const D3D11Buffer& getTex() const noexcept { return m_tex; }

		private:
			D3D11Buffer m_pos; 
			D3D11Buffer m_nor;
			D3D11Buffer m_tex;
		};

		//!
		//! MEMBER FUNCTIONS
		//!

		template<class Concrete> void CoreVideoBaseModelVBuffer<Concrete>::upload(D3D11DeviceContext p_context)
		{
			const D3D11_BOX l_offsets[] =
			{
				make_range(0, sizeof(pos_t) * parent()->getLength()),
				make_range(0, sizeof(nor_t) * parent()->getLength()),
				make_range(0, sizeof(tex_t) * parent()->getLength()),
			};

			//!
			//!

			p_context->UpdateSubresource(m_pos.get(), 0, &l_offsets[0], parent()->getPosData());
			p_context->UpdateSubresource(m_nor.get(), 0, &l_offsets[1], parent()->getNorData());
			p_context->UpdateSubresource(m_tex.get(), 0, &l_offsets[2], parent()->getTexData());
		}

		template<class Concrete> void CoreVideoBaseModelVBuffer<Concrete>::attach(D3D11DeviceContext p_context)
		{
			ID3D11Buffer * const l_buffers[] =
			{
				m_pos.get(),
				m_nor.get(),
				m_tex.get()
			};

			const UINT l_offsets[] = { 0, 0, 0 };
			const UINT l_strides[] =
			{
				sizeof(pos_t),
				sizeof(nor_t),
				sizeof(tex_t)
			};

			//!
			//!

			p_context->IASetVertexBuffers(0, 3, l_buffers, l_strides, l_offsets);
		}

		template<class Concrete> void CoreVideoBaseModelVBuffer<Concrete>::detach(D3D11DeviceContext p_context)
		{
			ID3D11Buffer * const l_buffers[] =
			{
				nullptr,
				nullptr,
				nullptr
			};

			const UINT l_offsets[] = { 0, 0, 0 };
			const UINT l_strides[] = { 0, 0 ,0 };

			//!
			//!

			p_context->IASetVertexBuffers(0, 3, l_buffers, l_strides, l_offsets);
		}

		

	}
}

#endif