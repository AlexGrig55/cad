#pragma once
#include "../database.h"
#include "../../../util/container/container.hpp"

template<class T>
class CAD_API cad::Database::NamedContainer : public base::Handler
{
	util::Container<T>	_list;
	const char*			_nameTable;

public:
	constexpr NamedContainer(const char* name)noexcept :_nameTable(name) {}

#pragma region getters_setters
	constexpr auto& list()const noexcept { return _list; }
	constexpr util::ConstContainer<T>& list() noexcept { return _list; }

	constexpr auto count()const noexcept { return _list.count(); }

	const T* findByName(const types::String& name)const noexcept;
	T* findByName(const types::String& name)noexcept;

	bool isExsist(const types::String& name)const noexcept  { return findByName(name) != nullptr; }
#pragma endregion getters_setters


#pragma region actions
	//if name object already exsist return false
	bool add(const T& val);
	//if name object already exsist return false
	bool add(T&& val);
	//if try removed standard object return false
	constexpr bool remove(size_t i) { if (_list[i].isStandard()) return false; _list.remove(i); return true;	}
#pragma endregion actions


#pragma region overrides
	constexpr const char* dxfName() const noexcept override { return _nameTable; }

protected:
	cad::Error::Code readDXF(translator::DXFInput& reader) noexcept override;
	cad::Error::Code writeDXF(translator::DXFOutput& writer) noexcept override;
#pragma endregion overrides
};