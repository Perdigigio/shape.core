#ifndef SHAPE_ASSET_READER_MODEL_HH__GUARD
#define SHAPE_ASSET_READER_MODEL_HH__GUARD

#include "io_reader.hh"

#include "asset_model.hh"
#include "asset_model_buffer.hh"

namespace shape
{

	template<> cModel read<cModel>(std::istream &);

} //! shape

#endif