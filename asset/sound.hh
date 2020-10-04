#ifndef SHAPE_CORE_ASSET_SOUND_HH__GUARD
#define SHAPE_CORE_ASSET_SOUND_HH__GUARD

#include "../type.hh"
#include "../base.hh"

namespace shape
{
	constexpr uuid_t IID_CoreAssetSound = { 0xfb9500a7, 0x0a17, 0x49b7, 0x9d00, 0x108ea156be51 };

	//!
	//! CORE SOUND
	//!

	class CoreAssetSound
	{
	public:
		inline CoreAssetSound()
		{
			m_format = uint32_t();
			m_length = uint32_t();
			m_stride = uint32_t();
			m_sampleFrequency = uint32_t();
		}

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

	template<class Reader, class Source> Source& CoreAssetSound::load(Source& p_source)
	{
		if (Reader::getFormat(p_source, IID_CoreAssetSound))
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

	template<class Writer, class Output> Output& CoreAssetSound::save(Output& p_output)
	{
		if (Writer::setFormat(p_output, IID_CoreAssetSound))
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