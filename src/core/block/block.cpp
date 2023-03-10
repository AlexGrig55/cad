#include <cad/core/block/block.h>
#include "../../translator/translator.hpp"


enum Codes
{
    Handle = 5, Layer = 8, Name = 2, TypeFlag_insertionUnits = 70,
    BasePoint_x = 10, BasePoint_y = 20, BasePoint_z = 30,
    Name2 = 3, Description = 4, XrefPath = 1, IsPaperSpace=67,

    Scalability = 280, Explodability = 281,
    BinData = 310
};

using tr = cad::translator::BaseDxfTranslator;

void cad::Block::actionBeforeAdded(entity::BaseEntity* entity)
{

}

void cad::Block::actionBeforeDeleted(entity::BaseEntity* entity)
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

cad::Error::Code cad::Block::readDXFBlk(translator::DXFInput& reader) noexcept try
{
    int16_t dxfCode = -1;
    std::string_view str;
    Error::Code errCode = Error::Code::NoErr;
    bool stop = false;
    types::int16 tmpFlag = 0;
    entity::BaseEntity* entity;

    while (reader.isGood() && !stop)
    {
        if(dxfCode !=0)
            reader.readCode(dxfCode);

        switch (dxfCode)
        {
        case 0:
            reader.readValue(str);
            if (str == tr::DXF_DATA_NAMES[tr::EndSec].second)
                stop = true;
            else
            {
                entity = translator::createEntityByName(str);
                tr::callReadObj(*entity, reader);
                if (str == "ENDBLK")
                {
                    _endBlkHandle = entity->handle();
                    delete entity;
                    stop = true;
                }
                else
                {
                    size_t hand = entity->handle();
                    _entities.add(entity);
                    entity->setHandle(hand);
                }
            }
            break;

        case Codes::Handle:
            setHandle(reader.readHandle());
            break;

        case Codes::IsPaperSpace:
            reader.readValue(_isPaperSpace);
            break;

        case Codes::Layer:
            reader.readValue(_layer);
            break;

        case Codes::TypeFlag_insertionUnits:
            reader.readValue(*(types::int16*)&_bitFlagType);
            break;

        case Codes::BasePoint_x:
            reader.readValue(_basePoint[0]);
            break;
        case Codes::BasePoint_y:
            reader.readValue(_basePoint[1]);
            break;
        case Codes::BasePoint_z:
            reader.readValue(_basePoint[2]);
            break;

        case Codes::Description:
            reader.readValue(_description);
            break;

        case Codes::XrefPath:
            reader.readValue(_xrefPath);
            break;

        default:
            reader.readValue();
            break;
        }
    }

    return errCode;
}
catch (...)
{
    return Error::Code::OutOfMemory;
}


cad::Error::Code cad::Block::writeDXFBlk(translator::DXFOutput& writer) noexcept
{
    auto localName = name();
    if (writer.version() == enums::Version::R12 && localName.size() && localName.front() == '*')
    {
        localName[0] = '$';
        localName.convert_to_upper();
    }

    writer.writeData(0, dxfName());

    if (writer.version() > enums::Version::R12)
        writer.writeHandle(Codes::Handle, handle());

    if (_isPaperSpace)
        writer.writeData(Codes::IsPaperSpace, _isPaperSpace);

    if (writer.version() > enums::Version::R12)
        writer.writeData(100, "AcDbEntity");

    writer.writeData(Codes::Layer, layer());

    if (writer.version() > enums::Version::R12)
        writer.writeData(100, "AcDbBlockBegin");

    writer.writeData(Codes::Name, localName);
    writer.writeData(Codes::TypeFlag_insertionUnits, types::int16(bitFlagType()));

    writer.writeData(Codes::BasePoint_x, basePoint());

    writer.writeData(Codes::Name2, localName);

    writer.writeData(Codes::XrefPath, xrefPath());

    if (name() != STANDARD_NAMES[0].second && name() != STANDARD_NAMES[1].second)
    {
        for (auto& entity : entities())
            tr::callWriteObj(*entity, writer);
    }

    writer.writeData(0, "ENDBLK");
    writer.writeHandle(Codes::Handle, _endBlkHandle);
    if (_isPaperSpace)
        writer.writeData(Codes::IsPaperSpace, _isPaperSpace);

    if (writer.version() > enums::Version::R12)
        writer.writeData(100, "AcDbEntity");

    writer.writeData(Codes::Layer, layer());

    if (writer.version() > enums::Version::R12)
        writer.writeData(100, "AcDbBlockEnd");

    return Error::Code::NoErr;
}


cad::Error::Code cad::Block::writeDXFBlkRecord(translator::DXFOutput& writer) noexcept
{
    auto errCode = Error::Code::NoErr;
    if (writer.version() == enums::Version::R12)
        return errCode;

    writer.writeData(0, dxfName());
    writer.writeHandle(Codes::Handle, handle());
    writer.writeData(100, "AcDbSymbolTableRecord");
    writer.writeData(100, "AcDbBlockTableRecord");
    //writer.writeData(Codes::Name, _parent->name());
    writer.writeData(Codes::TypeFlag_insertionUnits, _blkRec._units);
    writer.writeData(Codes::Explodability, _blkRec._exploadability);
    writer.writeData(Codes::Scalability, _blkRec._scalability);

    size_t count = 0;
    for (auto ptr = _blkRec._bitmapBinData.data(), end = ptr + _blkRec._bitmapBinData.size(); ptr < end; )
    {
        count = std::min(end - ptr, 255ll);
        writer.writeData(Codes::BinData, std::string_view(ptr, count));
        ptr += count;
    }

    return errCode;
}

cad::Block::Block(const Block& other):
    NamedObject(other),
    _blkRec(other._blkRec),
    _description(other._description),
    _layer(other._layer),
    _xrefPath(other._xrefPath),
    _basePoint(other._basePoint),
    _endBlkHandle(0),
    _bitFlagType(other._bitFlagType),
    _isPaperSpace(other._isPaperSpace)
{
    _entities.reserve(other.entityCount());
    for (auto& enty : other._entities)
        _entities.add(enty->copy());
}

cad::Block& cad::Block::operator=(const Block& other)
{
    NamedObject::operator=(other);

    _blkRec=other._blkRec;

    _description = other._description;
    setLayer(other._layer);
    _xrefPath = other._xrefPath;
    _basePoint = other._basePoint;
    _bitFlagType = other._bitFlagType;
    _isPaperSpace = other._isPaperSpace;

    clear();
    _entities.reserve(other._entities.count());
    for (auto& enty : other._entities)
        addEntity(enty->copy());

    return *this;
}


void cad::Block::addEntity(entity::BaseEntity* entity)
{
	assert(indexByVal(entity)== std::numeric_limits<size_t>::max() && "This value already exists");

	actionBeforeAdded(entity);
	_entities.add(entity);

    entity->_isOnPaperSpace = _isPaperSpace;
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
		actionBeforeDeleted(_entities[i]);
	}

	_entities.remove(ind, ind + count);
}

void cad::Block::addingToDb(Database* db) noexcept
{
    callAddingToDb(&_blkRec, db);
    base::Handler::addingToDb(db);
    _endBlkHandle = getAvailableHandle(db);

    for (auto& entity : _entities)
        callAddingToDb(entity, db);
}

void cad::Block::onUserKeeperNameChanged(const char* interfaceName, const types::String& name)
{
    _layer = name;
}

cad::Error::Code cad::Block::readDXF(translator::DXFInput& reader, char auxilData) noexcept
{
    if (auxilData == 1)
    {
        return readDXFBlk(reader);
    }
    else
    {
        return tr::callReadObj(_blkRec, reader);
    }
}

cad::Error::Code cad::Block::writeDXF(translator::DXFOutput& writer, char auxilData) noexcept
{
    if (auxilData == 1)
    {
        return writeDXFBlk(writer);
    }
    else
    {
        return writeDXFBlkRecord(writer);
    }
}


cad::Error::Code cad::Block::BlkRecord::readDXF(translator::DXFInput& reader, char) noexcept
{
    int16_t dxfCode = -1;
    std::string_view str;
    Error::Code errCode = Error::Code::NoErr;
    bool stop = false;

    while (reader.isGood() && !stop)
    {
        reader.readCode(dxfCode);

        switch (dxfCode)
        {
        case Codes::Handle:
            setHandle(reader.readHandle());
            break;

        case Codes::TypeFlag_insertionUnits:
            reader.readValue(_units);
            break;

        case Codes::Scalability:
            reader.readValue(_scalability);
            break;

        case Codes::Explodability:
            reader.readValue(_exploadability);
            break;

        case Codes::BinData:
            reader.readValue(str);
            _bitmapBinData.append(str);
            break;

        case 0:
            stop = true;
            break;

        default:
            reader.readValue();
            break;
        }
    }

    return errCode;
}


const std::vector<std::pair<const char*, const char*>> cad::Block::STANDARD_NAMES{
    {"$MODEL_SPACE","*Model_Space"},
    {"$PAPER_SPACE","*Paper_Space"}
};