#include "dxf_input.h"
#include <charconv>

template <class T>
void readFloatingNumber(const char* start,uint16_t size ,T& number) noexcept
{
	static_assert(std::is_floating_point<T>::value,"Invalid template");

	const char* end = start + size;

	while ((*start < '-' || *start > '9') && start < end)
		++start;

	while ((*(end-1) < '-' || *(end - 1) > '9') && start < end)
		--end;

	if (start < end)
		std::from_chars(start, end, number);
}

template <class T>
void readIntegralNumber(const char* start, uint16_t size, T& number,int base=10) noexcept
{
	static_assert(std::is_integral<T>::value, "Invalid template");

	const char* end = start + size;

	while ((*start < '-' || *start > '9') && start < end)
		++start;

	while ((*(end - 1) < '-' || *(end - 1) > '9') && start < end)
		--end;

	if (start < end)
		std::from_chars(start, end, number, base);
	else
		number = 0;
}

constexpr const int MAX_SIZE_ROW = 300;

uint16_t cad::translator::AsciiDXFInput::readRow()const noexcept
{
	uint16_t res = 0;
	auto data = currentPos();

	while (*(data + res) != '\n' && res < MAX_SIZE_ROW)
		++res;

	return res+1;
}

void cad::translator::AsciiDXFInput::readCode(int16_t* code) noexcept
{
	auto localOffset = readRow();
	int16_t tmpCode;

	readIntegralNumber((const char*)(currentPos()), localOffset, tmpCode);
	addOffset(localOffset);

	if (tmpCode == 999)//comment code
	{
		while (tmpCode == 999)
		{
			readValue();

			localOffset = readRow();
			readIntegralNumber((const char*)(currentPos()), localOffset, tmpCode);
			addOffset(localOffset);
		}
	}

	setLastCode(tmpCode);
	if (code)
		*code = tmpCode;
}

void cad::translator::AsciiDXFInput::readValue() noexcept
{
	auto localOffset = readRow();
	addOffset(localOffset);
}

void cad::translator::AsciiDXFInput::readValue(std::string_view& val) noexcept
{
	auto localOffset = readRow();
	if (localOffset == 0)
		return;

	auto currentPtr = (const char*)(currentPos());
	addOffset(localOffset);

	while (localOffset!=0&& *(currentPtr+localOffset-1)<' ')
	{
		--localOffset;
	}

	val = std::string_view(currentPtr, localOffset);
}

void cad::translator::AsciiDXFInput::readValue(types::String& val) noexcept
{
	std::string_view strView;
	readValue(strView);

	if (version() >= enums::Version::V2007)
	{
		val = types::String::fromUtf8(strView);
	}
	else
	{
		val = types::String::fromLatin(strView);
	}
}

void cad::translator::AsciiDXFInput::readValue(int code, int codeX, types::Point2& val) noexcept
{
	auto localOffset = readRow();

	readFloatingNumber((const char*)(currentPos()), localOffset, val[code/codeX-1]);

	addOffset(localOffset);
}

void cad::translator::AsciiDXFInput::readValue(int code, int codeX, types::Point3& val) noexcept
{
	auto localOffset = readRow();

	readFloatingNumber((const char*)(currentPos()), localOffset, val[code/codeX-1]);

	addOffset(localOffset);
}

void cad::translator::AsciiDXFInput::readValue(types::real& val) noexcept
{
	auto localOffset = readRow();

	readFloatingNumber((const char*)(currentPos()), localOffset, val);

	addOffset(localOffset);
}

void cad::translator::AsciiDXFInput::readValue(types::int16& val) noexcept
{
	auto localOffset = readRow();

	readIntegralNumber((const char*)(currentPos()), localOffset, val);

	addOffset(localOffset);
}

void cad::translator::AsciiDXFInput::readValue(types::int32& val) noexcept
{
	auto localOffset = readRow();

	readIntegralNumber((const char*)(currentPos()), localOffset, val);

	addOffset(localOffset);
}

void cad::translator::AsciiDXFInput::readValue(types::int64& val) noexcept
{
	auto localOffset = readRow();

	readIntegralNumber((const char*)(currentPos()), localOffset, val);

	addOffset(localOffset);
}

void cad::translator::AsciiDXFInput::readValue(types::boolean& val) noexcept
{
	types::int16 tmpVal;
	readValue(tmpVal);
	val = tmpVal;
}

void cad::translator::AsciiDXFInput::readValue(size_t& val, int base) noexcept
{
	auto localOffset = readRow();

	readIntegralNumber((const char*)(currentPos()), localOffset, val, base);

	addOffset(localOffset);
}


void cad::translator::BinaryDXFInput::readCode(int16_t* code) noexcept
{

}

void cad::translator::BinaryDXFInput::readValue() noexcept
{
}

void cad::translator::BinaryDXFInput::readValue(std::string_view& val) noexcept
{

}

void cad::translator::BinaryDXFInput::readValue(types::String& val) noexcept
{
	std::string_view strView;
	readValue(strView);


}

void cad::translator::BinaryDXFInput::readValue(int code, int codeX, types::Point2& val) noexcept
{
}

void cad::translator::BinaryDXFInput::readValue(int code, int codeX, types::Point3& val) noexcept
{
}

void cad::translator::BinaryDXFInput::readValue(types::real& val) noexcept
{

}

void cad::translator::BinaryDXFInput::readValue(types::int16& val) noexcept
{

}

void cad::translator::BinaryDXFInput::readValue(types::int32& val) noexcept
{

}

void cad::translator::BinaryDXFInput::readValue(types::int64& val) noexcept
{

}

void cad::translator::BinaryDXFInput::readValue(types::boolean& val) noexcept
{
}

void cad::translator::BinaryDXFInput::readValue(size_t& val, int base) noexcept
{
}
