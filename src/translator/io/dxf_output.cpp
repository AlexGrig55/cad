#include "dxf_output.h"
#include <charconv>
#include <ranges>

template <class T>
inline uint8_t integralNumberToString(char* buffer, uint8_t bufSize, T number, int base = 10) noexcept
{
	static_assert(std::is_integral<T>::value, "Invalid template");

	return std::to_chars(buffer, buffer + bufSize, number, base).ptr - buffer;
}

template <class T>
uint8_t floatingNumberToString(char* buffer, uint8_t bufSize, T number, int precision) noexcept
{
	static_assert(std::is_floating_point<T>::value,"Invalid template");

	if (precision < 0)
		return std::to_chars(buffer, buffer + bufSize, number).ptr - buffer;
	else
		return std::to_chars(buffer, buffer + bufSize, number,std::chars_format::general, precision).ptr- buffer;
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeCode(int16_t code)noexcept
{
	const uint8_t maxCountSpace = 3;
	auto startPtr = bufferForNumbers + maxCountSpace;
	auto size = integralNumberToString(startPtr, startPtr-bufferForNumbers , code);

	if (size == 0)
	{
		assert(false && "Invalid code");
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

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t code, std::string_view val)noexcept
{
	writeCode(code);

	writeToBuffer(val.data(), val.size());
	return toNewLine();
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t code, const types::String& val)noexcept
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

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t codeXvalue, const types::Point2& val)noexcept
{
	writeData(codeXvalue, val.x());
	writeData(codeXvalue + 10, val.y());

	return Error::Code::NoErr;
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t codeXvalue, const types::Point3& val)noexcept
{
	writeData(codeXvalue, val.x());
	writeData(codeXvalue + 10, val.y());
	writeData(codeXvalue + 20, val.z());

	return Error::Code::NoErr;
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t code, types::real val)noexcept
{
	writeCode(code);

	auto size = floatingNumberToString(bufferForNumbers, sizeof(bufferForNumbers), val, -1);
	writeToBuffer(bufferForNumbers, size);

	return toNewLine();
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t code, types::int16 val)noexcept
{
	static constexpr const int I_OFFSET = 5;
	writeCode(code);
	int offset = I_OFFSET;

	for (auto i : std::views::iota(bufferForNumbers, bufferForNumbers+ offset))
		*i = ' ';

	auto size = integralNumberToString(bufferForNumbers+ offset, sizeof(bufferForNumbers)- offset,val);

	while (offset&& I_OFFSET >= size)
	{
		--offset;
		++size;
	}

	writeToBuffer(bufferForNumbers+ offset, size);

	return toNewLine();
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t code, types::int32 val)noexcept
{
	writeCode(code);

	auto size = integralNumberToString(bufferForNumbers, sizeof(bufferForNumbers), val);
	writeToBuffer(bufferForNumbers, size);

	return toNewLine();
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t code, types::int64 val)noexcept
{
	writeCode(code);

	auto size = integralNumberToString(bufferForNumbers, sizeof(bufferForNumbers), val);
	writeToBuffer(bufferForNumbers, size);

	return toNewLine();
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeData(int16_t code, types::boolean val)noexcept
{
	return writeData(code, (types::int16)val);
}

cad::Error::Code cad::translator::AsciiDXFOutput::writeHandle(int16_t code, size_t hand)noexcept
{
	if (hand==SIZE_MAX)
	{
		//hand = ;
	}

	writeCode(code);

	auto size = integralNumberToString(bufferForNumbers, sizeof(bufferForNumbers), hand, 16);

	for (auto i : std::views::iota(bufferForNumbers, bufferForNumbers + size))
	{
		if (*i > '9')
			*i = std::toupper(*i);
	}

	writeToBuffer(bufferForNumbers, size);



	return toNewLine();
}




cad::Error::Code cad::translator::BinaryDXFOutput::writeCode(int16_t code)noexcept
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t code, std::string_view val)noexcept
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t code, const types::String& val)noexcept
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t codeXvalue, const types::Point2& val)noexcept
{
	return Error::Code();
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t codeXvalue, const types::Point3& val)noexcept
{
	return Error::Code();
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t code, types::real val)noexcept
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t code, types::int16 val)noexcept
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t code, types::int32 val)noexcept
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t code, types::int64 val)noexcept
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeData(int16_t code, types::boolean val)noexcept
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::translator::BinaryDXFOutput::writeHandle(int16_t code, size_t hand)noexcept
{
	return cad::Error::Code::NoErr;
}



