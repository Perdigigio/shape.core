#ifndef SHAPE_VIDEO_BASE_DEVICE_HH__GUARD
#define SHAPE_VIDEO_BASE_DEVICE_HH__GUARD

#include "video_gl_base.hh"

namespace shape {
namespace video {

	struct base_device
	{
		int major;
		int minor;

		//! -------------------------------------

		static void init(base_device *) noexcept;
		static void free(base_device *) noexcept;
	};

	class cBaseDevice : private base_device
	{
	public:
		inline cBaseDevice() noexcept
		{
			this->major = {};
			this->minor = {};
		}

		inline void init() noexcept { base_device::init(this); }
		inline void free() noexcept { base_device::free(this); }
	};

} //! shape::video
} //! shape

#endif