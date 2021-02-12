#ifndef SHAPE_ASSET_IMAGE_READER_HH__GUARD
#define SHAPE_ASSET_IMAGE_READER_HH__GUARD

#include "io_reader.hh"

//!
//!

namespace shape
{
	class cAssetImageData;

	/**
	 * @param stream
	 * @param source
	 */
	template<> std::istream & reader::read(std::istream &, cAssetImageData &);

}

#endif