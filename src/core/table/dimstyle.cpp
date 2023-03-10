#include <cad/core/table/vport.h>
#include "../../translator/translator.hpp"

enum Codes
{

};

using tr = cad::translator::BaseDxfTranslator;

void cad::table::Dimstyle::init()
{
	_variables.reserve(75);

	_variables.add(Variable("DIMPOST", types::String(), 3, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMAPOST", types::String(), 4, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMBLK", types::String(), 5, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMBLK1", types::String(), 6, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMBLK2", types::String(), 7, enums::Version::R12, enums::Version::V2018));

	_variables.add(Variable("DIMSCALE", types::real(), 40, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMASZ", types::real(), 41, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMEXO", types::real(), 42, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMDLI", types::real(), 43, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMEXE", types::real(), 44, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMRND", types::real(), 45, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMDLE", types::real(), 46, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMTP", types::real(), 47, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMTM", types::real(), 48, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMTXT", types::real(), 140, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMCEN", types::real(), 141, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMTSZ", types::real(), 142, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMALTF", types::real(), 143, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMLFAC", types::real(), 144, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMTVP", types::real(), 145, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMTFAC", types::real(), 146, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMGAP", types::real(), 147, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMALTRND", types::real(), 148, enums::Version::V2000, enums::Version::V2018));

	_variables.add(Variable("DIMTOL", types::int16(), 71, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMLIM", types::int16(), 72, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMTIH", types::int16(), 73, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMTOH", types::int16(), 74, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMSE1", types::int16(), 75, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMSE2", types::int16(), 76, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMTAD", types::int16(), 77, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMZIN", types::int16(), 78, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMAZIN", types::int16(), 79, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMALT", types::int16(), 170, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMALTD", types::int16(), 171, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMTOFL", types::int16(), 172, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMSAH", types::int16(), 173, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMTIX", types::int16(), 174, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMSOXD", types::int16(), 175, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMCLRD", types::int16(), 176, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMCLRE", types::int16(), 177, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMCLRT", types::int16(), 178, enums::Version::R12, enums::Version::V2018));
	_variables.add(Variable("DIMADEC", types::int16(), 179, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMUNIT", types::int16(), 270, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMDEC", types::int16(), 271, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMTDEC", types::int16(), 272, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMALTU", types::int16(), 273, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMALTTD", types::int16(), 274, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMAUNIT", types::int16(), 275, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMFRAC", types::int16(), 276, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMLUNIT", types::int16(), 277, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMDSEP", types::int16(), 278, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMTMOVE", types::int16(), 279, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMJUST", types::int16(), 280, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMSD1", types::int16(), 281, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMSD2", types::int16(), 282, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMTOLJ", types::int16(), 283, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMTZIN", types::int16(), 284, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMALTZ", types::int16(), 285, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMALTTZ", types::int16(), 286, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMFIT", types::int16(), 287, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMUPT", types::int16(), 288, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMATFIT", types::int16(), 289, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMTXSTY", types::String(), 340, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMLDRBLK", types::String(), 341, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMBLK", types::String(), 342, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMBLK1", types::String(), 343, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMBLK2", types::String(), 344, enums::Version::V2000, enums::Version::V2018));

	_variables.add(Variable("DIMLWD", types::int16(), 371, enums::Version::V2000, enums::Version::V2018));
	_variables.add(Variable("DIMLWE", types::int16(), 372, enums::Version::V2000, enums::Version::V2018));
}

cad::table::Dimstyle::Dimstyle(const types::String& name) noexcept :TableRecord(name)
{
	init();
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

cad::Error::Code cad::table::Dimstyle::readDXF(translator::DXFInput& reader, char auxilData) noexcept
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
		reader.readCode(dxfCode);

		switch (dxfCode)
		{
		case 0:
		case 105:
		case 70:
		case 2:
			stop=!readBaseTabRec(dxfCode, reader);
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
				reader.readValue();

			break;
		}
	}

	return errCode;
}

cad::Error::Code cad::table::Dimstyle::writeDXF(translator::DXFOutput& writer, char auxilData) noexcept
{
	auto errCode = writeTabRecordHeader(dxfName(), "AcDbDimstyleTableRecord", writer);

	for (auto& v : _variables)
	{
		if (writer.version() >=v.startVersion()&& writer.version() <= v.endVersion())
			switch (v.typeData())
			{
			case types::EType::Float:
				errCode = writer.writeData(v.code(),v.get<types::real>() );
				break;

			case types::EType::Int16:
				errCode = writer.writeData(v.code(), v.get<types::int16>());
				break;

			case types::EType::String:
				errCode = writer.writeData(v.code(), v.get<types::String>());
				break;

			default:
				assert(false && "wrong type in dim var");
				break;
			}
	}

	return errCode;
}