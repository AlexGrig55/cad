#include <cad/core/entity/line.h>
#include "../../translator/translator.hpp"

std::array<geom::Point3<cad::types::real>, 2> cad::entity::Line::minMax() const noexcept
{
	std::array<geom::Point3<cad::types::real>, 2> res;
	res[0][0] = std::min(_pos[0][0], _pos[1][0]);
	res[0][1] = std::min(_pos[0][1], _pos[1][1]);
	res[0][2] = std::min(_pos[0][2], _pos[1][2]);

	res[1][0] = std::max(_pos[0][0], _pos[1][0]);
	res[1][1] = std::max(_pos[0][1], _pos[1][1]);
	res[1][2] = std::max(_pos[0][2], _pos[1][2]);

	return res;
}

cad::entity::BaseEntity* cad::entity::Line::move(const geom::Vector3& direct) noexcept
{
	_pos[0] = geom::translate(_pos[0], direct);
	_pos[1] = geom::translate(_pos[1], direct);
	return this;
}

cad::entity::BaseEntity* cad::entity::Line::rotate(const geom::Point3<types::real>& center,
	const geom::Vector3& axis, geom::Angle ang) noexcept
{
	_pos[0] = geom::rotate(_pos[0],center,axis, ang);
	_pos[1] = geom::rotate(_pos[1],center,axis, ang);
	return this;
}

cad::entity::BaseEntity* cad::entity::Line::scale(const geom::Point3<types::real>& center,
	const geom::Vector3& scale) noexcept
{
	_pos[0] = geom::scale(_pos[0], center, scale);
	_pos[1] = geom::scale(_pos[1], center, scale);
	return this;
}

cad::entity::BaseEntity* cad::entity::Line::mirror(const geom::Plane<types::real>& relativePlane) noexcept
{
	_pos[0] = geom::mirror(_pos[0], relativePlane);
	_pos[1] = geom::mirror(_pos[1], relativePlane);
	return this;
}

enum Codes
{
    X0 = 10,
    Y0 = 20,
    Z0 = 30,
    X1 = 11,
    Y1 = 21,
    Z1 = 31,

    T = 39,
    Vx = 210,
    Vy = 220,
    Vz = 230
};

cad::Error::Code cad::entity::Line::readDXF(translator::DXFInput& reader, char auxilData) noexcept
{
    int16_t dxfCode = -1;
    std::string_view str;
    Error::Code errCode = Error::Code::NoErr;
    bool stop = false;
    types::int16 tmpFlag;

    while (reader.isGood() && !stop)
    {
        reader.readCode(dxfCode);

        switch (dxfCode)
        {
        case Codes::X0:
            reader.readValue(_pos[0][0]);
            break;
        case Codes::Y0:
            reader.readValue(_pos[0][1]);
            break;
        case Codes::Z0:
            reader.readValue(_pos[0][2]);
            break;

        case Codes::X1:
            reader.readValue(_pos[1][0]);
            break;
        case Codes::Y1:
            reader.readValue(_pos[1][1]);
            break;
        case Codes::Z1:
            reader.readValue(_pos[1][2]);
            break;

        case Codes::Vx:
            reader.readValue(_normal[0]);
            break;
        case Codes::Vy:
            reader.readValue(_normal[1]);
            break;
        case Codes::Vz:
            reader.readValue(_normal[2]);
            break;

        case Codes::T:
            reader.readValue(_thickness);
            break;

        default:
            stop = !readBaseEntity(dxfCode, reader);
            break;
        }
    }

    return errCode;
}

cad::Error::Code cad::entity::Line::writeDXF(translator::DXFOutput& writer, char auxilData) noexcept
{
    auto errCode = writeBaseEntity(writer, dxfName(), "AcDbLine");

    if (_thickness != 0)
        writer.writeData(Codes::T, _thickness);

    writer.writeData(Codes::X0, _pos[0]);
    writer.writeData(Codes::X1, _pos[1]);

    if (_normal.z() != 1)
        writer.writeData(Codes::Vx, _normal);

    return errCode;
}


