#pragma once
#include "../../util/defines/defines.hpp"
#include "../../enums/enums.hpp"
#include "../base/cad_obj.h"

namespace cad
{
	class CAD_API Class :public base::ICadObject
	{
		types::String	_recoedName;			//1
		types::String	_name;					//2
		types::String	_appName;				//3

		types::int32	_proxyCapabilitiesFlag;	//90
		types::int32	_inctanceCount;			//91
		types::boolean	_wasProxyFlag;			//280
		types::boolean	_isEntityFlag;			//281

	public:
		constexpr Class(const types::String& recordName, const types::String& className,
			const types::String& appName= "ObjectDBX Classes"):
			_recoedName(recordName), _name(className), _appName(appName),
			_proxyCapabilitiesFlag(0), _inctanceCount(0), _wasProxyFlag(0), _isEntityFlag(0)
		{}


#pragma region getters_setters
		constexpr auto& recordName()const noexcept { return _recoedName; }
		constexpr auto& name()const noexcept { return _name; }
		constexpr auto& appName()const noexcept { return _name; }

		constexpr auto proxyCapabilitiesFlag()const noexcept { return _proxyCapabilitiesFlag; }
		constexpr void setProxyCapabilitiesFlag(types::int32 val) noexcept { _proxyCapabilitiesFlag=val; }

		constexpr auto inctanceCount()const noexcept { return _inctanceCount; }

		constexpr auto wasProxyFlag()const noexcept { return _wasProxyFlag; }
		constexpr void setWasProxyFlag(types::int32 val) noexcept { _wasProxyFlag = val; }

		constexpr auto isEntityFlag()const noexcept { return _isEntityFlag; }
		constexpr void SetIsEntityFlag(types::int32 val) noexcept { _isEntityFlag = val; }
#pragma endregion getters_setters


#pragma region overrides
		constexpr const char* dxfName() const noexcept override { return "CLASS"; }

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer) noexcept override;
#pragma endregion overrides
	};
}