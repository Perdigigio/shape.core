#include "asset_sound.hh"

namespace shape
{
	static size_t get_stride_pcma(const sound *) noexcept;
	static size_t get_stride_pcmb(const sound *) noexcept;
	static size_t get_stride_pcmc(const sound *) noexcept;

	//!
	//!

	size_t cSound::get_stride() const noexcept
	{
		switch (fmt)
		{
			case sound_format::PCMa: return get_stride_pcma(this);
			case sound_format::PCMb: return get_stride_pcmb(this);
			case sound_format::PCMc: return get_stride_pcmc(this);
		}

		//!
		//! DEFAULT to 0
		//!

		return 0;
	}

	size_t cSound::get_length() const noexcept
	{
		switch (fmt)
		{
			case sound_format::PCMa: return get_stride_pcma(this) * this->len;
			case sound_format::PCMb: return get_stride_pcmb(this) * this->len;
			case sound_format::PCMc: return get_stride_pcmc(this) * this->len;
			case sound_format::FLAC: return this->len;
			case sound_format::H265: return this->len;
		}

		//!
		//! DEFAULT to 0
		//!

		return 0;
	}

	//!
	//!

	size_t get_stride_pcma(const sound * p_snd) noexcept { return (p_snd->chn * 010) / 010; }
	size_t get_stride_pcmb(const sound * p_snd) noexcept { return (p_snd->chn * 020) / 010; }
	size_t get_stride_pcmc(const sound * p_snd) noexcept { return (p_snd->chn * 030) / 010; }

}