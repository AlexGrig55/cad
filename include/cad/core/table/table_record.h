#pragma once

#include "../base/base.hpp"

namespace cad::table
{
	template <class IUser>
	class CAD_API TableRecord : public base::NamedObject<IUser>
	{
	private:
		types::int16 _standardBitFlags;

	public:
		constexpr TableRecord(const types::String& name) noexcept:
			base::NamedObject<IUser>(name), _standardBitFlags(0){}

		//flags by code 70
		constexpr auto bitFlags()const noexcept { return _standardBitFlags; }
		//flags by code 70
		constexpr void setBitFlags(types::int16 val)noexcept { _standardBitFlags = val; }

	protected:
		bool readBaseTabRec(int16_t dxfCode, translator::DXFInput& reader) noexcept;
		cad::Error::Code writeTabRecordHeader(std::string_view dxfName, std::string_view className,translator::DXFOutput& writer)noexcept;
	};
}