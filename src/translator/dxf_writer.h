#pragma once
#include "base_dxf_translator.hpp"


namespace cad::translator
{
	class DXFWriter :public BaseDxfTranslator
	{

	public:
		DXFWriter(Database* drawing, cad::enums::Locale locale, cad::enums::Version version) noexcept:
			BaseDxfTranslator(drawing,locale,version) {}
		
		Error::Code write(std::vector<types::byte>& buffer, bool isBinary) noexcept;
	};
}