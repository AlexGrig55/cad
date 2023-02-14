#include "dxf_output.h"
#include <charconv>

template <class T>
inline uint8_t integralNumberToString(char* buffer, uint8_t bufSize, T number, int base = 10) noexcept
{
	static_assert(std::is_integral<T>::value, "Invalid tempalte");

	return std::to_chars(buffer, buffer + bufSize, number, 10).ptr- buffer;
}

template <class T>
uint8_t floatingNumberToString(char* buffer, uint8_t bufSize, T number, int precision) noexcept
{
	static_assert(std::is_floating_point<T>::value,"Invalid tempalte");

	if (precision < 0)
		return std::to_chars(buffer, buffer + bufSize, number).ptr - buffer;
	else
		return std::to_chars(buffer, buffer + bufSize, number,std::chars_format::general, precision).ptr- buffer;
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeCode(int16_t code)
{
	const uint8_t maxCountSpace = 3;
	auto startPtr = bufferForNumbers + maxCountSpace;
	auto size = integralNumberToString(startPtr, startPtr-bufferForNumbers , code);

	if (size == 0)
	{
		assert("Invalid code");
		return cad::Error::Code::IOStreamWritingError;
	}

	while (size< maxCountSpace)
	{
		--startPtr;
		*startPtr = ' ';
		++size;
	}

	writeToBuffer(startPtr, size);
	return toNewLine();
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t code, std::string_view val)
{
	writeCode(code);

	writeToBuffer(val.data(), val.size());
	return toNewLine();
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t code, const types::String& val)
{
	writeCode(code);

	if (version() >= enums::Version::V2007)
	{
		auto str = val.toUtf8();
		writeToBuffer(str.data(), str.size());
	}
	else
	{
		auto str = val.toString();
		writeToBuffer(str.data(), str.size());
	}

	return toNewLine();
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t codeXvalue, const types::Point2& val)
{
	writeData(codeXvalue, val.x());
	writeData(codeXvalue + 10, val.y());

	return Error::Code::NoErr;
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t codeXvalue, const types::Point3& val)
{
	writeData(codeXvalue, val.x());
	writeData(codeXvalue + 10, val.y());
	writeData(codeXvalue + 20, val.z());

	return Error::Code::NoErr;
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t code, types::real val, int precision)
{
	writeCode(code);

	auto size=floatingNumberToString(bufferForNumbers,sizeof(bufferForNumbers),val, precision);
	writeToBuffer(bufferForNumbers, size);

	return toNewLine();
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t code, types::int16 val)
{
	writeCode(code);

	auto size = integralNumberToString(bufferForNumbers, sizeof(bufferForNumbers),val);
	writeToBuffer(bufferForNumbers, size);

	return toNewLine();
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t code, types::int32 val)
{
	writeCode(code);

	auto size = integralNumberToString(bufferForNumbers, sizeof(bufferForNumbers), val);
	writeToBuffer(bufferForNumbers, size);

	return toNewLine();
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t code, types::int64 val)
{
	writeCode(code);

	auto size = integralNumberToString(bufferForNumbers, sizeof(bufferForNumbers), val);
	writeToBuffer(bufferForNumbers, size);

	return toNewLine();
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t code, types::boolean val)
{
	return writeData(code, (types::int16)val);
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t code, size_t val, int base)
{
	writeCode(code);

	auto size = integralNumberToString(bufferForNumbers, sizeof(bufferForNumbers), val);
	writeToBuffer(bufferForNumbers, size);

	return toNewLine();
}




cad::Error::Code cad::translator::BinaryDXFOutput::writeCode(int16_t code)
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t code, std::string_view val)
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t code, const types::String& val)
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t codeXvalue, const types::Point2& val)
{
	return Error::Code();
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t codeXvalue, const types::Point3& val)
{
	return Error::Code();
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t code, types::real val, int precision)
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t code, types::int16 val)
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t code, types::int32 val)
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t code, types::int64 val)
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t code, types::boolean val)
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t code, size_t val, int base )
{
	return cad::Error::Code::NoErr;
}



