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

cad::Error::Code cad::table::View::readDXF(translator::DXFInput& reader, char auxilData) noexcept
{
    int16_t dxfCode = -1;
    std::string_view str;
    Error::Code errCode = Error::Code::NoErr;
    types::int16 auxilFlag;
    bool stop = false;

    while (reader.isGood() && !stop)
    {
        reader.readCode(dxfCode);

        switch (dxfCode)
        {

        case Codes::Center_x:
            reader.readValue(_center[0]);
            break;
        case Codes::Center_y:
            reader.readValue(_center[1]);
            break;

        case Codes::DirectFromTarget_x:
            reader.readValue(_directionFromTarget[0]);
            break;
        case Codes::DirectFromTarget_y:
            reader.readValue(_directionFromTarget[1]);
            break;
        case Codes::DirectFromTarget_z:
            reader.readValue(_directionFromTarget[2]);
            break;

        case Codes::TargetPoint_x:
            reader.readValue(_targetPoint[0]);
            break;
        case Codes::TargetPoint_y:
            reader.readValue(_targetPoint[1]);
            break;
        case Codes::TargetPoint_z:
            reader.readValue(_targetPoint[2]);
            break;

        case Codes::UcsOrigin_x:
            reader.readValue(_ucsOrigin[0]);
            break;
        case Codes::UcsOrigin_y:
            reader.readValue(_ucsOrigin[1]);
            break;
        case Codes::UcsOrigin_z:
            reader.readValue(_ucsOrigin[2]);
            break;

        case Codes::UcsXaxis_x:
            reader.readValue(_ucsXAxis[0]);
            break;
        case Codes::UcsXaxis_y:
            reader.readValue(_ucsXAxis[1]);
            break;
        case Codes::UcsXaxis_z:
            reader.readValue(_ucsXAxis[2]);
            break;

        case Codes::UcsYaxis_x:
            reader.readValue(_ucsYAxis[0]);
            break;
        case Codes::UcsYaxis_y:
            reader.readValue(_ucsYAxis[1]);
            break;
        case Codes::UcsYaxis_z:
            reader.readValue(_ucsYAxis[2]);
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
            stop = !TableRecord::readBaseTabRec(dxfCode, reader);
            break;
        }
    }

    return errCode;
}

cad::Error::Code cad::table::View::writeDXF(translator::DXFOutput& writer, char auxilData) noexcept
{
    auto errCode = writeTabRecordHeader(dxfName(), "AcDbViewTableRecord", writer);

    writer.writeData(Codes::ViewHeight, _viewHeight);
    writer.writeData(Codes::Center_x, _center);
    writer.writeData(Codes::ViewWidth, _viewWidth);
    writer.writeData(Codes::DirectFromTarget_x, _directionFromTarget);
    writer.writeData(Codes::TargetPoint_x, _targetPoint);
    writer.writeData(Codes::LensLength, _lensLength);
    writer.writeData(Codes::FrontClippingPlane, _frontClippingPlane);
    writer.writeData(Codes::BackClippingPlane, _backClippingPlane);
    writer.writeData(Codes::TwistAngle, _twistAngle);
    errCode = writer.writeData(Codes::ViewMode, _viewMode);

    if (writer.version() > enums::Version::R12)
    {
        writer.writeData(Codes::RenderMode, (types::int16)_renderMode);
        errCode = writer.writeData(Codes::UcsAssociated, _ucsAssociated);

        if (_ucsAssociated == 1)
        {
            writer.writeData(Codes::UcsOrigin_x, _ucsOrigin);
            writer.writeData(Codes::UcsXaxis_x, _ucsXAxis);
            writer.writeData(Codes::UcsYaxis_x, _ucsYAxis);
            writer.writeData(Codes::UcsOrthoType, (types::int16)_ucsOrthoType);
            writer.writeData(Codes::UcsElevation, _ucsElevation);
            writer.writeData(Codes::UcsAssociated, _ucsAssociated);
            errCode = writer.writeData(Codes::IsCameraPlottable, _isCameraPlottable);
        }
    }

    return errCode;
}