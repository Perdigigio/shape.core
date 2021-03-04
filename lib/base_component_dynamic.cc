#include "base_component_dynamic.hh"

#include "math_matrix.hh"
#include "math_vector.hh"
#include "math_affine.hh"

namespace shape
{

	void base_component_dynamic::look_to(base_component_dynamic *p_comp, real3 p_up, real3 p_to) noexcept
	{
		const real3 l_z = normalize(p_to);
		const real3 l_t = normalize(p_up);
		const real3 l_x = cross(l_t, l_z);
		const real3 l_y = cross(l_z, l_x);
		const real3 l_p =
		{
			dot(l_x, p_comp->pos),
			dot(l_y, p_comp->pos),
			dot(l_z, p_comp->pos),
		};

		//!
		//!

		p_comp->top = l_y;
		p_comp->fwd = l_z;
		p_comp->pos = l_p;
	}

	void base_component_dynamic::look_at(base_component_dynamic *p_comp, real3 p_up, real3 p_at) noexcept
	{
		//!
		//!

		base_component_dynamic::look_to(p_comp, p_up, sub(p_at, p_comp->pos));
	}

	void base_component_dynamic::rotate_x(base_component_dynamic *p_comp, float p_angle) noexcept
	{
		real3x3 l_rot;

		load_rotate_x(l_rot, p_angle);
			mul(p_comp->top, l_rot, p_comp->top);
			mul(p_comp->fwd, l_rot, p_comp->fwd);
	}

	void base_component_dynamic::rotate_y(base_component_dynamic *p_comp, float p_angle) noexcept
	{
		real3x3 l_rot;

		load_rotate_y(l_rot, p_angle);
			mul(p_comp->top, l_rot, p_comp->top);
			mul(p_comp->fwd, l_rot, p_comp->fwd);
	}

	void base_component_dynamic::rotate_z(base_component_dynamic *p_comp, float p_angle) noexcept
	{
		real3x3 l_rot;

		load_rotate_z(l_rot, p_angle);
			mul(p_comp->top, l_rot, p_comp->top);
			mul(p_comp->fwd, l_rot, p_comp->fwd);
	}

	real4x4 base_component_dynamic::calculate_R(base_component_dynamic const *p_comp) noexcept
	{
		const real3 z = normalize(p_comp->fwd);
		const real3 t = normalize(p_comp->top);
		const real3 x = cross(t, z);
		const real3 y = cross(z, x);

		real4x4 l_R;

		//!
		//! ASSEMBLE ROTATION FROM x, y, z VERSORS
		//!

		load_identity(l_R);
			set(r1(l_R), x, 0.f);
			set(r2(l_R), y, 0.f);
			set(r3(l_R), z, 0.f);

		//!
		//!

		return l_R;
	}
	real4x4 base_component_dynamic::calculate_S(base_component_dynamic const *p_comp) noexcept
	{
		real4x4 l_S;

		//!
		//! ASSEMBLE SCALING FROM scl
		//!

		load_identity(l_S);
			set(r1(l_S), x(p_comp->scl), 0.f, 0.f, 0.f);
			set(r2(l_S), 0.f, y(p_comp->scl), 0.f, 0.f);
			set(r3(l_S), 0.f, 0.f, z(p_comp->scl), 0.f);

		//!
		//!

		return l_S;
	}

	real4x4 base_component_dynamic::calculate_T(base_component_dynamic const *p_comp) noexcept
	{
		real4x4 l_T;

		//!
		//! ASSEMBLE TRANSLATION FROM pos
		//!

		load_identity(l_T);
			set(r1(l_T), 1.f, 0.f, 0.f, x(p_comp->pos));
			set(r2(l_T), 0.f, 1.f, 0.f, y(p_comp->pos));
			set(r3(l_T), 0.f, 0.f, 1.f, z(p_comp->pos));

		//!
		//!

		return l_T;
	}

	real4x4 base_component_dynamic::calculate_M(base_component_dynamic const *p_comp) noexcept
	{
		real4x4 l_M = calculate_R(p_comp);

		mul(l_M, calculate_S(p_comp), l_M);
		mul(l_M, calculate_T(p_comp), l_M);

		return l_M;
	}

} //! shape
