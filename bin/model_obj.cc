
#ifdef _MSC_VER
#	define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <iostream>
#include <vector>
#include <regex>
#include <unordered_map>
#include <string>
#include <cctype>

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
	std::cerr << "        " << "-h        print this message                                     " << std::endl;
	std::cerr << "        " << "-v        be verbose                                             " << std::endl;
	std::cerr << "        " << "src       input source, if - is passed input will be from stdin  " << std::endl;
}

const char *i_file = nullptr;
const char *o_file = nullptr;

bool v_flag = false;

//! 
//!

#include <asset_model.hh>
#include <asset_model_writer.hh>

#include <math.hh>

struct triple
{
	int v;
	int t;
	int n;
};

struct object
{
	inline object() noexcept : v(0), n(0), t(0) { }

	uint32_t v;
	uint32_t n;
	uint32_t t;
	uint32_t o;

	//!
	//!

	std::vector<triple> f;
};

std::vector<shape::IEEEFloat32> g_vp;
std::vector<sint16_t> g_vn;
std::vector<shape::IEEEFloat16> g_vt;


char g_line[1024] = {};
char g_last[1024] = {};

std::unordered_map<std::string, object> g_objects;

bool parse_v(const char *buf)
{
	float x, y, z;

	//!
	//!

	if (std::sscanf(buf, "%f %f %f", &x, &y, &z) == 3)
	{
		g_vp.push_back(shape::as_IEEEFloat32(x));
		g_vp.push_back(shape::as_IEEEFloat32(y));
		g_vp.push_back(shape::as_IEEEFloat32(z));
	}
	else
		return false;

	//!
	//!

	++g_objects[g_last].v;

	//!
	//!

	return true;
}

bool parse_n(const char *buf)
{
	float x, y, z;

	//!
	//!

	if (std::sscanf(buf, "%f %f %f", &x, &y, &z) == 3)
	{
		g_vn.push_back(sint16_t(x * 0x7FFF));
		g_vn.push_back(sint16_t(y * 0x7FFF));
		g_vn.push_back(sint16_t(z * 0x7FFF));
	}
	else
		return false;

	//!
	//!

	++g_objects[g_last].n;

	//!
	//!

	return true;
}

bool parse_t(const char *buf)
{
	float u, v;

	//!
	//!

	if (std::sscanf(buf, "%f %f", &u, &v) == 2)
	{
		g_vt.push_back(shape::as_IEEEFloat16(u));
		g_vt.push_back(shape::as_IEEEFloat16(v));
	}
	else
		return false;

	//!
	//!

	++g_objects[g_last].t;

	//!
	//!

	return true;
}

bool parse_triple(const char *buf)
{
	std::cmatch l_match;

	//!
	//!

	if (std::regex_search(buf, l_match, std::regex{"([0-9]+)(/([0-9]*)(/([0-9]+)?))"}))
	{
		triple l_triple =
		{
			std::max(std::atoi(l_match[1].str().c_str()), 0),
			std::max(std::atoi(l_match[3].str().c_str()), 0),
			std::max(std::atoi(l_match[5].str().c_str()), 0)
		};

		g_objects[g_last].f.push_back(l_triple);
	}
	else
		return false;

	//!
	//!

	return true;
}

bool parse_f(const char *buf)
{
	while (buf && parse_triple(buf))
	{
		//!
		//!

		buf = std::strchr(++buf, ' ');
	}

	//!
	//!

	return buf == NULL;
}

bool parse_o(const char *buf)
{
	std::memset(g_last, 0, sizeof g_last);

	//!
	//!

	for (size_t i = 0; i < (sizeof g_last - 1) && std::isprint(g_line[i]); i++)
	{
		//!
		//!

		g_last[i] = g_line[i];
	}

	//!
	//!

	return true;
}

int main(int argc, char ** argv)
{
	int opt;

	shape::file::type ifstream;
	shape::file::type ofstream;

	//!
	//!

	while ((opt = my_getopt(argc, argv, ":hvo:")) != -1)
	{
		switch (opt)
		{
			case 'o': o_file = optarg; break;
			case 'v': v_flag = true; break;
			case 'h': usage(argv[0]); return EXIT_SUCCESS;
			case ':': usage(argv[0]); return EXIT_FAILURE;
			case '?': usage(argv[0]); return EXIT_FAILURE;
		}
	}

	if (optind < argc && std::strcmp(argv[optind], "-") != 0)
	{
		i_file = argv[optind];
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
	//! READ OBJ FILE
	//!

	while(shape::stream::good(ifstream))
	{
		if (!std::fgets(g_line, sizeof g_line, ifstream.get()))
		{
			break;
		}

		//!
		//!

		if (g_line[0] == 'v')
			switch (g_line[1])
			{
				case ' ': parse_v(g_line + 2); break;
				case 'n': parse_n(g_line + 2); break;
				case 't': parse_t(g_line + 2); break;
			}
		else if (g_line[0] == 'f') parse_f(g_line + 1);
		else if (g_line[0] == 'o') parse_o(g_line + 1);
	}

	uint32_t l_offset = 0;

	for (auto & p : g_objects)
	{
		auto & f = p.second.f;

		if (v_flag)
			std::cerr << "processing sub object"                                         << std::endl
				  << "            name: " << (p.first.empty() ? "unknown" : p.first) << std::endl
				  << "        vertexes: " << p.second.v                              << std::endl
				  << "         indexes: " << p.second.f.size()                       << std::endl;

		//!
		//!

		if (f.size() % 3)
		{
			std::cerr
				<< "index count is not a multiple of 3, result may be not correct" << std::endl;
		}

		shape::cAssetModelData l_model { p.second.v, uint32_t(f.size()),
			shape::asset_model_flags::has_nor |
			shape::asset_model_flags::has_tex };

		auto l_pos = l_model.get_pos_data();
		auto l_nor = l_model.get_nor_data();
		auto l_tex = l_model.get_tex_data();
		auto l_idx = l_model.get_idx_data();

		std::memset(l_pos, 0, l_model.get_length(shape::base_model_buffer::pos));
		std::memset(l_nor, 0, l_model.get_length(shape::base_model_buffer::nor));
		std::memset(l_tex, 0, l_model.get_length(shape::base_model_buffer::tex));
		std::memset(l_idx, 0, l_model.get_length(shape::base_model_buffer::idx));

		for (size_t i = 0; i < l_model.get_vtx(); i++)
		{
			std::memcpy(&l_pos[i].dummy[0] , &g_vp[(l_offset + i) * 3 + 0], sizeof(uint32_t));
			std::memcpy(&l_pos[i].dummy[1] , &g_vp[(l_offset + i) * 3 + 1], sizeof(uint32_t));
			std::memcpy(&l_pos[i].dummy[2] , &g_vp[(l_offset + i) * 3 + 2], sizeof(uint32_t));
		}

		for (size_t i = 0; i < l_model.get_idx(); i++)
		{
			//!
			//!

			l_idx[i].dummy[0] = f[i].v - 1 - l_offset;
		}

		//!
		//! ASSEMBLE DATA
		//!

		for (const auto & _ : f)
		{
			auto _v = (_.v ? (_.v - 1) : 0) - l_offset;
			auto _n = (_.n ? (_.n - 1) : 0);
			auto _t = (_.t ? (_.t - 1) : 0);

			if (!g_vn.empty())
			{
				std::memcpy(&l_nor[_v].dummy[0], &g_vn[_n * 3 + 0], sizeof(uint16_t));
				std::memcpy(&l_nor[_v].dummy[1], &g_vn[_n * 3 + 1], sizeof(uint16_t));
				std::memcpy(&l_nor[_v].dummy[2], &g_vn[_n * 3 + 2], sizeof(uint16_t));
			}

			if (!g_vt.empty())
			{
				std::memcpy(&l_tex[_v].dummy[0], &g_vt[_t * 2 + 0], sizeof(uint16_t));
				std::memcpy(&l_tex[_v].dummy[1], &g_vt[_t * 2 + 1], sizeof(uint16_t));
			}
		}

		l_offset += p.second.v;

		//!
		//! WRITE DATA
		//!

		if (!shape::writer::write(ofstream, l_model))
		{
			std::cerr
				<< "error writing to file" << std::endl;

			std::exit(EXIT_FAILURE);
		}

		//!
		//! REMOVE PROCESSED DATA
		//!

		p.second = {};
	}

	//!
	//!

	return 0;
}
