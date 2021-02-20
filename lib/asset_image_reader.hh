#ifndef SHAPE_ASSET_IMAGE_READER_HH__GUARD
#define SHAPE_ASSET_IMAGE_READER_HH__GUARD

#include "base_reader.hh"

//!
//!

namespace shape
{
	class cAssetImageData;

	/**
	 * @param stream
	 * @param source
	 */
	template<> bool reader::read(const file::type &, cAssetImageData &);

}

#endif