#pragma once
#include "base_dxf_translator.hpp"


namespace cad::translator
{
	class DXFWriter :public BaseDxfTranslator
	{
		Error::Code writeStartSec(std::string_view name, DXFOutput& output)noexcept;
		Error::Code writeEndSec(DXFOutput& output)noexcept;

		Error::Code writeVars(Database& drawing, DXFOutput& output)noexcept;
		Error::Code writeClasses(Database& drawing, DXFOutput& output)noexcept;
		Error::Code writeTables(Database& drawing, DXFOutput& output)noexcept;
		Error::Code writeBlocks(Database& drawing, DXFOutput& output)noexcept;
		Error::Code writeEntities(Database& drawing, DXFOutput& output)noexcept;
		Error::Code writeObjects(Database& drawing, DXFOutput& output)noexcept;
	public:
		DXFWriter(Database* drawing, cad::enums::Locale locale, cad::enums::Version version) noexcept:
			BaseDxfTranslator(drawing,locale,version) {}
		
		Error::Code write(std::vector<types::byte>& buffer, bool isBinary) noexcept;
	};
}