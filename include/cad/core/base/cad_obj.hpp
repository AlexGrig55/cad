#pragma once
#include "../../enums/enums.hpp"
#include "../../color/color.h"
#include "../../util/defines/defines.hpp"
#include <string>

namespace cad::base
{
	class ICadObject
	{
	public:
		virtual ~ICadObject() = default;

		//return dxf name of this object
		virtual constexpr const char* dxfObjectName() const noexcept = 0;
	protected:
		//return count readed symbols
		virtual uint32_t fromDXF(std::string_view& buffer, enums::Version ver) noexcept = 0;
		virtual void toDXF(const std::string& buffer, enums::Version ver) noexcept = 0;
	};

	class Handler :public ICadObject
	{
	private:
		size_t _handle;

	protected:
		constexpr void setHandle(size_t val)noexcept { _handle = val; }

	public:
		constexpr Handler()noexcept :_handle(0) {}

		constexpr auto handle()const noexcept { return _handle; }
	};
}
