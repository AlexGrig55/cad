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
		const types::byte* _lastCodePos;

		const types::byte* const DATA;
		const types::byte* const END;
		const size_t SIZE;

		enums::Version				_version;
		enums::Locale				_locale;

	protected:
		void setLastCodePos() noexcept { _lastCodePos = _currentPos; }

	public:
		constexpr DXFInput(const types::byte* data, size_t size)noexcept :
			DATA(data), SIZE(size), _currentPos(data), END(data+size), _lastCodePos(data),
			_version(enums::Version::R12), _locale(enums::Locale::Cyrillic){}

		constexpr auto locale()const noexcept { return _locale; }
		constexpr auto version()const noexcept { return _version; }
		constexpr void setLocale(enums::Locale val)noexcept { _locale=val; }
		constexpr void setVersion(enums::Version val)noexcept { _version=val; }

		constexpr bool isGood()const noexcept { return _currentPos < END; }
		constexpr auto sizeFile()const noexcept { return SIZE; }
		constexpr const types::byte* currentPos()const noexcept { return _currentPos; }
		constexpr auto offset()const noexcept{ return _currentPos-DATA; }

		constexpr void addOffset(int32_t val) noexcept { _currentPos += val; }
		constexpr void setOffset(size_t val) noexcept{ assert(val< SIZE); _currentPos = DATA+ val; }

		//set current pos to start of last data code
		constexpr void toLastData()noexcept { _currentPos=_lastCodePos; }
	
		virtual void readCode(int16_t& code) noexcept = 0;

		//set new offset only
		virtual void readValue() noexcept = 0;

		virtual void readValue(std::string_view& val) noexcept = 0;
		virtual void readValue(types::String& val) noexcept = 0;
		virtual void readValue(types::real& val) noexcept = 0;
		virtual void readValue(types::int16& val) noexcept = 0;
		virtual void readValue(types::int32& val) noexcept = 0;
		virtual void readValue(types::int64& val) noexcept = 0;
		virtual void readValue(types::boolean& val) noexcept = 0;
		virtual size_t readHandle() noexcept = 0;

	};

	class AsciiDXFInput :public DXFInput
	{
		//return count symbols in row
		uint16_t readRow()const noexcept;

	public:
		constexpr AsciiDXFInput(const types::byte* data, size_t size)noexcept :DXFInput(data, size){}

		void readCode(int16_t& code) noexcept override;

		void readValue() noexcept override;
		void readValue(std::string_view& val) noexcept override;
		void readValue(types::String& val) noexcept override;
		void readValue(types::real& val) noexcept override;
		void readValue(types::int16& val) noexcept override;
		void readValue(types::int32& val) noexcept override;
		void readValue(types::int64& val) noexcept override;
		void readValue(types::boolean& val) noexcept override;
		size_t readHandle() noexcept override;
	};

	class BinaryDXFInput :public DXFInput
	{
	public:
		constexpr BinaryDXFInput(const types::byte* data, size_t size)noexcept :DXFInput(data, size) {}

		void readCode(int16_t& code) noexcept override;

		void readValue() noexcept override;
		void readValue(std::string_view& val) noexcept override;
		void readValue(types::String& val) noexcept override;
		void readValue(types::real& val) noexcept override;
		void readValue(types::int16& val) noexcept override;
		void readValue(types::int32& val) noexcept override;
		void readValue(types::int64& val) noexcept override;
		void readValue(types::boolean& val) noexcept override;
		size_t readHandle() noexcept override;

	};
}