#pragma once
#include "../../util/defines/defines.hpp"
#include "../../enums/enums.hpp"
#include "../base/base.hpp"

namespace cad
{
	class CAD_API Object:public base::ICadObject
	{
	public:


	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader, char auxilData=-1) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer, char auxilData = -1) noexcept override;
	};
}