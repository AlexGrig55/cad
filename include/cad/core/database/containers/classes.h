#pragma once
#include "../database.h"
#include "../../class/class.h"
#include "../../../util/container/container.hpp"

#include <vector>

class cad::Database::Classes: public util::ConstContainer<Class>, public base::ICadObject
{
public:
	Classes();

#pragma region overrides
	constexpr const char* dxfName() const noexcept override { return "CLASSES"; }

protected:


	cad::Error::Code readDXF(translator::DXFInput& reader, char auxilData = -1) noexcept override;
	cad::Error::Code writeDXF(translator::DXFOutput& writer, char auxilData = -1) noexcept override;
#pragma endregion overrides
};