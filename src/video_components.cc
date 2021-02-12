#include "video_components.hh"

#include "math_matrix.hh"
#include "math_vector.hh"
#include "math_affine.hh"

namespace shape
{
	namespace details
	{
		static constexpr real4 top = { 0, 1, 0, 0 };
		static constexpr real4 fwd = { 0, 0, 1, 0 };
	}

	//!
	//!

	static inline real4x4 get_rotation(real4x4) noexcept;

	//!
	//!

	real4 camera::get_pos(camera const *p_camera) noexcept
	{
		real4 l_pos;

		//!
		//! ASSUME ROW MAJOR
		//!

		x(l_pos) = w(p_camera->view.data[0]);
		y(l_pos) = w(p_camera->view.data[1]);
		z(l_pos) = w(p_camera->view.data[2]);
		z(l_pos) = w(p_camera->view.data[3]);


		//!
		//!

		return l_pos;
	}

	real4 camera::get_top(camera const *p_camera) noexcept { return mul(get_rotation(p_camera->view), details::top); }
	real4 camera::get_fwd(camera const *p_camera) noexcept { return mul(get_rotation(p_camera->view), details::fwd); }

	void camera::rotate_x(camera *p_camera, float p_angle) noexcept { real4x4 m; mul(p_camera->view, p_camera->view, load_rotate_x(m, p_angle)); }
	void camera::rotate_y(camera *p_camera, float p_angle) noexcept { real4x4 m; mul(p_camera->view, p_camera->view, load_rotate_y(m, p_angle)); }
	void camera::rotate_z(camera *p_camera, float p_angle) noexcept { real4x4 m; mul(p_camera->view, p_camera->view, load_rotate_z(m, p_angle)); }

	void camera::persp(camera *p_camera, float w, float h, float n, float f) noexcept
	{
		float a = 2 * n / w;
		float b = 2 * n / h;
		float c = f / (f - n);
		float d = f / (n - f) * n;

		//!
		//!

		copy(r1(p_camera->view), real4{ a, 0, 0, 0 });
		copy(r2(p_camera->view), real4{ 0, b, 0, 0 });
		copy(r3(p_camera->view), real4{ 0, 0, c, d });
		copy(r4(p_camera->view), real4{ 0, 0, 1, 0 });
	}

	void camera::ortho(camera *p_camera, float w, float h, float n, float f) noexcept
	{
		float a = 2 / w;
		float b = 2 / h;
		float c = 1 / (f - n);
		float d = n / (n - f);

		//!
		//!

		copy(r1(p_camera->view), real4{ a, 0, 0, 0 });
		copy(r2(p_camera->view), real4{ 0, b, 0, 0 });
		copy(r3(p_camera->view), real4{ 0, 0, c, d });
		copy(r4(p_camera->view), real4{ 0, 0, 0, 1 });
	}

	void camera::persp_off_center(camera *p_camera, float l, float r, float b, float t, float n, float f) noexcept
	{
		//!
	}

	void camera::ortho_off_center(camera *p_camera, float l, float r, float b, float t, float n, float f) noexcept
	{
		//!
	}

	void camera::persp_fov(camera *p_camera, float fov, float ratio, float n, float f) noexcept
	{
		float h = 1 / std::tan(fov * 0.5f);
		float w = h / (ratio);
		float a = f / (f - n);
		float b = f / (n - f) * n;

		//!
		//!

		copy(r1(p_camera->view), real4{ w, 0, 0, 0 });
		copy(r2(p_camera->view), real4{ 0, h, 0, 0 });
		copy(r3(p_camera->view), real4{ 0, 0, a, b });
		copy(r4(p_camera->view), real4{ 0, 0, 1, 0 });
	}

	void camera::look_to(camera *p_camera, real3 eye, real3 up, real3 fwd) noexcept
	{
		const auto zaxis = normalize(fwd);
		const auto xaxis = normalize(cross(up, zaxis));
		const auto yaxis = cross(zaxis, xaxis);

		copy(r1(p_camera->view), real4{ x(xaxis), y(xaxis), z(xaxis), -dot(xaxis, eye) });
		copy(r2(p_camera->view), real4{ x(yaxis), y(yaxis), z(yaxis), -dot(yaxis, eye) });
		copy(r3(p_camera->view), real4{ x(zaxis), y(zaxis), z(zaxis), -dot(zaxis, eye) });
		copy(r4(p_camera->view), real4{ 0, 0, 0, 1 });
	}

	void camera::look_at(camera *p_camera, real3 eye, real3 up, real3 obj) noexcept
	{
		//!
		//! LOOK AT (LEFT HANDED)
		//!

		camera::look_to(p_camera, eye, up, sub(obj, eye));
	}

	void camera::move_to(camera *p_camera, real3 p_position) noexcept
	{
		w(p_camera->view.data[0]) = x(p_position);
		w(p_camera->view.data[0]) = y(p_position);
		w(p_camera->view.data[0]) = z(p_position);
	}

	//!
	//!

	inline real4x4 get_rotation(real4x4 m) noexcept
	{
		w(m.data[0]) = 0;
		w(m.data[1]) = 0;
		w(m.data[2]) = 0;
		w(m.data[3]) = 1; return m;
	}


} //! shape
