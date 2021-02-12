#include "asset_image_reader.hh"
#include "asset_image.hh"

//!
//!

namespace shape
{
	namespace details
	{
		static constexpr auto MAGIC = fourcc('I', 'M', 'G', ' ');

		static constexpr auto MAJOR = uint16_t(1);
		static constexpr auto MINOR = uint16_t(0);

		//!
		//!

		static inline bool check_version(uint16_t major, uint16_t minor) noexcept
		{
			if (major == details::MAJOR)
				return minor >= details::MINOR;

			//!
			//!
	
			return major > details::MAJOR;
		}
	}

	//!
	//!

	template<> std::istream & reader::read(std::istream &p_stream, cAssetImageData &p_image)
	{
		uint32_t l_magic;
		uint16_t l_major;
		uint16_t l_minor;

		uint32_t l_image_wth = 0;
		uint16_t l_image_hth = 0;
		uint16_t l_image_fmt = 0;

		if (p_stream)
		{
			reader::read(p_stream, l_magic);
			reader::read(p_stream, l_major);
			reader::read(p_stream, l_minor);
		}

		if (p_stream)
		{
			if (l_magic == details::MAGIC && details::check_version(l_major, l_minor))
			{
				reader::read(p_stream, l_image_wth);
				reader::read(p_stream, l_image_hth);
				reader::read(p_stream, l_image_fmt);
			}
			else
				p_stream.setstate(std::ios::failbit);
		}

		cAssetImageData l_image{ l_image_wth, l_image_hth, l_image_fmt };

		//!
		//!

		if (p_stream.read(static_cast<char *>(l_image.get_data()), l_image.get_length()))
		{
			//!
			//! READ BITMAP DATA
			//!

			std::swap(p_image, l_image);
		}

		//!
		//!

		return p_stream;
	}

} //! shape