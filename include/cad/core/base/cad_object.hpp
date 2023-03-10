#pragma once
#include "../../enums/enums.hpp"
#include "../../color/color.h"
#include "../../util/defines/defines.hpp"
#include "../../util/container/container.hpp"
#include "../../errors/errors.h"
#include "../../types/types.hpp"

namespace cad
{
	namespace translator
	{
		class BaseDxfTranslator;
		class DXFInput;
		class DXFOutput;
	}
}

namespace cad::base
{
	class ICadObject
	{
		friend class translator::BaseDxfTranslator;

	public:
		virtual constexpr ~ICadObject() noexcept = default;

		//return dxf name of this object
		virtual constexpr const char* dxfName() const noexcept = 0;
	protected:

		virtual Error::Code readDXF(translator::DXFInput& reader,char auxilData=-1) noexcept = 0;
		virtual Error::Code writeDXF(translator::DXFOutput& reader, char auxilData = -1) noexcept = 0;
	};
}
