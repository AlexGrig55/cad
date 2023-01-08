#pragma once
#include "./base_entity.h"

namespace cad::entity
{
	class CAD_API Line : public BaseEntity
	{
	private:
		geom::Line3_d	_line;

		double			_thickness;
		geom::Vector3	_normal;//direction of local axis Z

		Line(const Line& val) = default;
		Line(Line&& val) = default;

	public:
		Line& operator=(const Line& val) = delete;
		constexpr Line(const geom::Line3_d& line = {},
			const Color& color = Color(enums::Color::ByLayer),
			const String& layer = L"0", const String& lineType = L"ByLayer")noexcept :
			BaseEntity(color, layer, lineType), _line(line), _normal(0,0,1), _thickness(0){}
		constexpr Line(const geom::Point3_d& p0, const geom::Point3_d& p1,
			const Color& color = Color(enums::Color::ByLayer),
			const String& layer = L"0", const String& lineType = L"ByLayer")noexcept :
			Line({p0,p1},color, layer, lineType){}

		constexpr Line(const geom::Line2_d& line, const Color& color = Color(enums::Color::ByLayer),
			const String& layer = L"0", const String& lineType = L"ByLayer")noexcept :
			Line({ line.point(0).toPoint3(), line.point(1).toPoint3() },
			color, layer, lineType) {}
		constexpr Line(const geom::Point2_d& p0, const geom::Point2_d& p1,
			const Color& color = Color(enums::Color::ByLayer),
			const String& layer = L"0", const String& lineType = L"ByLayer")noexcept :
			Line({ p0,p1 }, color, layer, lineType) {}

#pragma region getters_setters
		constexpr const auto& line()const noexcept { return _line; }
		constexpr void setLine(const geom::Line3_d& val) noexcept { _line = val; }
		constexpr void setLine(const geom::Line2_d& val) noexcept { _line = { val.point(0).toPoint3(),val.point(1).toPoint3() }; }

		constexpr const auto& point(uint8_t i)const noexcept { return _line.point(i); }
		constexpr void setPoint(uint8_t i,const geom::Point3_d& val) noexcept { _line.point(i)=val; }
		constexpr void setPoint(uint8_t i, const geom::Point2_d& val) noexcept { _line.point(i) = val.toPoint3(); }

		constexpr const auto& normal()const noexcept { return _normal; }
		inline void setNormal(const geom::Vector3& val) noexcept { _normal = val; _normal.normalize(); }
		inline void setNormal(geom::real x, geom::real y, geom::real z) noexcept { setNormal({x,y,z}); }

		constexpr auto thickness()const noexcept { return _thickness; }
		constexpr void setThickness(double val) noexcept { _thickness = val; }
#pragma endregion getters_setters


#pragma region overrides
		constexpr const char* dxfObjectName() const noexcept { return "LINE"; }
		constexpr enums::EntyType type() const noexcept override { return enums::EntyType::Line; }
		std::array<geom::Point3_d, 2> minMax() const noexcept override;
		constexpr BaseEntity* copy()const override { return new Line(*this); }

		BaseEntity* move(const geom::Vector3& direct)noexcept override;
		BaseEntity* rotate(const geom::Point3_d& center, const geom::Vector3& axis,
			geom::Angle ang)noexcept override;
		BaseEntity* scale(const geom::Point3_d& center, const geom::Vector3& scale)noexcept override;
		BaseEntity* mirror(const geom::Plane_d& relativePlane)noexcept override;

	protected:
		uint32_t fromDXF(std::string_view& buffer, enums::Version ver)noexcept override;
		void toDXF(const std::string& buffer, enums::Version ver)noexcept override;
#pragma endregion overrides
	};
}
