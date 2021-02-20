#ifndef SHAPE_ASSET_SOUND_HH__GUARD
#define SHAPE_ASSET_SOUND_HH__GUARD

#include "type.hh"
#include "base.hh"

namespace shape
{
	struct sound_format
	{
		static constexpr uint32_t PCMa = fourcc('P', 'C', 'M', 'a'); //! BYTE
		static constexpr uint32_t PCMb = fourcc('P', 'C', 'M', 'b'); //! WORD
		static constexpr uint32_t PCMc = fourcc('P', 'C', 'M', 'c'); //! UINT - 24 bit
		static constexpr uint32_t H265 = fourcc('H', '2', '6', '5');
		static constexpr uint32_t FLAC = fourcc('F', 'L', 'A', 'C');
	};

	struct sound
	{
		uint32_t fmt;
		uint32_t chn;
		uint32_t sps;
		uint32_t len;
	};

	//!
	//! CORE SOUND
	//!

	class cSound : private sound
	{
	public:
		/**
		* @param fmt
		* @param chn
		* @param sps
		* @param len
		*/
		inline cSound(uint32_t fmt, uint32_t chn, uint32_t sps, uint32_t len) noexcept
		{
			this->fmt = fmt;
			this->chn = chn;
			this->sps = sps;
			this->len = len;
		}

		//!
		//!

		inline uint32_t get_fmt() const noexcept { return this->fmt; }
		inline uint32_t get_chn() const noexcept { return this->chn; }
		inline uint32_t get_sps() const noexcept { return this->sps; }
		inline uint32_t get_len() const noexcept { return this->len; }

		//!
		//!

		size_t get_stride() const noexcept;
		size_t get_length() const noexcept;
	};

	template<class tag> inline typename buffer<tag>::type_t sound_alloc(const cSound& p_sound)
	{
		//!
		//!

		return buffer_alloc<tag>(p_sound.get_length());
	}

}

#endif