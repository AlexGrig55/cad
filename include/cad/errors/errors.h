#pragma once
#include <string>
#include <map>

namespace cad
{
	class Error
	{
	public:
		enum class Code
		{
			NoErr,
			InvalidPath,
			OutOfMemory,
			CannotOpenFile,
			IOStreamReadingError,
			IOStreamWritingError,
			InvalidDataInFile,
			InvalidVersion,
			InvalidLocale
		};

		static auto errorText(Code code)noexcept { return arrStringErrCodes[code]; }
		static constexpr const auto& errorsList()noexcept { return arrStringErrCodes; }
	private:
		static std::map< Code, const char*> arrStringErrCodes;
	};

}
