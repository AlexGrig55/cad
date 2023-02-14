#pragma once

#include "../base/cad_obj.h"

namespace cad::table
{
	class CAD_API TableObject:public base::NamedObject
	{
	private:
		types::int16 _standardBitFlags;

	public:
		constexpr TableObject(const types::String& name) noexcept:
			NamedObject(name), _standardBitFlags(0){}

		//flags by code 70
		constexpr auto bitFlags()const noexcept { return _standardBitFlags; }
		//flags by code 70
		constexpr void setBitFlags(types::int16 val)noexcept { _standardBitFlags = val; }

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer) noexcept override;
	};
}