#include <cad/errors/errors.h>


std::map< cad::Error::Code, std::string> cad::Error::arrStringErrCodes{
	{Error::Code::NoErr,				"No errors"},
	{Error::Code::NotValidPath,			"Invalid path"},
	{Error::Code::OutOfMemory,			"Out of memory"},
	{Error::Code::CannotOpenFile,		"Can not open file"},
	{Error::Code::IOStreamReadingError,	"IO stream reading error"},
	{Error::Code::IOStreamWritingError,	"IO stream writing error"},
	{Error::Code::InvalidDataInFile,	"Invalid data in file"}
};
