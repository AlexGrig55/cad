#pragma once
#include <string>
#include <cad/util/defines/defines.hpp>
#include <cad/types/types.hpp>
#include <cad/enums/enums.hpp>

namespace cad::translator
{
	class DXFInput
	{
	private:
		const types::byte* _currentPos;

		const types::byte* const DATA;
		const types::byte* const END;
		const size_t SIZE;

		int16_t _lastCode;

		enums::Version				_version;
		enums::Locale				_locale;

	protected:
		void setLastCode(int16_t code) noexcept { _lastCode = code; }

	public:
		constexpr DXFInput(const types::byte* data, size_t size)noexcept :
			DATA(data), SIZE(size), _currentPos(data), END(data+size), _lastCode(-1),
			_version(enums::Version::R12), _locale(enums::Locale::Cyrillic){}

		constexpr auto locale()const noexcept { return _locale; }
		constexpr auto version()const noexcept { return _version; }
		constexpr void setLocale(enums::Locale val)noexcept { _locale=val; }
		constexpr void setVersion(enums::Version val)noexcept { _version=val; }

		constexpr auto lastCode()const noexcept { return _lastCode; }
		constexpr bool isGood()const noexcept { return _currentPos < END; }
		constexpr auto sizeFile()const noexcept { return SIZE; }
		constexpr const types::byte* currentPos()const noexcept { return _currentPos; }
		constexpr auto offset()const noexcept{ return _currentPos-DATA; }

		constexpr void addOffset(int32_t val) noexcept { _currentPos += val; }
		constexpr void setOffset(size_t val) noexcept{ assert(val< SIZE); _currentPos = DATA+ val; }

		//If code ptr is null, set new offset only
		//If the code means a comment, the codes and values will be read automatically
		//until a code not equal to the comment appears.
		virtual void readCode(int16_t* code = nullptr) noexcept = 0;

		//set new offset only
		virtual void readValue() noexcept = 0;

		virtual void readValue(std::string_view& val) noexcept = 0;
		virtual void readValue(types::String& val) noexcept = 0;
		virtual void readValue(int code,int codeX,types::Point2& val) noexcept = 0;
		virtual void readValue(int code,int codeX,types::Point3& val) noexcept = 0;
		virtual void readValue(types::real& val) noexcept = 0;
		virtual void readValue(types::int16& val) noexcept = 0;
		virtual void readValue(types::int32& val) noexcept = 0;
		virtual void readValue(types::int64& val) noexcept = 0;
		virtual void readValue(types::boolean& val) noexcept = 0;
		virtual void readValue(size_t& val,int base=10) noexcept = 0;

	};

	class AsciiDXFInput :public DXFInput
	{
		//return count symbols in row
		uint16_t readRow()const noexcept;

	public:
		constexpr AsciiDXFInput(const types::byte* data, size_t size)noexcept :DXFInput(data, size){}

		void readCode(int16_t* code) noexcept override;

		void readValue() noexcept override;
		void readValue(std::string_view& val) noexcept override;
		void readValue(types::String& val) noexcept override;
		void readValue(int code,int codeX, types::Point2& val) noexcept override;
		void readValue(int code,int codeX, types::Point3& val) noexcept override;
		void readValue(types::real& val) noexcept override;
		void readValue(types::int16& val) noexcept override;
		void readValue(types::int32& val) noexcept override;
		void readValue(types::int64& val) noexcept override;
		void readValue(types::boolean& val) noexcept override;
		void readValue(size_t& val, int base = 10) noexcept override;

	};

	class BinaryDXFInput :public DXFInput
	{
	public:
		constexpr BinaryDXFInput(const types::byte* data, size_t size)noexcept :DXFInput(data, size) {}

		void readCode(int16_t* code) noexcept override;

		void readValue() noexcept override;
		void readValue(std::string_view& val) noexcept override;
		void readValue(types::String& val) noexcept override;
		void readValue(int code, int codeX, types::Point2& val) noexcept override;
		void readValue(int code, int codeX, types::Point3& val) noexcept override;
		void readValue(types::real& val) noexcept override;
		void readValue(types::int16& val) noexcept override;
		void readValue(types::int32& val) noexcept override;
		void readValue(types::int64& val) noexcept override;
		void readValue(types::boolean& val) noexcept override;
		void readValue(size_t& val, int base = 10) noexcept override;

	};
}