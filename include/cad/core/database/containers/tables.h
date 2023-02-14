#pragma once
#include "../database.h"
#include "../../../util/container/container.hpp"

template<class T>
class CAD_API cad::Database::Table: public base::Handler
{
	util::Container<T>	_list;
	const char*			_nameTable;
public:
	constexpr Table(const char* name)noexcept :_nameTable(name) {}

#pragma region getters_setters
	constexpr auto& list()const noexcept { return _list; }
	constexpr util::ConstContainer<T>& list() noexcept { return _list; }

	constexpr auto count()const noexcept { return _list.count(); }
#pragma endregion getters_setters


#pragma region actions
	constexpr bool add(const T& val) { _list.add(val); }
	constexpr bool add(T&& val) { _list.add(std::move(val)); }
	constexpr bool remove(size_t i) { _list.remove(i); }
#pragma endregion actions


#pragma region overrides
	constexpr const char* dxfName() const noexcept override { return _nameTable; }

protected:
	cad::Error::Code readDXF(translator::DXFInput& reader) noexcept override;
	cad::Error::Code writeDXF(translator::DXFOutput& writer) noexcept override;
#pragma endregion overrides
};