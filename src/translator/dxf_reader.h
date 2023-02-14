#pragma once
#include "base_dxf_translator.hpp"
#include "./io/dxf_input.h"

namespace cad::translator
{

	class DXFReader :public BaseDxfTranslator
	{
		enum TypeFile
		{
			ASCII,
			Binary,
			Unk
		};
		TypeFile getTypeFile(const types::byte* byteArrayData, size_t size)const noexcept;
		bool checkIsValidEndOfFile(const types::byte* byteArrayData, size_t size)const noexcept;

		Error::Code readHeader(DXFInput& input)noexcept;
		Error::Code readClasses(DXFInput& input)noexcept;
		Error::Code readTables(DXFInput& input)noexcept;
		Error::Code readBlocks(DXFInput& input)noexcept;
		Error::Code readEntities(DXFInput& input)noexcept;
		Error::Code readObjects(DXFInput& input)noexcept;
		Error::Code readUnknown(DXFInput& input)noexcept;

	public:
		DXFReader(Database* drawing, cad::enums::Locale locale, cad::enums::Version version) :
			BaseDxfTranslator(drawing, locale, version) {}

		Error::Code read(const types::byte* byteArrayData, size_t size) noexcept;
	};
}

