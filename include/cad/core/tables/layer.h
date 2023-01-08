#pragma once
#include "./table_object.h"


namespace cad::table
{
	class ILayerUser
	{
	public:
		virtual ~ILayerUser() = default;
		virtual constexpr const String& layer()const noexcept = 0;
		virtual void setLayer(const String& layerName)noexcept = 0;
	};

	class CAD_API Layer : public TableObject
	{

	public:
		constexpr Layer(const String& name)noexcept:TableObject(name,name==L"0") {}

#pragma region getters_setters
		
#pragma endregion getters_setters


#pragma region actions
		inline Layer* copy()const { return new Layer(*this); }
#pragma endregion actions


#pragma region overrides
		constexpr const char* dxfObjectName() const noexcept { return "LAYER"; }

	protected:
		uint32_t fromDXF(std::string_view& buffer, enums::Version ver)noexcept override;
		void toDXF(const std::string& buffer, enums::Version ver)noexcept override;
#pragma endregion overrides
	};
}
