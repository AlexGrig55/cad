#include <cad/core/table/table_object.h>
#include "../../translator/translator.hpp"

cad::Error::Code cad::table::TableObject::readDXF(translator::DXFInput& reader) noexcept
{
	switch (reader.lastCode())
	{
	case 105:
	case 5:
	{
		size_t h;
		reader.readValue(h, 16);
		setHandle(h);
	}
		break;

	case 70:
		reader.readValue(_standardBitFlags);
		break;

	default:
		base::NamedObject::readDXF(reader);
	}

	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::table::TableObject::writeDXF(translator::DXFOutput& writer) noexcept
{
	writer.writeData(0, dxfName());

	if (dxfName()==std::string_view("DIMSTYLE"))
		writer.writeData(105, handle());
	else
		writer.writeData(5, handle());

	writer.writeData(2, name());
	auto err = writer.writeData(70, bitFlags());
	if (writer.version() > enums::Version::R12)
		err= writer.writeData(100, "AcDbSymbolTableRecord");

	return err;
}
