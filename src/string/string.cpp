#include <cad/string/string.h>
#include <filesystem>

void cad::String::convertToUpper(const std::locale& locale)
{
	auto& ctype=std::use_facet<std::ctype<wchar_t>> (locale);
	std::transform(begin(), end(), begin(), [&](auto c) {return ctype.toupper(c); });
}

void cad::String::convertToLower(const std::locale& locale)
{
	auto& ctype = std::use_facet<std::ctype<wchar_t>>(locale);
	std::transform(begin(), end(), begin(), [&](auto c) {return ctype.tolower(c); });
}

cad::String cad::String::getUpper(const std::locale& locale) const
{
	String res(size());
	auto& ctype = std::use_facet<std::ctype<wchar_t>>(locale);
	std::transform(begin(), end(), res.begin(), [&](auto c) {return ctype.toupper(c); });
	return res;
}

cad::String cad::String::getLower(const std::locale& locale) const
{
	String res(size());
	auto& ctype = std::use_facet<std::ctype<wchar_t>>(locale);
	std::transform(begin(), end(), res.begin(), [&](auto c) {return ctype.tolower(c); });
	return res;
}

std::string cad::String::toLatin() const
{
	auto wv = std::wstring_view(this->c_str());

	return std::filesystem::_Convert_wide_to<std::char_traits<char>, std::allocator<char>, char>(wv, std::allocator<char>());
}

std::u8string cad::String::toUtf8() const
{
	auto wv = std::wstring_view(this->c_str());

	return std::filesystem::_Convert_wide_to<std::char_traits<char8_t>, std::allocator<char8_t>, char8_t>(wv, std::allocator<char>());
}

std::u16string cad::String::toUtf16() const
{
	auto wv = std::wstring_view(this->c_str());

	return std::filesystem::_Convert_wide_to<std::char_traits<char16_t>, std::allocator<char16_t>, char16_t>(wv, std::allocator<char16_t>());
}

std::u32string cad::String::toUtf32() const
{
	auto wv = std::wstring_view(this->c_str());

	return std::filesystem::_Convert_wide_to<std::char_traits<char32_t>, std::allocator<char32_t>, char32_t>(wv, std::allocator<char32_t>());
}

std::wstring cad::String::toWstring() const
{
	return *this;
}

cad::String cad::String::fromLatin(const std::string& str,bool isUtf8)
{
	std::string_view sv = str;
	if (isUtf8)
	{
		return String(std::filesystem::_Convert_narrow_to_wide(__std_code_page::_Utf8, sv).c_str());
	}
	else
	{
		return String(std::filesystem::_Convert_narrow_to_wide(__std_fs_code_page(), sv).c_str());
	}
}

cad::String cad::String::fromUtf8(const std::u8string& str)
{
	const std::string_view _Input_as_char{ reinterpret_cast<const char*>(str.data()), str.size() };
	String res( std::filesystem::_Convert_narrow_to_wide(__std_code_page::_Utf8, _Input_as_char).c_str());
	return res;
}

cad::String cad::String::fromUtf16(const std::u16string& str)
{
	std::u16string_view usv=str;
	String res(std::filesystem::_Convert_stringoid_to_wide(usv, std::filesystem::_Normal_conversion{}).c_str());

	return res;
}

cad::String cad::String::fromUtf32(const std::u32string& str)
{
	std::u32string_view Usv = str;
	String res(std::filesystem::_Convert_stringoid_to_wide(Usv, std::filesystem::_Normal_conversion{}).c_str());

	return res;
}

cad::String cad::String::fromWstring(const std::wstring & str)
{
	return String(str.c_str());
}
