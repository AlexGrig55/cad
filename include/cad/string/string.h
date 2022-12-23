#pragma once
#include <assert.h>
#include <string>
#include <locale>
#include <charconv>

namespace cad
{
	//base string is std::wstring
	class String:protected std::wstring
	{
		typedef std::wstring src_str;
	public:
		constexpr String() {}
		constexpr String(uint32_t size, wchar_t ch=L' ') :src_str(size, ch) {}
		constexpr String(const wchar_t*const str) :src_str(str){}
		constexpr String(const String& other) :src_str(other) {}
		constexpr String(String&& other) : src_str(other) {}

		using src_str::at;
		using src_str::size;

		using src_str::operator+=;
		using src_str::operator=;
		using src_str::operator[];

		using src_str::back;
		using src_str::front;

		using src_str::begin;
		using src_str::end;

		using src_str::capacity;
		using src_str::reserve;
		using src_str::resize;
		using src_str::shrink_to_fit;

		using src_str::clear;
		using src_str::c_str;

		using src_str::data;
		using src_str::empty;

		using src_str::erase;
		using src_str::substr;

		using src_str::find;
		using src_str::rfind;

		using src_str::starts_with;
		using src_str::ends_with;


		void convertToUpper(const std::locale& locale= std::locale(""));
		void convertToLower(const std::locale& locale = std::locale(""));

		String getUpper(const std::locale& locale = std::locale(""))const;
		String getLower(const std::locale& locale = std::locale(""))const;

		template <class T>
		T toNumber(bool* done=nullptr) const;
		std::string toLatin()const;
		std::u8string toUtf8()const;
		std::u16string toUtf16()const;
		std::u32string toUtf32()const;
		std::wstring toWstring()const;

		template <class T>
		static String fromIntegral(T num,int base=10);
		template <class T>
		static String fromFloatingPoint(T num, std::chars_format format = std::chars_format::general);
		static String fromLatin(const std::string& str, bool isUtf8=false);
		static String fromUtf8(const std::u8string& str);
		static String fromUtf16(const std::u16string& str);
		static String fromUtf32(const std::u32string& str);
		static String fromWstring(const std::wstring& str);
	};

	template<class T>
	inline T String::toNumber(bool* done) const
	{
		T resNum=0;
		std::string tmpStr(this->size(),' ');

		uint32_t countSymb = 0;
		for (auto& i : *this)
		{
			if (i < 102 && i > 43)
			{
				tmpStr[countSymb] = i;
				++countSymb;
			}
		}
		auto ptr = tmpStr.data();
		auto res = std::from_chars(ptr, ptr+ countSymb, resNum);

		if (done)
		{
			*done = res.ec==std::errc(0);
		}

		return resNum;
	}

	template<class T>
	inline String String::fromIntegral(T num, int base)
	{
		char buf[21]{};
		auto res=std::to_chars(buf, buf + 21, num, base);
		int size = res.ptr - buf;
		String resStr(size);

		for (int i = 0; i < size; i++)
		{
			resStr[i] = buf[i];
		}

		return resStr;
	}

	template<class T>
	inline String String::fromFloatingPoint(T num, std::chars_format format)
	{
		char buf[21]{};
		auto res = std::to_chars(buf, buf + 21, num, format);
		int size = res.ptr - buf;
		String resStr(size);

		for (int i = 0; i < size; i++)
		{
			resStr[i] = buf[i];
		}

		return resStr;
	}
}