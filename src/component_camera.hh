#ifndef SHAPE_COMPONENT_CAMERA_HH__GUARD
#define SHAPE_COMPONENT_CAMERA_HH__GUARD

#include "base.hh"
#include "type.hh"

namespace shape
{

	struct camera
	{
		real4x4 view;
		real4x4 proj;

		//! --------------------------------------------------------

		static real4 get_pos(camera const *) noexcept;
		static real4 get_top(camera const *) noexcept;
		static real4 get_fwd(camera const *) noexcept;

		//! --------------------------------------------------------

		static void rotate_x(camera *, float) noexcept;
		static void rotate_y(camera *, float) noexcept;
		static void rotate_z(camera *, float) noexcept;

		static void persp(camera *, float, float, float, float) noexcept;
		static void ortho(camera *, float, float, float, float) noexcept;

		static void persp_off_center(camera *, float, float, float, float, float, float) noexcept;
		static void ortho_off_center(camera *, float, float, float, float, float, float) noexcept;

		static void persp_fov(camera *, float, float, float, float) noexcept;

		static void look_to(camera *, real3, real3, real3) noexcept;
		static void look_at(camera *, real3, real3, real3) noexcept;

		static void move_to(camera *, real3) noexcept;
	};

	class cComponentCamera : private camera
	{
		inline cComponentCamera() noexcept
		{
			load_identity(this->view);
			load_identity(this->proj);
		}

		//! -------------------------------------------------------------------------------------------------

		inline real4x4 get_view() const noexcept { return this->view; }
		inline real4x4 get_proj() const noexcept { return this->proj; }

		inline real4 get_pos() const noexcept { return camera::get_pos(this); }
		inline real4 get_top() const noexcept { return camera::get_top(this); }
		inline real4 get_fwd() const noexcept { return camera::get_fwd(this); }

		//! -------------------------------------------------------------------------------------------------

		inline void rotate_x(float angle) noexcept { camera::rotate_x(this, angle); }
		inline void rotate_y(float angle) noexcept { camera::rotate_y(this, angle); }
		inline void rotate_z(float angle) noexcept { camera::rotate_z(this, angle); }

		inline void persp(float w, float h, float n, float f) noexcept { camera::persp(this, w, h, n, f); }
		inline void ortho(float w, float h, float n, float f) noexcept { camera::ortho(this, w, h, n, f); }

		inline void persp_off_center(float l, float r, float b, float t, float n, float f) noexcept { camera::persp_off_center(this, l, r, b, t, n, f); }
		inline void ortho_off_center(float l, float r, float b, float t, float n, float f) noexcept { camera::ortho_off_center(this, l, r, b, t, n, f); }

		inline void persp_fov(float fov, float ratio, float n, float f) noexcept { camera::persp_fov(this, fov, ratio, n, f); }

		inline void look_to(real3 eye, real3 up, real3 fwd) noexcept { camera::look_to(this, eye, up, fwd); }
		inline void look_at(real3 eye, real3 up, real3 obj) noexcept { camera::look_at(this, eye, up, obj); }

		inline void move_to(real3 pos) noexcept { camera::move_to(this, pos); }
	};


} //! shape

#endif
