#include <cad/core/database/containers/blocks.h>
#include "../../../translator/translator.hpp"

using tr = cad::translator::BaseDxfTranslator;

size_t cad::Database::Blocks::purge() noexcept
{
	size_t counter = 0;

	for (size_t i = 2; i < count();)
	{
		auto blk = list()[i];
		if (blk->isStandard() || blk->isPaperSpace()||blk->userCount())
		{
			++i;
			continue;
		}

		remove(i);
		++counter;
	}

	return counter;
}

cad::Error::Code cad::Database::Blocks::readDXF(translator::DXFInput& reader, char auxilData) noexcept
{
	if (auxilData == 1)
	{
		return readBlocks(reader);
	}
	else
	{
		return readBlockRecs(reader);
	}
}

cad::Error::Code cad::Database::Blocks::writeDXF(translator::DXFOutput& writer, char auxilData) noexcept
{
	if (auxilData == 1)
	{
		return writeBlocks(writer);
	}
	else if (writer.version() > enums::Version::R12)
	{
		return writeBlockRecs(writer);
	}

	return Error::Code::NoErr;
}

cad::Block* cad::Database::Blocks::getOrCreateObjectByName(types::String& bufferName, enums::Version ver)
{
	if (ver == enums::Version::R12)
		if (bufferName.size() && bufferName.front() == '$')
			bufferName.front() = '*';

	return NamedContainer::getOrCreateObjectByName(bufferName,false);
}

cad::Error::Code cad::Database::Blocks::readBlocks(translator::DXFInput& reader) noexcept
{
	int16_t code = 0;
	std::string_view str;
	types::String auxiliaStr;
	Error::Code errCode = Error::Code::NoErr;

	bool stop = false;

	while (!stop && reader.isGood() && errCode == Error::Code::NoErr)
	{
		reader.readCode(code);
		reader.readValue(str);

		if (code != 0)
		{
			errCode = Error::Code::InvalidDataInFile;
			break;
		}

		if (str == "BLOCK")
		{
			if (!findData(2, 0, auxiliaStr, reader))
				errCode = Error::Code::InvalidDataInFile;
			else
				errCode = tr::callReadObj(*getOrCreateObjectByName(auxiliaStr, reader.version()), reader, 1);
		}
		else
			stop = true;

		reader.toLastData();
	}

	reader.readCode(code);
	reader.readValue();

	return errCode;
}

cad::Error::Code cad::Database::Blocks::writeBlocks(translator::DXFOutput& writer) noexcept
{
	auto err = cad::Error::Code::NoErr;

	for (auto& blk : list())
	{
		if (err != cad::Error::Code::NoErr)
			break;
		err = tr::callWriteObj(*blk, writer, 1);
	}

	return err;
}

cad::Error::Code cad::Database::Blocks::readBlockRecs(translator::DXFInput& input) noexcept try
{
	std::string_view str;
	types::String auxilStr;
	auto err = Error::Code::NoErr;
	bool stop = false;
	types::int16 dxfCode = -1;

	while (dxfCode != 0 && input.isGood() && err == Error::Code::NoErr)
	{
		input.readCode(dxfCode);
		switch (dxfCode)
		{
		case 0:
			break;
		case 5:
			setHandle(input.readHandle());
			break;
		default:
			input.readValue();
			break;
		}
	}

	while (!stop && input.isGood() && err == Error::Code::NoErr)
	{
		if (dxfCode == 0)
		{
			input.readValue(str);
		}
		else
		{
			err = Error::Code::InvalidDataInFile;
			break;
		}

		switch (StringConverter::toId(str))
		{
		case StringConverter::toId(tr::DXF_DATA_NAMES[tr::Endtab].second):
			stop = true;
			break;

		default:
			if (!findData(2, 0, auxilStr, input))
				err = Error::Code::InvalidDataInFile;
			else
				err = tr::callReadObj(*getOrCreateObjectByName(auxilStr, input.version()), input, 0);
		}
	}

	return err;
}
catch (...)
{
	return cad::Error::Code::OutOfMemory;
}

cad::Error::Code cad::Database::Blocks::writeBlockRecs(translator::DXFOutput& writer) noexcept
{
	auto err =
		writer.writeData(tr::DXF_DATA_NAMES[tr::Table].first, tr::DXF_DATA_NAMES[tr::Table].second);
	err = writer.writeData(tr::DXF_CODE_OF_NAME_TAB, "BLOCK_RECORD");

	err = writer.writeHandle();
	err = writer.writeData(330, 0);
	err = writer.writeData(100, "AcDbSymbolTable");
	err = writer.writeData(70,count());

	for (auto& blk : list())
	{
		if (err != cad::Error::Code::NoErr)
			break;
		err = tr::callWriteObj(*blk, writer, 0);
	}

	err = writer.writeData(tr::DXF_DATA_NAMES[tr::Endtab].first, tr::DXF_DATA_NAMES[tr::Endtab].second);

	return err;
}

cad::util::ConstContainer<cad::Block*>& cad::Database::Blocks::paperSpaces()
{
	_paperSpaceBlocks.clear();

	for (auto & i : list())
		if (i->isPaperSpace())
			_paperSpaceBlocks.add(i);

	return _paperSpaceBlocks;
}

cad::util::ConstContainer<const cad::Block*>& cad::Database::Blocks::paperSpaces() const
{
	_paperSpaceBlocks.clear();

	for (auto& i : list())
		if (i->isPaperSpace())
			_paperSpaceBlocks.add((Block*)i);

	return *(util::ConstContainer<const Block*>*) & _paperSpaceBlocks;
}

cad::util::ConstContainer<cad::Block*>& cad::Database::Blocks::auxiliaryBlocks()
{
	_auxiliaryBlocks.clear();

	return _auxiliaryBlocks;
}

cad::util::ConstContainer<const cad::Block*>& cad::Database::Blocks::auxiliaryBlocks() const
{
	_auxiliaryBlocks.clear();

	return *(util::ConstContainer<const Block*>*) & _auxiliaryBlocks;
}

cad::util::ConstContainer<cad::Block*>& cad::Database::Blocks::regularBlocks()
{
	_regularBlocks.clear();

	for (int j = 0; auto & i : list())
		if (!i->isPaperSpace() && j++ != 0)
			_regularBlocks.add(i);

	return _regularBlocks;
}

cad::util::ConstContainer<const cad::Block*>& cad::Database::Blocks::regularBlocks() const
{
	_regularBlocks.clear();

	for (int j = 0; auto & i : list())
		if (!i->isPaperSpace() && j++ != 0)
			_regularBlocks.add((cad::Block*)&i);

	return *(util::ConstContainer<const Block*>*) & _regularBlocks;
}

cad::types::int16 cad::Database::Blocks::paperSpaceCount() const noexcept
{
	types::int16 counter = 0;
	for (auto & i : list())
		if (i->isPaperSpace())
			++counter;
	return counter;
}

cad::types::int16 cad::Database::Blocks::auxiliaryBlockCount() const noexcept
{
	types::int16 counter = 0;

	return counter;
}

cad::types::int16 cad::Database::Blocks::regularBlockCount() const noexcept
{
	types::int16 counter = 0;
	for (auto& i : list())
		if (!i->isPaperSpace())
			++counter;
	return counter - 1;//-1 - it model space
}
