#ifndef SHAPE_ASSET_WRITER_MODEL_HH__GUARD
#define SHAPE_ASSET_WRITER_MODEL_HH__GUARD

#include "../../io/writer.hh"

#include "../model.hh"
#include "../model_buffer.hh"

namespace shape
{

	template<> bool write<cModel>(std::ostream &, const cModel &);

} //! shape

#endif