#pragma once
#include "../../string/string.h"
#include "../base/cad_obj.hpp"
#include "../tables/layer.h"

#include <geom/geom.hpp>
#include <filesystem>

namespace cad
{
	class CAD_API Block : public base::Handler, public table::ILayerUser
	{
		String				_name;
		String				_description;
		String				_layer;
		std::filesystem::path _xrefPath;

		geom::Point3_d		_basePoint;

		enums::BlockBitFlagType	_bitFlagType;

	public:
		constexpr Block(const String& name,
			const String& layer = L"0")noexcept :
			_name(name),_layer(layer), _bitFlagType(enums::BlockBitFlagType::None) {}


#pragma region getters_setters
		constexpr const auto& name()					const noexcept { return _name; }
		constexpr void	setName(const String& val)		noexcept { _name = val; }

		constexpr const auto& description()					const noexcept { return _description; }
		constexpr void	setDescription(const String& val)	noexcept { _description = val; }

		constexpr const auto& xrefPath()					const noexcept { return _xrefPath; }
		constexpr void	setXefPath(const std::filesystem::path& val)noexcept { _xrefPath = val; }

		constexpr const auto& basePoint()					const noexcept { return _basePoint; }
		constexpr void	setBasePoint(const geom::Point3_d& val)noexcept { _basePoint = val; }

		constexpr util::cad_int16 bitFlagType() const noexcept { return util::cad_int16(_bitFlagType); }
#pragma endregion getters_setters


#pragma region actions
		inline Block* copy()const { return new Block(*this); }
#pragma endregion actions


#pragma region overrides
		constexpr const char* dxfObjectName() const noexcept { return "BLOCK"; }

		constexpr const String& layer()					const noexcept override { return _layer; }
		constexpr void	setLayer(const String& val)		noexcept override { _layer = val; }

	protected:
		uint32_t fromDXF(std::string_view& buffer, enums::Version ver)noexcept override;
		void toDXF(const std::string& buffer, enums::Version ver)noexcept override;
#pragma endregion overrides
	};
}
