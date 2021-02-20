#ifndef SHAPE_ASSET_IMAGE_WRITER_HH__GUARD
#define SHAPE_ASSET_IMAGE_WRITER_HH__GUARD

#include "base_writer.hh"

//!
//!

namespace shape
{
	class cAssetImageData;

	/**
	 * @param stream
	 * @param source
	 */
	template<> bool writer::write(const file::type &, const cAssetImageData &);
}

#endif