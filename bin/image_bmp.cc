#include <iostream>
#include <cstring>

#include "getopt.h"

#ifdef _WIN32
#	define STDIN_FILENO (_fileno(stdin))
#	define STDOUT_FILENO (_fileno(stdout))
#else
#	include <unistd.h>
#endif

static void usage(const char * argv) noexcept
{
	std::cerr << "usage:  " << argv << " [options] [src]" << std::endl;
	std::cerr << "        " << "-o file   specify output file, otherwise output will go in stdout" << std::endl;
	std::cerr << "        " << "-x mode   specify compression algorithm: [dxt1, dxt3, dxt5]      " << std::endl;
	std::cerr << "        " << "-h        print this message                                     " << std::endl;
	std::cerr << "        " << "src       input source, if - is passed input will be from stdin  " << std::endl;
}

const char *i_file = nullptr;
const char *o_file = nullptr;
const char *x_flag = nullptr;

//! 
//!

#include <asset_image.hh>
#include <asset_image_writer.hh>

shape::file::type ifstream;
shape::file::type ofstream;

int main(int argc, char ** argv)
{
	int opt;

	//!
	//!

	while ((opt = my_getopt(argc, argv, ":ho:x:")) != -1)
	{
		switch (opt)
		{
			case 'o': o_file = optarg; break;
			case 'x': x_flag = optarg; break;
			case 'h': usage(argv[0]); return EXIT_SUCCESS;
			case ':': usage(argv[0]); return EXIT_FAILURE;
			case '?': usage(argv[0]); return EXIT_FAILURE;
		}
	}

	if (optind < argc && std::strcmp(argv[optind], "-") != 0)
	{
		i_file = argv[optind];
	}

	if (x_flag &&
		(std::strcmp(x_flag, "dxt1") != 0) &&
		(std::strcmp(x_flag, "dxt3") != 0) &&
		(std::strcmp(x_flag, "dxt5") != 0))
	{
		std::cerr
			<< "invalid compression format: " << x_flag << std::endl;

		std::exit(EXIT_FAILURE);
	}

	//!
	//!

	ifstream = i_file ?
		shape::stream::open_istream(i_file) : shape::stream::open_istream(STDIN_FILENO);

	ofstream = o_file ?	
		shape::stream::open_ostream(o_file) : shape::stream::open_ostream(STDOUT_FILENO);

	if (shape::stream::fail(ifstream) || shape::stream::fail(ofstream))
	{
		perror(NULL),
			std::exit(EXIT_FAILURE);
	}

	//!
	//!

	shape::cAssetImageData l_image;

	const char l_bmp_bm[] =
	{
		(char)std::fgetc(ifstream.get()),
		(char)std::fgetc(ifstream.get())
	};

	uint32_t l_bmp_length;
	uint16_t l_bmp_reserved_1;
	uint16_t l_bmp_reserved_2;
	uint32_t l_bmp_offset;

	uint32_t l_dib_size;
	sint32_t l_dib_w;
	sint32_t l_dib_h;
	uint16_t l_dib_planes;
	uint16_t l_dib_bits;
	uint32_t l_dib_compression;
	uint32_t l_dib_imagesize;
	sint32_t l_dib_xresolution;
	sint32_t l_dib_yresolution;
	uint32_t l_dib_ncolours;
	uint32_t l_dib_icolours;

	uint32_t l_w;
	uint32_t l_h;

	if (l_bmp_bm[0] != 'B' || l_bmp_bm[1] != 'M')
	{
		std::cerr
			<< "invalid bitmap signature" << std::endl;

		std::exit(EXIT_FAILURE);
	}
	//!
	//! BMP
	//!

	std::fread(&l_bmp_length,     4, 1, ifstream.get());
	std::fread(&l_bmp_reserved_1, 2, 1, ifstream.get());
	std::fread(&l_bmp_reserved_2, 2, 1, ifstream.get());
	std::fread(&l_bmp_offset,     4, 1, ifstream.get());

	//!
	//! DIB
	//!

	std::fread(&l_dib_size,        4, 1, ifstream.get());
	std::fread(&l_dib_w,           4, 1, ifstream.get());
	std::fread(&l_dib_h,           4, 1, ifstream.get());
	std::fread(&l_dib_planes,      2, 1, ifstream.get());
	std::fread(&l_dib_bits,        2, 1, ifstream.get());
	std::fread(&l_dib_compression, 4, 1, ifstream.get());
	std::fread(&l_dib_imagesize,   4, 1, ifstream.get());
	std::fread(&l_dib_xresolution, 4, 1, ifstream.get());
	std::fread(&l_dib_yresolution, 4, 1, ifstream.get());
	std::fread(&l_dib_ncolours,    4, 1, ifstream.get());
	std::fread(&l_dib_icolours,    4, 1, ifstream.get());

	//!
	//!

	if (l_dib_compression)
	{
		std::cerr
			<< "invalid compression mode: only plain rgb data supported" << std::endl;

		std::exit(EXIT_FAILURE);
	}

	l_w = (uint32_t)((l_dib_w & 0x80000000) ? ~l_dib_w + 1 : l_dib_w);
	l_h = (uint32_t)((l_dib_h & 0x80000000) ? ~l_dib_h + 1 : l_dib_h);

	//!
	//!

	switch (l_dib_bits)
	{
		case 16: l_image = { shape::video::pixel::BM16, l_w, l_h }; break;
		case 24: l_image = { shape::video::pixel::BM24, l_w, l_h }; break;
		case 32: l_image = { shape::video::pixel::BM32, l_w, l_h }; break;

		//!
		//! UNSUPPORTED FORMAT
		//!

		default:
			std::cerr
				<< "invalid bitmap format: only 16, 24 and 32 bits format supported" << std::endl;

			std::exit(EXIT_FAILURE);
	}

	//!
	//! READ DATA
	//!

	std::fread(l_image.get_data(), l_image.get_stride(), l_image.get_hth(), ifstream.get());

	//!

	if (!shape::stream::good(ifstream) || !shape::writer::write(ofstream, l_image))
	{
		//!
		//! WRITE
		//!

		std::exit(EXIT_FAILURE);
	}

	//!
	//!

	return 0;
}
