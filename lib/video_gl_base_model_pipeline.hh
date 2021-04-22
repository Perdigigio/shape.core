#ifndef SHAPE_VIDEO_GL_BASE_MODEL_PIPELINE_HH__GUARD
#define SHAPE_VIDEO_GL_BASE_MODEL_PIPELINE_HH__GUARD

#include "video_gl_base.hh"

namespace shape
{

	struct base_blend_mask
	{
		static constexpr GLuint R = (1 << 0);
		static constexpr GLuint G = (1 << 1);
		static constexpr GLuint B = (1 << 2);
		static constexpr GLuint A = (1 << 3);
	};

	struct base_blend
	{
		GLuint color_src;
		GLuint color_ops;
		GLuint color_dst;
		GLuint alpha_src;
		GLuint alpha_ops;
		GLuint alpha_dst;
		GLuint write_msk;
	};

	struct base_depth_stencil
	{
		GLuint depth_test;
		GLuint depth_mask;
		GLuint depth_func;

		GLuint stencil_f_fail;
		GLuint stencil_f_fail_depth;
		GLuint stencil_f_pass;
		GLuint stencil_f_func;
		GLuint stencil_b_fail;
		GLuint stencil_b_fail_depth;
		GLuint stencil_b_pass;
		GLuint stencil_b_func;
	};

	struct base_rasterizer
	{
		GLuint fill_mode;
		GLuint cull_mode;

		float depth_bias;
		float depth_bias_clamp;
		float depth_bias_slope;

		GLboolean enable_depth_clip;
		GLboolean enable_multisample;
		GLboolean enable_antialiased_line;
		GLboolean enable_scissor_test;
	};

	struct base_depth_mask
	{
		static constexpr GLuint WRITE = 0xFFFFFFFF;
	};

	struct base_program
	{
		GLuint vshader;
		GLuint hshader;
		GLuint dshader;
		GLuint gshader;
		GLuint fshader;
	};

	struct base_model_pipeline_desc
	{
		base_program program;
		base_blend blend;
		base_depth_stencil depth_stencil;
		base_rasterizer rasterizer;
	};

	//!
	//!

	class cBaseBlend : public base_blend
	{
		static const struct _OFF {} OFF;
		static const struct _ADD {} ADD;
		static const struct _SUB {} SUB;
		static const struct _MUL {} MUL;
		static const struct _MIX_ALPHA {} MIX_ALPHA;
		static const struct _MIX_CONST {} MIX_CONST;

		//!
		//!

		cBaseBlend(const _OFF &) noexcept;
		cBaseBlend(const _ADD &) noexcept;
		cBaseBlend(const _SUB &) noexcept;
		cBaseBlend(const _MUL &) noexcept;
		cBaseBlend(const _MIX_ALPHA &) noexcept;
		cBaseBlend(const _MIX_CONST &) noexcept;
	};

	class cBaseDepthStencil : public base_depth_stencil
	{
		static const struct _OFF {} OFF;
		static const struct _LEQ {} LEQ; //! <=
		static const struct _GEQ {} GEQ; //! >=
		static const struct _ALWAYS_PASS {} ALWAYS_PASS;
		static const struct _ALWAYS_FAIL {} ALWAYS_FAIL;

		//!
		//!

		cBaseDepthStencil(const _OFF &) noexcept;
		cBaseDepthStencil(const _LEQ &) noexcept;
		cBaseDepthStencil(const _GEQ &) noexcept;
		cBaseDepthStencil(const _ALWAYS_PASS &) noexcept;
		cBaseDepthStencil(const _ALWAYS_FAIL &) noexcept;
	};

}

#endif