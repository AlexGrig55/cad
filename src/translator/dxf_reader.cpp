#include "dxf_reader.h"
#include <cad/cad.hpp>


cad::translator::DXFReader::TypeFile cad::translator::DXFReader::getTypeFile(const types::byte* byteArrayData,
	size_t size) const noexcept
{
	std::string_view strView((const char*)byteArrayData,size);
	if (strView.starts_with("AutoCAD Binary DXF"))
	{
		return TypeFile::Binary;
	}
	else
	{
		bool valid = false;
		bool stop = false;
		auto ptr = byteArrayData;
		const auto endPtr = ptr + size;

		while (!stop && ptr < endPtr)
		{
			switch (*ptr++)
			{
			case ' ':
				continue;
			case '0':
				stop = true;
				valid = true;
				break;
			default:
				valid = false;
				stop = true;
				break;
			}
		}

		if (valid)
		{
			stop = false;
			while (!stop && ptr < endPtr)
			{
				switch (*ptr++)
				{
				case '\n':
				case '\r':
					continue;
				case 'S':
					stop = true;
					valid = true;
					break;
				default:
					valid = false;
					stop = true;
					break;
				}
			}

			valid = std::string_view((const char*)(--ptr), 7) == "SECTION";
		}

		if(valid)
			return TypeFile::ASCII;
		else
			return TypeFile::Unk;
	}

}

bool cad::translator::DXFReader::checkIsValidEndOfFile(const types::byte* byteArrayData, size_t size)const noexcept
{
	auto pos = (const char*)byteArrayData + size - 1;
	size_t i = 0;
	for (; i < 10; i++,--pos)
	{
		if (*pos == 'E')
			break;
	}

	if (i>3)
	{
		std::string_view str(pos, i);

		return str.starts_with("EOF");
	}

	return false;
}


cad::Error::Code cad::translator::DXFReader::readHeader(DXFInput& input) noexcept
{
	return callReadObj(DRAWING->variables(), input);
}


cad::Error::Code cad::translator::DXFReader::readClasses(DXFInput& input) noexcept
{
	return callReadObj(DRAWING->classes(), input);
}

using tr = cad::translator::BaseDxfTranslator;

cad::Error::Code readUnknownTab(cad::translator::DXFInput& input)
{
	cad::Error::Code code = cad::Error::Code::NoErr;
	cad::types::int16 dxfCode;
	std::string_view str;

	while (input.isGood() && code == cad::Error::Code::NoErr)
	{
		input.readCode(&dxfCode);

		if (dxfCode == tr::DXF_DATA_NAMES[tr::NameSec::Endtab].first)
		{
			input.readValue(str);
			if (str == tr::DXF_DATA_NAMES[tr::NameSec::Endtab].second)
				break;
		}
		else
			input.readValue();
	}

	return code;
}

cad::Error::Code cad::translator::DXFReader::readTables(DXFInput& input) noexcept
{
	Error::Code code = Error::Code::NoErr;
	int16_t dxfCode;
	std::string_view str;
	constexpr auto& endSec = DXF_DATA_NAMES[NameSec::EndSec];
	bool stop = false;

	while (!stop && input.isGood() && code == Error::Code::NoErr)
	{
		input.readCode(&dxfCode);
		input.readValue(str);

		if (dxfCode != tr::DXF_CODE_OF_NAME_TAB && dxfCode != endSec.first)
		{
			code = Error::Code::InvalidDataInFile;
			break;
		}

		switch (StringConverter::toId(str))
		{
		case StringConverter::toId("APPID"):
			code = callReadObj(DRAWING->appids(), input);
			break;

		case StringConverter::toId("LAYER"):
			code = callReadObj(DRAWING->layers(), input);
			break;

		case StringConverter::toId("LTYPE"):
			code = callReadObj(DRAWING->linetypes(), input);
			break;

		case StringConverter::toId("STYLE"):
			code = callReadObj(DRAWING->styles(), input);
			break;

		case StringConverter::toId("UCS"):
			code = callReadObj(DRAWING->UCSes(), input);
			break;

		case StringConverter::toId("VIEW"):
		case StringConverter::toId("BLOCK_RECORD"):
		case StringConverter::toId("DIMSTYLE"):
		case StringConverter::toId("VPORT"):
			code = readUnknownTab(input);
			break;

		case StringConverter::toId(endSec.second):
			stop = true;
			break;

		case StringConverter::toId(DXF_DATA_NAMES[NameSec::Table].second):
			break;

		default:
			code = readUnknownTab(input);
			break;
		}

	}

	return code;
}


cad::Error::Code cad::translator::DXFReader::readBlocks(DXFInput& input) noexcept
{
	Error::Code code = Error::Code::NoErr;

	code = readUnknown(input);
	return code;
}


cad::Error::Code cad::translator::DXFReader::readEntities(DXFInput& input) noexcept
{
	Error::Code code = Error::Code::NoErr;

	code = readUnknown(input);
	return code;
}


cad::Error::Code cad::translator::DXFReader::readObjects(DXFInput& input) noexcept
{
	Error::Code code = Error::Code::NoErr;

	code = readUnknown(input);

	return code;
}


cad::Error::Code cad::translator::DXFReader::readUnknown(DXFInput& input) noexcept
{
	int16_t dxfCode;
	std::string_view str;
	auto& endSec= DXF_DATA_NAMES[NameSec::EndSec];

	do
	{
		input.readCode(&dxfCode);
		if (dxfCode == endSec.first)
		{
			input.readValue(str);
			if (str == endSec.second)
				return Error::Code::NoErr;
		}
		else
			input.readValue();

	} while (input.isGood());

	return Error::Code::InvalidDataInFile;
}


cad::Error::Code cad::translator::DXFReader::read(const types::byte* byteArrayData, size_t size) noexcept
{
	Error::Code codErr = Error::Code::NoErr;

	auto bufferSize = size;
	DXFInput* iputPtr = nullptr;
	AsciiDXFInput asciiIput((const types::byte*)byteArrayData, bufferSize);
	BinaryDXFInput binaryInput((const types::byte*)byteArrayData, bufferSize);

	switch (getTypeFile(byteArrayData,size))
	{
	case TypeFile::ASCII:
		iputPtr = &asciiIput;
		break;

	case TypeFile::Binary:
		iputPtr = &binaryInput;
		break;

	case TypeFile::Unk:
	default:
		return Error::Code::InvalidDataInFile;
	}

	if (!checkIsValidEndOfFile(byteArrayData, size))
		return Error::Code::InvalidDataInFile;

	int16_t code;
	std::string_view value;

	bool stop = false;

	while (!stop && iputPtr->offset() < bufferSize && codErr == Error::Code::NoErr)
	{
		iputPtr->readCode(&code);
		iputPtr->readValue(value);

		if (code != DXF_CODE_OF_NAME_SEC && code != 0)
		{
			stop = true;
			codErr= Error::Code::InvalidDataInFile;
			break;
		}

		switch (StringConverter::toId(value))
		{
		case StringConverter::toId(DXF_DATA_NAMES[NameSec::Eof].second):
			stop = true;
			break;

		case StringConverter::toId(DXF_DATA_NAMES[NameSec::Section].second):
			break;

		case StringConverter::toId(DXF_DATA_NAMES[NameSec::Header].second):
			codErr = readHeader(*iputPtr);
			break;

		case StringConverter::toId(DXF_DATA_NAMES[NameSec::Classes].second):
			codErr = readClasses(*iputPtr);
			break;

		case StringConverter::toId(DXF_DATA_NAMES[NameSec::Tables].second):
			codErr = readTables(*iputPtr);
			break;

		case StringConverter::toId(DXF_DATA_NAMES[NameSec::Blocks].second):
			codErr = readBlocks(*iputPtr);
			break;

		case StringConverter::toId(DXF_DATA_NAMES[NameSec::BaseEntity].second):
			codErr = readEntities(*iputPtr);
			break;

		case StringConverter::toId(DXF_DATA_NAMES[NameSec::Obj].second):
			codErr = readTables(*iputPtr);
			break;

		default:
			codErr = readUnknown(*iputPtr);
			break;
		}
	}

	if (!stop && codErr == Error::Code::NoErr)
		codErr = Error::Code::InvalidDataInFile;

	return codErr;
}