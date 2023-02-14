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

cad::Error::Code cad::table::Vport::readDXF(translator::DXFInput& reader) noexcept
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

        case Codes::PlotStyleSheet:
            reader.readValue(_plotStyleSheet);
            break;

        case Codes::LoverLelftCorner_x:
        case Codes::LoverLelftCorner_y:
            reader.readValue(dxfCode, LoverLelftCorner_x,_loverLelftCorner);
            break;

        case Codes::UpperRightCorner_x:
        case Codes::UpperRightCorner_y:
            reader.readValue(dxfCode, UpperRightCorner_x, _upperRightCorner);
            break;

        case Codes::Center_x:
        case Codes::Center_y:
            reader.readValue(dxfCode, Center_x, _center);
            break;

        case Codes::SnapBasePoint_x:
        case Codes::SnapBasePoint_y:
            reader.readValue(dxfCode, SnapBasePoint_x, _snapBasePoint);
            break;

        case Codes::SnapSpacing_x:
        case Codes::SnapSpacing_y:
            reader.readValue(dxfCode, SnapSpacing_x, _snapSpacing);
            break;

        case Codes::GridSpacing_x:
        case Codes::GridSpacing_y:
            reader.readValue(dxfCode, GridSpacing_x, _gridSpacing);
            break;

        case Codes::DirectionFromTargetPoint_x:
        case Codes::DirectionFromTargetPoint_y:
        case Codes::DirectionFromTargetPoint_z:
            reader.readValue(dxfCode, DirectionFromTargetPoint_x, _directionFromTargetPoint);
            break;

        case Codes::ViewTargetPoint_x:
        case Codes::ViewTargetPoint_y:
        case Codes::ViewTargetPoint_z:
            reader.readValue(dxfCode, ViewTargetPoint_x, _viewTargetPoint);
            break;

        case Codes::UcsOrigin_x:
        case Codes::UcsOrigin_y:
        case Codes::UcsOrigin_z:
            reader.readValue(dxfCode, UcsOrigin_x, _ucsOrigin);
            break;

        case Codes::UcsXaxis_x:
        case Codes::UcsXaxis_y:
        case Codes::UcsXaxis_z:
            reader.readValue(dxfCode, UcsXaxis_x, _ucsXaxis);
            break;

        case Codes::UcsYaxis_x:
        case Codes::UcsYaxis_y:
        case Codes::UcsYaxis_z:
            reader.readValue(dxfCode, UcsYaxis_x, _ucsYaxis);
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
            errCode = TableObject::readDXF(reader);
            break;
        }
    }

    return errCode;
}

cad::Error::Code cad::table::Vport::writeDXF(translator::DXFOutput& writer) noexcept
{
    Error::Code errCode = TableObject::writeDXF(writer);

    if (errCode != Error::Code::NoErr)
        return errCode;

    if (writer.version() > enums::Version::R12)
        writer.writeData(100, "AcDbVportTableRecord");

    writer.writeData(Codes::LoverLelftCorner_x, _loverLelftCorner);
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
    writer.writeData(Codes::UcsIconSetting, _ucsIconSetting);

    if(_plotStyleSheet.size())
        writer.writeData(Codes::PlotStyleSheet, _plotStyleSheet);
    writer.writeData(Codes::RenderMode, (types::int16)_renderMode);

    writer.writeData(Codes::UcsOrigin_x, _ucsOrigin);
    writer.writeData(Codes::UcsXaxis_x, _ucsXaxis);
    writer.writeData(Codes::UcsYaxis_x, _ucsYaxis);

    writer.writeData(Codes::UcsOrthoType, (types::int16)_ucsOrthoType);
    writer.writeData(Codes::Elevation, _elevation);

    if(_shadePlotSetting)
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
    if(_ambientColor[2])
        writer.writeData(Codes::AmbientColor_2, _ambientColor[2]);

    return errCode;
}