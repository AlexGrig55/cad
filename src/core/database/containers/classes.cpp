#include <cad/core/database/containers/classes.h>
#include "../../../translator/translator.hpp"

using tr = cad::translator::BaseDxfTranslator;

cad::Database::Classes::Classes():util::ConstContainer<Class>
	{
		Class("ACDBDICTIONARYWDFLT","AcDbDictionaryWithDefault","ObjectDBX Classes"),
		Class("MATERIAL","AcDbMaterial","ObjectDBX Classes"),
		Class("VISUALSTYLE","AcDbVisualStyle","ObjectDBX Classes"),
		Class("SCALE","AcDbScale","ObjectDBX Classes")
	}
{
}

cad::Error::Code cad::Database::Classes::readDXF(translator::DXFInput& reader) noexcept
{
	int16_t code;
	std::string_view str;

	Error::Code errCode = Error::Code::NoErr;
	constexpr auto& endSec = tr::DXF_DATA_NAMES[tr::EndSec];
	bool stop = false;

	while (!stop && reader.isGood() && errCode == Error::Code::NoErr)
	{
		reader.readCode(&code);
		if (code == endSec.first)
		{
			reader.readValue(str);
			switch (StringConverter::toId(str))
			{
			case StringConverter::toId("CLASS"):
				break;

			case StringConverter::toId(endSec.second):
				stop = true;
				break;

			default:
				errCode = Error::Code::InvalidDataInFile;
				break;
			}
		}
		else
			reader.readValue();
	}

	return errCode;
}

cad::Error::Code cad::Database::Classes::writeDXF(translator::DXFOutput& writer) noexcept
{
	const auto& sec = tr::DXF_DATA_NAMES[tr::Section];
	const auto& endSec = tr::DXF_DATA_NAMES[tr::EndSec];

	Error::Code errCode = writer.writeData(sec.first, sec.second);
	writer.writeData(2, dxfName());

	for (auto& c : *this)
		tr::callWriteObj(c, writer);

	errCode = writer.writeData(endSec.first, endSec.second);

	return errCode;
}
