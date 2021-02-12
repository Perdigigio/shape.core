#ifndef SHAPE_ASSET_MODEL_WRITER_HH__GUARD
#define SHAPE_ASSET_MODEL_WRITER_HH__GUARD

#include "io_writer.hh"

namespace shape
{

	class cAssetModelData;

	/**
	 * @param stream
	 * @param source
	 */
	template<> std::ostream & writer::write(std::ostream &, const cAssetModelData &);

	//!
	//!

	template<> std::ostream & writer::write(std::ostream &, const base_model::pos_t &);
	template<> std::ostream & writer::write(std::ostream &, const base_model::nor_t &);
	template<> std::ostream & writer::write(std::ostream &, const base_model::tex_t &);
	template<> std::ostream & writer::write(std::ostream &, const base_model::skn_t &);
	template<> std::ostream & writer::write(std::ostream &, const base_model::idx_t &);

} //! shape

#endif