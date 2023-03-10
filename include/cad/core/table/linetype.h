#pragma once
#include "./table_record.h"
#include "./../../util/container/container.hpp"

namespace cad::table
{
	class ILinetypeUser :public base::IUser
	{
	public:
		virtual constexpr ~ILinetypeUser() noexcept = default;
		virtual constexpr const types::String& linetype()const noexcept = 0;
		virtual void setLinetype(const types::String& name)noexcept = 0;
	};

	class CAD_API Linetype : public TableRecord<ILinetypeUser>
	{
	public:
		class Element
		{
			friend class Linetype;

			types::String	_text;//9
			size_t			_ptrToStyle;//340
			types::real		_spaceLength;//49
			types::real		_scale;//46
			types::real		_rotation;//50
			types::int16	_elementType;//74
			types::int16	_shapeNumber;//75

		public:
			constexpr Element(types::real spaceLength) noexcept :
				_spaceLength(spaceLength), _elementType(0), _shapeNumber(0), _ptrToStyle(0), _scale(0),
				_rotation(0){}

			constexpr auto& text()const noexcept { return _text; }
			constexpr void setText(const types::String& val) noexcept { _text = val; }

			constexpr auto ptrToStyle()const noexcept { return _ptrToStyle; }
			constexpr void setPtrToStyle(size_t val) noexcept { _ptrToStyle = val; }

			constexpr auto spaceLength()const noexcept { return _spaceLength; }
			constexpr void setSpaceLength(types::real val) noexcept { _spaceLength=val; }

			constexpr auto scale()const noexcept { return _scale; }
			constexpr void setScale(types::real val) noexcept { _scale = val; }

			constexpr auto rotation()const noexcept { return _scale; }
			constexpr void setRotation(types::real val) noexcept { _scale = val; }

			constexpr auto elementType()const noexcept { return _elementType; }
			constexpr void setElementType(types::int16 val) noexcept { _elementType = val; }

			constexpr auto shapeNumber()const noexcept { return _shapeNumber; }
			constexpr void setShapeNumber(types::int16 val) noexcept { _shapeNumber = val; }

		};

	private:

		util::Container<Element> _elements;

		types::String		_descriptiveText;//3
		types::real			_patternLength;//40

	private:
		Element* getCurrentElementForRead(uint32_t& auxilFlag,uint32_t flagCurrentCode);

	public:
		constexpr Linetype(const types::String& name, const types::String& descriptText="")noexcept :
			TableRecord(name), _descriptiveText(descriptText),
			_patternLength(0)
		{}
		constexpr ~Linetype() noexcept = default;

#pragma region getters_setters
		constexpr auto& elements()noexcept { return _elements; }
		constexpr auto& elements()const noexcept { return _elements; }

		constexpr auto countElements()const noexcept { return _elements.count(); }

		constexpr auto& descriptiveText()const noexcept { return _descriptiveText; }
		constexpr void setDescriptiveText(const types::String& val) noexcept { _descriptiveText =val; }

		constexpr auto patternLength()const noexcept { return _patternLength; }
		constexpr void setPatternLength(types::real val) noexcept { _patternLength = val; }
#pragma endregion getters_setters
		

#pragma region overrides
		constexpr const char* dxfName() const noexcept { return "LTYPE"; }

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader, char auxilData = -1) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer, char auxilData = -1) noexcept override;
#pragma endregion overrides
	};
}
