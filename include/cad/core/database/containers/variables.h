#pragma once
#include "../database.h"
#include "../../variable/variable.h"
#include "../../../util/var_values/var_values.h"

#include <vector>
#include <array>


class CAD_API cad::Database::Variables: public base::ICadObject
{
	static constexpr const int COUNT_GENERAL_VARS = 19;

	class GeneralVariables
	{
		std::array<Variable, COUNT_GENERAL_VARS>* _generalVarsPtr;
	public:
		GeneralVariables(std::array<Variable, COUNT_GENERAL_VARS>* generalVarsPtr) :
			_generalVarsPtr(generalVarsPtr) {}

		GeneralVariables(const GeneralVariables&) = delete;
		GeneralVariables(GeneralVariables&&) = delete;
		void operator=(const GeneralVariables&) = delete;

		constexpr const auto& variables()const noexcept { return *_generalVarsPtr; }

		auto version()const noexcept {
			return util::VersionsList::getVersionNum((*_generalVarsPtr)[0].get<types::String>());
		}
		void setVersion(enums::Version val) noexcept {
			(*_generalVarsPtr)[0].set(types::String(util::VersionsList::getVersionName(val)));
		}

		auto locale()const noexcept {
			return util::LocalesList::getLocaleNum((*_generalVarsPtr)[1].get<types::String>());
		}
		void setLocale(enums::Locale val) noexcept {
			(*_generalVarsPtr)[1].set(util::LocalesList::getLocale(val));
		}

		constexpr auto& lastSavedUser()const noexcept { return (*_generalVarsPtr)[2].get<types::String>(); }
		constexpr void setLastSavedUser(const types::String& val) noexcept { (*_generalVarsPtr)[2].set(val); }

		constexpr auto lineTypeScale()const noexcept { return (*_generalVarsPtr)[3].get<types::real>(); }
		constexpr void setLineTypeScale(types::real val) noexcept { (*_generalVarsPtr)[3].set(val); }

		constexpr auto dimensionScale()const noexcept { return (*_generalVarsPtr)[4].get<types::real>(); }
		constexpr void setDimensionScale(types::real val) noexcept { (*_generalVarsPtr)[4].set(val); }

		constexpr auto pointStyle()const noexcept { return enums::PointStyle((*_generalVarsPtr)[5].get<types::int16>()); }
		constexpr void setPointStyle(enums::PointStyle val) noexcept { (*_generalVarsPtr)[5].set(types::int16(val)); }

		//If value < 0 - relative size, else absolute
		constexpr auto pointSize()const noexcept { return (*_generalVarsPtr)[6].get<types::real>(); }
		//If value < 0 - relative size, else absolute
		constexpr void setPointSize(types::real val) noexcept { (*_generalVarsPtr)[6].set(val); }

		constexpr auto lineWeightTurnOn()const noexcept { return (*_generalVarsPtr)[7].get<types::boolean>(); }
		constexpr void setLineWeightTurnOn(types::boolean val) noexcept { (*_generalVarsPtr)[7].set(val); }

		//5 variables for write any integer data. 0<=i<=4
		constexpr auto userIntValue(uint8_t i)const noexcept { return (*_generalVarsPtr)[9 + i].get<types::int32>(); }
		//5 variables for write any integer data. 0<=i<=4
		constexpr void setUserIntValue(uint8_t i, types::int32 val) noexcept { (*_generalVarsPtr)[9 + i].set(val); }

		//5 variables for write any real data. 0<=i<=4
		constexpr auto userRealValue(uint8_t i)const noexcept { return (*_generalVarsPtr)[9 + i].get<types::real>(); }
		//5 variables for write any real data. 0<=i<=4
		constexpr void setUserRealValue(uint8_t i, types::real val) noexcept { (*_generalVarsPtr)[9 + i].set(val); }
	};

	std::array<Variable, COUNT_GENERAL_VARS>_generalVars;
	std::vector<Variable>					_customVars;

	GeneralVariables _generalVarsInc;

public:
	Variables(enums::Locale locale,enums::Version ver)noexcept;


#pragma region getters_setters
	//Get var by name, return null if not exsist, find general and custom vars
	Variable* variable(const char* name)noexcept;
	//Get var by name, return null if not exsist, find general and custom vars
	const Variable* variable(const char* name)const noexcept;

	//Get var by index, return null if not exsist, find general and custom vars.
	//index_custom_var = local_custom_index + count_general_vars
	Variable* variable(uint32_t i)noexcept;
	//Get var by index, return null if not exsist, find general and custom vars.
	//index_custom_var = local_custom_index + count_general_vars
	const Variable* variable(uint32_t i)const noexcept;

	constexpr auto& generalVariables()noexcept { return _generalVarsInc; }
	constexpr auto& generalVariables()const noexcept { return _generalVarsInc; }
	constexpr auto& customVariables()noexcept { return _customVars; }
	constexpr auto& customVariables()const noexcept { return _customVars; }

	//return count of general variables
	constexpr auto countGeneral()const { return _generalVars.size(); }
	//return count of custom variables
	inline auto countCustom()const { return _customVars.size(); }


#pragma endregion getters_setters


#pragma region actions
	//Add custom variable, if var with same name exsist - throw exception
	void add(const Variable& var);
	//Remove custom var, globalIndex = countGeneralVar + indexCustomVar
	//Can throw exception
	void remove(uint32_t i, bool globalIndex = false);
	inline void clearCustomVars()noexcept { _customVars.clear(); }

	bool isVariableExsist(const char* name)const noexcept { return variable(name) != nullptr; }
#pragma endregion actions


#pragma region overrides
	constexpr const char* dxfName() const noexcept override { return "HEADER"; }
protected:
	cad::Error::Code readDXF(translator::DXFInput& reader) noexcept override;
	cad::Error::Code writeDXF(translator::DXFOutput& writer) noexcept override;
#pragma endregion overrides
};