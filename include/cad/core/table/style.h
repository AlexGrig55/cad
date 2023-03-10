#pragma once
#include "./table_record.h"

namespace cad::table
{
	class IStyleUser :public base::IUser
	{
	public:
		virtual ~IStyleUser() = default;
		virtual constexpr const types::String& style()const noexcept = 0;
		virtual void setStyle(const types::String& name)noexcept = 0;
	};

	class CAD_API Style : public TableRecord<IStyleUser>
	{
		types::String	_fontFileName;//3
		types::String	_bigFontFileName;//4

		types::real		_fixedHeight;//40
		types::real		_lastHeight;//42
		types::real		_widthFactor;//41
		types::real		_obliqueAngle;//50

		types::int32	_trueTypeFlags;//1071
		types::int16	_generationFlag;//71

	public:
		constexpr Style(const types::String& name)noexcept :
			TableRecord(name), _fixedHeight(0), _lastHeight(0.2), _widthFactor(1), _obliqueAngle(0),
			_generationFlag(0), _trueTypeFlags(0)
		{}
		constexpr ~Style()noexcept = default;

#pragma region getters_setters
		constexpr auto& fontFileName()const noexcept { return _fontFileName; }
		constexpr void setFontFileName(const types::String& val) noexcept { _fontFileName = val; }

		constexpr auto& bigFontFileName()const noexcept { return _bigFontFileName; }
		constexpr void setBigFontFileName(const types::String& val) noexcept { _bigFontFileName = val; }

		constexpr auto fixedHeight()const noexcept { return _fixedHeight; }
		constexpr void setFixedHeight(types::real val) noexcept { _fixedHeight = val; }

		constexpr auto lastHeight()const noexcept { return _lastHeight; }
		constexpr void setLastHeight(types::real val) noexcept { _lastHeight = val; }

		constexpr auto widthFactor()const noexcept { return _widthFactor; }
		constexpr void setWidthFactor(types::real val) noexcept { _widthFactor = val; }

		constexpr auto obliqueAngle()const noexcept { return _obliqueAngle; }
		constexpr void setObliqueAngle(types::real val) noexcept { _obliqueAngle = val; }

		constexpr auto generationFlag()const noexcept { return _generationFlag; }
		constexpr void setGenerationFlag(types::int16 val) noexcept { _generationFlag = val; }

		constexpr auto trueTypeFlags()const noexcept { return _trueTypeFlags; }
		constexpr void getTrueTypeFlags(types::int16 val) noexcept { _trueTypeFlags = val; }
#pragma endregion getters_setters


#pragma region overrides
		constexpr const char* dxfName() const noexcept { return "STYLE"; }

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader, char auxilData = -1) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer, char auxilData = -1) noexcept override;
#pragma endregion overrides
	};
}
