#pragma once
#include <cad/errors/errors.h>
#include <cad/enums/enums.hpp>
#include <cad/core/database/database.h>

#include "../string/string_converter.hpp"
#include "./io/dxf_input.h"
#include "./io/dxf_output.h"

namespace cad::translator
{
	class BaseDxfTranslator
	{
		enums::Locale _locale;
		enums::Version _version;

	public:
		BaseDxfTranslator(Database* drawing, enums::Locale locale, enums::Version version)noexcept:
			DRAWING(drawing),_locale(locale),_version(version){};

		Database* const DRAWING;

		static inline auto callReadObj(base::ICadObject& obj, DXFInput& reader, char auxilData = -1)noexcept { return obj.readDXF(reader,auxilData); }
		static inline auto callWriteObj(base::ICadObject& obj, DXFOutput& writer, char auxilData = -1)noexcept { return obj.writeDXF(writer,auxilData); }

		constexpr void setLocale(enums::Locale val)noexcept { _locale = val; }
		constexpr auto locale()const noexcept{ return _locale; }

		constexpr void setVersion(cad::enums::Version val) noexcept{ _version = val; }
		constexpr auto version()const noexcept{ return _version; }

		enum NameSec
		{
			Header,
			Classes,
			Tables,
			Blocks,
			Entities,
			Objects,

			Table,
			Endtab,

			Section,
			EndSec,
			Eof
		};

		static constexpr const int16_t DXF_CODE_OF_NAME_SEC = 2;
		static constexpr const int16_t DXF_CODE_OF_NAME_TAB = 2;
		static constexpr const int16_t DXF_CODE_OF_COMMENT = 999;
		static constexpr const std::pair<int16_t,const char*> DXF_DATA_NAMES[]{
			{DXF_CODE_OF_NAME_SEC,"HEADER"},
			{DXF_CODE_OF_NAME_SEC,"CLASSES"},
			{DXF_CODE_OF_NAME_SEC,"TABLES"},
			{DXF_CODE_OF_NAME_SEC,"BLOCKS"},
			{DXF_CODE_OF_NAME_SEC,"ENTITIES"},
			{DXF_CODE_OF_NAME_SEC,"OBJECTS"},
			{0,"TABLE"}, {0,"ENDTAB"},
			{0,"SECTION"},{0,"ENDSEC"},{0,"EOF"}
		};
	};
}

