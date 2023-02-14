#include <cad/core/base/cad_obj.h>
#include "../../translator/translator.hpp"

cad::Error::Code cad::base::NamedObject::readDXF(translator::DXFInput& reader) noexcept
{
	switch (reader.lastCode())
	{
	case 2:
		reader.readValue(_name);
		break;

	default:
		reader.readValue();
		break;
	}

	return Error::Code::NoErr;
}

cad::Error::Code cad::base::NamedObject::writeDXF(translator::DXFOutput& reader) noexcept
{
	return reader.writeData(2, _name);
}
