#pragma once
#include <cad/core/entity/entities.hpp>
#include "./io/dxf_input.h"

namespace cad::translator
{
	entity::BaseEntity* createEntityByName(std::string_view dxfName);

	template <class T>
	bool findData(types::int16 codeOfData, types::int16 stopCode,T& val,DXFInput& input)noexcept
	{
		int16_t dxfCode = -1;
		auto startOffset = input.offset();

		while (stopCode != dxfCode&& input.isGood())
		{
			input.readCode(dxfCode);
			if (dxfCode== codeOfData)
			{
				input.readValue(val);
				break;
			}
			else
			{
				input.readValue();
			}
		}

		input.setOffset(startOffset);
		return dxfCode== codeOfData;
	}
}