#include <cad/core/entity/base_entity.h>

cad::Error::Code cad::entity::BaseEntity::readDXF(translator::DXFInput& reader) noexcept
{
	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::entity::BaseEntity::writeDXF(translator::DXFOutput& reader) noexcept
{
	return cad::Error::Code::NoErr;
}
