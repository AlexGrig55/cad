#pragma once
#include "./base_entity.h"

namespace cad::entity
{
	class CAD_API Point : public BaseEntity
	{
	private:
		types::Point3	_pos;
		types::Point3	_normal;//direction of local axis Z

		types::real		_thickness;
		types::real		_shapeAngle;//angle for PDMODE

	public:
		constexpr Point(const types::Point3& p = {},
			const options::CreateEnt& opt = options::CreateEnt())noexcept :
			BaseEntity(opt), _pos(p), _normal(0,0,1), _thickness(0), _shapeAngle(0){}

		constexpr Point(const types::Point2& p,
			const options::CreateEnt& opt = options::CreateEnt())noexcept :
			Point({ p.x(), p.y(), 0 }, opt) {}

		constexpr Point(types::real x, types::real y, types::real z = 0,
			const options::CreateEnt& opt = options::CreateEnt())noexcept:
			Point({ x,y,z }, opt) {}

#pragma region getters_setters
		constexpr void setPosition(double x, double y, double z = 0) noexcept { _pos = { x,y,z }; }
		template <class T>
		constexpr void setPosition(const geom::Point3<T>& val) noexcept { _pos[0] = val[0]; _pos[1] = val[1]; _pos[2] = val[2]; }
		template <class T>
		constexpr void setPosition(const geom::Point2<T>& val) noexcept { _pos[0] = val[0]; _pos[1] = val[1]; _pos[2] = 0; }
		constexpr void setX(types::real val) noexcept { _pos.setX(val); }
		constexpr void setY(types::real val) noexcept { _pos.setY(val); }
		constexpr void setZ(types::real val) noexcept { _pos.setZ(val); }

		constexpr auto x()const noexcept { _pos.x(); }
		constexpr auto y()const noexcept { _pos.y(); }
		constexpr auto z()const noexcept { _pos.z(); }

		constexpr auto& pos()const noexcept { return _pos; }
		constexpr auto toGeom()const noexcept { return _pos; }

		constexpr auto shapeAngle()const noexcept { return _shapeAngle; }
		constexpr void setShapeAngle(types::real val) noexcept { _shapeAngle = val; }

		constexpr auto normal()const noexcept { return _normal.toVector3(); }
		void setNormal(const geom::Vector3& val) noexcept { auto v = val.normalized(); _normal[0] = v[0]; _normal[1] = v[1]; _normal[2] = v[2]; }
		void setNormal(types::real x, types::real y, types::real z) noexcept { _normal = { x,y,z }; }

		constexpr auto thickness()const noexcept { return _thickness; }
		constexpr void setThickness(double val) noexcept { _thickness = val; }
#pragma endregion getters_setters


#pragma region overrides
		constexpr const char* dxfName() const noexcept { return "POINT"; }
		constexpr enums::EntyType type() const noexcept override { return enums::EntyType::Point; }
		std::array<geom::Point3<types::real>, 2> minMax() const noexcept override { return {_pos,_pos}; }
		constexpr BaseEntity* copy()const override { return new Point(*this); }

		BaseEntity* move(const geom::Vector3& direct)noexcept override;
		BaseEntity* rotate(const geom::Point3<types::real>& center, const geom::Vector3& axis,
			geom::Angle ang)noexcept override;
		BaseEntity* scale(const geom::Point3<types::real>& center, const geom::Vector3& scale)noexcept override;
		BaseEntity* mirror(const geom::Plane<types::real>& relativePlane)noexcept override;

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader, char auxilData = -1) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer, char auxilData = -1) noexcept override;
#pragma endregion overrides
	};
}
