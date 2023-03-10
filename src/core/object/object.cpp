#include <cad/core/object/object.h>

cad::Error::Code cad::Object::readDXF(translator::DXFInput& reader, char auxilData) noexcept
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::Object::writeDXF(translator::DXFOutput& writer, char auxilData) noexcept
{
	return cad::Error::Code::NoErr;
}
