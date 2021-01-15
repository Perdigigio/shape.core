#ifndef SHAPE_ASSET_READER_MODEL_HH__GUARD
#define SHAPE_ASSET_READER_MODEL_HH__GUARD

#include "../../io/reader.hh"

#include "../model.hh"
#include "../model_buffer.hh"

namespace shape
{

	template<> cModel read<cModel>(std::istream &);

} //! shape

#endif