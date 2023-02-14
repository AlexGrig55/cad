#include <cad/core/table/vport.h>
#include "../../translator/translator.hpp"

enum Codes
{

};

using tr = cad::translator::BaseDxfTranslator;

cad::table::Dimstyle::Dimstyle(const types::String& name) noexcept :TableObject(name), _variables{
	Variable("DIMPOST",		types::String(),	3,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMAPOST",	types::String(),	4,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMBLK",		types::String(),	5,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMBLK1",		types::String(),	6,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMBLK2",		types::String(),	7,		enums::Version::R12,	enums::Version::V2018),

	Variable("DIMSCALE",	types::real(),		40,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMASZ",		types::real(),		41,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMEXO",		types::real(),		42,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMDLI",		types::real(),		43,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMEXE",		types::real(),		44,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMRND",		types::real(),		45,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMDLE",		types::real(),		46,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTP",		types::real(),		47,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTM",		types::real(),		48,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTXT",		types::real(),		140,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMCEN",		types::real(),		141,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTSZ",		types::real(),		142,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMALTF",		types::real(),		143,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMLFAC",		types::real(),		144,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTVP",		types::real(),		145,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTFAC",		types::real(),		146,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMGAP",		types::real(),		147,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMALTRND",	types::real(),		148,	enums::Version::R12,	enums::Version::V2018),

	Variable("DIMTOL",		types::int16(),		71,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMLIM",		types::int16(),		72,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTIH",		types::int16(),		73,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTOH",		types::int16(),		74,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMSE1",		types::int16(),		75,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMSE2",		types::int16(),		76,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTAD",		types::int16(),		77,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMZIN",		types::int16(),		78,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMAZIN",		types::int16(),		79,		enums::Version::R12,	enums::Version::V2018),
	Variable("DIMALT",		types::int16(),		170,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMALTD",		types::int16(),		171,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTOFL",		types::int16(),		172,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMSAH",		types::int16(),		173,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTIX",		types::int16(),		174,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMSOXD",		types::int16(),		175,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMCLRD",		types::int16(),		176,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMCLRE",		types::int16(),		177,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMCLRT",		types::int16(),		178,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMADEC",		types::int16(),		179,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMUNIT",		types::int16(),		270,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMDEC",		types::int16(),		271,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTDEC",		types::int16(),		272,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMALTU",		types::int16(),		273,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMALTTD",	types::int16(),		274,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMAUNIT",	types::int16(),		275,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMFRAC",		types::int16(),		276,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMLUNIT",	types::int16(),		277,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMDSEP",		types::int16(),		278,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTMOVE",	types::int16(),		279,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMJUST",		types::int16(),		280,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMSD1",		types::int16(),		281,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMSD2",		types::int16(),		282,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTOLJ",		types::int16(),		283,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTZIN",		types::int16(),		284,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMALTZ",		types::int16(),		285,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMALTTZ",	types::int16(),		286,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMFIT",		types::int16(),		287,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMUPT",		types::int16(),		288,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMATFIT",	types::int16(),		289,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTXSTY",	types::int16(),		340,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTXSTY",	types::String(),	340,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMTXSTY",	types::String(),	340,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMLDRBLK",	types::String(),	341,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMBLK",		types::String(),	342,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMBLK1",		types::String(),	343,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMBLK2",		types::String(),	344,	enums::Version::R12,	enums::Version::V2018),

	Variable("DIMLWD",		types::int16(),		371,	enums::Version::R12,	enums::Version::V2018),
	Variable("DIMLWE",		types::int16(),		372,	enums::Version::R12,	enums::Version::V2018)
}
{
}

cad::table::Dimstyle::Variable* cad::table::Dimstyle::variableByCode(uint16_t code) noexcept
{
	for (auto& i : _variables)
		if (i.code() == code)
			return &i;
	return nullptr;
}

const cad::table::Dimstyle::Variable* cad::table::Dimstyle::variableByCode(uint16_t code)const noexcept
{
	for (auto& i : _variables)
		if (i.code() == code)
			return &i;
	return nullptr;
}

cad::table::Dimstyle::Variable* cad::table::Dimstyle::variableByName(std::string_view name) noexcept
{
	for (auto& i : _variables)
		if (i.name()==name)
			return &i;
	return nullptr;
}

const cad::table::Dimstyle::Variable* cad::table::Dimstyle::variableByName(std::string_view name)const noexcept
{
	for (auto& i : _variables)
		if (i.name() == name)
			return &i;
	return nullptr;
}

cad::Error::Code cad::table::Dimstyle::readDXF(translator::DXFInput& reader) noexcept
{
	int16_t dxfCode = -1;
	std::string_view str;
	Error::Code errCode = Error::Code::NoErr;
	types::int16 auxilFlag;
	bool stop = false;
	Variable* var;

	types::real auxilR;
	types::int16 auxilI;
	types::String auxilS;

	while (reader.isGood() && !stop)
	{
		reader.readCode(&dxfCode);

		switch (dxfCode)
		{
		case tr::DXF_DATA_NAMES[tr::Endtab].first:
			reader.readValue(str);
			if (str == tr::DXF_DATA_NAMES[tr::Endtab].second)
				stop = true;
			else
				errCode = Error::Code::InvalidDataInFile;
			break;


		default:
			var = variableByCode(dxfCode);
			if (var)
			{
				switch (var->typeData())
				{
				case types::EType::Float:
					reader.readValue(auxilR);
					var->set(auxilR);
					break;

				case types::EType::Int16:
					reader.readValue(auxilI);
					var->set(auxilI);
					break;

				case types::EType::String:
					reader.readValue(auxilS);
					var->set(auxilS);
					break;

				default:
					reader.readValue();
					assert(false&&"wrong type in dim var");
					break;
				}

			}
			else
				errCode = TableObject::readDXF(reader);
			break;
		}
	}

	return errCode;
}

cad::Error::Code cad::table::Dimstyle::writeDXF(translator::DXFOutput& writer) noexcept
{
	Error::Code errCode = TableObject::writeDXF(writer);

	if (errCode != Error::Code::NoErr)
		return errCode;

	if (writer.version() > enums::Version::R12)
		writer.writeData(100, "AcDbDimStyleTableRecord");

	for (auto& v : _variables)
	{
		if (writer.version() >=v.startVersion()&& writer.version() <= v.endVersion())
			switch (v.typeData())
			{
			case types::EType::Float:
				writer.writeData(v.code(),v.get<types::real>() );
				break;

			case types::EType::Int16:
				writer.writeData(v.code(), v.get<types::int16>());
				break;

			case types::EType::String:
				writer.writeData(v.code(), v.get<types::String>());
				break;

			default:
				assert(false && "wrong type in dim var");
				break;
			}
	}

	return errCode;
}