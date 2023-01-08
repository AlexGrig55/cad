#pragma once
#include "base_dxf_translator.hpp"

namespace cad
{

	class DXFReader :public BaseDxfTranslator
	{
		size_t offset = 0;
		size_t countBytes=0;
		const char* dataPtr = 0;
		const char* endFile = 0;

		//return count symbols in row
		uint32_t readRow(const char* const startRow, std::string_view& strView)const noexcept;
		uint32_t readData(const char* const startRow, DXFdata& data)const noexcept;

		bool checkIsValidEndOfFile();

		Error::Code readHeader()noexcept;
		Error::Code readClasses()noexcept;
		Error::Code readTables()noexcept;
		Error::Code readBlocks()noexcept;
		Error::Code readEntities()noexcept;
		Error::Code readObjects()noexcept;
		Error::Code readUnknown()noexcept;

	public:
		DXFReader(DataBase* drawing) : BaseDxfTranslator(drawing) {}

		Error::Code read(const dxf_buffer& buffer) noexcept;
	};
}

