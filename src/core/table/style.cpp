#include <cad/core/table/style.h>
#include "../../translator/translator.hpp"

enum Codes
{
    FixedHeight=40,
    WidthFactor=41,
    ObliqueAngle=50,
    GenerationFlag=71,
    LastHeight = 42,
    PrimaryFontFileName = 3,
    BigFontFileName = 4,
    TrueTypeFlags = 1071
};

using tr = cad::translator::BaseDxfTranslator;

cad::Error::Code cad::table::Style::readDXF(translator::DXFInput& reader, char auxilData) noexcept
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

        case Codes::FixedHeight:
            reader.readValue(_fixedHeight);
            break;

        case Codes::WidthFactor:
            reader.readValue(_widthFactor);
            break;

        case Codes::ObliqueAngle:
            reader.readValue(_obliqueAngle);
            break;

        case Codes::GenerationFlag:
            reader.readValue(_generationFlag);
            break;

        case Codes::LastHeight:
            reader.readValue(_lastHeight);
            break;

        case Codes::PrimaryFontFileName:
            reader.readValue(_fontFileName);
            break;

        case Codes::BigFontFileName:
            reader.readValue(_bigFontFileName);
            break;

        case Codes::TrueTypeFlags:
            reader.readValue(_trueTypeFlags);
            break;

        default:
            stop = !TableRecord::readBaseTabRec(dxfCode, reader);
            break;
        }
    }

    return errCode;
}

cad::Error::Code cad::table::Style::writeDXF(translator::DXFOutput& writer, char auxilData) noexcept
{
    auto errCode = writeTabRecordHeader(dxfName(), "AcDbTextStyleTableRecord", writer);

    writer.writeData(Codes::FixedHeight,fixedHeight());
    writer.writeData(Codes::WidthFactor, widthFactor());
    writer.writeData(Codes::ObliqueAngle, obliqueAngle());
    writer.writeData(Codes::GenerationFlag, generationFlag());
    writer.writeData(Codes::LastHeight, lastHeight());
    writer.writeData(Codes::PrimaryFontFileName, fontFileName());
    writer.writeData(Codes::BigFontFileName, bigFontFileName());

    if (trueTypeFlags() != 0 && writer.version() > enums::Version::R12)
        writer.writeData(Codes::TrueTypeFlags, trueTypeFlags());

    return errCode;
}
