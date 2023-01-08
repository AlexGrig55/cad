#pragma once
#include <cad/errors/errors.h>
#include <cad/enums/enums.hpp>
#include <cad/core/database/database.h>
#include "../string/string_converter.hpp"


namespace cad
{
	typedef std::string dxf_buffer;

	class BaseDxfTranslator
	{
	public:
		BaseDxfTranslator(DataBase* drawing)noexcept: DRAWING(drawing){};

		struct DXFdata
		{
			int code=-1;
			std::string_view val;

			template <class T>
			constexpr T convertValToIntegral(uint32_t base=10)const {
				auto ptr = val.data();
				if (*ptr != ' ')
				{
					return StringConverter::convertToIntegral<T>(val, base);
				}

				for (auto end = ptr + val.size(); ptr < end && *ptr == ' '; ++ptr)
				{
				}
				return StringConverter::convertToIntegral<T>(ptr, val.size()-(ptr- val.data()), base);
			}
			template <class T>
			constexpr T convertValToFloatPoint()const {
				auto ptr = val.data();
				if (*ptr != ' ')
				{
					return StringConverter::convertToIntegral<T>(val);
				}

				for (auto end = ptr + val.size(); ptr < end && *ptr == ' '; ++ptr)
				{
				}
				return StringConverter::convertToFloatPoint<T>(ptr, val.size() - (ptr - val.data()));
			}

			constexpr bool operator == (const DXFdata& other)const { return other.code == code && other.val == val; }
		};

		DataBase* const DRAWING;

		enum NameSec
		{
			Header,
			Classes,
			Tables,
			Blocks,
			BaseEntity,
			Obj,

			Section,
			EndSec,
			Eof
		};

		static constexpr const DXFdata DXF_DATA_NAMES[]{	{2,"HEADER"} ,{2,"CLASSES"} ,{2,"TABLES"},{2,"BLOCKS"},{2,"ENTITIES"},{2,"OBJECTS"}, 
															{0,"SECTION"},{0,"ENDSEC"},{0,"EOF"} };
	};
}

