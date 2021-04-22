#include "base_image_tga.hh"

namespace shape
{

	struct tga_header
	{
		char id_length;
		char cmap_type;
		char bmap_type;
		short int cmap_xorigin;
		short int cmap_clength;
		char cmap_depth;
		short int bmap_xorigin;
		short int bmap_yorigin;
		short int bmap_w;
		short int bmap_h;
		char bmap_format;
		char desc;
	};

	static tga_header read_tga(const cBaseStream &p_stream) noexcept
	{
		tga_header l_tga;

		//!
		//! TGA
		//!

		std::fread(&l_tga.id_length,    1, 1, p_stream.get_handle());
		std::fread(&l_tga.cmap_type,    1, 1, p_stream.get_handle());
		std::fread(&l_tga.bmap_type,    1, 1, p_stream.get_handle());
		std::fread(&l_tga.cmap_xorigin, 2, 1, p_stream.get_handle());
		std::fread(&l_tga.cmap_clength, 2, 1, p_stream.get_handle());
		std::fread(&l_tga.cmap_depth,   1, 1, p_stream.get_handle());
		std::fread(&l_tga.bmap_xorigin, 2, 1, p_stream.get_handle());
		std::fread(&l_tga.bmap_yorigin, 2, 1, p_stream.get_handle());
		std::fread(&l_tga.bmap_w,       2, 1, p_stream.get_handle());
		std::fread(&l_tga.bmap_h,       2, 1, p_stream.get_handle());
		std::fread(&l_tga.bmap_format,  1, 1, p_stream.get_handle());
		std::fread(&l_tga.desc,         1, 1, p_stream.get_handle());

		//!
		//!

		return l_tga;
	}

	//!
	//!

	static cBaseImage read_img(const cBaseStream &p_stream) noexcept
	{
		const auto l_bmp = read_tga(p_stream);

		const auto l_wth = static_cast<uint32_t>(l_bmp.bmap_w < 0 ? ~l_bmp.bmap_w + 1 : l_bmp.bmap_w);
		const auto l_hth = static_cast<uint32_t>(l_bmp.bmap_h < 0 ? ~l_bmp.bmap_h + 1 : l_bmp.bmap_h);

		//!
		//!

		if (p_stream.good() && l_bmp.bmap_type == 2)
		{
			switch (l_bmp.bmap_format)
			{
				case 16: return { shape::video::pixel::BM16, l_wth, l_hth };
				case 24: return { shape::video::pixel::BM24, l_wth, l_hth };
				case 32: return { shape::video::pixel::BM32, l_wth, l_hth };
			}
		}

		//!
		//!

		return {};
	}

	template<class mtag> static cBaseImageData<mtag> read_buf(const cBaseStream &p_stream)
	{
		cBaseImageData<mtag> l_bmp { read_img(p_stream) };

		//!
		//!

		if (p_stream.good())
		{
			//!
			//!

			std::fread(l_bmp.get_bitmap(), 1, l_bmp.get_length(), p_stream.get_handle());
		}

		//!
		//!

		return std::move(l_bmp);
	}

	//!
	//!

	cBaseImageData<heap_t> base_image_tga::load_heap(const cBaseStream &p_stream) { return read_buf<heap_t>(p_stream); }
	cBaseImageData<page_t> base_image_tga::load_page(const cBaseStream &p_stream) { return read_buf<page_t>(p_stream); }
	cBaseImageData<temp_t> base_image_tga::load_temp(const cBaseStream &p_stream) { return read_buf<temp_t>(p_stream); }

} //! shape