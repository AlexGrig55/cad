#pragma once
#include "../../util/defines/defines.hpp"
#include "../../enums/enums.hpp"
#include "../base/cad_obj.h"

namespace cad
{
	class CAD_API Object:public base::ICadObject
	{
	public:


	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer) noexcept override;
	};
}