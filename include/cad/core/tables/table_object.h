#pragma once
#include "../../string/string.h"
#include "../base/cad_obj.hpp"

namespace cad::table
{
	class CAD_API TableObject:public base::Handler
	{
	private:
		String _name;

		bool _isStandardObject;
	public:
		constexpr TableObject(const String& name,bool isStandard) noexcept:
			_name(name), _isStandardObject(isStandard){}

		constexpr const auto& name()				const noexcept { return _name; }
		constexpr void	setName(const String& val)	noexcept { _name = val; }

		constexpr bool isStandardObject()			const noexcept { return _isStandardObject; }

	protected:
		uint32_t fromDXF(std::string_view& buffer, enums::Version ver)noexcept override;
		void toDXF(const std::string& buffer, enums::Version ver)noexcept override;
	};
}