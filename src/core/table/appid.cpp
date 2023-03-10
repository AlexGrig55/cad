#include <cad/core/table/appid.h>
#include "../../translator/translator.hpp"


using tr = cad::translator::BaseDxfTranslator;

cad::Error::Code cad::table::Appid::readDXF(translator::DXFInput& reader, char auxilData) noexcept
{
    int16_t dxfCode = -1;
    std::string_view str;
    Error::Code errCode = Error::Code::NoErr;
    bool stop = false;

    while (reader.isGood() && !stop)
    {
        reader.readCode(dxfCode);

        stop = !readBaseTabRec(dxfCode, reader);
    }

    return errCode;
}

cad::Error::Code cad::table::Appid::writeDXF(translator::DXFOutput& writer, char auxilData) noexcept
{
    return writeTabRecordHeader(dxfName(), "AcDbRegAppTableRecord", writer);
}