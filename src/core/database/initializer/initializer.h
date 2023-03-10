#pragma once
#include <cad/core/database/database.h>

class cad::Database::Initializer
{
	static void createContainers(Database* db);
	static void createStandardObjects(Database* db);
	static void makeObjectsStandard(Database* db) noexcept;

	template <class T>
	static constexpr void makeObjectStandard(T* obj) noexcept { obj->_isStandard = true; }

public:
	static Error::Code initDb(Database* db)noexcept;

	static bool fillHandles(Database* db)noexcept;
};