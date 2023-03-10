#include <cad/core/variable/variable.h>
#include "../../translator/translator.hpp"


cad::Error::Code cad::Variable::readDXF(translator::DXFInput& reader, char auxilData) noexcept
{
	int16_t dxfCode;
	reader.readCode(dxfCode);

	auto type = typeData();
	if (isDummy())
	{
		this->_dataCode = dxfCode;

		if (dxfCode == 10)
			type = types::EType(-1);
		else
			type = types::Type::getByDxfCode(this->_dataCode);
	}

	bool needReadCode = true;

	switch (type)
	{
	case types::EType::String:
	{
		std::string_view str;
		reader.readValue(str);
		set(types::String::fromUtf8(str));

		break;
	}

	case types::EType::Float:
	{
		types::real val;
		reader.readValue(val);
		set(val);
	}
		break;

	case types::EType::Int16:
	{
		types::int16 val;
		reader.readValue(val);
		set(val);
	}
		break;

	case types::EType::Int32:
	{
		types::int32 val;
		reader.readValue(val);
		set(val);
	}
		break;

	case types::EType::Int64:
	{
		types::int64 val;
		reader.readValue(val);
		set(val);
	}
		break;

	case types::EType::Bool:
	{
		types::boolean val;
		reader.readValue(val);
		set(val);
	}
		break;

	case types::EType::Point2:
	{
		types::Point2 val;
		reader.readValue(val[0] );

		reader.readCode(dxfCode);
		reader.readValue(val[1]);
		set(val);

		break;
	}


	case types::EType::Point3:
	{
		types::Point3 val;
		reader.readValue(val[0]);

		reader.readCode(dxfCode);
		reader.readValue(val[1]);

		reader.readCode(dxfCode);
		reader.readValue(val[2]);
		set(val);

		break;
	}


	default:
	{
		if (type == types::EType(-1))
		{
			types::real val[3]{};
			char i = 0;
			for (; i < 3 && (dxfCode != 9 && dxfCode != 0 && reader.isGood()); ++i)
			{
				reader.readValue(val[i]);

				reader.readCode(dxfCode);
			}

			if (i==2)
				set(types::Point2(val[0],val[1]));
			else
				set(types::Point3(val[0], val[1], val[2]));

			needReadCode = false;
		}
		else
		{
			reader.readValue();
		}

		break;
	}

	}

	if(needReadCode)
		reader.readCode(dxfCode);

	while (dxfCode != 9 && dxfCode != 0 && reader.isGood())
	{
		reader.readValue();
		reader.readCode(dxfCode);
	}

	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::Variable::writeDXF(translator::DXFOutput& writer, char auxilData) noexcept
{
	if (writer.version() < _startVersion)
		return cad::Error::Code::NoErr;

	auto errCode = writer.writeData(9, name());
	if (errCode != cad::Error::Code::NoErr)
		return errCode;

	const auto type = typeData();

	switch (type)
	{
	case types::EType::String:
		errCode = writer.writeData(_dataCode, get<types::String>());
		break;

	case types::EType::Float:
		errCode = writer.writeData(_dataCode, get<types::real>());
		break;

	case types::EType::Int16:
		errCode = writer.writeData(_dataCode, get<types::int16>());
		break;

	case types::EType::Int32:
		errCode = writer.writeData(_dataCode, get<types::int32>());
		break;

	case types::EType::Int64:
		errCode = writer.writeData(_dataCode, get<types::int64>());
		break;

	case types::EType::Bool:
		errCode = writer.writeData(_dataCode, get<types::boolean>());
		break;

	case types::EType::Point2:
	{
		auto &p= get<types::Point2>();
		writer.writeData(10, p.x());
		errCode = writer.writeData(20, p.y());
	}
		break;

	case types::EType::Point3:
	{
		auto& p = get<types::Point3>();
		writer.writeData(10, p.x());
		writer.writeData(20, p.y());
		errCode = writer.writeData(30, p.z());
	}
		break;
	}

	return errCode;
}
