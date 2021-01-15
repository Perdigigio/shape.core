#ifndef SHAPE_VIDEO_BASE_HH__GUARD
#define SHAPE_VIDEO_BASE_HH__GUARD

#include "../base.hh"
#include "../type.hh"

namespace shape {
namespace video {

	struct pixel
	{
		static constexpr auto LUMA = fourcc('L', 'U', 'M', 'A'); //! r:8
		static constexpr auto BM16 = fourcc('B', 'M', '1', '6'); //! b:5 g:6 r:5
		static constexpr auto BM24 = fourcc('B', 'M', '2', '4'); //! b:8 g:8 r:8
		static constexpr auto BM32 = fourcc('B', 'M', '3', '2'); //! b:8 g:8 r:8 a:8
		static constexpr auto DXT1 = fourcc('D', 'X', 'T', '1'); //! b:5 g:6 r:5
		static constexpr auto DXT3 = fourcc('D', 'X', 'T', '3'); //! b:5 g:6 r:5 a:4
		static constexpr auto DXT5 = fourcc('D', 'X', 'T', '5'); //! b:5 g:6 r:5 a:8
		static constexpr auto ATI1 = fourcc('A', 'T', 'I', '1'); //! r:8
		static constexpr auto ATI2 = fourcc('A', 'T', 'I', '2'); //! r:8 g:8
		static constexpr auto ETC1 = fourcc('E', 'T', 'C', '1'); //!
		static constexpr auto ETC2 = fourcc('E', 'T', 'C', '2'); //!
		static constexpr auto HD32 = fourcc('H', 'D', '3', '2'); //! r:11 g:11 b:10
		static constexpr auto HD64 = fourcc('H', 'D', '6', '4'); //! r:16 g:16 b:16 a:16
	};

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
	};

	struct base_blend_buffer
	{
		real4 dq0[128];
		real4 dq1[128];
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
