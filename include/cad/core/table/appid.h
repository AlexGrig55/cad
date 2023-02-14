#pragma once
#include "./table_object.h"


namespace cad::table
{
	class IAppidUser
	{
	public:
		virtual ~IAppidUser() = default;
		virtual constexpr const types::String& appid()const noexcept = 0;
		virtual constexpr void setAppid(const types::String& name) = 0;
	};

	class CAD_API Appid : public TableObject
	{
	public:
		constexpr Appid(const types::String& name)noexcept:TableObject(name){}

#pragma region overrides
		constexpr const char* dxfName() const noexcept { return "APPID"; }

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer) noexcept override;
#pragma endregion overrides
	};
}
