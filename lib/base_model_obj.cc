#include "base_model_obj.hh"

//!
//! STD
//!

#include <vector>

//!
//! MSVC deprecation warning suppress workaround
//!

#ifdef _MSC_VER
#	pragma warning( push )
#	pragma warning( disable : 4996 )
#endif

namespace shape
{
	static constexpr auto MAX_LINE = 2048;

	struct base_model_tri
	{
		long p[3];
		long t[3];
		long n[3];
	};

	static void parse_v(std::vector<base_model_pos>&, const char *);
	static void parse_n(std::vector<base_model_nor>&, const char *);
	static void parse_t(std::vector<base_model_tex>&, const char *);
	static void parse_f(std::vector<base_model_tri>&, const char *);

	//!
	//!
	//!

	template<class mtag> cBaseModelData<mtag> read_obj(const cBaseStream &p_fh)
	{
		char l_line[MAX_LINE];

		//!
		//! TEMP DATA
		//!

		std::vector<base_model_pos> l_pos;
		std::vector<base_model_nor> l_nor;
		std::vector<base_model_tex> l_tex;
		std::vector<base_model_tri> l_tri;

		//!
		//!

		while(p_fh.good())
		{
			if (!std::fgets(l_line, sizeof l_line, p_fh.get_handle()))
			{
				break;
			}

			//!
			//!

			if (l_line[0] == 'v')
				switch (l_line[1])
				{
					case ' ': parse_v(l_pos, l_line); break;
					case 'n': parse_n(l_nor, l_line); break;
					case 't': parse_t(l_tex, l_line); break;
				}
			else
				if (l_line[0] == 'f') parse_f(l_tri, l_line);
		}

		uint32_t l_vtx = static_cast<uint32_t>(l_pos.size());
		uint32_t l_idx = static_cast<uint32_t>(l_tri.size());

		cBaseModelData<mtag> l_model
		{
			{ l_vtx, l_idx * 3, base_model_flag::has_nor | base_model_flag::has_tex }
		};

		auto l_pos_buffer = l_model.get_pos_buffer();
		auto l_nor_buffer = l_model.get_nor_buffer();
		auto l_tex_buffer = l_model.get_tex_buffer();
		auto l_idx_buffer = l_model.get_idx_buffer();

		//!
		//!

		std::memcpy(l_pos_buffer, l_pos.data(), l_model.get_length(base_model_fourcc::pos));

		for (uint32_t i = 0; i < l_idx; i++)
		{
			l_idx_buffer[i * 3 + 0].dummy[0] = static_cast<uint32_t>(l_tri[i].p[0] - 1);
			l_idx_buffer[i * 3 + 1].dummy[0] = static_cast<uint32_t>(l_tri[i].p[1] - 1);
			l_idx_buffer[i * 3 + 2].dummy[0] = static_cast<uint32_t>(l_tri[i].p[2] - 1);

			l_nor_buffer[l_tri[i].p[0] - 1] = (l_tri[i].n[0] > 0) ? l_nor[l_tri[i].n[0] - 1] : base_model_nor{};
			l_nor_buffer[l_tri[i].p[1] - 1] = (l_tri[i].n[1] > 0) ? l_nor[l_tri[i].n[1] - 1] : base_model_nor{};
			l_nor_buffer[l_tri[i].p[2] - 1] = (l_tri[i].n[2] > 0) ? l_nor[l_tri[i].n[2] - 1] : base_model_nor{};
			l_tex_buffer[l_tri[i].p[0] - 1] = (l_tri[i].t[0] > 0) ? l_tex[l_tri[i].t[0] - 1] : base_model_tex{};
			l_tex_buffer[l_tri[i].p[1] - 1] = (l_tri[i].t[1] > 0) ? l_tex[l_tri[i].t[1] - 1] : base_model_tex{};
			l_tex_buffer[l_tri[i].p[2] - 1] = (l_tri[i].t[2] > 0) ? l_tex[l_tri[i].t[2] - 1] : base_model_tex{};
		}

		//!
		//!

		return std::move(l_model);
	}

	cBaseModelData<heap_t> base_model_obj::load_heap(const cBaseStream &p_fh) { return read_obj<heap_t>(p_fh); }
	cBaseModelData<page_t> base_model_obj::load_page(const cBaseStream &p_fh) { return read_obj<page_t>(p_fh); }
	cBaseModelData<temp_t> base_model_obj::load_temp(const cBaseStream &p_fh) { return read_obj<temp_t>(p_fh); }

	//!
	//!

	void parse_v(std::vector<base_model_pos> &p_pos, const char *p_line)
	{
		base_model_pos l_pos;

		float x;
		float y;
		float z;

		if (std::sscanf(p_line, "v %f %f %f", &x, &y, &z) >= 3)
		{
			l_pos.dummy[0] = as_IEEEFloat32(x); //! SAFE CAST
			l_pos.dummy[1] = as_IEEEFloat32(y); //! SAFE CAST
			l_pos.dummy[2] = as_IEEEFloat32(z); //! SAFE CAST
		}

		//!
		//!

		p_pos.push_back(l_pos);
	}

	void parse_n(std::vector<base_model_nor> &p_nor, const char *p_line)
	{
		base_model_nor l_nor = {};

		float x;
		float y;
		float z;

		if (std::sscanf(p_line, "vn %f %f %f", &x, &y, &z) >= 3)
		{
			l_nor.dummy[0] = static_cast<uint16_t>((x + 1) / 2 * 0xFFFF); //! CAST TO UNORM-16
			l_nor.dummy[1] = static_cast<uint16_t>((y + 1) / 2 * 0xFFFF); //! CAST TO UNORM-16
			l_nor.dummy[2] = static_cast<uint16_t>((z + 1) / 2 * 0xFFFF); //! CAST TO UNORM-16
		}

		//!
		//!

		p_nor.push_back(l_nor);
	}

	void parse_t(std::vector<base_model_tex> &p_tex, const char *p_line)
	{
		base_model_tex l_tex = {};

		float u;
		float v;

		if (std::sscanf(p_line, "vt %f %f", &u, &v) >= 2)
		{
			l_tex.dummy[0] = as_IEEEFloat16(u); //! CAST TO UNORM-16
			l_tex.dummy[1] = as_IEEEFloat16(v); //! CAST TO UNORM-16
		}

		//!
		//!

		p_tex.push_back(l_tex);
	}

	void parse_f(std::vector<base_model_tri> &p_tri, const char *p_line)
	{
		base_model_tri l_tri = { 0 };

		char l_p1[MAX_LINE];
		char l_p2[MAX_LINE];
		char l_p3[MAX_LINE];

		if (std::sscanf(p_line, "f %2047s %2047s %2047s", l_p1, l_p2, l_p3) >= 3)
		{
			l_tri.p[0] = std::strtol(l_p1, NULL, 10);
			l_tri.p[1] = std::strtol(l_p2, NULL, 10);
			l_tri.p[2] = std::strtol(l_p3, NULL, 10);

			const char *l_t1 = std::strchr(l_p1, '/');
			const char *l_t2 = std::strchr(l_p2, '/');
			const char *l_t3 = std::strchr(l_p3, '/');
			const char *l_n1 = l_t1 ? std::strchr(l_t1 + 1, '/') : nullptr;
			const char *l_n2 = l_t2 ? std::strchr(l_t2 + 1, '/') : nullptr;
			const char *l_n3 = l_t3 ? std::strchr(l_t3 + 1, '/') : nullptr;

			l_tri.t[0] = l_t1 ? std::strtol(l_t1 + 1, NULL, 10) : 0;
			l_tri.t[1] = l_t2 ? std::strtol(l_t2 + 1, NULL, 10) : 0;
			l_tri.t[2] = l_t3 ? std::strtol(l_t3 + 1, NULL, 10) : 0;
			l_tri.n[0] = l_n1 ? std::strtol(l_n1 + 1, NULL, 10) : 0;
			l_tri.n[1] = l_n2 ? std::strtol(l_n2 + 1, NULL, 10) : 0;
			l_tri.n[2] = l_n3 ? std::strtol(l_n3 + 1, NULL, 10) : 0;
		}

		//!
		//!

		p_tri.push_back(l_tri);
	}

} //! shape


#ifdef _MSC_VER
#	pragma warning( pop )
#endif