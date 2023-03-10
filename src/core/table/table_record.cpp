#include <cad/core/table/table_record.h>
#include "../../translator/translator.hpp"

namespace cad::table
{
	class ILayerUser;
	class IAppidUser;
	class ILinetypeUser;
	class IStyleUser;
	class IUcsUser;
	class IViewUser;
	class IVportUser;
	class IDimstyleUser;
}

template cad::table::TableRecord<cad::table::ILayerUser>;
template cad::table::TableRecord<cad::table::IAppidUser>;
template cad::table::TableRecord<cad::table::ILinetypeUser>;
template cad::table::TableRecord<cad::table::IStyleUser>;
template cad::table::TableRecord<cad::table::IUcsUser>;
template cad::table::TableRecord<cad::table::IViewUser>;
template cad::table::TableRecord<cad::table::IVportUser>;
template cad::table::TableRecord<cad::table::IDimstyleUser>;

template<class T>
bool cad::table::TableRecord<T>::readBaseTabRec(int16_t dxfCode, translator::DXFInput& reader) noexcept
{
	switch (dxfCode)
	{
	case 105:
	case 5:
		base::NamedObject<T>::setHandle(reader.readHandle());
		break;

	case 70:
		reader.readValue(_standardBitFlags);
		break;

	case 0:
		reader.readValue();
		return false;

	default:
		reader.readValue();
	}

	return true;
}


template<class IUser>
cad::Error::Code cad::table::TableRecord<IUser>::writeTabRecordHeader(std::string_view dxfName, std::string_view className, translator::DXFOutput& writer) noexcept
{
	writer.writeData(0, dxfName);

	if (writer.version() > enums::Version::R12)
	{
		writer.writeHandle(dxfName == "DIMSTYLE" ? 105 : 5, TableRecord<IUser>::handle());
		writer.writeData(100, "AcDbSymbolTableRecord");
		writer.writeData(100, className);
	}

	writer.writeData(2, TableRecord<IUser>::name());

	writer.writeData(70, bitFlags());

	return cad::Error::Code::NoErr;
}

