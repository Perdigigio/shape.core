#ifndef SHAPE_CORE_ASSET_SOUND_HH__GUARD
#define SHAPE_CORE_ASSET_SOUND_HH__GUARD

#include "../type.hh"
#include "../base.hh"

namespace shape
{
	constexpr uuid_t IID_CoreSound = { 0xfb9500a7, 0x0a17, 0x49b7, 0x9d00, 0x108ea156be51 };

	//!
	//! CORE SOUND
	//!

	class CoreSound
	{
	public:
		template<class Reader, class Source> Source& load(Source&);
		template<class Writer, class Output> Output& save(Output&);

		//!
		//! GETTERS
		//!

		inline uint32_t getFormat() const { return m_format; }
		inline uint32_t getLength() const { return m_length; }
		inline uint32_t getStride() const { return m_stride; }
		inline uint32_t getSampleFrequency() const { return m_sampleFrequency; }

	private:
		uint32_t m_format;
		uint32_t m_stride;
		uint32_t m_length;
		uint32_t m_sampleFrequency;
	};

	//!
	//!

	template<class Reader, class Source> Source& CoreSound::load(Source& p_source)
	{
		if (Reader::getFormat(p_source, IID_CoreSound))
		{
			Reader::get(p_source, m_format);
			Reader::get(p_source, m_stride);
			Reader::get(p_source, m_length);
			Reader::get(p_source, m_sampleFrequency);
		}

		//!
		//!

		return p_source;
	}

	template<class Writer, class Output> Output& CoreSound::save(Output& p_output)
	{
		if (Writer::setFormat(p_output, IID_CoreSound))
		{
			Writer::set(p_outset, m_format);
			Writer::set(p_outset, m_stride);
			Writer::set(p_outset, m_length);
			Writer::set(p_outset, m_sampleFrequency);
		}

		//!
		//!

		return p_output;
	}

}

#endif