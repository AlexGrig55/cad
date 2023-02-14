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


	codErr = callWriteObj(DRAWING->variables(), *outputPtr);
	if (codErr!= Error::Code::NoErr)
		return codErr;

	codErr = callWriteObj(DRAWING->classes(), *outputPtr);
	if (codErr != Error::Code::NoErr)
		return codErr;


	codErr = outputPtr->writeData(0, "EOF");

	outputPtr->removeEmptySpace();

	return codErr;
}
