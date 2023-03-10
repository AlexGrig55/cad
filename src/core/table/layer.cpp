#include <cad/core/table/layer.h>
#include "../../translator/translator.hpp"

enum Codes
{
    Color=62,
    LineType=6,
    PlottingFlag=290,
    LineWeight=370
};

using tr = cad::translator::BaseDxfTranslator;

void cad::table::Layer::onUserKeeperNameChanged(const char* interfaceName, const types::String& name)
{
    _linetype = name;
}

cad::Error::Code cad::table::Layer::readDXF(translator::DXFInput& reader, char auxilData) noexcept
{
    int16_t dxfCode=-1;
    std::string_view str;
    Error::Code errCode = Error::Code::NoErr;
    bool stop = false;

    while (reader.isGood() && !stop)
    {
        reader.readCode(dxfCode);

        switch (dxfCode)
        {

        case Codes::Color:
        {
            types::int16 tmpColor;
            reader.readValue(tmpColor);
            _isOn = tmpColor >= 0;
            _color = Color(abs(tmpColor));
        }
            break;

        case Codes::LineType:
            reader.readValue(_linetype);
            break;

        case Codes::PlottingFlag:
            reader.readValue(_plotFlag);
            break;

        case Codes::LineWeight:
        {
            types::int16 tmp;
            reader.readValue(tmp);
            _lineWeight = (enums::LineWeight)tmp;
        }
            break;

        default:
            stop = !TableRecord::readBaseTabRec(dxfCode, reader);
            break;
        }
    }

    return errCode;
}

cad::Error::Code cad::table::Layer::writeDXF(translator::DXFOutput& writer, char auxilData) noexcept
{
    auto errCode = writeTabRecordHeader(dxfName(), "AcDbLayerTableRecord", writer);

    writer.writeData(Codes::Color, color().aci());

    writer.writeData(Codes::LineType, linetype());

    if (writer.version() > enums::Version::R12)
    {
        writer.writeData(Codes::LineWeight, (types::int16)lineWeight());
        errCode = writer.writeData(Codes::PlottingFlag, plotFlag());
    }

    return errCode;
}
