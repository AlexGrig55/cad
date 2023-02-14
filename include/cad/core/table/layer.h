#pragma once
#include "./table_object.h"
#include "./linetype.h"

namespace cad::table
{
	class ILayerUser
	{
	public:
		virtual ~ILayerUser() = default;
		virtual constexpr const types::String& layer()const noexcept = 0;
		virtual void setLayer(const types::String& layerName)noexcept = 0;
	};

	class CAD_API Layer : public TableObject, public ILinetypeUser
	{
		types::String				_linetype;

		Color				_color;

		types::boolean		_plotFlag;

		enums::LineWeight	_lineWeight;

		bool				_isOn;

		enum Flags { Frozen = 1, Locked = 4 };

	public:
		constexpr Layer(const types::String& name)noexcept :
			TableObject(name), _color(enums::Color::White), _plotFlag(true),
			_lineWeight(enums::LineWeight::Default), _isOn(true)
		{}

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
		cad::Error::Code readDXF(translator::DXFInput& reader) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer) noexcept override;
#pragma endregion overrides
	};
}
