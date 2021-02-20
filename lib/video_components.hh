#ifndef SHAPE_VIDEO_COMPONENTS_HH__GUARD
#define SHAPE_VIDEO_COMPONENTS_HH__GUARD

#include "base.hh"
#include "math.hh"

namespace shape {
namespace video {

	struct camera_view
	{
		real4 pos;
		real4 fwd;
		real4 top;
	};

	struct camera_proj
	{
		float w, h;
		float n, f;
	};

} //! shape::video
} //! shape

#endif
