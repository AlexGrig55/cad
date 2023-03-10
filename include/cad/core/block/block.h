#pragma once
#include "../base/base.hpp"
#include "../table/layer.h"
#include "../entity/entities.hpp"

#include <geom/geom.hpp>
#include <filesystem>

namespace cad
{
	class IBlockUser :public base::IUser
	{
	public:
		virtual const types::String& blockName()const noexcept = 0;
		virtual void setBlockName(const types::String& val)noexcept = 0;
	};

	class CAD_API Block : public base::NamedObject<IBlockUser>, public table::ILayerUser
	{
		struct BlkRecord :public base::Handler
		{
		public:
			std::string		_bitmapBinData;
			types::int16	_exploadability = 1;
			types::int16	_scalability = 1;
			types::int16	_units = 0;

			constexpr const char* dxfName() const noexcept { return "BLOCK_RECORD"; }

		protected:
			Error::Code readDXF(translator::DXFInput& reader,char) noexcept override;
			Error::Code writeDXF(translator::DXFOutput& writer, char) noexcept override { return Error::Code(); }
		};

		util::Container<entity::BaseEntity*>	_entities;

		BlkRecord				_blkRec;

		types::String			_description;
		types::String			_layer;
		types::String			_xrefPath;

		types::Point3			_basePoint;

		size_t					_endBlkHandle;

		enums::BlockBitFlagType	_bitFlagType;

		types::int16			_isPaperSpace;

		//first - <=r12; second - >r12
		static const std::vector<std::pair<const char*, const char*>> STANDARD_NAMES;

	private:
		void actionBeforeAdded(entity::BaseEntity* entity);
		void actionBeforeDeleted(entity::BaseEntity* entity);
		size_t indexByVal(const entity::BaseEntity* entityPtr)const noexcept;

		Error::Code readDXFBlk(translator::DXFInput& reader)noexcept;
		Error::Code writeDXFBlk(translator::DXFOutput& writer)noexcept;
		Error::Code writeDXFBlkRecord(translator::DXFOutput& writer)noexcept;

	public:
		constexpr Block(const types::String& name,
			const types::String& layer = "0",bool isPaperSpace=false)noexcept :
			base::NamedObject<IBlockUser>(name),_layer(layer),
			_bitFlagType(enums::BlockBitFlagType::None),
			_isPaperSpace(isPaperSpace), _endBlkHandle(0){}

		Block(const Block& other);
		Block(Block&& other) = default;

		~Block()noexcept { clear(); }

		Block& operator=(const Block& other);

#pragma region getters_setters
		constexpr const util::ConstContainer<const entity::BaseEntity*>& entities()const noexcept { 
			return *(util::ConstContainer<const entity::BaseEntity*>*)((void*)&_entities);
		}
		constexpr util::ConstContainer<entity::BaseEntity*>& entities() noexcept { return _entities; }
		constexpr auto entityCount() const noexcept { return _entities.count(); }

		constexpr const auto& description() const noexcept { return _description; }
		constexpr void	setDescription(const types::String& val) noexcept { _description = val; }

		constexpr const auto& xrefPath() const noexcept { return _xrefPath; }
		constexpr void	setXefPath(const types::String& val)noexcept { _xrefPath = val; }

		constexpr const auto& basePoint() const noexcept { return _basePoint; }
		constexpr void	setBasePoint(const types::Point3& val)noexcept { _basePoint = val; }

		constexpr types::int16 bitFlagType() const noexcept { return types::int16(_bitFlagType); }

		constexpr bool isPaperSpace()const noexcept { return _isPaperSpace; }

		constexpr const auto& bitmapBinData() const noexcept { return _blkRec._bitmapBinData; }
		constexpr void setBitmapBinData(std::string_view binData){ _blkRec._bitmapBinData = binData; }
	
		constexpr auto exploadability() const noexcept { return _blkRec._exploadability; }
		constexpr void setBitmapBinData(types::int16 val) noexcept { _blkRec._exploadability = val; }

		constexpr auto scalability() const noexcept { return _blkRec._scalability; }
		constexpr void setScalability(types::int16 val) noexcept { _blkRec._scalability = val; }

		constexpr auto units() const noexcept { return _blkRec._units; }
		constexpr void setUnits(types::int16 val) noexcept { _blkRec._units = val; }
#pragma endregion getters_setters


#pragma region actions
		void addEntity(cad::entity::BaseEntity* entity);

		void delEntity(const cad::entity::BaseEntity* entityPtr);
		void delEntity(size_t ind, size_t count = 1);
		//clear container with entities
		void clear()noexcept { delEntity(0, entityCount()); }

		constexpr void swapEntities(size_t indFirst, size_t indSecond)noexcept 
		{ std::swap(_entities[indFirst], _entities[indSecond]); }
#pragma endregion actions


#pragma region overrides
		constexpr const char* dxfName() const noexcept { return "BLOCK"; }

		constexpr const types::String& layer()					const noexcept override { return _layer; }
		constexpr void	setLayer(const types::String& val)		override { _layer = val; }
		constexpr void	setLayer(types::String&& val)			override { _layer = std::move(val); }

	protected:
		void addingToDb(Database* db)noexcept override;
		void onUserKeeperNameChanged(const char* interfaceName, const types::String& name)override;
		//if auxilData==1 - blk else - blk record
		Error::Code readDXF(translator::DXFInput& reader, char auxilData)	noexcept override;
		//if auxilData==1 - blk else - blk record
		Error::Code writeDXF(translator::DXFOutput& writer, char auxilData)noexcept override;
#pragma endregion overrides
	};
}
