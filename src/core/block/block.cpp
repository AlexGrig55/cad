#include <cad/core/block/block.h>

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

	return SIZE_MAX;
}

void cad::Block::addEntity(entity::BaseEntity* entity)
{
	assert(indexByVal(entity)<SIZE_MAX && "This value already exsists");

	actionBeforAdded(entity); 
	_entities.add(entity);
}

void cad::Block::delEntity(const entity::BaseEntity* entityPtr)
{
	auto i = indexByVal(entityPtr);

	assert(i < SIZE_MAX && "This value not found in container");
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

cad::Error::Code cad::Block::readDXF(translator::DXFInput& reader) noexcept
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::Block::writeDXF(translator::DXFOutput& reader) noexcept
{
	return cad::Error::Code::NoErr;
}
