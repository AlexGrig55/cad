#pragma once
#include "base_dxf_translator.hpp"

namespace cad
{
	class DXFWriter :public BaseDxfTranslator
	{

	public:
		DXFWriter(DataBase* drawing) noexcept: BaseDxfTranslator(drawing) {}
		
		Error::Code write(dxf_buffer& buffer) noexcept;
	};
}