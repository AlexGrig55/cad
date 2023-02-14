#pragma once
#include "../base/cad_obj.h"
#include "../table/layer.h"

#include <geom/geom.hpp>
#include <filesystem>

namespace cad
{
	class CAD_API Block : public base::NamedObject, public table::ILayerUser
	{
		types::String			_description;
		types::String			_layer;
		std::filesystem::path	_xrefPath;

		geom::Point3_d		_basePoint;

		enums::BlockBitFlagType	_bitFlagType;

	public:
		constexpr Block(const types::String& name,
			const types::String& layer = "0")noexcept :
			base::NamedObject(name),_layer(layer), _bitFlagType(enums::BlockBitFlagType::None) {}


#pragma region getters_setters
		constexpr const auto& description()					const noexcept { return _description; }
		constexpr void	setDescription(const types::String& val)	noexcept { _description = val; }

		constexpr const auto& xrefPath()					const noexcept { return _xrefPath; }
		constexpr void	setXefPath(const std::filesystem::path& val)noexcept { _xrefPath = val; }

		constexpr const auto& basePoint()					const noexcept { return _basePoint; }
		constexpr void	setBasePoint(const geom::Point3_d& val)noexcept { _basePoint = val; }

		constexpr types::int16 bitFlagType() const noexcept { return types::int16(_bitFlagType); }
#pragma endregion getters_setters


#pragma region actions
		//inline Block* copy()const { return new Block(*this); }
#pragma endregion actions


#pragma region overrides
		constexpr const char* dxfName() const noexcept { return "BLOCK"; }

		constexpr const types::String& layer()					const noexcept override { return _layer; }
		constexpr void	setLayer(const types::String& val)		noexcept override { _layer = val; }

	protected:
		Error::Code readDXF(translator::DXFInput& reader) noexcept override;
		Error::Code writeDXF(translator::DXFOutput& reader) noexcept override;
#pragma endregion overrides
	};
}
