#include <cad/core/table/appid.h>
#include "../../translator/translator.hpp"

enum Codes
{
    Flag = 70
};

using tr = cad::translator::BaseDxfTranslator;

cad::Error::Code cad::table::Appid::readDXF(translator::DXFInput& reader) noexcept
{
    int16_t dxfCode = -1;
    std::string_view str;
    Error::Code errCode = Error::Code::NoErr;
    bool stop = false;

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
            errCode = TableObject::readDXF(reader);
            break;
        }
    }

    return errCode;
}

cad::Error::Code cad::table::Appid::writeDXF(translator::DXFOutput& writer) noexcept
{
    Error::Code errCode = TableObject::writeDXF(writer);

    if (errCode != Error::Code::NoErr)
        return errCode;

    if (writer.version() > enums::Version::R12)
        writer.writeData(100, "AcDbRegAppTableRecord");

    return errCode;
}