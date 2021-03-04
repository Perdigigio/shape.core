
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

std::vector<sint32_t> g_v;
std::vector<sint16_t> g_n;
std::vector<sint16_t> g_t;

struct object
{
	std::vector<triple> f;
};

uint32_t g_vtx = 0;
uint32_t g_idx = 0;

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
		g_v.push_back(shape::as_IEEEFloat32(x));
		g_v.push_back(shape::as_IEEEFloat32(y));
		g_v.push_back(shape::as_IEEEFloat32(z));
	}
	else
		return false;

	g_vtx++;

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
		g_n.push_back(sint16_t(x * 0x7FFF));
		g_n.push_back(sint16_t(y * 0x7FFF));
		g_n.push_back(sint16_t(z * 0x7FFF));
	}
	else
		return false;

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
		g_t.push_back(shape::as_IEEEFloat16(u));
		g_t.push_back(shape::as_IEEEFloat16(v));
	}
	else
		return false;

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

	g_idx++;

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

	if (v_flag)
		std::cerr << "start parsing " << g_last << std::endl;

	//!
	//!

	return true;
}

int main(int argc, char ** argv)
{
	int opt;

	shape::file::type ifstream;
	shape::file::type ofstream;

//	argc = 5;
//	argv = new char *[5]{ argv[0],
//		"-o", "C:\\Users\\fracc\\Documents\\Progetti\\shape.test\\build\\Debug\\cube.mod",
//		"-v", "C:\\Users\\fracc\\Documents\\Progetti\\shape.test\\cube.obj"};

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

	shape::cAssetModelData l_model
	{
		g_vtx, g_idx, shape::asset_model_flags::has_nor | shape::asset_model_flags::has_tex, static_cast<uint32_t>(g_objects.size() & 0xFFFFFFFF)
	};

	uint32_t l_last_idx = 0;
	uint32_t l_last_sub = 0;

	auto l_pos = l_model.get_pos_data();
	auto l_nor = l_model.get_nor_data();
	auto l_tex = l_model.get_tex_data();
	auto l_idx = l_model.get_idx_data();
	auto l_sub = l_model.get_sub_data();

	std::memset(l_nor, 0, l_model.get_length(shape::base_model_fourcc::nor));
	std::memset(l_tex, 0, l_model.get_length(shape::base_model_fourcc::tex));

	for (size_t i = 0; i < l_model.get_vtx(); i++)
	{
		std::memcpy(&l_pos[i].dummy[0] , &g_v[i * 3 + 0], sizeof(sint32_t));
		std::memcpy(&l_pos[i].dummy[1] , &g_v[i * 3 + 1], sizeof(sint32_t));
		std::memcpy(&l_pos[i].dummy[2] , &g_v[i * 3 + 2], sizeof(sint32_t));
	}

	for (const auto& o : g_objects)
	{
		l_sub[l_last_sub++] = { l_last_idx, static_cast<uint32_t>(o.second.f.size() & 0xFFFFFFFF) };

		//!
		//!

		if (o.second.f.size() % 3)
		{
			std::cerr
				<< "index count is not a multiple of 3, result may be not correct" << std::endl;
		}

		for (const auto &_ : o.second.f)
		{
			//!
			//!

			l_idx[l_last_idx++].dummy[0] = _.v - 1;
		}

		//!
		//! ASSEMBLE DATA
		//!

		for (const auto &_ : o.second.f)
		{
			auto _v = (_.v ? (_.v - 1) : 0);
			auto _n = (_.n ? (_.n - 1) : 0);
			auto _t = (_.t ? (_.t - 1) : 0);

			if (!g_n.empty())
			{
				std::memcpy(&l_nor[_v].dummy[0], &g_n[_n * 3 + 0], sizeof(uint16_t));
				std::memcpy(&l_nor[_v].dummy[1], &g_n[_n * 3 + 1], sizeof(uint16_t));
				std::memcpy(&l_nor[_v].dummy[2], &g_n[_n * 3 + 2], sizeof(uint16_t));
			}

			if (!g_t.empty())
			{
				std::memcpy(&l_tex[_v].dummy[0], &g_t[_t * 2 + 0], sizeof(uint16_t));
				std::memcpy(&l_tex[_v].dummy[1], &g_t[_t * 2 + 1], sizeof(uint16_t));
			}
		}
	}

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
	//!

	return 0;
}
