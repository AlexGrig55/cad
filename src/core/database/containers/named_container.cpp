#include <cad/core/database/containers/named_container.h>
#include "../../../translator/translator.hpp"
#include <cad/core/block/block.h>
#include <cad/core/table/table_records.hpp>

template cad::Database::NamedContainer<cad::table::Layer>;
template cad::Database::NamedContainer<cad::table::Appid>;
template cad::Database::NamedContainer<cad::table::Linetype>;
template cad::Database::NamedContainer<cad::table::Style>;
template cad::Database::NamedContainer<cad::table::Ucs>;
template cad::Database::NamedContainer<cad::table::View>;
template cad::Database::NamedContainer<cad::table::Vport>;
template cad::Database::NamedContainer<cad::table::Dimstyle>;
template cad::Database::NamedContainer<cad::Block>;

template<class T>
const T* cad::Database::NamedContainer<T>::findByName(const types::String& name)const noexcept
{
	for (auto& i : list())
		if (types::String::compare(i->name(),name))
			return i;

	return nullptr;
}

template<class T>
T* cad::Database::NamedContainer<T>::findByName(const types::String& name)noexcept
{
	for (auto& i : list())
		if (types::String::compare(i->name(), name,types::String::CaseSens::Insensitive))
			return i;

	return nullptr;
}

template<class T>
void cad::Database::NamedContainer<T>::add(const T& val)
{
	checkAddingValidation(&val);
	addingActions(adding(new T(val)));
}

template<class T>
void cad::Database::NamedContainer<T>::add(T&& val)
{
	checkAddingValidation(&val);
	addingActions(adding(new T(std::move(val))));
}

template<class T>
void cad::Database::NamedContainer<T>::add(T* val)
{
	checkAddingValidation(val);
	addingActions(adding(val));
}

template<class T>
void cad::Database::NamedContainer<T>::remove(const types::String& name)
{
	for (auto& obj : _list)
		if (types::String::compare(obj->name(), name, types::String::CaseSens::Insensitive))
		{
			removing(&obj - _list.data(), 1);
		}
}

template<class T>
void cad::Database::NamedContainer<T>::remove(size_t index, size_t count)
{
	if (index + count > _list.count())
		throw std::exception("Invalid index or count of elements");
	
	for (auto ptr : std::views::iota(_list.data() + index, _list.data() + index + count))
	{
		checkDeletingValidation(*ptr);
		actionsBeforeDeleting(*ptr);
	}

	removing(index, count);
}

template<class T>
size_t cad::Database::NamedContainer<T>::purge() noexcept
{
	size_t counter = 0;
	T* obj;
	for (size_t i = 0; i < count();)
	{
		obj = _list[i];
		if (obj->isStandard() || obj->userCount())
		{
			++i;
			continue;
		}

		remove(i);
		++counter;
	}

	return counter;
}

template<class T>
void cad::Database::NamedContainer<T>::checkAddingValidation(const T* obj)
{
	if (count() == std::numeric_limits<types::int16>::max())
		throw std::exception("The allowed number of elements has been exceeded");
	if (isContains(obj->name()))
		throw std::exception("The object with this name already exists");
}

template<class T>
void cad::Database::NamedContainer<T>::checkDeletingValidation(const T* obj)
{
	if (obj->isStandard())
		throw std::exception("This object cannot be deleted because it is standard");
	if (obj->userCount() != 0)
		throw std::exception("This object cannot be deleted because it has users");
}

template<class T>
void cad::Database::NamedContainer<T>::addingActions( T* val)
{
	assert(_db && "db is null");
	callAddingToDb(val, _db);
}

template<class T>
void cad::Database::NamedContainer<T>::actionsBeforeDeleting(T* val)
{

}

template<class T>
T* cad::Database::NamedContainer<T>::getOrCreateObjectByName(const types::String& name, bool forceAddition)
{
	T* obj = nullptr;
	if (!forceAddition)
	{
		obj = findByName(name);
	}

	if (obj == nullptr)
	{
		add(T(name));
		obj = _list.back();
	}

	return obj;
}

using tr = cad::translator::BaseDxfTranslator;

template<class T>
cad::Error::Code cad::Database::NamedContainer<T>::readDXF(translator::DXFInput& reader, char auxilData) noexcept
{
	types::String auxilStr;
	int16_t code = 0;
	std::string_view str;

	Error::Code errCode = Error::Code::NoErr;
	constexpr auto& endTab = tr::DXF_DATA_NAMES[tr::Endtab];
	bool stop = false;
	int numberActiveVport = 0;

	while (!stop && reader.isGood() && errCode == Error::Code::NoErr)
	{
		reader.readCode(code);

		switch (code)
		{
		case endTab.first:
			reader.readValue(str);
			if (str==dxfName())
			{
				if (!findData(2, 0, auxilStr, reader))
					errCode = Error::Code::InvalidDataInFile;
				else
				{
					errCode = tr::callReadObj(*this->getOrCreateObjectByName(auxilStr, numberActiveVport), reader, 0);
					numberActiveVport += str == "VPORT" &&
						types::String::compare(auxilStr, "*Active", types::String::CaseSens::Insensitive);
				}
			}
			else
				stop = true;

			break;

		case 105:
		case 5:
			NamedContainer<T>::setHandle(reader.readHandle());
			break;

		default:
			reader.readValue();
			break;
		}
	}

	return errCode;
}

template<class T>
cad::Error::Code cad::Database::NamedContainer<T>::writeDXF(translator::DXFOutput& writer, char auxilData) noexcept
{
	writer.writeData(tr::DXF_DATA_NAMES[tr::Table].first, tr::DXF_DATA_NAMES[tr::Table].second);
	writer.writeData(2, dxfName());

	if (writer.version() > enums::Version::R12)
	{
		writer.writeHandle(5, handle());
		writer.writeHandle(330, 0);
		writer.writeData(100, "AcDbSymbolTable");
	}

	writer.writeData(70, count());

	for (auto& i : _list)
	{
		tr::callWriteObj(*i, writer);
	}

	return writer.writeData(tr::DXF_DATA_NAMES[tr::Endtab].first, tr::DXF_DATA_NAMES[tr::Endtab].second);
}