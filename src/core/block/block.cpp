#include <cad/core/block/block.h>
#include "../../translator/translator.hpp"

void cad::Block::actionBeforAdded(entity::BaseEntity* entity)
{

}

void cad::Block::actionBeforDeleted(entity::BaseEntity* entity)
{
	delete entity;
}

size_t cad::Block::indexByVal(const entity::BaseEntity* entityPtr) const noexcept
{
	size_t res = 0;

	for (auto& i : entities())
	{
		if (i==entityPtr)
		{
			return res;
		}
		++res;
	}

    return std::numeric_limits<size_t>::max();
}

cad::entity::BaseEntity* cad::Block::createEntityByName(std::string_view name)
{
    entity::BaseEntity* object = nullptr;

    switch (StringConverter::toId(name))
    {
    case StringConverter::toId("POINT"):
        object = new entity::Point(0,0);
        break;

    case StringConverter::toId("LINE"):
        object = new entity::Line(types::Point3(), types::Point3());
        break;

    case StringConverter::toId("ENDBLK"):
        break;
    }

    return object;
}

cad::entity::BaseEntity* cad::Block::readEntity(std::string_view entiName, translator::DXFInput& reader) noexcept
{
    entity::BaseEntity* object = createEntityByName(entiName);    

    if (object)
    {
        tr::callReadObj(*object,reader);
    }
    else
    {
        types::int16 dxfCode = 1;
        while (dxfCode!=0)
        {
            reader.readCode(&dxfCode);
            reader.readValue();
        }
    }

    return object;
}

void cad::Block::addEntity(entity::BaseEntity* entity)
{
	assert(indexByVal(entity)< std::numeric_limits<size_t>::max() && "This value already exists");

	actionBeforAdded(entity);
	_entities.add(entity);
}

void cad::Block::delEntity(const entity::BaseEntity* entityPtr)
{
	auto i = indexByVal(entityPtr);

	assert(i < std::numeric_limits<size_t>::max() && "This value was not found in the container");
	delEntity(i,1);
}

void cad::Block::delEntity(size_t ind, size_t count)
{
	for (size_t i = ind; i < count; i++)
	{
		actionBeforDeleted(_entities[i]);
	}

	_entities.remove(ind, ind + count);
}

enum Codes
{
    Handle = 5, Layer = 8, Name = 2, TypeFlag = 70, BasePoint_x = 10, BasePoint_y = 20, BasePoint_z = 30, Name2 = 3, Description = 4, XrefPath = 1
};

using tr = cad::translator::BaseDxfTranslator;

cad::Error::Code cad::Block::readDXF(translator::DXFInput& reader) noexcept
{
    int16_t dxfCode = -1;
    std::string_view str;
    Error::Code errCode = Error::Code::NoErr;
    bool stop = false;
    types::int16 tmpFlag;
    entity::BaseEntity* entity;

    while (reader.isGood() && !stop)
    {
        reader.readCode(&dxfCode);

        switch (dxfCode)
        {
        case tr::DXF_DATA_NAMES[tr::EndSec].first:
            reader.readValue(str);
            if (str == tr::DXF_DATA_NAMES[tr::EndSec].second)
                stop = true;
            else
                entity = readEntity(str, reader);
            break;

        case Codes::Handle:
            reader.readValue(str);
            setHandle(StringConverter::convertToIntegral<size_t>(str, 16));
            break;

        case Codes::Layer:
            reader.readValue(_layer);
            break;

        case Codes::TypeFlag:
            reader.readValue(*(types::int16*)&_bitFlagType);
            break;

        case Codes::BasePoint_x:
        case Codes::BasePoint_y:
        case Codes::BasePoint_z:
            reader.readValue(dxfCode, Codes::BasePoint_x, _basePoint);
            break;

        case Codes::Description:
            reader.readValue(_description);
            break;

        case Codes::XrefPath:
            reader.readValue(_xrefPath);
            break;

        default:
            errCode = base::NamedObject::readDXF(reader);
            break;
        }
    }

    return errCode;
}

cad::Error::Code cad::Block::writeDXF(translator::DXFOutput& writer) noexcept
{
    auto localName = name();
    if (writer.version() == enums::Version::R12&& localName.size()&& localName.front()=='*')
    {
        localName[0] = '$';
        localName.convert_to_upper();
    }

    writer.writeData(0, dxfName());
    writer.writeData(Codes::Handle, handle(), 16);

    if (writer.version() > enums::Version::R12)
        writer.writeData(100, "AcDbEntity");

    writer.writeData(Codes::Layer, layer());

    if (writer.version() > enums::Version::R12)
        writer.writeData(100, "AcDbBlockBegin");

    writer.writeData(Codes::Name, localName);
    writer.writeData(Codes::TypeFlag, types::int16(bitFlagType()));

    writer.writeData(Codes::BasePoint_x, basePoint());

    writer.writeData(Codes::Name2, localName);

    writer.writeData(Codes::XrefPath, xrefPath());

    if (name()!= STANDARD_NAMES[0].second&& name() != STANDARD_NAMES[1].second)
    {
        for (auto& enty : entities())
            tr::callWriteObj(*enty, writer);
    }

    writer.writeData(0, "ENDBLK");
    writer.writeData(Codes::Handle, handle() + 1, 16);
    writer.writeData(100, "AcDbEntity");
    writer.writeData(Codes::Layer, layer());
    return writer.writeData(100, "AcDbBlockEnd");
}

const std::vector<std::pair<const char*, const char*>> cad::Block::STANDARD_NAMES{
    {"$MODEL_SPACE","*Model_Space"},
    {"$PAPER_SPACE","*Paper_Space"}
};