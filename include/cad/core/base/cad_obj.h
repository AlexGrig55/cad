#pragma once
#include "../../enums/enums.hpp"
#include "../../color/color.h"
#include "../../util/defines/defines.hpp"
#include "../../errors/errors.h"
#include "../../types/types.hpp"


namespace cad::translator
{
	class BaseDxfTranslator;
	class DXFInput;
	class DXFOutput;
}

namespace cad::base
{
	class ICadObject
	{
		friend class translator::BaseDxfTranslator;

	public:
		virtual ~ICadObject() = default;

		//return dxf name of this object
		virtual constexpr const char* dxfName() const noexcept = 0;
	protected:

		virtual Error::Code readDXF(translator::DXFInput& reader) noexcept = 0;
		virtual Error::Code writeDXF(translator::DXFOutput& reader) noexcept = 0;
	};

	class Handler :public ICadObject
	{
	private:
		size_t _handle;

	protected:
		constexpr void setHandle(size_t val) noexcept { _handle= val; }

	public:
		constexpr Handler()noexcept :_handle(0) {}

		constexpr auto handle()const noexcept { return _handle; }
	};

	class NamedObject :public Handler
	{
	private:
		types::String	_name;
		bool			_isStandard;

	protected:
		constexpr auto& nameRef() noexcept { return _name; }

	public:
		constexpr NamedObject(const types::String& name)noexcept : _name(name), _isStandard(false) {}

		constexpr auto& name()const noexcept { return _name; }
		constexpr void setName(const types::String& val) noexcept { _name = val; }
		constexpr void setName(types::String&& val) noexcept { _name = std::move(val); }

		//if return true, this object can't del from db
		constexpr bool isStandard()const noexcept { return _isStandard; }

	protected:
		
		Error::Code readDXF(translator::DXFInput& reader) noexcept override;
		Error::Code writeDXF(translator::DXFOutput& reader) noexcept override;
	};
}
