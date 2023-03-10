#pragma once
#include "./table_record.h"


namespace cad::table
{
	class IUcsUser :public base::IUser
	{
	public:
		virtual constexpr ~IUcsUser() noexcept = default;
		virtual constexpr const types::String& ucs()const noexcept = 0;
		virtual void setUcs(const types::String& name)noexcept = 0;
	};

	class CAD_API Ucs : public TableRecord<IUcsUser>
	{
	public:
		enum class OrthoType :types::int16
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
		constexpr Ucs(const types::String& name)noexcept:
			TableRecord(name),_elevation(0), _orthoType(OrthoType::No) {}
		constexpr ~Ucs()noexcept = default;

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
		cad::Error::Code readDXF(translator::DXFInput& reader, char auxilData = -1) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer, char auxilData = -1) noexcept override;
#pragma endregion overrides
	};
}
