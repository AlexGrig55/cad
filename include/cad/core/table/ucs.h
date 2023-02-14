#pragma once
#include "./table_object.h"


namespace cad::table
{
	class CAD_API UCS : public TableObject
	{
	public:
		enum class OrthoType:types::int16
		{
			No=0,Top = 1, Bot = 2, Front = 3, Back = 4, Left = 5, Right = 6
		};

	private:
		types::Point3	_origin;//10,20,30
		types::Point3	_xDirect;//11,21,31
		types::Point3	_yDirect;//12,22,32
		types::Point3	_orthoOrigin;//13,23,33

		types::real		_elevation;//146

		OrthoType		_orthoType;//71

	public:
		constexpr UCS(const types::String& name)noexcept:
			TableObject(name),_elevation(0), _orthoType(OrthoType::No) {}

		constexpr auto& origin()const noexcept { return _origin; }
		constexpr void origin(const types::Point3& val) noexcept { _origin = val; }

		constexpr auto& xDirect()const noexcept { return _xDirect; }
		constexpr void xDirect(const types::Point3& val) noexcept { _xDirect = val; }

		constexpr auto& yDirect()const noexcept { return _yDirect; }
		constexpr void yDirect(const types::Point3& val) noexcept { _yDirect = val; }

		constexpr auto& orthoOrigin()const noexcept { return _orthoOrigin; }
		constexpr void orthoOrigin(const types::Point3& val) noexcept { _orthoOrigin = val; }

		constexpr auto& elevation()const noexcept { return _elevation; }
		constexpr void elevation(types::real val) noexcept { _elevation = val; }

		constexpr auto& orthoType()const noexcept { return _orthoType; }
		constexpr void orthoType(OrthoType val) noexcept { _orthoType = val; }

#pragma region overrides
		constexpr const char* dxfName() const noexcept { return "UCS"; }

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer) noexcept override;
#pragma endregion overrides
	};
}
