#ifndef SHAPE_ASSET_MODEL_READER_HH__GUARD
#define SHAPE_ASSET_MODEL_READER_HH__GUARD

#include "io_reader.hh"

namespace shape
{
	class cAssetModelData;

	//!
	//!

	template<> std::istream & reader::read(std::istream &, cAssetModelData &);

	//!
	//!

	template<> std::istream & reader::read(std::istream &, base_model::pos_t &);
	template<> std::istream & reader::read(std::istream &, base_model::nor_t &);
	template<> std::istream & reader::read(std::istream &, base_model::tex_t &);
	template<> std::istream & reader::read(std::istream &, base_model::skn_t &);
	template<> std::istream & reader::read(std::istream &, base_model::idx_t &);

} //! shape

#endif