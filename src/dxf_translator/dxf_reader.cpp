#include "dxf_reader.h"

uint32_t cad::DXFReader::readRow(const char* const startRow,std::string_view& strView) const noexcept
{
	const char* ptr = startRow;

	while (*ptr != '\n'&& ptr< endFile)
		++ptr;

	uint32_t countReaded = ptr - startRow+1;

	ptr = startRow+ countReaded;
	do
	{
		ptr--;
	} while (*ptr=='\r'|| *ptr == '\n');


	strView = std::string_view(startRow, ptr- startRow+1);

	return countReaded;
}


uint32_t cad::DXFReader::readData(const char* const startRow, DXFdata& data) const noexcept
{
	uint32_t count = readRow(startRow, data.val);

	data.code = data.convertValToIntegral<int>();
	count += readRow(startRow+ count, data.val);
	return count;
}


bool cad::DXFReader::checkIsValidEndOfFile()
{
	auto pos = dataPtr + countBytes - 1;
	size_t i = 0;
	for (; dataPtr <= pos; i++,--pos)
	{
		if (*pos == 'E')
			break;

	}

	size_t offsetOfEnd = pos- dataPtr;

	if (i>3)
	{
		std::string_view str(pos, i);

		return str.find("EOF") == 0;
	}

	return false;
}


cad::Error::Code cad::DXFReader::readHeader() noexcept
{
	Error::Code code = Error::Code::NoErr;
	DXFdata auxilData;
	code= readUnknown();
	return code;
}


cad::Error::Code cad::DXFReader::readClasses() noexcept
{
	Error::Code code = Error::Code::NoErr;
	DXFdata auxilData;
	code = readUnknown();
	return code;
}


cad::Error::Code cad::DXFReader::readTables() noexcept
{
	Error::Code code = Error::Code::NoErr;
	DXFdata auxilData;
	code = readUnknown();
	return code;
}


cad::Error::Code cad::DXFReader::readBlocks() noexcept
{
	Error::Code code = Error::Code::NoErr;
	DXFdata auxilData;
	code = readUnknown();
	return code;
}


cad::Error::Code cad::DXFReader::readEntities() noexcept
{
	Error::Code code = Error::Code::NoErr;
	DXFdata auxilData;
	code = readUnknown();
	return code;
}


cad::Error::Code cad::DXFReader::readObjects() noexcept
{
	Error::Code code = Error::Code::NoErr;
	DXFdata auxilData;
	code = readUnknown();
	return code;
}


cad::Error::Code cad::DXFReader::readUnknown() noexcept
{
	Error::Code code = Error::Code::NoErr;
	DXFdata auxilData;

	do
	{
		offset += readData(dataPtr+ offset, auxilData);
	} while (offset<countBytes&& auxilData!=DXF_DATA_NAMES[NameSec::EndSec]);

	return code;
}


cad::Error::Code cad::DXFReader::read(const dxf_buffer& buffer) noexcept
{
	Error::Code codErr = Error::Code::NoErr;

	offset = 0;
	countBytes = buffer.size();
	dataPtr = buffer.data();
	endFile = dataPtr + countBytes;
	std::string_view strView;

	if (!checkIsValidEndOfFile())
		return Error::Code::InvalidDataInFile;

	DXFdata auxilData;

	while (countBytes > offset && codErr == Error::Code::NoErr)
	{
		offset += readData(dataPtr + offset, auxilData);

		if (auxilData == DXF_DATA_NAMES[NameSec::Eof])
		{
			return codErr;//file is valid if return from this plase only;
		}
		else if (auxilData!= DXF_DATA_NAMES[NameSec::Section])
		{
			codErr= Error::Code::InvalidDataInFile;
			continue;
		}

		offset += readData(dataPtr + offset, auxilData);

		switch (StringConverter::toId(auxilData.val))
		{
		case StringConverter::toId(DXF_DATA_NAMES[NameSec::Header].val):
			codErr=readHeader();
			break;

		case StringConverter::toId(DXF_DATA_NAMES[NameSec::Classes].val):
			codErr = readClasses();
			break;

		case StringConverter::toId(DXF_DATA_NAMES[NameSec::Tables].val):
			codErr = readTables();
			break;

		case StringConverter::toId(DXF_DATA_NAMES[NameSec::Blocks].val):
			codErr = readBlocks();
			break;

		case StringConverter::toId(DXF_DATA_NAMES[NameSec::Entity].val):
			codErr = readEntities();
			break;

		case StringConverter::toId(DXF_DATA_NAMES[NameSec::Obj].val):
			codErr = readTables();
			break;

		default:
			codErr = readUnknown();
			break;
		}
	}

	if (codErr == Error::Code::NoErr)
	{
		return Error::Code::InvalidDataInFile;
	}
	return codErr;
}