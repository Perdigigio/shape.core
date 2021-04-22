#include "base_image_bmp.hh"

namespace shape
{

	struct bmp_header
	{
		uint32_t length;
		uint16_t reserved_1;
		uint16_t reserved_2;
		uint32_t offset;
	};

	struct dib_header
	{
		uint32_t size;
		sint32_t w;
		sint32_t h;
		uint16_t planes;
		uint16_t bits;
		uint32_t compression;
		uint32_t imagesize;
		sint32_t xresolution;
		sint32_t yresolution;
		uint32_t ncolours;
		uint32_t icolours;
	};

	static bmp_header read_bmp(const cBaseStream &p_stream) noexcept
	{
		bmp_header l_bmp;

		//!
		//! BMP
		//!

		std::fread(&l_bmp.length,     4, 1, p_stream.get_handle());
		std::fread(&l_bmp.reserved_1, 2, 1, p_stream.get_handle());
		std::fread(&l_bmp.reserved_2, 2, 1, p_stream.get_handle());
		std::fread(&l_bmp.offset,     4, 1, p_stream.get_handle());

		//!
		//!

		return l_bmp;
	}

	static dib_header read_dib(const cBaseStream &p_stream) noexcept
	{
		dib_header l_dib;

		//!
		//! DIB
		//!

		std::fread(&l_dib.size,        4, 1, p_stream.get_handle());
		std::fread(&l_dib.w,           4, 1, p_stream.get_handle());
		std::fread(&l_dib.h,           4, 1, p_stream.get_handle());
		std::fread(&l_dib.planes,      2, 1, p_stream.get_handle());
		std::fread(&l_dib.bits,        2, 1, p_stream.get_handle());
		std::fread(&l_dib.compression, 4, 1, p_stream.get_handle());
		std::fread(&l_dib.imagesize,   4, 1, p_stream.get_handle());
		std::fread(&l_dib.xresolution, 4, 1, p_stream.get_handle());
		std::fread(&l_dib.yresolution, 4, 1, p_stream.get_handle());
		std::fread(&l_dib.ncolours,    4, 1, p_stream.get_handle());
		std::fread(&l_dib.icolours,    4, 1, p_stream.get_handle());

		//!
		//!

		return l_dib;
	}

	//!
	//!

	static cBaseImage read_img(const cBaseStream &p_stream) noexcept
	{
		const char l_B = std::fgetc(p_stream.get_handle());
		const char l_M = std::fgetc(p_stream.get_handle());

		if (l_B != 'B' || l_M != 'M')
		{
			//!
			//! NOT A BITMAP
			//!

			return {};
		}

		const auto l_bmp = read_bmp(p_stream);
		const auto l_dib = read_dib(p_stream);
		const auto l_wth = static_cast<uint32_t>(l_dib.w < 0 ? ~l_dib.w + 1 : l_dib.w);
		const auto l_hth = static_cast<uint32_t>(l_dib.h < 0 ? ~l_dib.h + 1 : l_dib.h);

		//!
		//!

		if (p_stream.good() && l_dib.compression == 0 && l_dib.planes == 1)
		{
			switch (l_dib.bits)
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

	cBaseImageData<heap_t> base_image_bmp::load_heap(const cBaseStream &p_stream) { return read_buf<heap_t>(p_stream); }
	cBaseImageData<page_t> base_image_bmp::load_page(const cBaseStream &p_stream) { return read_buf<page_t>(p_stream); }
	cBaseImageData<temp_t> base_image_bmp::load_temp(const cBaseStream &p_stream) { return read_buf<temp_t>(p_stream); }

} //! shape