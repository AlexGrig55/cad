#pragma once
#include "dxf_base_translator.hpp"

namespace cad
{
	class DXFWriter :public DXFBaseTranslator
	{

	public:
		DXFWriter(DataBase* drawing) noexcept: DXFBaseTranslator(drawing) {}
		
		Error::Code write(dxf_buffer& buffer) noexcept;
	};
}