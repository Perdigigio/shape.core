#include "asset_image_writer.hh"
#include "asset_image.hh"

namespace shape
{
	namespace details
	{
		static constexpr auto MAGIC = fourcc('I', 'M', 'G', ' ');

		static constexpr auto MAJOR = uint16_t(1);
		static constexpr auto MINOR = uint16_t(0);
	}

	template<> std::ostream & writer::write(std::ostream &p_stream, const cAssetImageData &p_image)
	{
		writer::write(p_stream, details::MAGIC);
		writer::write(p_stream, details::MAJOR);
		writer::write(p_stream, details::MINOR);

		if (p_stream)
		{
			writer::write(p_stream, p_image.get_wth());
			writer::write(p_stream, p_image.get_hth());
			writer::write(p_stream, p_image.get_fmt());
		}

		if (p_stream)
			p_stream.write(static_cast<const char *>(p_image.get_data()), p_image.get_length());

		//!
		//!

		return p_stream;
	}

	
}