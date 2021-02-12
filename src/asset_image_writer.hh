#ifndef SHAPE_ASSET_IMAGE_WRITER_HH__GUARD
#define SHAPE_ASSET_IMAGE_WRITER_HH__GUARD

#include "io_writer.hh"

//!
//!

namespace shape
{
	class cAssetImageData;

	/**
	 * @param stream
	 * @param source
	 */
	template<> std::ostream & writer::write(std::ostream &, const cAssetImageData &);
}

#endif