#pragma once
#include "./table_record.h"
#include "./linetype.h"

namespace cad::table
{
	class ILayerUser :public base::IUser
	{
	public:
		virtual constexpr ~ILayerUser() noexcept = default;
		virtual constexpr const types::String& layer()const noexcept = 0;
		virtual void setLayer(const types::String& layerName) = 0;
		virtual void setLayer(types::String&& layerName) = 0;
	};

	class CAD_API Layer : public TableRecord<ILayerUser>, public ILinetypeUser
	{
		types::String		_linetype;

		Color				_color;

		types::boolean		_plotFlag;

		enums::LineWeight	_lineWeight;

		bool				_isOn;

		enum Flags { Frozen = 1, Locked = 4 };

	public:
		constexpr Layer(const types::String& name)noexcept :
			TableRecord(name), _color(Color::White), _plotFlag(true),
			_lineWeight(enums::LineWeight::Default), _isOn(true)
		{}
		constexpr ~Layer()noexcept = default;

#pragma region getters_setters
		constexpr auto color()const noexcept { return _color; }
		constexpr void setColor(const Color& val)noexcept { _color = val; }

		constexpr bool isFrozen()const noexcept { return bitFlags() & Frozen; }
		constexpr void setFrozen(bool val) noexcept { setBitFlags(bitFlags() & ~Frozen); }

		constexpr bool isLocked()const noexcept { return bitFlags() & Locked; }
		constexpr void setLocked(bool val) noexcept { setBitFlags(bitFlags() & ~Locked); }

		constexpr bool isOn()const noexcept { return _isOn; }
		constexpr void setOn(bool val) noexcept { _isOn = val; }

		constexpr auto plotFlag()const noexcept { return _plotFlag; }
		constexpr void setPlotFlag(bool val) noexcept { _plotFlag = val; }

		constexpr auto lineWeight()const noexcept { return _lineWeight; }
		constexpr void setLineWeight(enums::LineWeight val) noexcept { _lineWeight = val; }
#pragma endregion getters_setters


#pragma region overrides
		constexpr const types::String& linetype()const noexcept override { return _linetype; }
		void setLinetype(const types::String& name)noexcept override { _linetype = name; }

		constexpr const char* dxfName() const noexcept { return "LAYER"; }

	protected:
		void onUserKeeperNameChanged(const char* interfaceName, const types::String& name)override;
		cad::Error::Code readDXF(translator::DXFInput& reader, char auxilData = -1) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer, char auxilData = -1) noexcept override;
#pragma endregion overrides
	};
}
