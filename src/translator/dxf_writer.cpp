#include "dxf_writer.h"
#include <cad/cad.hpp>

cad::Error::Code cad::translator::DXFWriter::write(std::vector<types::byte>& buffer,bool isBinary) noexcept
{
	Error::Code codErr = Error::Code::NoErr;

	AsciiDXFOutput asciiInput(buffer, version(), locale());
	BinaryDXFOutput binaryInput(buffer, version(), locale());
	DXFOutput* outputPtr = nullptr;

	if (isBinary)
		outputPtr = &binaryInput;
	else
		outputPtr = &asciiInput;

	codErr = writeVars(*DRAWING, *outputPtr);
	if (codErr != Error::Code::NoErr)
		return codErr;

	codErr = writeClasses(*DRAWING, *outputPtr);
	if (codErr != Error::Code::NoErr)
		return codErr;

	codErr = writeTables(*DRAWING, *outputPtr);
	if (codErr != Error::Code::NoErr)
		return codErr;

	codErr = writeBlocks(*DRAWING, *outputPtr);
	if (codErr != Error::Code::NoErr)
		return codErr;

	codErr = writeEntities(*DRAWING, *outputPtr);
	if (codErr != Error::Code::NoErr)
		return codErr;

	codErr = writeObjects(*DRAWING, *outputPtr);
	if (codErr != Error::Code::NoErr)
		return codErr;

	codErr = outputPtr->writeData(0, "EOF");

	outputPtr->removeEmptySpace();

	return codErr;
}

cad::Error::Code cad::translator::DXFWriter::writeStartSec(std::string_view name, DXFOutput& output) noexcept
{
	output.writeData(DXF_DATA_NAMES[Section].first, DXF_DATA_NAMES[Section].second);
	return output.writeData(DXF_CODE_OF_NAME_SEC, name);
}

cad::Error::Code cad::translator::DXFWriter::writeEndSec(DXFOutput& output) noexcept
{
	return output.writeData(DXF_DATA_NAMES[EndSec].first, DXF_DATA_NAMES[EndSec].second);
}

cad::Error::Code cad::translator::DXFWriter::writeVars(Database& drawing, DXFOutput& output) noexcept
{
	auto errCode = writeStartSec(drawing.variables().dxfName(), output);

	errCode = callWriteObj(drawing.variables(), output);

	errCode = writeEndSec(output);

	return errCode;
}

cad::Error::Code cad::translator::DXFWriter::writeClasses(Database& drawing, DXFOutput& output) noexcept
{
	if (output.version() <= enums::Version::R12)
		return Error::Code::NoErr;

	auto errCode = writeStartSec(drawing.classes().dxfName(), output);

	errCode = callWriteObj(drawing.classes(), output);

	errCode = writeEndSec(output);

	return errCode;
}

cad::Error::Code cad::translator::DXFWriter::writeTables(Database& drawing, DXFOutput& output) noexcept
{
	auto errCode = writeStartSec(DXF_DATA_NAMES[Tables].second, output);

	errCode = callWriteObj(drawing.vports(), output);
	if (errCode != Error::Code::NoErr)
		return errCode;

	errCode = callWriteObj(drawing.linetypes(), output);
	if (errCode != Error::Code::NoErr)
		return errCode;

	errCode = callWriteObj(drawing.layers(), output);
	if (errCode != Error::Code::NoErr)
		return errCode;

	errCode = callWriteObj(drawing.styles(), output);
	if (errCode != Error::Code::NoErr)
		return errCode;

	errCode = callWriteObj(drawing.views(), output);
	if (errCode != Error::Code::NoErr)
		return errCode;

	errCode = callWriteObj(drawing.ucses(), output);
	if (errCode != Error::Code::NoErr)
		return errCode;

	errCode = callWriteObj(drawing.appids(), output);
	if (errCode != Error::Code::NoErr)
		return errCode;

	errCode = callWriteObj(drawing.dimstyles(), output);
	if (errCode != Error::Code::NoErr)
		return errCode;

	errCode = callWriteObj(drawing.blocks(), output, 0);
	if (errCode != Error::Code::NoErr)
		return errCode;

	errCode = writeEndSec(output);

	return errCode;
}

cad::Error::Code cad::translator::DXFWriter::writeBlocks(Database& drawing, DXFOutput& output) noexcept
{
	auto errCode = writeStartSec(drawing.blocks().dxfName(), output);

	errCode = callWriteObj(drawing.blocks(), output, 1);

	errCode = writeEndSec(output);

	return errCode;
}

cad::Error::Code cad::translator::DXFWriter::writeEntities(Database& drawing, DXFOutput& output) noexcept
{
	auto errCode = writeStartSec(DXF_DATA_NAMES[Entities].second, output);

	auto& modelSpace = drawing.blocks().list()[0];
	auto& paperSpace = drawing.blocks().list()[1];

	for (auto& entity : modelSpace->entities())
	{
		errCode = callWriteObj(*entity, output);
		if (errCode != Error::Code::NoErr)
			return errCode;
	}
	for (auto& entity : paperSpace->entities())
	{
		errCode = callWriteObj(*entity, output);
		if (errCode != Error::Code::NoErr)
			return errCode;
	}
	errCode = writeEndSec(output);

	return errCode;
}

cad::Error::Code cad::translator::DXFWriter::writeObjects(Database& drawing, DXFOutput& output) noexcept
{
	if (output.version() <= enums::Version::R12)
		return Error::Code::NoErr;

	auto errCode = writeStartSec(DXF_DATA_NAMES[Objects].second, output);

	//errCode = callWriteObj(drawing.en(), output);

	errCode = writeEndSec(output);

	return errCode;
}
