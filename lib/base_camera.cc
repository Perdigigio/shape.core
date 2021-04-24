#include "base_camera.hh"

#include "math_matrix.hh"
#include "math_vector.hh"
#include "math_affine.hh"

#include "math_quaternion.hh"

namespace shape
{

	void base_camera::rotate_x(base_camera *p_cam, float angle) noexcept
	{
		q_rotate(p_cam->view_fwd, cross(p_cam->view_top, p_cam->view_fwd), angle, p_cam->view_fwd);
		q_rotate(p_cam->view_top, cross(p_cam->view_top, p_cam->view_fwd), angle, p_cam->view_top);
	}

	void base_camera::rotate_y(base_camera *p_cam, float angle) noexcept { q_rotate(p_cam->view_fwd, p_cam->view_top, angle, p_cam->view_fwd); }
	void base_camera::rotate_z(base_camera *p_cam, float angle) noexcept { q_rotate(p_cam->view_top, p_cam->view_fwd, angle, p_cam->view_top); }

	real4x4 base_camera::get_view(base_camera const *p_cam) noexcept
	{
		real4x4 l_view;

		//!
		//!

		const real3 l_pos = p_cam->view_pos;
		const real3 l_fwd = p_cam->view_fwd;
		const real3 l_tmp = p_cam->view_top;
		const real3 l_rgt = cross(l_tmp, l_fwd);
		const real3 l_top = cross(l_fwd, l_rgt);

		//!
		//! BUILD VIEW MATRIX
		//!

		set(r1(l_view), l_rgt, 0.f);
		set(r2(l_view), l_top, 0.f);
		set(r3(l_view), l_fwd, 0.f);
		set(r4(l_view), l_pos, 1.f);

		//!
		//!

		return transpose(invert(l_view));
	}

	real4x4 base_camera::get_proj(base_camera const *p_cam) noexcept
	{
		float a = 2 * p_cam->proj_nzp / p_cam->proj_wth;
		float b = 2 * p_cam->proj_nzp / p_cam->proj_hth;
		float c = p_cam->proj_fzp / (p_cam->proj_fzp - p_cam->proj_nzp);
		float d = p_cam->proj_fzp / (p_cam->proj_nzp - p_cam->proj_fzp) * p_cam->proj_nzp;

		//!
		//! BUILD VIEW MATRIX
		//!

		const real4x4 l_proj
		{
			a, 0, 0, 0,
			0, b, 0, 0,
			0, 0, c, d,
			0, 0, 1, 0
		};

		//!
		//!

		return l_proj;
	}



//!	void base_component_dynamic::look_to(base_component_dynamic *p_comp, real3 p_up, real3 p_to) noexcept
//!	{
//!		const real3 l_z = normalize(p_to);
//!		const real3 l_t = normalize(p_up);
//!		const real3 l_x = cross(l_t, l_z);
//!		const real3 l_y = cross(l_z, l_x);
//!		const real3 l_p =
//!		{
//!			dot(l_x, p_comp->pos),
//!			dot(l_y, p_comp->pos),
//!			dot(l_z, p_comp->pos),
//!		};
//!
//!		//!
//!		//!
//!
//!		p_comp->top = l_y;
//!		p_comp->fwd = l_z;
//!		p_comp->pos = l_p;
//!	}
//!
//!	void base_component_dynamic::look_at(base_component_dynamic *p_comp, real3 p_up, real3 p_at) noexcept
//!	{
//!		//!
//!		//!
//!
//!		base_component_dynamic::look_to(p_comp, p_up, sub(p_at, p_comp->pos));
//!	}
//!
//!	void base_component_dynamic::rotate_x(base_component_dynamic *p_comp, float p_angle) noexcept
//!	{
//!		real3x3 l_rot;
//!
//!		load_rotate_x(l_rot, p_angle);
//!			mul(p_comp->top, l_rot, p_comp->top);
//!			mul(p_comp->fwd, l_rot, p_comp->fwd);
//!	}
//!
//!	void base_component_dynamic::rotate_y(base_component_dynamic *p_comp, float p_angle) noexcept
//!	{
//!		real3x3 l_rot;
//!
//!		load_rotate_y(l_rot, p_angle);
//!			mul(p_comp->top, l_rot, p_comp->top);
//!			mul(p_comp->fwd, l_rot, p_comp->fwd);
//!	}
//!
//!	void base_component_dynamic::rotate_z(base_component_dynamic *p_comp, float p_angle) noexcept
//!	{
//!		real3x3 l_rot;
//!
//!		load_rotate_z(l_rot, p_angle);
//!			mul(p_comp->top, l_rot, p_comp->top);
//!			mul(p_comp->fwd, l_rot, p_comp->fwd);
//!	}
//!
//!	real4x4 base_component_dynamic::calculate_R(base_component_dynamic const *p_comp) noexcept
//!	{
//!		const real3 z = normalize(p_comp->fwd);
//!		const real3 t = normalize(p_comp->top);
//!		const real3 x = cross(t, z);
//!		const real3 y = cross(z, x);
//!
//!		real4x4 l_R;
//!
//!		//!
//!		//! ASSEMBLE ROTATION FROM x, y, z VERSORS
//!		//!
//!
//!		load_identity(l_R);
//!			set(r1(l_R), x, 0.f);
//!			set(r2(l_R), y, 0.f);
//!			set(r3(l_R), z, 0.f);
//!
//!		//!
//!		//!
//!
//!		return l_R;
//!	}
//!	real4x4 base_component_dynamic::calculate_S(base_component_dynamic const *p_comp) noexcept
//!	{
//!		real4x4 l_S;
//!
//!		//!
//!		//! ASSEMBLE SCALING FROM scl
//!		//!
//!
//!		load_identity(l_S);
//!			set(r1(l_S), x(p_comp->scl), 0.f, 0.f, 0.f);
//!			set(r2(l_S), 0.f, y(p_comp->scl), 0.f, 0.f);
//!			set(r3(l_S), 0.f, 0.f, z(p_comp->scl), 0.f);
//!
//!		//!
//!		//!
//!
//!		return l_S;
//!	}
//!
//!	real4x4 base_component_dynamic::calculate_T(base_component_dynamic const *p_comp) noexcept
//!	{
//!		real4x4 l_T;
//!
//!		//!
//!		//! ASSEMBLE TRANSLATION FROM pos
//!		//!
//!
//!		load_identity(l_T);
//!			set(r1(l_T), 1.f, 0.f, 0.f, x(p_comp->pos));
//!			set(r2(l_T), 0.f, 1.f, 0.f, y(p_comp->pos));
//!			set(r3(l_T), 0.f, 0.f, 1.f, z(p_comp->pos));
//!
//!		//!
//!		//!
//!
//!		return l_T;
//!	}
//!
//!	real4x4 base_component_dynamic::calculate_M(base_component_dynamic const *p_comp) noexcept
//!	{
//!		real4x4 l_M = calculate_R(p_comp);
//!
//!		mul(l_M, calculate_S(p_comp), l_M);
//!		mul(l_M, calculate_T(p_comp), l_M);
//!
//!		return l_M;
//!	}
//!
} //! shape
