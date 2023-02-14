#pragma once

#include <cstdint>
#include <geom/geom.hpp>
#include "../../../third-party/ustring/include/usting/ustring.hpp"

namespace cad::types
{
	typedef uint8_t byte;

	//code range: 0-9, 100, 102, 105, 300-369, 390-399, 410-419, 430-439, 470-481, 999-1009
	//UString - unicode string
	typedef UString String;

	//code range: 10-59, 110-149, 210-239, 460-469, 1010-1059
	typedef double real;

	//code range: 60-79, 170-179, 270-289, 370-389, 400-409, 1060-1070
	typedef int16_t int16;

	//code range: 90-99, 420-429, 440-449, 1071
	typedef int32_t int32;

	//code range: 160-169
	typedef int64_t int64;

	//code range: 290-299
	typedef bool boolean;

	typedef geom::Point2<real> Point2;
	typedef geom::Point3<real> Point3;

	enum class EType
	{
		String,
		Float,
		Int16,
		Int32,
		Int64,
		Bool,
		Point2,
		Point3,
		Unk
	};

	class Type
	{
		struct DataType
		{
			EType typeIndex;
			int16_t startCode;
			int16_t endCode;
		};

		static constexpr const DataType dataTypes[]
		{
			//code range: 0-9, 100, 102, 105, 300-369, 390-399, 410-419, 430-439, 470-481, 999-1009
			{EType::String,	0,		9},
			{EType::String,	100,	100},
			{EType::String,	102,	102},
			{EType::String,	105,	105},
			{EType::String,	300,	369},
			{EType::String,	390,	399},
			{EType::String,	410,	419},
			{EType::String,	430,	439},
			{EType::String,	470,	481},
			{EType::String,	999,	1009},

			//code range: 10-59, 110-149, 210-239, 460-469, 1010-1059
			{EType::Float,	10,		59},
			{EType::Float,	110,	149},
			{EType::Float,	210,	239},
			{EType::Float,	460,	469},
			{EType::Float,	1010,	1059},

			//code range: 60-79, 170-179, 270-289, 370-389, 400-409, 1060-1070
			{EType::Int16,	60,		79},
			{EType::Int16,	170,	179},
			{EType::Int16,	270,	289},
			{EType::Int16,	370,	389},
			{EType::Int16,	400,	409},
			{EType::Int16,	1060,	1070},

			//code range: 90-99, 420-429, 440-449, 1071
			{EType::Int32,	90,		99},
			{EType::Int32,	420,	429},
			{EType::Int32,	440,	449},
			{EType::Int32,	1071,	1071},

			//code range: 160-169
			{EType::Int64,	160,	169},

			//code range: 290-299
			{EType::Bool,	290,	299}
		};

	public:
		static constexpr EType getByDxfCode(uint16_t dxfCode)noexcept
		{
			for (auto& i : dataTypes)
			{
				if (dxfCode >= i.startCode && dxfCode <= i.endCode)
					return i.typeIndex;
			}
			return EType::Unk;
		}
	};
}