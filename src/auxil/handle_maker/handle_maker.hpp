#pragma once
#include <assert.h>

namespace cad::auxil
{
	class HandleMaker
	{
		size_t _handle;
	public:
		HandleMaker(size_t startValueOfHandle) :_handle(startValueOfHandle) {}

		constexpr size_t newHandle()noexcept { return _handle++; }

		constexpr size_t handle()noexcept { return _handle; }
		constexpr void setHandle(size_t val)noexcept { assert(val> _handle); _handle = val; }
	};
}