#ifndef SHAPE_CORE_VIDEO_SHADER_HH__GUARD
#define SHAPE_CORE_VIDEO_SHADER_HH__GUARD

#include "../base.hh"
#include "../type.hh"

namespace shape
{

	template<class Shader> class CoreVideoShader
	{
		/**
		 * @param lhs
		 * @param rhs
		 */
		template<class T> friend void swap(CoreVideoShader<T>&,  CoreVideoShader<T>&);

	public:
		typedef typename Shader::handle_t handle_t;
		typedef typename Shader::length_t length_t;
		typedef typename Shader::source_t source_t;

		//!
		//!

		inline CoreVideoShader() noexcept
		{
			m_handle = handle_t();
			m_length = length_t();
			m_source = source_t();
		}

		inline CoreVideoShader(const CoreVideoShader& p_other) noexcept
		{
			if (!Shader::grab(p_other.m_handle))
			{
				CoreError::error("called Shader::grab on invalid handle");
			}

			//!
			//!

			m_handle = p_other.m_handle;
			m_length = p_other.m_length;
			m_source = p_other.m_source;
		}

		inline CoreVideoShader(handle_t p_handle, length_t p_length, source_t p_source) noexcept
		{
			m_handle = p_handle;
			m_length = p_length;
			m_source = p_source;
		}

		//!
		//! GETTERS
		//!

		inline handle_t getHandle() const { return m_handle; }
		inline length_t getLength() const { return m_length; }
		inline source_t getSource() const { return m_source; }

		//!
		//!

		inline CoreVideoShader& operator=(CoreVideoShader p_other)
		{
			//!
			//! COPY-SWAP
			//!

			return swap(*this, p_other), *this;
		}

		//!
		//!

		~CoreVideoShader()
		{
			Shader::drop(m_handle);
		}

	private:
		handle_t m_handle;
		length_t m_length;
		source_t m_source;
	};

	//!
	//!

	template<class Shader> void swap(CoreVideoShader<Shader>& lhs,  CoreVideoShader<Shader>& rhs)
	{
		std::swap(lhs.m_handle, rhs.m_handle);
		std::swap(lhs.m_length, rhs.m_length);
		std::swap(lhs.m_source, rhs.m_source);
	}

}

#endif