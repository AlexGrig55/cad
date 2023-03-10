#include "util.h"
#include "../string/string_converter.hpp"

cad::entity::BaseEntity* cad::translator::createEntityByName(std::string_view dxfName)
{
	entity::BaseEntity* entity = nullptr;

	switch (StringConverter::toId(dxfName))
	{
	case StringConverter::toId("LINE"):
		entity = new entity::Line();
		break;

	case StringConverter::toId("POINT"):
		entity = new entity::Point();
		break;

	default:
		entity = new entity::Unknown();
	}

	return entity;
}
