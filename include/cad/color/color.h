#pragma once

#include <assert.h>

#include "../util/defines/defines.hpp"
#include "../enums/enums.hpp"

namespace cad
{
	class Color
	{
		uint8_t			_rgb[3];
		enums::Color	_state;

	public:
		constexpr Color(uint8_t r, uint8_t g, uint8_t b):
			_state(enums::Color::Other), _rgb{r,g,b} {}
		explicit constexpr Color(enums::Color val) : _state(val), _rgb{} {}
		//from Autocad Color Index
		explicit constexpr Color(types::int16 ACI) : _state(enums::Color::Other), _rgb{} {}

		constexpr auto r()const noexcept { return _rgb[0]; }
		constexpr auto g()const noexcept { return _rgb[1]; }
		constexpr auto b()const noexcept { return _rgb[2]; }

		types::int16 toACI()const { return 0; }
		uint32_t toRGB24Bit()const { return *(uint32_t*)_rgb; }

		constexpr auto state()const { return _state; }

		bool isByLayer()const { return enums::Color::ByLayer == _state; }
		bool isByBlock()const { return enums::Color::ByBlock == _state; }
	};
}