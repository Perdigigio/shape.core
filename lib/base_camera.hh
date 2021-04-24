#ifndef SHAPE_BASE_CAMERA_HH__GUARD
#define SHAPE_BASE_CAMERA_HH__GUARD

#include "base.hh"
#include "math.hh"

namespace shape
{

	struct base_camera
	{
		real3 view_pos;
		real3 view_fwd;
		real3 view_top;

		float proj_wth;
		float proj_hth;
		float proj_nzp;
		float proj_fzp;

		//! ------------------------------------------------------

		static void rotate_x(base_camera *, float) noexcept;
		static void rotate_y(base_camera *, float) noexcept;
		static void rotate_z(base_camera *, float) noexcept;

		//! ------------------------------------------------------

		static real4x4 get_view(base_camera const *) noexcept;
		static real4x4 get_proj(base_camera const *) noexcept;
	};

	class cBaseCamera : private base_camera
	{
	public:
		inline cBaseCamera() noexcept
		{
			this->view_pos = { 0.f, 0.f, 0.f };
			this->view_fwd = { 0.f, 0.f, 1.f };
			this->view_top = { 0.f, 1.f, 0.f };
			this->proj_wth = {};
			this->proj_hth = {};
			this->proj_nzp = {};
			this->proj_fzp = {};
		}

		inline cBaseCamera(float wth, float hth, float nzp, float fzp) noexcept : cBaseCamera{}
		{
			this->proj_wth = wth;
			this->proj_hth = hth;
			this->proj_nzp = nzp;
			this->proj_fzp = fzp;
		}

		inline void rotate_x(float angle) noexcept { base_camera::rotate_x(this, angle); }
		inline void rotate_y(float angle) noexcept { base_camera::rotate_y(this, angle); }
		inline void rotate_z(float angle) noexcept { base_camera::rotate_z(this, angle); }

		//!
		//! SETTERS
		//!

		inline void set_view_pos(real3 p_pos) { this->view_pos = p_pos; }
		inline void set_view_fwd(real3 p_fwd) { this->view_fwd = p_fwd; } //! SHOULD BE NORMALIZED
		inline void set_view_top(real3 p_top) { this->view_top = p_top; } //! SHOULD BE NORMALIZED

		//!
		//! GETTERS
		//!

		inline real4x4 get_view() const noexcept { return base_camera::get_view(this); }
		inline real4x4 get_proj() const noexcept { return base_camera::get_proj(this); }

		inline real3 get_view_pos() const noexcept { return this->view_pos; };
		inline real3 get_view_fwd() const noexcept { return this->view_fwd; };
		inline real3 get_view_top() const noexcept { return this->view_top; };

		inline float get_proj_wth() const noexcept { return this->proj_wth; };
		inline float get_proj_hth() const noexcept { return this->proj_hth; };
		inline float get_proj_nzp() const noexcept { return this->proj_nzp; };
		inline float get_proj_fzp() const noexcept { return this->proj_fzp; };
	};

} //! shape

#endif
