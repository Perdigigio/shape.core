#ifndef SHAPE_ASSET_WRITER_MODEL_HH__GUARD
#define SHAPE_ASSET_WRITER_MODEL_HH__GUARD

#include "io_writer.hh"

#include "asset_model.hh"
#include "asset_model_buffer.hh"

namespace shape
{

	template<> bool write<cModel>(std::ostream &, const cModel &);

} //! shape

#endif