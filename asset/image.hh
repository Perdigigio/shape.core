#ifndef SHAPE_CORE_ASSET_IMAGE_HH__GUARD
#define SHAPE_CORE_ASSET_IMAGE_HH__GUARD

#include "../type.hh"
#include "../base.hh"

namespace shape
{
	constexpr uuid_t IID_CoreAssetImage = { 0x61b6c2ed, 0x36b3, 0x4d34, 0xba77, 0x676b11cb8b69 };

	//!
	//! CORE IMAGE
	//!

	class CoreAssetImage
	{
	public:
		inline CoreAssetImage() noexcept
		{
			m_levels = uint16_t();
			m_layers = uint16_t();
			m_w = uint16_t();
			m_h = uint16_t();
			m_d = uint16_t();
		}

		/**
		 * @param levels
		 * @param layers
		 * @param w
		 * @param h
		 * @param d
		 */
		inline CoreAssetImage(uint16_t p_levels, uint16_t p_layers, uint16_t p_w, uint16_t p_h, uint16_t p_d) noexcept
		{
			m_levels = p_levels;
			m_layers = p_layers;
			m_w = p_w;
			m_h = p_h;
			m_d = p_d;
		}

		template<class Reader, class Output> Output& load(Output&) noexcept;
		template<class Reader, class Output> Output& save(Output&) noexcept;

		//!
		//! GETTERS
		//!

		inline uint16_t getLevels() const noexcept { return m_levels; }
		inline uint16_t getLayers() const noexcept { return m_layers; }
		inline uint16_t getW() const noexcept { return m_w; }
		inline uint16_t getH() const noexcept { return m_h; }
		inline uint16_t getD() const noexcept { return m_d; }

	private:
		uint16_t m_levels;
		uint16_t m_layers;
		uint16_t m_w;
		uint16_t m_h;
		uint16_t m_d;
	};

	//!
	//!

	template<class Reader, class Output> Output& CoreAssetImage::load(Output& p_source) noexcept
	{
		if (Reader::getFormat(p_source, IID_CoreAssetImage))
		{
			Reader::get(p_source, m_levels);
			Reader::get(p_source, m_layers);
			Reader::get(p_source, m_w);
			Reader::get(p_source, m_h);
			Reader::get(p_source, m_d);
		}

		//!
		//!

		return Reader::end(p_source);
	}

	template<class Writer, class Output> Output& CoreAssetImage::save(Output& p_output) noexcept
	{
		if (Writer::setFormat(p_output, IID_CoreAssetImage))
		{
			Writer::set(p_output, m_levels);
			Writer::set(p_output, m_layers);
			Writer::set(p_output, m_w);
			Writer::set(p_output, m_h);
			Writer::set(p_output, m_d);
		}

		//!
		//!

		return Writer::end(p_output);
	}

}

#endif