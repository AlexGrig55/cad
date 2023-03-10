#include <cad/core/table/ucs.h>
#include "../../translator/translator.hpp"

enum Codes
{
    Origin_x = 10, Origin_y = 20, Origin_z = 30,
    XDirect_x = 11, XDirect_y = 21, XDirect_z = 31,
    YDirect_x = 12, YDirect_y = 22, YDirect_z = 32,
    OrthoOrigin_x = 13, OrthoOrigin_y = 23, OrthoOrigin_z = 33,

    Elevation = 146,

    OrthoType = 71
};

using tr = cad::translator::BaseDxfTranslator;

cad::Error::Code cad::table::Ucs::readDXF(translator::DXFInput& reader, char auxilData) noexcept
{
    int16_t dxfCode=-1;
    std::string_view str;
    Error::Code errCode = Error::Code::NoErr;
    bool stop = false;
    types::int16 tmpFlag;

    while (reader.isGood() && !stop)
    {
        reader.readCode(dxfCode);

        switch (dxfCode)
        {

        case Codes::Origin_x:
        case Codes::Origin_y:
        case Codes::Origin_z:
            reader.readValue(_origin[dxfCode / 10 - 1]);
            break;

        case Codes::XDirect_x:
        case Codes::XDirect_y:
        case Codes::XDirect_z:
            reader.readValue(_xDirect[dxfCode / 10 - 1]);
            break;

        case Codes::YDirect_x:
        case Codes::YDirect_y:
        case Codes::YDirect_z:
            reader.readValue(_yDirect[dxfCode / 10 - 1]);
            break;

        case Codes::OrthoOrigin_x:
        case Codes::OrthoOrigin_y:
        case Codes::OrthoOrigin_z:
            reader.readValue(_orthoOrigin[dxfCode / 10 - 1]);
            break;

        case Codes::Elevation:
            reader.readValue(_elevation);
            break;

        case Codes::OrthoType:
            reader.readValue(tmpFlag);
            _orthoType = (OrthoType)tmpFlag;
            break;

        default:
            stop = !TableRecord::readBaseTabRec(dxfCode, reader);
            break;
        }
    }

    return errCode;
}

cad::Error::Code cad::table::Ucs::writeDXF(translator::DXFOutput& writer, char auxilData) noexcept
{
    auto errCode = writeTabRecordHeader(dxfName(), "AcDbUCSTableRecord", writer);

    writer.writeData(Codes::Origin_x, origin());
    writer.writeData(Codes::XDirect_x, xDirect());
    writer.writeData(Codes::XDirect_y, yDirect());

    writer.writeData(79, 0);

    writer.writeData(Codes::Elevation, elevation());

    writer.writeData(Codes::OrthoType, (types::int16)orthoType());

    return writer.writeData(Codes::OrthoOrigin_x, orthoOrigin());
}
