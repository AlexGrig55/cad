#pragma once
#include "./base_entity.h"

namespace cad::entity
{
	class CAD_API Point : public BaseEntity
	{
	private:
		geom::Point3_d	_coor;

		double			_thickness;
		geom::Vector3	_normal;//direction of local axis Z

		geom::Angle		_angleShape;//angle for PDMODE

	public:
		constexpr Point(const geom::Point3_d& p = {}, const Color& color = Color(enums::Color::ByLayer),
			const types::String& layer = "0", const types::String& lineType = "ByLayer")noexcept :
			BaseEntity(color, layer, lineType), _coor(p), _normal(0,0,1), _thickness(0){}

		constexpr Point(const geom::Point2_d& p = {}, const Color& color = Color(enums::Color::ByLayer),
			const types::String& layer = "0", const types::String& lineType = "ByLayer")noexcept :
			Point({ p.x(), p.y(), 0 }, color, layer, lineType) {}

		constexpr Point(double x, double y, double z = 0)noexcept:
			Point(geom::Point3_d{ x,y,z }) {}

#pragma region getters_setters
		constexpr const auto& coor()const noexcept { return _coor; }
		constexpr void setCoor(double x, double y, double z = 0) noexcept { _coor = { x,y,z }; }
		constexpr void setCoor(const geom::Point3_d& val) noexcept { _coor = val; }
		constexpr void setCoor(const geom::Point2_d& val) noexcept { _coor = { val.x(),val.y(),0 }; }

		constexpr auto angleShape()const noexcept { return _angleShape; }
		constexpr void setAngleShape(geom::Angle val) noexcept { _angleShape = val; }

		constexpr const auto& normal()const noexcept { return _normal; }
		inline void setNormal(const geom::Vector3& val) noexcept { _normal = val; _normal.normalize(); }
		inline void setNormal(geom::real x, geom::real y, geom::real z) noexcept { setNormal({x,y,z}); }

		constexpr auto thickness()const noexcept { return _thickness; }
		constexpr void setThickness(double val) noexcept { _thickness = val; }
#pragma endregion getters_setters


#pragma region overrides
		constexpr const char* dxfName() const noexcept { return "POINT"; }
		constexpr enums::EntyType type() const noexcept override { return enums::EntyType::Point; }
		std::array<geom::Point3_d, 2> minMax() const noexcept override { return {_coor,_coor}; }
		constexpr BaseEntity* copy()const override { return new Point(*this); }

		BaseEntity* move(const geom::Vector3& direct)noexcept override;
		BaseEntity* rotate(const geom::Point3_d& center, const geom::Vector3& axis,
			geom::Angle ang)noexcept override;
		BaseEntity* scale(const geom::Point3_d& center, const geom::Vector3& scale)noexcept override;
		BaseEntity* mirror(const geom::Plane_d& relativePlane)noexcept override;

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& reader) noexcept override;
#pragma endregion overrides
	};
}
