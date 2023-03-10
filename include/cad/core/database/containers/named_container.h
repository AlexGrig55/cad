#pragma once
#include "../database.h"
#include "../../../util/container/container.hpp"
#include <ranges>

template<class T>
class cad::Database::NamedContainer : public base::Handler
{
	util::Container<T*>	_list;
	const char*			_nameTable;
	Database*			_db;

public:
	constexpr NamedContainer(const char* name, Database* db)noexcept :_nameTable(name), _db(db) {assert(db&&"db is null"); }
	constexpr ~NamedContainer()noexcept { removing(0, _list.count()); }

#pragma region getters_setters
	constexpr auto& list()const noexcept { return _list; }
	constexpr util::ConstContainer<T*>& list() noexcept { return _list; }

	constexpr types::int16 count()const noexcept { return _list.count(); }

	const T* findByName(const types::String& name)const noexcept;
	T* findByName(const types::String& name)noexcept;

	bool isContains(const types::String& name)const noexcept  { return findByName(name) != nullptr; }
#pragma endregion getters_setters


#pragma region actions
	//throws an exception if the block name is already contained
	void add(const T& val);
	//throws an exception if the block name is already contained
	void add(T&& val);
	//throws an exception if the block name is already contained
	//add an object from the heap only
	void add(T* val);

	//throws an exception if the block cannot be deleted
	void remove(const types::String& name);
	//throws an exception if the block cannot be deleted
	void remove(size_t index, size_t count = 1);

	//delete all unused and non standard
	//return count deleted
	size_t purge()noexcept;

protected:
	T* getOrCreateObjectByName(const types::String& name, bool forceAddition);

	void checkAddingValidation(const T* obj);
	void checkDeletingValidation(const T* obj);

	constexpr T* adding(T* obj) { _list.add(obj); return _list.back(); }
	constexpr void removing(size_t i,size_t count) {
		for (auto i : std::views::iota(_list.data()+i, _list.data() + i+count))
			delete* i;
		_list.remove(i,i+count);
	}

private:
	void addingActions(T* val);
	void actionsBeforeDeleting(T* val);
#pragma endregion actions

public:
#pragma region overrides
	constexpr const char* dxfName() const noexcept override { return _nameTable; }

protected:
	cad::Error::Code readDXF(translator::DXFInput& reader, char auxilData = -1) noexcept override;
	cad::Error::Code writeDXF(translator::DXFOutput& writer, char auxilData = -1) noexcept override;
#pragma endregion overrides
};