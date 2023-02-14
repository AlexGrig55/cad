#include <cad/core/database/containers/named_container.h>
#include "../../../translator/translator.hpp"
#include <cad/core/block/block.h>
#include <cad/core/table/tables.hpp>

template cad::Database::NamedContainer<cad::Block>;
template cad::Database::NamedContainer<cad::table::Layer>;
template cad::Database::NamedContainer<cad::table::Appid>;
template cad::Database::NamedContainer<cad::table::Linetype>;
template cad::Database::NamedContainer<cad::table::Style>;
template cad::Database::NamedContainer<cad::table::UCS>;
template cad::Database::NamedContainer<cad::table::View>;
template cad::Database::NamedContainer<cad::table::Vport>;
template cad::Database::NamedContainer<cad::table::Dimstyle>;

template<class T>
const T* cad::Database::NamedContainer<T>::findByName(const types::String& name)const noexcept
{
	for (auto& i : list())
		if (types::String::compare(i.name(),name))
			return &i;

	return nullptr;
}

template<class T>
T* cad::Database::NamedContainer<T>::findByName(const types::String& name)noexcept
{
	for (auto& i : list())
		if (types::String::compare(i.name(), name))
			return &i;

	return nullptr;
}

template<class T>
bool cad::Database::NamedContainer<T>::add(const T& val)
{
	if (isExsist(val.name()))
		return false;

	_list.add(val);
	return true;
}

template<class T>
bool cad::Database::NamedContainer<T>::add(T&& val)
{
	if (isExsist(val.name()))
		return false;

	_list.add(std::move(val));
	return true;
}

using tr = cad::translator::BaseDxfTranslator;

template<class T>
cad::Error::Code cad::Database::NamedContainer<T>::readDXF(translator::DXFInput& reader) noexcept
{
	int16_t code=0;
	std::string_view str;
	size_t hand;

	Error::Code errCode = Error::Code::NoErr;
	constexpr auto& endTab = tr::DXF_DATA_NAMES[tr::Endtab];
	bool stop = false;

	while (!stop && reader.isGood() && errCode == Error::Code::NoErr)
	{
		reader.readCode(&code);

		switch (code)
		{
		case endTab.first:
			reader.readValue(str);
			if (str==dxfName())
			{
				T obj("");
				errCode = tr::callReadObj(obj, reader);
				if (errCode== Error::Code::NoErr)
				{
					this->add(std::move(obj));
				}
			}
			else
				stop = true;

			break;

		case 105:
		case 5:
			reader.readValue(hand,16);
			setHandle(hand);
			break;

		default:
			reader.readValue();
			break;
		}
	}

	return errCode;
}

template<class T>
cad::Error::Code cad::Database::NamedContainer<T>::writeDXF(translator::DXFOutput& writer) noexcept
{
	writer.writeData(tr::DXF_DATA_NAMES[tr::Table].first, tr::DXF_DATA_NAMES[tr::Table].second);
	writer.writeData(2, dxfName());
	writer.writeData(5, handle(), 16);

	if(writer.version()>enums::Version::R12)
		writer.writeData(100, "AcDbSymbolTable");

	writer.writeData(70, count());

	for (auto& i : _list)
	{
		tr::callWriteObj(i, writer);
	}

	return writer.writeData(tr::DXF_DATA_NAMES[tr::Endtab].first, tr::DXF_DATA_NAMES[tr::Endtab].second);
}