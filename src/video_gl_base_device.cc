#include "video_gl_base_device.hh"

namespace shape {
namespace video {

	void base_device::init(base_device * p_device) noexcept
	{
		if (gladLoadGL())
		{
			p_device->major = GLVersion.major;
			p_device->minor = GLVersion.minor;
		}
	}

	void base_device::free(base_device * p_device) noexcept
	{
		p_device->major = GLVersion.major = 0;
		p_device->minor = GLVersion.minor = 0;
	}


} //! shape::video
} //! shape