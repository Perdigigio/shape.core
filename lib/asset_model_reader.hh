#ifndef SHAPE_ASSET_MODEL_READER_HH__GUARD
#define SHAPE_ASSET_MODEL_READER_HH__GUARD

#include "base_reader.hh"

namespace shape
{
	class cAssetModelData;

	//!
	//!

	template<> bool reader::read(const file::type &, cAssetModelData &);

	//!
	//!

	template<> bool reader::read(const file::type &, base_model::pos_t &);
	template<> bool reader::read(const file::type &, base_model::nor_t &);
	template<> bool reader::read(const file::type &, base_model::tex_t &);
	template<> bool reader::read(const file::type &, base_model::skn_t &);
	template<> bool reader::read(const file::type &, base_model::idx_t &);

} //! shape

#endif