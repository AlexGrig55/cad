#pragma once

#include <assert.h>

#include "../util/defines/defines.hpp"
#include "../enums/enums.hpp"

namespace cad
{
	class CAD_API Color
	{
	public:
		enum DefaultAci :types::int16
		{
			ByBlock = 0,
			Red=1,
			Yellow=2,
			Green=3,
			Cyan=4,
			Blue=5,
			Magenta=6,
			White=7,
			ByLayer=256
		};

	private:
		types::int16 _aci;
		std::array<uint8_t, 3> _rgb;

		static const std::vector<std::array<uint8_t, 3>> aciToRgbLookup;

		//get autocad color index
		static types::int16 rgbToACI(uint8_t r, uint8_t g, uint8_t b) noexcept;

	public:
		Color(uint8_t r, uint8_t g, uint8_t b)noexcept;

		//from Autocad Color Index
		//ACI is invalid - set White color
		explicit constexpr Color(types::int16 ACI)noexcept:
			_aci((ACI > ByLayer || ACI < ByBlock) ? White : ACI) {	_rgb = aciToRgbLookup[_aci]; }

		//autocad color index
		constexpr auto aci()const noexcept { return _aci; }
		constexpr auto r()const noexcept { return _rgb[0]; }
		constexpr auto g()const noexcept { return _rgb[1]; }
		constexpr auto b()const noexcept { return _rgb[2]; }

		constexpr uint32_t toRGB24Bit()const noexcept { return *(uint32_t*)&_rgb; }

		constexpr bool isByLayer()const noexcept{ return DefaultAci::ByLayer == _aci; }
		constexpr bool isByBlock()const noexcept{ return DefaultAci::ByBlock == _aci; }

		constexpr bool operator==(types::int16 ACI)const noexcept { return _aci== ACI; }
		constexpr bool operator!=(types::int16 ACI)const noexcept { return _aci != ACI; }

		constexpr bool operator==(const Color& other)const noexcept { return r() == other.r() && g() == other.g() && b() == other.b(); }
		constexpr bool operator!=(const Color& other)const noexcept { return !(*this==other); }
	};
}