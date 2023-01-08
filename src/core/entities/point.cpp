#include <cad/core/entities/point.h>

cad::entity::BaseEntity* cad::entity::Point::move(const geom::Vector3& direct) noexcept
{
	_coor = geom::translate(_coor,direct);
	return this;
}

cad::entity::BaseEntity* cad::entity::Point::rotate(const geom::Point3_d& center,
	const geom::Vector3& axis, geom::Angle ang) noexcept
{
	_coor = geom::rotate(_coor, center, axis,ang);
	return this;
}

cad::entity::BaseEntity* cad::entity::Point::scale(const geom::Point3_d& center,
	const geom::Vector3& scale) noexcept
{
	_coor = geom::scale(_coor, center, scale);
	return this;
}

cad::entity::BaseEntity* cad::entity::Point::mirror(const geom::Plane_d& relativePlane) noexcept
{
	_coor = geom::mirror(_coor, relativePlane);
	return this;
}

enum class Code
{
	ClassName=100,
	x=10,
	y=20,
	z=30,
	t=39,
	vx=210,
	vy=220,
	vz=230,
	angle=50
};

uint32_t cad::entity::Point::fromDXF(std::string_view& buffer, enums::Version ver) noexcept
{
	uint32_t offset = 0;
	BaseEntity::fromDXF(buffer,ver);


	return offset;
}

void cad::entity::Point::toDXF(const std::string& buffer, enums::Version ver) noexcept
{

}
