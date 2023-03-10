#include "initializer.h"
#include <cad/core/database/containers/containers.hpp>


void cad::Database::Initializer::createContainers(Database* db)
{
	db->_variables = new Variables(enums::Locale::CentralEurope, enums::Version::V2018);
	db->_classes = new Classes();
	db->_blocks = new Blocks(db);

	db->_appids = new NamedContainer<table::Appid>("APPID",db);
	db->_linetypes = new NamedContainer<table::Linetype>("LTYPE", db);
	db->_layers = new NamedContainer<table::Layer>("LAYER", db);
	db->_views = new NamedContainer<table::View>("VIEW", db);
	db->_styles = new NamedContainer<table::Style>("STYLE", db);
	db->_ucses = new NamedContainer<table::Ucs>("UCS", db);
	db->_vports = new NamedContainer<table::Vport>("VPORT", db);
	db->_dimstyles = new NamedContainer<table::Dimstyle>("DIMSTYLE", db);

	db->_objects;
}

void cad::Database::Initializer::createStandardObjects(Database* db)
{
	db->_appids->add(table::Appid("ACAD"));

	db->_linetypes->add(table::Linetype("ByBlock"));
	db->_linetypes->add(table::Linetype("ByLayer"));
	db->_linetypes->add(table::Linetype("Continuous","Solid line"));

	db->_layers->add(table::Layer("0"));

	db->_styles->add(table::Style("Standard"));
	db->_styles->add(table::Style("Annotative"));

	db->_vports->add(table::Vport("*Active"));

	db->_dimstyles->add(table::Dimstyle("Standard"));

	db->_blocks->add(Block("*Model_Space"));
	db->_blocks->add(Block("*Paper_Space"));
}


void cad::Database::Initializer::makeObjectsStandard(Database* db) noexcept
{
	for (auto& obj : db->_appids->list())
		makeObjectStandard(obj);
	for (auto& obj : db->_linetypes->list())
		makeObjectStandard(obj);
	for (auto& obj : db->_layers->list())
		makeObjectStandard(obj);
	for (auto& obj : db->_styles->list())
		makeObjectStandard(obj);
	for (auto& obj : db->_ucses->list())
		makeObjectStandard(obj);
	for (auto& obj : db->_views->list())
		makeObjectStandard(obj);
	for (auto& obj : db->_vports->list())
		makeObjectStandard(obj);
	for (auto& obj : db->_dimstyles->list())
		makeObjectStandard(obj);
	for (auto& obj : db->_blocks->list())
		makeObjectStandard(obj);
}

cad::Error::Code cad::Database::Initializer::initDb(Database* db) noexcept try
{
    createContainers(db);
    createStandardObjects(db);
	makeObjectsStandard(db);

    return Error::Code::NoErr;
}
catch (...)
{
    return Error::Code::OutOfMemory;
}


void fillHandleInfo(cad::base::Handler* handlerObj, size_t minMaxHandle[2],
	std::vector<cad::base::Handler*>& invalidHandleObjects)
{
	if (handlerObj->handle() == 0)
	{
		invalidHandleObjects.emplace_back(handlerObj);
	}
	else if (handlerObj->handle() < minMaxHandle[0])
	{
		minMaxHandle[0] = handlerObj->handle();
	}
	else if (handlerObj->handle() > minMaxHandle[1])
	{
		minMaxHandle[1] = handlerObj->handle();
	}
}

void fillAuxilHandleData(cad::Database& db, size_t minMaxHandle[2],
	std::vector<cad::base::Handler*>& invalidHandleObjects)
{
	fillHandleInfo(&db.appids(), minMaxHandle, invalidHandleObjects);
	fillHandleInfo(&db.linetypes(), minMaxHandle, invalidHandleObjects);
	fillHandleInfo(&db.layers(), minMaxHandle, invalidHandleObjects);
	fillHandleInfo(&db.styles(), minMaxHandle, invalidHandleObjects);
	fillHandleInfo(&db.ucses(), minMaxHandle, invalidHandleObjects);
	fillHandleInfo(&db.views(), minMaxHandle, invalidHandleObjects);
	fillHandleInfo(&db.vports(), minMaxHandle, invalidHandleObjects);
	fillHandleInfo(&db.dimstyles(), minMaxHandle, invalidHandleObjects);
	fillHandleInfo(&db.blocks(), minMaxHandle, invalidHandleObjects);

	for (auto obj : db.appids().list())
		fillHandleInfo(obj, minMaxHandle, invalidHandleObjects);

	for (auto obj : db.linetypes().list())
		fillHandleInfo(obj, minMaxHandle, invalidHandleObjects);

	for (auto obj : db.layers().list())
		fillHandleInfo(obj, minMaxHandle, invalidHandleObjects);

	for (auto obj : db.styles().list())
		fillHandleInfo(obj, minMaxHandle, invalidHandleObjects);

	for (auto obj : db.ucses().list())
		fillHandleInfo(obj, minMaxHandle, invalidHandleObjects);

	for (auto obj : db.views().list())
		fillHandleInfo(obj, minMaxHandle, invalidHandleObjects);

	for (auto obj : db.vports().list())
		fillHandleInfo(obj, minMaxHandle, invalidHandleObjects);

	for (auto obj : db.dimstyles().list())
		fillHandleInfo(obj, minMaxHandle, invalidHandleObjects);

	for (auto obj : db.blocks().list())
		fillHandleInfo(obj, minMaxHandle, invalidHandleObjects);

	//for (auto& obj : objects().list())
	//	fillHandleInfo(&obj, minMaxHandle, invalidHandleObjects);
}

bool cad::Database::Initializer::fillHandles(Database* db) noexcept try
{
	std::vector<cad::base::Handler*> invalidHandleObjects;
	size_t minMaxHandle[2]{ std::numeric_limits<size_t>::max(),std::numeric_limits<size_t>::min() };

	fillAuxilHandleData(*db, minMaxHandle, invalidHandleObjects);

	db->_actualHandle = 1;

	for (auto& obj : invalidHandleObjects)
	{
		if (db->_actualHandle == minMaxHandle[0])
			db->_actualHandle = minMaxHandle[1] + 1;

		obj->setHandle(db->_actualHandle++);
	}

	return true;
}
catch (...)
{
	return false;
}

