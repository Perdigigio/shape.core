#ifndef SHAPE_VIDEO_BASE_MODEL_PARANS_HH__GUARD
#define SHAPE_VIDEO_BASE_MODEL_PARANS_HH__GUARD

#include "video_gl_base.hh"

namespace shape {
namespace video {

	struct base_model_params
	{
		GLuint model_handle;
		GLuint model_stride;
		GLuint model_length;
		GLuint model_offset;
		GLuint frame_handle;
		GLuint frame_stride;
		GLuint frame_length;
		GLuint frame_offset;
		GLuint blend_handle;
		GLuint blend_stride;
		GLuint blend_length;
		GLuint blend_offset;

		GLvoid *model_buffer;
		GLvoid *frame_buffer;
		GLvoid *blend_buffer;

		//! --------------------------------------------------------------------------

		static bool init(base_model_params *, GLuint, GLuint, GLuint) noexcept;

		//! --------------------------------------------------------------------------

		static void discard_model(base_model_params *) noexcept;
		static void discard_frame(base_model_params *) noexcept;
		static void discard_blend(base_model_params *) noexcept;

		//! --------------------------------------------------------------------------

		static void next_model(base_model_params *) noexcept;
		static void next_frame(base_model_params *) noexcept;
		static void next_blend(base_model_params *) noexcept;

		static void copy_model(base_model_params const *, base_model_buffer const *) noexcept;
		static void copy_frame(base_model_params const *, base_frame_buffer const *) noexcept;
		static void copy_blend(base_model_params const *, base_blend_buffer const *) noexcept;
		static void bind_model(base_model_params const *, GLuint) noexcept;
		static void bind_frame(base_model_params const *, GLuint) noexcept;
		static void bind_blend(base_model_params const *, GLuint) noexcept;

		//! --------------------------------------------------------------------------

		static void free(base_model_params *) noexcept;
	};

	//!
	//!

	class cBaseModelParams : private base_model_params
	{
	public:
		inline cBaseModelParams() noexcept
		{
			this->model_handle = {};
			this->model_stride = {};
			this->model_length = {};
			this->model_offset = {};
			this->frame_handle = {};
			this->frame_stride = {};
			this->frame_length = {};
			this->frame_offset = {};
			this->blend_handle = {};
			this->blend_stride = {};
			this->blend_length = {};
			this->blend_offset = {};
			this->model_buffer = {};
			this->frame_buffer = {};
			this->blend_buffer = {};
		}

		inline cBaseModelParams(cBaseModelParams && p_other) noexcept
		{
			std::swap(this->model_handle, p_other.model_handle);
			std::swap(this->model_stride, p_other.model_stride);
			std::swap(this->model_length, p_other.model_length);
			std::swap(this->model_offset, p_other.model_offset);
			std::swap(this->frame_handle, p_other.frame_handle);
			std::swap(this->frame_stride, p_other.frame_stride);
			std::swap(this->frame_length, p_other.frame_length);
			std::swap(this->frame_offset, p_other.frame_offset);
			std::swap(this->blend_handle, p_other.blend_handle);
			std::swap(this->blend_stride, p_other.blend_stride);
			std::swap(this->blend_length, p_other.blend_length);
			std::swap(this->blend_offset, p_other.blend_offset);
			std::swap(this->model_buffer, p_other.model_buffer);
			std::swap(this->frame_buffer, p_other.frame_buffer);
			std::swap(this->blend_buffer, p_other.blend_buffer);
		}

		/**
		 * @param model-num
		 * @param frame-num
		 * @param blend-num
		 */
		cBaseModelParams(GLuint, GLuint, GLuint);

		//!
		//!

		inline void discard_model() noexcept { base_model_params::discard_model(this); }
		inline void discard_frame() noexcept { base_model_params::discard_frame(this); }
		inline void discard_blend() noexcept { base_model_params::discard_blend(this); }

		//! --------------------------------------------------------------------------

		inline void next_model() noexcept { base_model_params::next_model(this); }
		inline void next_frame() noexcept { base_model_params::next_frame(this); }
		inline void next_blend() noexcept { base_model_params::next_blend(this); }

		inline void copy_model(base_model_buffer const *p_src) const noexcept { base_model_params::copy_model(this, p_src); }
		inline void copy_frame(base_frame_buffer const *p_src) const noexcept { base_model_params::copy_frame(this, p_src); }
		inline void copy_blend(base_blend_buffer const *p_src) const noexcept { base_model_params::copy_blend(this, p_src); }
		inline void bind_model(GLuint p_slot) const noexcept { base_model_params::bind_model(this, p_slot); }
		inline void bind_frame(GLuint p_slot) const noexcept { base_model_params::bind_frame(this, p_slot); }
		inline void bind_blend(GLuint p_slot) const noexcept { base_model_params::bind_blend(this, p_slot); }

		//!
		//! GETTERS
		//!

		inline GLuint get_model_handle() const noexcept { return this->model_handle; }
		inline GLuint get_model_stride() const noexcept { return this->model_stride; }
		inline GLuint get_model_length() const noexcept { return this->model_length; }
		inline GLuint get_model_offset() const noexcept { return this->model_offset; }
		inline GLuint get_frame_handle() const noexcept { return this->frame_handle; }
		inline GLuint get_frame_stride() const noexcept { return this->frame_stride; }
		inline GLuint get_frame_length() const noexcept { return this->frame_length; }
		inline GLuint get_frame_offset() const noexcept { return this->frame_offset; }
		inline GLuint get_blend_handle() const noexcept { return this->blend_handle; }
		inline GLuint get_blend_stride() const noexcept { return this->blend_stride; }
		inline GLuint get_blend_length() const noexcept { return this->blend_length; }
		inline GLuint get_blend_offset() const noexcept { return this->blend_offset; }

		//!
		//!

		inline GLvoid * get_model_buffer() const noexcept { return this->model_buffer; }
		inline GLvoid * get_frame_buffer() const noexcept { return this->frame_buffer; }
		inline GLvoid * get_blend_buffer() const noexcept { return this->blend_buffer; }

		//! --------------------------------------------------------------------------

		inline cBaseModelParams& operator= (cBaseModelParams p_other) noexcept
		{
			std::swap(this->model_handle, p_other.model_handle);
			std::swap(this->model_stride, p_other.model_stride);
			std::swap(this->model_length, p_other.model_length);
			std::swap(this->model_offset, p_other.model_offset);
			std::swap(this->frame_handle, p_other.frame_handle);
			std::swap(this->frame_stride, p_other.frame_stride);
			std::swap(this->frame_length, p_other.frame_length);
			std::swap(this->frame_offset, p_other.frame_offset);
			std::swap(this->blend_handle, p_other.blend_handle);
			std::swap(this->blend_stride, p_other.blend_stride);
			std::swap(this->blend_length, p_other.blend_length);
			std::swap(this->blend_offset, p_other.blend_offset);
			std::swap(this->model_buffer, p_other.model_buffer);
			std::swap(this->frame_buffer, p_other.frame_buffer);
			std::swap(this->blend_buffer, p_other.blend_buffer); return *this;
		}

		//! --------------------------------------------------------------------------

		inline ~cBaseModelParams() noexcept { base_model_params::free(this); }
	};

} //! shape::video
} //! shape

#endif
