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

	char l_id_length;
	char l_cmap_type;
	char l_bmap_type;
	short int l_cmap_xorigin;
	short int l_cmap_clength;
	char l_cmap_depth;
	short int l_bmap_xorigin;
	short int l_bmap_yorigin;
	short int l_bmap_w;
	short int l_bmap_h;
	char l_bmap_format;
	char l_desc;

	uint32_t l_w;
	uint32_t l_h;

	//!
	//! TGA
	//!

	std::fread(&l_id_length, 1, 1, ifstream.get());
	std::fread(&l_cmap_type, 1, 1, ifstream.get());
	std::fread(&l_bmap_type, 1, 1, ifstream.get());
	std::fread(&l_cmap_xorigin, 2, 1, ifstream.get());
	std::fread(&l_cmap_clength, 2, 1, ifstream.get());
	std::fread(&l_cmap_depth, 1, 1, ifstream.get());
	std::fread(&l_bmap_xorigin, 2, 1, ifstream.get());
	std::fread(&l_bmap_yorigin, 2, 1, ifstream.get());
	std::fread(&l_bmap_w, 2, 1, ifstream.get());
	std::fread(&l_bmap_h, 2, 1, ifstream.get());
	std::fread(&l_bmap_format, 1, 1, ifstream.get());
	std::fread(&l_desc, 1, 1, ifstream.get());

	//!
	//!

	if (l_bmap_type != 2)
	{
		std::cerr
			<< "invalid compression mode: only plain rgb data supported" << std::endl;

		std::exit(EXIT_FAILURE);
	}

	l_w = (uint32_t)((l_bmap_w & 0x80000000) ? ~l_bmap_w + 1 : l_bmap_w);
	l_h = (uint32_t)((l_bmap_h & 0x80000000) ? ~l_bmap_h + 1 : l_bmap_h);

	//!
	//!

	switch (l_bmap_format)
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
