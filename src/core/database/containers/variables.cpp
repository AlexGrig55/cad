#include <cad/core/database/containers/variables.h>
#include<cad/util/var_values/var_values.h>
#include "../../../translator/translator.hpp"

using namespace cad::util;
using namespace cad::types;
typedef cad::enums::Version Ver;

enum VarIndex
{
	Version=0,
	Locale = 1,
};

cad::Database::Variables::Variables(enums::Locale locale, enums::Version ver)noexcept:
	_generalVarsInc(&_generalVars),
	_generalVars{
		Variable{"$ACADVER",		VersionsList::getVersionName(ver),	1					},	//0
		Variable{"$DWGCODEPAGE",	LocalesList::getLocaleName(locale),	3					},	//1
		Variable{"$LASTSAVEDBY",	"",								1,		Ver::V2004	},	//2
		Variable{"$LTSCALE",		real(1.),						40					},	//3
		Variable{"$DIMSCALE",		real(1.),						40					},	//4
		Variable{"$PDMODE",			int16(0),						70					},	//5
		Variable{"$PDSIZE",			real(5.),						40					},	//6
		Variable{"$HANDSEED",		"",								5					},	//7
		Variable{"$LWDISPLAY",		boolean(1),						290,	Ver::V2000	},	//8

		Variable{"$USERI1",			int16(0),						70,					},	//9
		Variable{"$USERI2",			int16(0),						70,					},	//10
		Variable{"$USERI3",			int16(0),						70,					},	//11
		Variable{"$USERI4",			int16(0),						70,					},	//12
		Variable{"$USERI5",			int16(0),						70,					},	//13
		Variable{"$USERR1",			real(0.),						40,					},	//14
		Variable{"$USERR2",			real(0.),						40,					},	//15
		Variable{"$USERR3",			real(0.),						40,					},	//16
		Variable{"$USERR4",			real(0.),						40,					},	//17
		Variable{"$USERR5",			real(0.),						40,					}	//18
	}
{
	_customVars.reserve(140);
}

cad::Variable* cad::Database::Variables::variable(const char* name) noexcept
{
	for (auto& i : _generalVars)
	{
		if (i.name() == name)
		{
			return &i;
		}
	}
	for (auto& i : _customVars)
	{
		if (i.name() == name)
		{
			return &i;
		}
	}
	return nullptr;
}

const cad::Variable* cad::Database::Variables::variable(const char* name) const noexcept
{
	for (auto& i : _generalVars)
	{
		if (i.name()==name)
		{
			return &i;
		}
	}
	for (auto& i : _customVars)
	{
		if (i.name()== name)
		{
			return &i;
		}
	}
	return nullptr;
}

cad::Variable* cad::Database::Variables::variable(uint32_t i) noexcept
{
	cad::Variable* res = nullptr;
	if (i>= countGeneral()+countCustom())
		return res;

	if (i>= countGeneral())
	{
		i -= countGeneral();
		auto iter = _customVars.begin();
		std::advance(iter,i);
		res = &*iter;
	}
	else
	{
		res = &_generalVars[i];
	}
	return res;
}

const cad::Variable* cad::Database::Variables::variable(uint32_t i) const noexcept
{
	const cad::Variable* res = nullptr;
	if (i >= countGeneral() + countCustom())
		return res;

	if (i >= countGeneral())
	{
		i -= countGeneral();
		auto iter = _customVars.begin();
		std::advance(iter, i);
		res = &*iter;
	}
	else
	{
		res = &_generalVars[i];
	}
	return res;
}

void cad::Database::Variables::add(const Variable& var)
{
	if (isVariableExsist(var.name().data()))
		throw std::exception("Variable with same name already exsists");
	else if(var.typeData()==types::EType::Unk)
		throw std::exception("Invalid variable type");
	else
		_customVars.emplace_back(var);
}

void cad::Database::Variables::remove(uint32_t i, bool globalIndex)
{
	if (globalIndex)
		i -= countGeneral();

	assert(i < _customVars.size());

	_customVars.erase(_customVars.begin() + i);
}

using tr = cad::translator::BaseDxfTranslator;

cad::Error::Code cad::Database::Variables::readDXF(translator::DXFInput& reader) noexcept
{
	int16_t code;
	reader.readCode(&code);
	std::string_view str;
	std::string tmpStr;

	cad::Variable* varPtr;

	Error::Code errCode = Error::Code::NoErr;
	bool stop = false;

	while (!stop && reader.isGood() && errCode == Error::Code::NoErr)
	{
		code = reader.lastCode();
		reader.readValue(str);

		switch (code)
		{
		case tr::DXF_DATA_NAMES[tr::EndSec].first:

			if (str != tr::DXF_DATA_NAMES[tr::EndSec].second)
				errCode = Error::Code::InvalidDataInFile;

			stop = true;
			break;

		case 9:
		{
			tmpStr = str;
			varPtr = this->variable(tmpStr.data());
			bool isGeneralVar = varPtr;
			if (!isGeneralVar)
			{
				//min need for create dummy
				varPtr = &_customVars.emplace_back(Variable(tmpStr.data(), 0,
					std::numeric_limits<int16_t>::min()));
			}

			errCode = tr::callReadObj(*varPtr, reader);

			if (isGeneralVar)
			{
				if (varPtr==&_generalVars[VarIndex::Version])
				{
					reader.setVersion(util::VersionsList::getVersionNum(
						_generalVars[VarIndex::Version].get<types::String>()));
				}
				else if (varPtr == &_generalVars[VarIndex::Locale])
				{
					reader.setLocale(util::LocalesList::getLocaleNum(
						_generalVars[VarIndex::Locale].get<types::String>()));
				}
			}
		}
			break;

		default:
			stop = true;
			errCode = Error::Code::InvalidDataInFile;
		}
	}

	return errCode;
}

cad::Error::Code cad::Database::Variables::writeDXF(translator::DXFOutput& writer) noexcept
{

	const auto& sec = tr::DXF_DATA_NAMES[tr::Section];
	const auto& endSec = tr::DXF_DATA_NAMES[tr::EndSec];

	Error::Code errCode = writer.writeData(sec.first, sec.second);
	writer.writeData(2, dxfName());

	for (auto& var : this->_generalVars)
	{
		errCode = tr::callWriteObj(var, writer);
		if (errCode != Error::Code::NoErr)
			return errCode;
	}
	for (auto& var : this->_customVars)
	{
		errCode = tr::callWriteObj(var, writer);
		if (errCode != Error::Code::NoErr)
			return errCode;
	}

	return writer.writeData(endSec.first, endSec.second);
}


