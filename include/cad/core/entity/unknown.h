#pragma once
#include "./base_entity.h"

namespace cad::entity
{
	class CAD_API Unknown : public BaseEntity
	{
	private:
		std::string _dxfName;


	public:
		constexpr Unknown()noexcept : BaseEntity(options::CreateEnt()){}


#pragma region overrides
		constexpr const char* dxfName() const noexcept { return _dxfName.c_str(); }
		constexpr enums::EntyType type() const noexcept override { return enums::EntyType::Unknown; }
		std::array<geom::Point3_d, 2> minMax() const noexcept override { return { }; }
		constexpr BaseEntity* copy()const override { return new Unknown(*this); }

		BaseEntity* move(const geom::Vector3& direct)noexcept override { return this; }
		BaseEntity* rotate(const geom::Point3_d& center, const geom::Vector3& axis,
			geom::Angle ang)noexcept override { return this; }
		BaseEntity* scale(const geom::Point3_d& center, const geom::Vector3& scale)noexcept override { return this; }
		BaseEntity* mirror(const geom::Plane_d& relativePlane)noexcept override { return this; }

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader, char auxilData = -1) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& reader, char auxilData = -1) noexcept override { return Error::Code::NoErr; }
#pragma endregion overrides
	};
}
