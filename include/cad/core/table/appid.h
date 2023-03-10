#pragma once
#include "./table_record.h"


namespace cad::table
{
	class IAppidUser :public base::IUser
	{
	public:
		virtual constexpr const types::String& appid()const noexcept = 0;
		virtual constexpr void setAppid(const types::String& name) = 0;
	};

	class CAD_API Appid : public TableRecord<IAppidUser>
	{
	public:
		constexpr Appid(const types::String& name)noexcept:TableRecord(name){}

#pragma region overrides
		constexpr const char* dxfName() const noexcept { return "APPID"; }

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader, char auxilData = -1) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer, char auxilData = -1) noexcept override;
#pragma endregion overrides
	};
}
