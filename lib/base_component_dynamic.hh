#ifndef SHAPE_BASE_COMPONENT_DYNAMIC_HH__GUARD
#define SHAPE_BASE_COMPONENT_DYNAMIC_HH__GUARD

#include "base.hh"
#include "math.hh"

namespace shape
{

	struct base_component_dynamic
	{
		real3 top;
		real3 fwd;
		real3 pos;
		real3 scl;

		//! ----------------------------------------------------------------

		static void look_to(base_component_dynamic *, real3, real3) noexcept;
		static void look_at(base_component_dynamic *, real3, real3) noexcept;

		//! ----------------------------------------------------------------

		static void rotate_x(base_component_dynamic *, float) noexcept;
		static void rotate_y(base_component_dynamic *, float) noexcept;
		static void rotate_z(base_component_dynamic *, float) noexcept;

		//! ----------------------------------------------------------------

		static real4x4 calculate_R(base_component_dynamic const *) noexcept;
		static real4x4 calculate_S(base_component_dynamic const *) noexcept;
		static real4x4 calculate_T(base_component_dynamic const *) noexcept;
		static real4x4 calculate_M(base_component_dynamic const *) noexcept;
	};

	//!
	//!

	struct cBaseComponentDynamic : private base_component_dynamic
	{
		inline cBaseComponentDynamic() noexcept
		{
			shape::set(this->top, 0.f, 1.f, 0.f);
			shape::set(this->fwd, 0.f, 0.f, 1.f);
			shape::set(this->pos, 0.f, 0.f, 0.f);
			shape::set(this->scl, 1.f, 1.f, 1.f);
		}

		//! -------------------------------------------------------------------------------------------------

		inline void look_to(real3 up, real3 to) noexcept { base_component_dynamic::look_to(this, up, to); }
		inline void look_at(real3 up, real3 at) noexcept { base_component_dynamic::look_at(this, up, at); }

		//! -------------------------------------------------------------------------------------------------

		inline void rotate_x(float a) noexcept { base_component_dynamic::rotate_x(this, a); }
		inline void rotate_y(float a) noexcept { base_component_dynamic::rotate_y(this, a); }
		inline void rotate_z(float a) noexcept { base_component_dynamic::rotate_z(this, a); }

		//! -------------------------------------------------------------------------------------------------

		inline real4x4 calculate_R() const noexcept { return base_component_dynamic::calculate_R(this); }
		inline real4x4 calculate_S() const noexcept { return base_component_dynamic::calculate_S(this); }
		inline real4x4 calculate_T() const noexcept { return base_component_dynamic::calculate_T(this); }
		inline real4x4 calculate_M() const noexcept { return base_component_dynamic::calculate_M(this); }

		//! -------------------------------------------------------------------------------------------------

		inline void set_top(float x, float y, float z) noexcept { shape::set(this->top, x, y, z); }
		inline void set_fwd(float x, float y, float z) noexcept { shape::set(this->fwd, x, y, z); }
		inline void set_pos(float x, float y, float z) noexcept { shape::set(this->pos, x, y, z); }
		inline void set_scl(float x, float y, float z) noexcept { shape::set(this->scl, x, y, z); }

		inline void set_top(real3 v) noexcept { shape::copy(this->top, v); }
		inline void set_fwd(real3 v) noexcept { shape::copy(this->fwd, v); }
		inline void set_pos(real3 v) noexcept { shape::copy(this->pos, v); }
		inline void set_scl(real3 v) noexcept { shape::copy(this->scl, v); }

		//! -------------------------------------------------------------------------------------------------

		inline real3 get_top() const noexcept { return this->top; }
		inline real3 get_fwd() const noexcept { return this->fwd; }
		inline real3 get_pos() const noexcept { return this->pos; }
		inline real3 get_scl() const noexcept { return this->pos; }
	};

} //! shape

#endif
