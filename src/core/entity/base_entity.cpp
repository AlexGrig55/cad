#include <cad/core/entity/base_entity.h>
#include "../../translator/translator.hpp"
#include <cad/core/database/database.h>
#include <cad/core/database/containers/containers.hpp>

enum Codes
{
    Handle = 5,
    LineTypeName = 6,
    Layer = 8,
    Color = 62,
    OnPaperSpace = 67,
    LineScale = 48,
    Invisible = 60,
    LineWeight=370
};

void cad::entity::BaseEntity::onUserKeeperNameChanged(const char* interfaceName, const types::String& name)
{
    if (strcmp(interfaceName, typeid(table::ILayerUser).name()) == 0)
        _layer = name;
    else
        _lineType = name;
}

void cad::entity::BaseEntity::addingToDb(Database* db)
{
    base::Handler::addingToDb(db);

    auto layerPtr = db->layers().findByName(_layer);
    if (layerPtr == nullptr)
    {
        layerPtr = new table::Layer(_layer);
        db->layers().add(layerPtr);
    }
    layerPtr->

    auto ltypePtr = db->linetypes().findByName(_lineType);
    if (ltypePtr == nullptr)
    {
        ltypePtr = new table::Linetype(_lineType);
        db->linetypes().add(ltypePtr);
    }


}

bool cad::entity::BaseEntity::readBaseEntity(int16_t code, translator::DXFInput& input) noexcept
{
    std::string_view str;
    types::int16 auxilInt;

    switch (code)
    {
    case Codes::LineTypeName:
        input.readValue(_lineType);
        break;

    case Codes::Layer:
        input.readValue(_layer);
        break;

    case Codes::Color:
        input.readValue(auxilInt);
        _color = Color(auxilInt);
        break;

    case Codes::OnPaperSpace:
        input.readValue(_isOnPaperSpace);
        break;

    case Codes::LineScale:
        input.readValue(_lineTypeScale);
        break;

    case Codes::Invisible:
        input.readValue(_visible);
        break;

    case Codes::LineWeight:
        input.readValue(*(types::int16*)&_lineWeight);
        break;

    case Codes::Handle:
        setHandle(input.readHandle());
        break;

    case 0:
        return false;

    default:
        input.readValue();
    }

	return true;
}


cad::Error::Code cad::entity::BaseEntity::writeBaseEntity(translator::DXFOutput& output,
    std::string_view dxfName,std::string_view nameClass)noexcept
{
    output.writeData(0, dxfName);
    output.writeHandle(Codes::Handle, handle());

    if(output.version()!=enums::Version::R12)
        output.writeData(100, "AcDbEntity");

    if(_isOnPaperSpace)
        output.writeData(Codes::OnPaperSpace, _isOnPaperSpace);

    output.writeData(Codes::Layer, _layer);

    if (output.version() != enums::Version::R12)
        output.writeData(100, nameClass);

    output.writeData(Codes::LineTypeName, _lineType);

    output.writeData(Codes::Color, _color.aci());

    if (output.version() != enums::Version::R12)
    {
        output.writeData(Codes::LineScale, _lineTypeScale);
        output.writeData(Codes::LineWeight, (types::int16)_lineWeight);
    }

	return output.writeData(Codes::Invisible, _visible);
}
