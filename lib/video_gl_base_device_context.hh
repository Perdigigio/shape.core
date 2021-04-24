#ifndef SHAPE_VIDEO_BASE_SAMPLER_HH__GUARD
#define SHAPE_VIDEO_BASE_SAMPLER_HH__GUARD

#include "video_gl_base.hh"

#define SHAPE_MAX_UBUFFERS (16)
#define SHAPE_MAX_TEXTURES (16)
#define SHAPE_MAX_SAMPLERS (16)


namespace shape {
namespace video {

	typedef void (__cdecl *action_t)(uint32_t, void *);

	struct base_device_action
	{
		uint32_t id;

		//!
		//!

		void (__cdecl *on_enter)(uint32_t, void *);
		void (__cdecl *on_leave)(uint32_t, void *);
	};

	struct base_device_queue
	{

	};

} //! shape::video
} //! shape

#endif