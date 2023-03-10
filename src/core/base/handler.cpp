#include <cad/core/base/handler.h>
#include <cad/core/database/database.h>

size_t cad::base::Handler::getAvailableHandle(Database* db) noexcept
{
	return db->_actualHandle++;
}

void cad::base::Handler::addingToDb(Database* db) noexcept
{
	assert(db&&"db is null");
	_handle = getAvailableHandle(db);
}
