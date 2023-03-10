#include <cad/core/entity/unknown.h>
#include "../../translator/translator.hpp"

cad::Error::Code cad::entity::Unknown::readDXF(translator::DXFInput& reader, char auxilData) noexcept
{
    int16_t dxfCode = -1;
    std::string_view str;
    Error::Code errCode = Error::Code::NoErr;
    bool stop = false;

    reader.toLastData();

    reader.readCode(dxfCode);
    reader.readValue(str);

    if (dxfCode!=0)
    {
        errCode = Error::Code::InvalidDataInFile;
    }

    _dxfName = str;

    while (reader.isGood() && !stop && errCode == Error::Code::NoErr)
    {
        reader.readCode(dxfCode);

        stop = !readBaseEntity(dxfCode, reader);
    }

    return errCode;
}



