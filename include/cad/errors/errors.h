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
			NotValidPath,
			OutOfMemory,
			CannotOpenFile,
			IOStreamReadingError,
			IOStreamWritingError,
			InvalidDataInFile
		};

		const auto getErrorText(Code code) { return arrStringErrCodes[code]; }

	private:
		static std::map< Code, std::string> arrStringErrCodes;
	};

}
