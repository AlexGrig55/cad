#pragma once
#include "../base/cad_obj.h"
#include "../table/layer.h"
#include "../entity/entities.hpp"

#include <geom/geom.hpp>
#include <filesystem>

namespace cad
{
	class CAD_API Block : public base::NamedObject, public table::ILayerUser
	{
		util::Container<entity::BaseEntity*>	_entities;

		types::String			_description;
		types::String			_layer;
		types::String			_xrefPath;

		types::Point3			_basePoint;

		enums::BlockBitFlagType	_bitFlagType;

		//first - <=r12; second - >r12
		static const std::vector<std::pair<const char*, const char*>> STANDARD_NAMES;

	private:
		void actionBeforAdded(entity::BaseEntity* entity);
		void actionBeforDeleted(entity::BaseEntity* entity);
		size_t indexByVal(const entity::BaseEntity* entityPtr)const noexcept;

		entity::BaseEntity* createEntityByName(std::string_view name);
		entity::BaseEntity* readEntity(std::string_view entiName, translator::DXFInput& reader)noexcept;

	public:
		constexpr Block(const types::String& name,
			const types::String& layer = "0")noexcept :
			base::NamedObject(name),_layer(layer), _bitFlagType(enums::BlockBitFlagType::None) {}
		~Block()noexcept { clear(); }

#pragma region getters_setters
		constexpr const util::ConstContainer<const entity::BaseEntity*>& entities()const noexcept { 
			return *(util::ConstContainer<const entity::BaseEntity*>*)((void*)&_entities);
		}
		constexpr util::ConstContainer<entity::BaseEntity*>& entities() noexcept { return _entities; }
		constexpr auto countEntities() const noexcept { return _entities.count(); }

		constexpr const auto& description() const noexcept { return _description; }
		constexpr void	setDescription(const types::String& val) noexcept { _description = val; }

		constexpr const auto& xrefPath() const noexcept { return _xrefPath; }
		constexpr void	setXefPath(const types::String& val)noexcept { _xrefPath = val; }

		constexpr const auto& basePoint() const noexcept { return _basePoint; }
		constexpr void	setBasePoint(const types::Point3& val)noexcept { _basePoint = val; }

		constexpr types::int16 bitFlagType() const noexcept { return types::int16(_bitFlagType); }
#pragma endregion getters_setters


#pragma region actions
		void addEntity(cad::entity::BaseEntity* entity);

		void delEntity(const cad::entity::BaseEntity* entityPtr);
		void delEntity(size_t ind, size_t count = 1);
		//clear container with entities
		void clear()noexcept { delEntity(0, countEntities()); }

		constexpr void swapEntities(size_t indFirstEnt, size_t indSecondEnt)noexcept { std::swap(_entities[indFirstEnt], _entities[indSecondEnt]); }
#pragma endregion actions


#pragma region overrides
		constexpr const char* dxfName() const noexcept { return "BLOCK"; }

		constexpr const types::String& layer()					const noexcept override { return _layer; }
		constexpr void	setLayer(const types::String& val)		noexcept override { _layer = val; }

	protected:
		Error::Code readDXF(translator::DXFInput& reader)	noexcept override;
		Error::Code writeDXF(translator::DXFOutput& reader)	noexcept override;
#pragma endregion overrides
	};
}
