#include <cad/core/entities/line.h>

std::array<geom::Point3_d, 2> cad::entity::Line::minMax() const noexcept
{
	return _line.minMax();
}

cad::entity::BaseEntity* cad::entity::Line::move(const geom::Vector3& direct) noexcept
{
	_line.move(direct);
	return this;
}

cad::entity::BaseEntity* cad::entity::Line::rotate(const geom::Point3_d& center,
	const geom::Vector3& axis, geom::Angle ang) noexcept
{
	_line.rotate(center, axis, ang);
	return this;
}

cad::entity::BaseEntity* cad::entity::Line::scale(const geom::Point3_d& center,
	const geom::Vector3& scale) noexcept
{
	_line.scale(center, scale);
	return this;
}

cad::entity::BaseEntity* cad::entity::Line::mirror(const geom::Plane_d& relativePlane) noexcept
{
	_line.mirror(relativePlane);
	return this;
}

enum class Code
{
	ClassName=100,

	x0=10,
	y0=20,
	z0=30,
	x1 = 11,
	y2 = 21,
	z3 = 31,

	t=39,
	vx=210,
	vy=220,
	vz=230,
	angle=50
};

uint32_t cad::entity::Line::fromDXF(std::string_view& buffer, enums::Version ver) noexcept
{
	uint32_t offset = 0;
	BaseEntity::fromDXF(buffer,ver);


	return offset;
}

void cad::entity::Line::toDXF(const std::string& buffer, enums::Version ver) noexcept
{

}
