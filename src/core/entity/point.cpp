#include <cad/core/entity/point.h>
#include "../../translator/translator.hpp"

cad::entity::BaseEntity* cad::entity::Point::move(const geom::Vector3& direct) noexcept
{
	_pos = geom::translate(_pos,direct);
	return this;
}

cad::entity::BaseEntity* cad::entity::Point::rotate(const types::Point3& center,
	const geom::Vector3& axis, geom::Angle ang) noexcept
{
	_pos = geom::rotate(_pos, center, axis,ang);
	return this;
}

cad::entity::BaseEntity* cad::entity::Point::scale(const types::Point3& center,
	const geom::Vector3& scale) noexcept
{
	_pos = geom::scale(_pos, center, scale);
	return this;
}

cad::entity::BaseEntity* cad::entity::Point::mirror(const geom::Plane<types::real>& relativePlane) noexcept
{
	_pos = geom::mirror(_pos, relativePlane);
	return this;
}

enum Codes
{
	X = 10,
	Y = 20,
	Z = 30,
	T = 39,
	Vx = 210,
	Vy = 220,
	Vz = 230,
	Angle = 50
};

cad::Error::Code cad::entity::Point::readDXF(translator::DXFInput& reader, char auxilData) noexcept
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

        case Codes::X:
            reader.readValue(_pos[0]);
            break;
        case Codes::Y:
            reader.readValue(_pos[1]);
            break;
        case Codes::Z:
            reader.readValue(_pos[2]);
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

        case Codes::Angle:
            reader.readValue(_shapeAngle);
            break;

        default:
            stop = !readBaseEntity(dxfCode, reader);
            break;
        }
    }

    return errCode;
}

cad::Error::Code cad::entity::Point::writeDXF(translator::DXFOutput& writer, char auxilData) noexcept
{
    auto errCode = writeBaseEntity(writer, dxfName(), "AcDbPoint");

    writer.writeData(Codes::X, _pos);

    if(_thickness!=0)
        writer.writeData(Codes::T, _thickness);

    if (_normal.z() != 1)
        writer.writeData(Codes::Vx, _normal);

    if(_shapeAngle!=0)
        writer.writeData(Codes::Angle, _shapeAngle);

    return errCode;
}


