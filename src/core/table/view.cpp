#include <cad/core/table/view.h>
#include "../../translator/translator.hpp"

enum Codes
{
    Center_x = 10, Center_y = 20,
    DirectFromTarget_x = 11, DirectFromTarget_y = 21, DirectFromTarget_z = 31,
    TargetPoint_x = 12, TargetPoint_y = 22, TargetPoint_z = 32,
    UcsOrigin_x = 110, UcsOrigin_y = 120, UcsOrigin_z = 130,
    UcsXaxis_x = 111, UcsXaxis_y = 121, UcsXaxis_z = 131,
    UcsYaxis_x = 112, UcsYaxis_y = 122, UcsYaxis_z = 132,

    ViewHeight = 40,
    ViewWidth = 41,
    LensLength = 42,
    FrontClippingPlane = 43,
    BackClippingPlane = 44,

    TwistAngle = 50,
    UcsElevation = 146,

    ViewMode = 71,
    RenderMode = 281,
    UcsAssociated = 72,
    IsCameraPlottable = 73,
    UcsOrthoType = 79
};

using tr = cad::translator::BaseDxfTranslator;

cad::Error::Code cad::table::View::readDXF(translator::DXFInput& reader) noexcept
{
    int16_t dxfCode = -1;
    std::string_view str;
    Error::Code errCode = Error::Code::NoErr;
    types::int16 auxilFlag;
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

        case Codes::Center_x:
        case Codes::Center_y:
            reader.readValue(dxfCode, Codes::Center_x, _center);
            break;

        case Codes::DirectFromTarget_x:
        case Codes::DirectFromTarget_y:
        case Codes::DirectFromTarget_z:
            reader.readValue(dxfCode, Codes::DirectFromTarget_x, _directionFromTarget);
            break;

        case Codes::TargetPoint_x:
        case Codes::TargetPoint_y:
        case Codes::TargetPoint_z:
            reader.readValue(dxfCode, Codes::TargetPoint_x, _targetPoint);
            break;

        case Codes::UcsOrigin_x:
        case Codes::UcsOrigin_y:
        case Codes::UcsOrigin_z:
            reader.readValue(dxfCode, Codes::UcsOrigin_x, _ucsOrigin);
            break;

        case Codes::UcsXaxis_x:
        case Codes::UcsXaxis_y:
        case Codes::UcsXaxis_z:
            reader.readValue(dxfCode, Codes::UcsXaxis_x, _ucsXaxis);
            break;

        case Codes::UcsYaxis_x:
        case Codes::UcsYaxis_y:
        case Codes::UcsYaxis_z:
            reader.readValue(dxfCode, Codes::UcsYaxis_x, _ucsYaxis);
            break;

        case Codes::ViewHeight:
            reader.readValue(_viewHeight);
            break;

        case Codes::ViewWidth:
            reader.readValue(_viewWidth);
            break;

        case Codes::LensLength:
            reader.readValue(_lensLength);
            break;

        case Codes::FrontClippingPlane:
            reader.readValue(_frontClippingPlane);
            break;

        case Codes::BackClippingPlane:
            reader.readValue(_backClippingPlane);
            break;

        case Codes::TwistAngle:
            reader.readValue(_twistAngle);
            break;

        case Codes::UcsElevation:
            reader.readValue(_ucsElevation);
            break;

        case Codes::ViewMode:
            reader.readValue(_viewMode);
            break;

        case Codes::RenderMode:
            reader.readValue(auxilFlag);
            _renderMode = RenderMode(auxilFlag);
            break;

        case Codes::UcsAssociated:
            reader.readValue(_ucsAssociated);
            break;

        case Codes::IsCameraPlottable:
            reader.readValue(_isCameraPlottable);
            break;

        case Codes::UcsOrthoType:
            reader.readValue(auxilFlag);
            _ucsOrthoType = OrthoType(auxilFlag);
            break;

        default:
            errCode = TableObject::readDXF(reader);
            break;
        }
    }

    return errCode;
}

cad::Error::Code cad::table::View::writeDXF(translator::DXFOutput& writer) noexcept
{
    Error::Code errCode = TableObject::writeDXF(writer);

    if (errCode != Error::Code::NoErr)
        return errCode;

    if (writer.version() > enums::Version::R12)
        writer.writeData(100, "AcDbViewTableRecord");

    writer.writeData(Codes::ViewHeight, _viewHeight);
    writer.writeData(Codes::Center_x, _center);
    writer.writeData(Codes::ViewWidth, _viewWidth);
    writer.writeData(Codes::DirectFromTarget_x, _directionFromTarget);
    writer.writeData(Codes::TargetPoint_x, _targetPoint);
    writer.writeData(Codes::LensLength, _lensLength);
    writer.writeData(Codes::FrontClippingPlane, _frontClippingPlane);
    writer.writeData(Codes::BackClippingPlane, _backClippingPlane);
    writer.writeData(Codes::TwistAngle, _twistAngle);
    writer.writeData(Codes::ViewMode, _viewMode);
    writer.writeData(Codes::RenderMode, (types::int16)_renderMode);
    errCode=writer.writeData(Codes::UcsAssociated, _ucsAssociated);

    if (_ucsAssociated == 1)
    {
        writer.writeData(Codes::UcsOrigin_x, _ucsOrigin);
        writer.writeData(Codes::UcsXaxis_x, _ucsXaxis);
        writer.writeData(Codes::UcsYaxis_x, _ucsYaxis);
        writer.writeData(Codes::UcsOrthoType, (types::int16)_ucsOrthoType);
        writer.writeData(Codes::UcsElevation, _ucsElevation);
        writer.writeData(Codes::UcsAssociated, _ucsAssociated);
        errCode = writer.writeData(Codes::IsCameraPlottable, _isCameraPlottable);
    }

    return errCode;
}