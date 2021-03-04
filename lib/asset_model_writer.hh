#ifndef SHAPE_ASSET_MODEL_WRITER_HH__GUARD
#define SHAPE_ASSET_MODEL_WRITER_HH__GUARD

#include "base_writer.hh"

namespace shape
{

	class cAssetModelData;

	/**
	 * @param stream
	 * @param source
	 */
	template<> bool writer::write(const file::type &, const cAssetModelData &);

	//!
	//!

	template<> bool writer::write(const file::type &, const base_model::pos_t &);
	template<> bool writer::write(const file::type &, const base_model::nor_t &);
	template<> bool writer::write(const file::type &, const base_model::tex_t &);
	template<> bool writer::write(const file::type &, const base_model::skn_t &);
	template<> bool writer::write(const file::type &, const base_model::idx_t &);
	template<> bool writer::write(const file::type &, const base_model::sub_t &);

} //! shape

#endif