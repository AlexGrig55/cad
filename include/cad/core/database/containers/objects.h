#pragma once
#include "../database.h"



class cad::Database::Objects: public base::ICadObject
{
	
public:

#pragma region getters_setters
	
#pragma endregion getters_setters


#pragma region actions
	
#pragma endregion actions


#pragma region overrides
	constexpr const char* dxfName() const noexcept override { return "OBJECTS"; }
protected:
	cad::Error::Code readDXF(translator::DXFInput& reader, char auxilData = -1) noexcept override;
	cad::Error::Code writeDXF(translator::DXFOutput& writer, char auxilData = -1) noexcept override;
#pragma endregion overrides
};