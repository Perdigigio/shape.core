#ifndef SHAPE_CORE_ASSET_IMAGE_HH__GUARD
#define SHAPE_CORE_ASSET_IMAGE_HH__GUARD

#include "../type.hh"
#include "../base.hh"

namespace shape
{
	constexpr uuid_t IID_CoreImage = { 0x61b6c2ed, 0x36b3, 0x4d34, 0xba77, 0x676b11cb8b69 };

	//!
	//! CORE IMAGE
	//!

	struct CoreImage
	{
	public:
		template<class Reader, class Output> Output& load(Output&) noexcept;
		template<class Reader, class Output> Output& save(Output&) noexcept;

		//!
		//! GETTERS
		//!

		inline uint32_t getFormat() const noexcept { return m_format; }
		inline uint32_t getStride() const noexcept { return m_stride; }
		inline uint32_t getLength() const noexcept { return m_length; }
		inline uint16_t getW() const noexcept { return m_w; }
		inline uint16_t getH() const noexcept { return m_h; }

	private:
		uint32_t m_format;
		uint32_t m_stride;
		uint32_t m_length;
		uint16_t m_w;
		uint16_t m_h;
	};

	//!
	//!

	template<class Reader, class Output> Output& CoreImage::load(Output& p_source) noexcept
	{
		if (Reader::getFormat(p_source, IID_CoreImage))
		{
			Reader::get(p_source, m_format);
			Reader::get(p_source, m_length);
			Reader::get(p_source, m_stride);
			Reader::get(p_source, m_w);
			Reader::get(p_source, m_h);
		}

		//!
		//!

		return p_source;
	}

	template<class Writer, class Output> Output& CoreImage::save(Output& p_output) noexcept
	{
		if (Writer::setFormat(p_output, IID_CoreImage))
		{
			Writer::set(p_output, m_format);
			Writer::set(p_output, m_length);
			Writer::set(p_output, m_stride);
			Writer::set(p_output, m_w);
			Writer::set(p_output, m_h);
		}

		//!
		//!

		return p_output;
	}

}

#endif