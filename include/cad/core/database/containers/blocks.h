#pragma once
#include "../database.h"
#include "./named_container.h"

class cad::Database::Blocks: public cad::Database::NamedContainer<Block>
{
	mutable util::Container<Block*> _regularBlocks;
	mutable util::Container<Block*> _paperSpaceBlocks;
	mutable util::Container<Block*> _auxiliaryBlocks;

public:
	constexpr Blocks(Database* db) :NamedContainer("BLOCKS",db) {}

#pragma region getters_setters
	constexpr Block* modelSpace() noexcept{ return list().front(); }
	constexpr const Block* modelSpace()const noexcept { return list().front(); }

	//if you add or remove a block, this container may no longer be valid
	util::ConstContainer<Block*>& paperSpaces();
	//if you add or remove a block, this container may no longer be valid
	util::ConstContainer<const Block*>& paperSpaces()const;

	//if you add or remove a block, this container may no longer be valid
	util::ConstContainer<Block*>& auxiliaryBlocks();
	//if you add or remove a block, this container may no longer be valid
	util::ConstContainer<const Block*>& auxiliaryBlocks()const;

	//if you add or remove a block, this container may no longer be valid
	util::ConstContainer<Block*>& regularBlocks();
	//if you add or remove a block, this container may no longer be valid
	util::ConstContainer<const Block*>& regularBlocks()const;

	types::int16 paperSpaceCount()const noexcept;
	types::int16 auxiliaryBlockCount()const noexcept;
	types::int16 regularBlockCount()const noexcept;
#pragma endregion getters_setters


#pragma region actions

	//delete all unused, non standard and non paper_space blocks
	//return count deleted
	size_t purge()noexcept;
#pragma endregion actions


#pragma region overrides
	constexpr const char* dxfName() const noexcept override { return "BLOCKS"; }
protected:
	//1 - blk; other - blk record
	cad::Error::Code readDXF(translator::DXFInput& reader, char auxilData) noexcept override;
	//1 - blk; other - blk record
	cad::Error::Code writeDXF(translator::DXFOutput& writer, char auxilData) noexcept override;
#pragma endregion overrides

private:
	Block* getOrCreateObjectByName(types::String& bufferNmae, enums::Version ver);

	cad::Error::Code readBlocks(translator::DXFInput& reader) noexcept;
	cad::Error::Code writeBlocks(translator::DXFOutput& writer) noexcept;
	cad::Error::Code readBlockRecs(translator::DXFInput& reader) noexcept;
	cad::Error::Code writeBlockRecs(translator::DXFOutput& writer) noexcept;
};