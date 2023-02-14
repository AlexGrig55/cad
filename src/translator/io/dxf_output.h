#pragma once
#include <string>
#include <cad/util/defines/defines.hpp>
#include <cad/types/types.hpp>
#include <vector>
#include <cad/errors/errors.h>
#include <cad/enums/enums.hpp>

namespace cad::translator
{
	class DXFOutput
	{
	private:
		std::vector<types::byte>&	_byteArray;
		size_t						_availabelSpace;
		types::byte*				_currentPos;
		enums::Version				_version;
		enums::Locale				_locale;

	protected:
		Error::Code writeToBuffer(const void* data, size_t size) noexcept
		{
			if (_availabelSpace < size)
			{
				auto offset = _currentPos - _byteArray.data();
				auto oldSize = _byteArray.size();
				size_t newSize = (oldSize + size) * 1.2;
				if (newSize > _byteArray.max_size())
					return Error::Code::OutOfMemory;

				_byteArray.resize(newSize);
				_currentPos = _byteArray.data() + offset;
				_availabelSpace = newSize - offset;
			}

			memcpy(_currentPos, data, size);
			_currentPos += size;
			_availabelSpace -= size;

			return Error::Code::NoErr;
		}

		virtual Error::Code writeCode(int16_t code) = 0;

	public:
		constexpr DXFOutput(std::vector<types::byte>& byteArray, enums::Version ver, enums::Locale loc)noexcept :
		_byteArray(byteArray),
		_currentPos(byteArray.data()+byteArray.size()),
		_availabelSpace(0),
		_version(ver),
		_locale(loc)
		{	}

		constexpr auto locale()const noexcept { return _locale; }
		constexpr auto version()const noexcept { return _version; }

		virtual Error::Code writeData(int16_t code, std::string_view val) = 0;
		virtual Error::Code writeData(int16_t code, const types::String& val) = 0;
		virtual Error::Code writeData(int16_t codeXvalue, const types::Point2& val) = 0;
		virtual Error::Code writeData(int16_t codeXvalue, const types::Point3& val) = 0;
		//prec=-1 - auto
		virtual Error::Code writeData(int16_t code, types::real val,int precision=-1) = 0;
		virtual Error::Code writeData(int16_t code, types::int16 val) = 0;
		virtual Error::Code writeData(int16_t code, types::int32 val) = 0;
		virtual Error::Code writeData(int16_t code, types::int64 val) = 0;
		virtual Error::Code writeData(int16_t code, types::boolean val) = 0;
		virtual Error::Code writeData(int16_t code, size_t val,int base=10) = 0;

		void removeEmptySpace()noexcept { _byteArray.resize(_byteArray.size()-_availabelSpace); }
	};

	class CAD_API AsciiDXFOutput :public DXFOutput
	{
		char bufferForNumbers[40]{};
		const char newLineSymbols[2]{ '\r','\n'};
		size_t countNewLineSymbols;

		inline Error::Code toNewLine() { return writeToBuffer(newLineSymbols, countNewLineSymbols); }

		Error::Code writeCode(int16_t code) override;

	public:
		constexpr AsciiDXFOutput(std::vector<types::byte>& byteArray, enums::Version ver, enums::Locale loc)noexcept :
		DXFOutput(byteArray,ver,loc),
		countNewLineSymbols(sizeof(newLineSymbols)){}

		Error::Code writeData(int16_t code, std::string_view val) override;
		Error::Code writeData(int16_t code, const types::String& val) override;
		Error::Code writeData(int16_t codeXvalue, const types::Point2& val)override;
		Error::Code writeData(int16_t codeXvalue, const types::Point3& val)override;
		Error::Code writeData(int16_t code, types::real val, int precision=-1) override;
		Error::Code writeData(int16_t code, types::int16 val) override;
		Error::Code writeData(int16_t code, types::int32 val) override;
		Error::Code writeData(int16_t code, types::int64 val) override;
		Error::Code writeData(int16_t code, types::boolean val) override;
		Error::Code writeData(int16_t code, size_t val,int base=10) override;

	};

	class CAD_API BinaryDXFOutput :public DXFOutput
	{
		Error::Code writeCode(int16_t code) override;

	public:
		constexpr BinaryDXFOutput(std::vector<types::byte>& byteArray, enums::Version ver, enums::Locale loc)noexcept :
			DXFOutput(byteArray,ver,loc) {}

		Error::Code writeData(int16_t code, std::string_view val) override;
		Error::Code writeData(int16_t code, const types::String& val) override;
		Error::Code writeData(int16_t codeXvalue, const types::Point2& val)override;
		Error::Code writeData(int16_t codeXvalue, const types::Point3& val)override;
		Error::Code writeData(int16_t code, types::real val, int precision=-1) override;
		Error::Code writeData(int16_t code, types::int16 val) override;
		Error::Code writeData(int16_t code, types::int32 val) override;
		Error::Code writeData(int16_t code, types::int64 val) override;
		Error::Code writeData(int16_t code, types::boolean val) override;
		Error::Code writeData(int16_t code, size_t val, int base = 10) override;

	};
}