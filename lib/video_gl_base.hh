#ifndef SHAPE_VIDEO_BASE_HH__GUARD
#define SHAPE_VIDEO_BASE_HH__GUARD

#include "base.hh"
#include "type.hh"
#include "math.hh"

namespace shape {
namespace video {

	struct failure : shape::failure
	{
		const char * what() const noexcept override { return "shape::video::failure"; }
	};

	//! -----------------------------------------------------------------------------------

	struct base_region
	{
		int x0, x1; //! w: x1 - x0
		int y0, y1; //! h: y1 - y0
		int z0, z1; //! d: z1 - z0
	};

	//! -----------------------------------------------------------------------------------

	static inline constexpr int x(const base_region& r) noexcept { return r.x0; }
	static inline constexpr int y(const base_region& r) noexcept { return r.y0; }
	static inline constexpr int z(const base_region& r) noexcept { return r.z0; }
	static inline constexpr int w(const base_region& r) noexcept { return r.x1 - r.x0; }
	static inline constexpr int h(const base_region& r) noexcept { return r.y1 - r.y0; }
	static inline constexpr int d(const base_region& r) noexcept { return r.z1 - r.z0; }

	//! -----------------------------------------------------------------------------------

	struct base_model_buffer
	{
		real4x4 model;
		real4x4 model_view;
		real4x4 model_view_proj;
		real4x4 inv_model;
		real4x4 inv_model_view;
		real4x4 inv_model_view_proj;

		real4 reference_pos;
		real4 reference_fwd;
		real4 reference_top;
		real4 albedo;
		real4 normal;
		real4 params;

		real2x2 transform_uv0;
		real2x2 transform_uv1;
	};

	struct base_frame_buffer
	{
		real4x4 view;
		real4x4 proj;
		real4x4 view_proj;
		real4x4 inv_view;
		real4x4 inv_proj;
		real4x4 inv_view_proj;

		real4 camera_pos;
		real4 camera_fwd;
		real4 camera_top;
		real2 viewport_pos;
		real2 viewport_ext;

		real4 light_dir;
		real4 light_col;
	};

	struct base_blend_buffer
	{
		real4 dq0[128];
		real4 dq1[128];
	};

} //! shape::video
} //! shape

#include "video_gl_glad.h"

namespace shape {
namespace video {


	template<class F>
	static inline void last_error(F p_callback)
	{
		while (GLenum error = glGetError()) p_callback(error);
	}

	//!
	//!

	static inline void gl_get(GLboolean &v, GLenum e) noexcept { glGetBooleanv(e, &v);   }
	static inline void gl_get(GLint &v,     GLenum e) noexcept { glGetIntegerv(e, &v);   }
	static inline void gl_get(GLint64 &v,   GLenum e) noexcept { glGetInteger64v(e, &v); }
	static inline void gl_get(GLfloat &v,   GLenum e) noexcept { glGetFloatv(e, &v);     }
	static inline void gl_get(GLdouble &v,  GLenum e) noexcept { glGetDoublev(e, &v);    }

	template<class T, GLenum E> struct gl_getter
	{
		inline gl_getter() noexcept { gl_get(value, E); }

		//!
		//!

		T value;
	};

} //! shape::video
} //! shape

#endif
