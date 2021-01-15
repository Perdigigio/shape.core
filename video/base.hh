#ifndef SHAPE_VIDEO_BASE_HH__GUARD
#define SHAPE_VIDEO_BASE_HH__GUARD

#include "../base.hh"

namespace shape {
namespace video {

	struct failure : shape::failure
	{
		const char * what() const override { return "shape::video::failure"; }
	};

	enum class attrib
	{
		float_1,
		float_2,
		float_3,
		float_4,

		half_2,
		half_4,

		int_1,
		int_2,
		int_3,
		int_4,
		unsigned_int_1,
		unsigned_int_2,
		unsigned_int_3,
		unsigned_int_4,

		short_2,
		short_2_norm,
		short_4,
		short_4_norm,
		unsigned_short_2,
		unsigned_short_2_norm,
		unsigned_short_4,
		unsigned_short_4_norm
	};



} //! shape::video
} //! shape

#include "glad/glad.h"

namespace shape {
namespace video {


	template<class F>
	static inline void last_error(F p_callback)
	{
		while (GLenum error = glGetError()) p_callback(error);
	}

} //! shape::video
} //! shape

#endif