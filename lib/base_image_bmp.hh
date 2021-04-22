#ifndef SHAPE_BASE_IMAGE_BMP_HH__GUARD
#define SHAPE_BASE_IMAGE_BMP_HH__GUARD

#include "base_image.hh"
#include "base_stream.hh"

namespace shape
{

	struct base_image_bmp
	{
		static cBaseImageData<heap_t> load_heap(const cBaseStream &);
		static cBaseImageData<page_t> load_page(const cBaseStream &);
		static cBaseImageData<temp_t> load_temp(const cBaseStream &);
	};

}

#endif
