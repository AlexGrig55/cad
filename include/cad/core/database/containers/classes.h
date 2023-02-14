#pragma once
#include "../database.h"
#include "../../class/class.h"
#include "../../../util/container/container.hpp"

#include <vector>

class CAD_API cad::Database::Classes: public util::ConstContainer<Class>, public base::ICadObject
{
public:
	Classes();

#pragma region overrides
	constexpr const char* dxfName() const noexcept override { return "CLASSES"; }

protected:


	cad::Error::Code readDXF(translator::DXFInput& reader) noexcept override;
	cad::Error::Code writeDXF(translator::DXFOutput& writer) noexcept override;
#pragma endregion overrides
};