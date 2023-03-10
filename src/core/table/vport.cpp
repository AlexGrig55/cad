#include <cad/core/table/vport.h>
#include "../../translator/translator.hpp"

enum Codes
{
    PlotStyleSheet=1,
    LoverLelftCorner_x=10, LoverLelftCorner_y = 20,
    UpperRightCorner_x = 11, UpperRightCorner_y = 21,
    Center_x = 12, Center_y = 22,
    SnapBasePoint_x = 13, SnapBasePoint_y = 23,
    SnapSpacing_x = 14, SnapSpacing_y = 24,
    GridSpacing_x = 15, GridSpacing_y = 25,
    DirectionFromTargetPoint_x=16, DirectionFromTargetPoint_y = 26, DirectionFromTargetPoint_z = 36,
    ViewTargetPoint_x = 17, ViewTargetPoint_y = 27, ViewTargetPoint_z = 37,
    UcsOrigin_x = 110, UcsOrigin_y = 120, UcsOrigin_z = 130,
    UcsXaxis_x = 111, UcsXaxis_y = 121, UcsXaxis_z = 131,
    UcsYaxis_x = 112, UcsYaxis_y = 122, UcsYaxis_z = 132,

    LensLength = 42,
    FrontClippingPlane = 43,
    BackClippingPlane =44,
    ViewHeight = 40,
    AspectRatio = 41,
    SnapRotation = 50,
    ViewTwistAngle = 51,
    Elevation = 146,
    Brightness = 141,
    Contrast = 142,

    CircleSides = 72,

    RenderMode = 281,
    ViewMode = 71,
    UcsIconSetting = 74,
    UcsOrthoType = 79,
    ShadePlotSetting = 170,
    MajorGridLines = 60,
    DefaultLightOn = 292,
    DefaultLightType = 282,
    
    AmbientColor_0=63,
    AmbientColor_1 =  421,
    AmbientColor_2 =  431
};

using tr = cad::translator::BaseDxfTranslator;

cad::Error::Code cad::table::Vport::readDXF(translator::DXFInput& reader, char auxilData) noexcept
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

        case Codes::PlotStyleSheet:
            reader.readValue(_plotStyleSheet);
            break;

        case Codes::LoverLelftCorner_x:
            reader.readValue(_loverLeftCorner[0]);
            break;
        case Codes::LoverLelftCorner_y:
            reader.readValue(_loverLeftCorner[1]);
            break;

        case Codes::UpperRightCorner_x:
            reader.readValue(_upperRightCorner[0]);
            break;
        case Codes::UpperRightCorner_y:
            reader.readValue(_upperRightCorner[1]);
            break;

        case Codes::Center_x:
            reader.readValue(_center[0]);
            break;
        case Codes::Center_y:
            reader.readValue(_center[1]);
            break;

        case Codes::SnapBasePoint_x:
            reader.readValue(_snapBasePoint[0]);
            break;
        case Codes::SnapBasePoint_y:
            reader.readValue(_snapBasePoint[1]);
            break;

        case Codes::SnapSpacing_x:
            reader.readValue(_snapSpacing[0]);
            break;
        case Codes::SnapSpacing_y:
            reader.readValue(_snapSpacing[1]);
            break;

        case Codes::GridSpacing_x:
            reader.readValue(_gridSpacing[0]);
            break;
        case Codes::GridSpacing_y:
            reader.readValue(_gridSpacing[1]);
            break;

        case Codes::DirectionFromTargetPoint_x:
            reader.readValue(_directionFromTargetPoint[0]);
            break;
        case Codes::DirectionFromTargetPoint_y:
            reader.readValue(_directionFromTargetPoint[1]);
            break;
        case Codes::DirectionFromTargetPoint_z:
            reader.readValue(_directionFromTargetPoint[2]);
            break;

        case Codes::ViewTargetPoint_x:
            reader.readValue(_viewTargetPoint[0]);
            break;
        case Codes::ViewTargetPoint_y:
            reader.readValue(_viewTargetPoint[1]);
            break;
        case Codes::ViewTargetPoint_z:
            reader.readValue(_viewTargetPoint[2]);
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
        case Codes::UcsYaxis_y:
            reader.readValue(_ucsYAxis[1]);
        case Codes::UcsYaxis_z:
            reader.readValue(_ucsYAxis[2]);
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

        case Codes::ViewHeight:
            reader.readValue(_viewHeight);
            break;

        case Codes::AspectRatio:
            reader.readValue(_aspectRatio);
            break;

        case Codes::SnapRotation:
            reader.readValue(_snapRotation);
            break;

        case Codes::ViewTwistAngle:
            reader.readValue(_viewTwistAngle);
            break;

        case Codes::Elevation:
            reader.readValue(_elevation);
            break;

        case Codes::Brightness:
            reader.readValue(_brightness);
            break;

        case Codes::Contrast:
            reader.readValue(_contrast);
            break;

        case Codes::CircleSides:
            reader.readValue(_circleSides);
            break;

        case Codes::RenderMode:
            reader.readValue(auxilFlag);
            _renderMode= RenderMode(auxilFlag);
            break; 

        case Codes::ViewMode:
            reader.readValue(_viewMode);
            break;

        case Codes::UcsIconSetting:
            reader.readValue(_ucsIconSetting);
            break;

        case Codes::UcsOrthoType:
            reader.readValue(auxilFlag);
            _ucsOrthoType = UcsOrthoType(auxilFlag);
            break;

        case Codes::ShadePlotSetting:
            reader.readValue(_shadePlotSetting);
            break;

        case Codes::MajorGridLines:
            reader.readValue(_majorGridLines);
            break;

        case Codes::DefaultLightOn:
            reader.readValue(_defaultLightOn);
            break;

        case Codes::DefaultLightType:
            reader.readValue(_defaultLightType);
            break;

        case Codes::AmbientColor_0:
            reader.readValue(_ambientColor[0]);
            break;
        case Codes::AmbientColor_1:
            reader.readValue(_ambientColor[1]);
            break;
        case Codes::AmbientColor_2:
            reader.readValue(_ambientColor[2]);
            break;

        default:
            stop = !TableRecord::readBaseTabRec(dxfCode,reader);
            break;
        }
    }

    return errCode;
}

cad::Error::Code cad::table::Vport::writeDXF(translator::DXFOutput& writer, char auxilData) noexcept
{
    auto errCode = writeTabRecordHeader(dxfName(), "AcDbVportTableRecord", writer);

    writer.writeData(Codes::LoverLelftCorner_x, _loverLeftCorner);
    writer.writeData(Codes::UpperRightCorner_x, _upperRightCorner);
    writer.writeData(Codes::Center_x, _center);
    writer.writeData(Codes::SnapBasePoint_x, _snapBasePoint);
    writer.writeData(Codes::SnapSpacing_x, _snapSpacing);
    writer.writeData(Codes::GridSpacing_x, _gridSpacing);
    writer.writeData(Codes::DirectionFromTargetPoint_x, _directionFromTargetPoint);
    writer.writeData(Codes::ViewTargetPoint_x, _viewTargetPoint);

    writer.writeData(Codes::ViewHeight, _viewHeight);
    writer.writeData(Codes::AspectRatio, _aspectRatio);
    writer.writeData(Codes::LensLength, _lensLength);
    writer.writeData(Codes::FrontClippingPlane, _frontClippingPlane);
    writer.writeData(Codes::BackClippingPlane, _backClippingPlane);
    writer.writeData(Codes::SnapRotation, _snapRotation);
    writer.writeData(Codes::ViewTwistAngle, _viewTwistAngle);

    writer.writeData(Codes::ViewMode, _viewMode);
    writer.writeData(Codes::CircleSides, _circleSides);
    if (writer.version() <= enums::Version::R12)
        writer.writeData(73, (types::int16)1);
    writer.writeData(Codes::UcsIconSetting, _ucsIconSetting);
    if (writer.version() <= enums::Version::R12)
    {
        writer.writeData(75, (types::int16)0);
        writer.writeData(76, (types::int16)0);
        writer.writeData(77, (types::int16)0);
        writer.writeData(78, (types::int16)0);
    }

    if (writer.version() > enums::Version::R12)
    {
        if (_plotStyleSheet.size())
            writer.writeData(Codes::PlotStyleSheet, _plotStyleSheet);

        writer.writeData(Codes::RenderMode, (types::int16)_renderMode);
        writer.writeData(Codes::UcsOrigin_x, _ucsOrigin);
        writer.writeData(Codes::UcsXaxis_x, _ucsXAxis);
        writer.writeData(Codes::UcsYaxis_x, _ucsYAxis);
        writer.writeData(Codes::UcsOrthoType, (types::int16)_ucsOrthoType);
        writer.writeData(Codes::Elevation, _elevation);

        if (_shadePlotSetting)
            writer.writeData(Codes::ShadePlotSetting, _shadePlotSetting);

        writer.writeData(Codes::MajorGridLines, _majorGridLines);
        writer.writeData(Codes::DefaultLightOn, _defaultLightOn);

        writer.writeData(Codes::DefaultLightType, _defaultLightType);
        writer.writeData(Codes::Brightness, _brightness);
        writer.writeData(Codes::Contrast, _contrast);

        if (_ambientColor[0])
            writer.writeData(Codes::AmbientColor_0, _ambientColor[0]);
        if (_ambientColor[1])
            writer.writeData(Codes::AmbientColor_1, _ambientColor[1]);
        if (_ambientColor[2])
            writer.writeData(Codes::AmbientColor_2, _ambientColor[2]);
    }

    return errCode;
}