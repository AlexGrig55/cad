#pragma once
#include "./base_entity.h"

namespace cad::entity
{
	class CAD_API Line : public BaseEntity
	{
	private:
		types::Point3	_pos[2];

		types::real		_thickness;
		types::Point3	_normal;//direction of local axis Z

	public:
		explicit constexpr Line(types::real x0=0, types::real y0=0, types::real z0=0,
			types::real x1=0, types::real y1=0, types::real z1=0,
			const options::CreateEnt& opt = options::CreateEnt())noexcept :
			BaseEntity(opt), _pos{ {x0,y0,z0},{x1,y1,z1} }, _normal(0, 0, 1), _thickness(0) {}

		template <class T>
		constexpr Line(const geom::Point3<T>& p0, const geom::Point3<T>& p1,
			const options::CreateEnt& opt = options::CreateEnt())noexcept :
			Line(p0.x(), p0.y(), p0.z(), p1.x(), p1.y(), p1.z(),opt) {}

		template <class T>
		explicit constexpr Line(const geom::Line3<T>& line,
			const options::CreateEnt& opt = options::CreateEnt())noexcept :
			Line(line.point(0), line.point(1), opt) {}

		template <class T>
		constexpr Line(const geom::Point2<T>& p0, const geom::Point2<T>& p1,
			const options::CreateEnt& opt = options::CreateEnt())noexcept :
			Line( p0.x(),p0.y(),0 ,  p1.x(),p1.y(),0 , opt) {}

		template <class T>
		explicit constexpr Line(const geom::Line2<T>& line,
			const options::CreateEnt& opt = options::CreateEnt())noexcept :
			Line(line.point(0), line.point(1), opt) {}

#pragma region getters_setters
		auto toGeom()const noexcept { return geom::Line3<types::real>(_pos[0],_pos[1]); }

		constexpr const auto& point(uint8_t i)const noexcept { return _pos[i]; }

		template <class T>
		constexpr void setPoints(const geom::Point3<T>& pos0, const geom::Point3<T>& pos1) noexcept;
		template <class T>
		constexpr void setPoints(const geom::Point2<T>& pos0, const geom::Point2<T>& pos1) noexcept;
		template <class T>
		constexpr void setPoints(const geom::Line3<T>& line) noexcept { setPoints(line.point(0), line.point(1)); }
		template <class T>
		constexpr void setPoints(const geom::Line2<T>& line) noexcept { setPoints(line.point(0), line.point(1)); }

		constexpr void setPoint(uint8_t i, types::real x, types::real y, types::real z = 0) noexcept;
		template <class T>
		constexpr void setPoint(uint8_t i, const geom::Point3<T>& val) noexcept { setPoint(i,val.x(), val.y(), val.z()); }
		template <class T>
		constexpr void setPoint(uint8_t i, const geom::Point2<T>& val) noexcept { setPoint(i, val.x(), val.y(), 0); }


		constexpr auto normal()const noexcept { return geom::Vector3(_normal[0], _normal[1], _normal[2]); }
		void setNormal(const geom::Vector3& val) noexcept { auto v = val.normalized(); _normal[0] = v[0]; _normal[1] = v[1]; _normal[2] = v[2]; }
		void setNormal(types::real x, types::real y, types::real z) noexcept { _normal = { x,y,z }; }

		constexpr auto thickness()const noexcept { return _thickness; }
		constexpr void setThickness(types::real val) noexcept { _thickness = val; }
#pragma endregion getters_setters


#pragma region overrides
		constexpr const char* dxfName() const noexcept { return "LINE"; }
		constexpr enums::EntyType type() const noexcept override { return enums::EntyType::Line; }
		std::array<geom::Point3<types::real>, 2> minMax() const noexcept override;
		constexpr BaseEntity* copy()const override { return new Line(*this); }

		BaseEntity* move(const geom::Vector3& direct)noexcept override;
		BaseEntity* rotate(const geom::Point3<types::real>& center, const geom::Vector3& axis,
			geom::Angle ang)noexcept override;
		BaseEntity* scale(const geom::Point3<types::real>& center, const geom::Vector3& scale)noexcept override;
		BaseEntity* mirror(const geom::Plane<types::real>& relativePlane)noexcept override;

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader, char auxilData = -1) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& reader, char auxilData = -1) noexcept override;
#pragma endregion overrides
	};

	template<class T>
	constexpr void Line::setPoints(const geom::Point3<T>& pos0, const geom::Point3<T>& pos1) noexcept
	{
		_pos[0][0] = pos0[0];
		_pos[0][1] = pos0[1];
		_pos[0][2] = pos0[2];
		_pos[1][0] = pos1[0];
		_pos[1][1] = pos1[1];
		_pos[1][2] = pos1[2];
	}

	template<class T>
	constexpr void Line::setPoints(const geom::Point2<T>& pos0, const geom::Point2<T>& pos1) noexcept
	{
		_pos[0][0] = pos0[0];
		_pos[0][1] = pos0[1];
		_pos[1][0] = pos1[0];
		_pos[1][1] = pos1[1];
		_pos[0][2] = _pos[1][2] = 0;
	}

	constexpr void Line::setPoint(uint8_t i, types::real x, types::real y, types::real z) noexcept
	{
		assert(i < 2);

		_pos[i][0] = x;
		_pos[i][1] = y;
		_pos[i][2] = z;
	}
}
