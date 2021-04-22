#ifndef SHAPE_BASE_MODEL_OBJ_HH__GUARD
#define SHAPE_BASE_MODEL_OBJ_HH__GUARD

#include "base_model.hh"
#include "base_stream.hh"

namespace shape
{

	struct base_model_obj
	{
		static cBaseModelData<heap_t> load_heap(const cBaseStream &);
		static cBaseModelData<page_t> load_page(const cBaseStream &);
		static cBaseModelData<temp_t> load_temp(const cBaseStream &);
	};

}

#endif
