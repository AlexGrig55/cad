#pragma once
#include "../../auxil/string/string.hpp"
#include "../../enums/enums.hpp"

namespace cad::entities
{
	class BaseEnty
	{

		bool _visible;

	public:
		BaseEnty():_visible(true){}


		constexpr auto						visible()				const noexcept	{ return _visible; }
		constexpr void						setVisible(bool val)	noexcept		{ _visible = val; }


		//return dxf name of this object
		virtual constexpr const char*		dxfName()				const noexcept = 0;
		virtual constexpr enums::EntyType	type()					const noexcept = 0;

		virtual std::string					toString()				const noexcept = 0;
	};
}
