#pragma once
#include "../../util/defines/defines.hpp"
#include "../../enums/enums.hpp"
#include "../base/cad_obj.h"

#include <variant>
#include <geom/geom.hpp>
#include <string>

namespace cad
{
	//https://help.autodesk.com/view/OARX/2018/ENU/?guid=GUID-A85E8E67-27CD-4C59-BE61-4DC9FADBE74A - values of vars
	class CAD_API Variable:public base::ICadObject
	{
	private:
		std::variant<types::String,types::real, types::int16, types::int32,
			types::int64, types::boolean, types::Point2, types::Point3 > _val;

		std::string_view	_name;
		int16_t				_dataCode;
		//types::EType		_dataType;
		enums::Version		_startVersion;

		constexpr bool isDummy()const noexcept { return _dataCode == std::numeric_limits<int16_t>::min(); }
	public:
		//Can use:	types::string, types::real, types::int16, types::int32, types::int64, types::boolean, types::Point2, types::Point3
		//
		//<dxfCode> - for points can be any
		template <class T>
		constexpr Variable(const char* name, const T& val,
			int16_t dxfCode, enums::Version startVersion= enums::Version::R12):
			_name(name), _dataCode(dxfCode), _val(val), _startVersion(startVersion) {
			//if _dataCode==min - it is dummy object for readed from file
			if (!isDummy())
			{
				auto eType = types::Type::getByDxfCode(_dataCode);
				if ((eType != types::EType::Point2 && eType != types::EType::Point3) && eType == types::EType::Unk)
				{
					throw std::exception("This type cannot be used for variables");
				}

				if (_val.index() != size_t(eType))
				{
					throw std::exception("Dxf code does not match the data type");
				}
			}
		}

		constexpr auto typeData()const noexcept { return types::EType(_val.index()); }

		//throw exception if set wrong data type
		template<class T>
		constexpr const auto& get()const { return std::get<T>(_val); }

		template <class T>
		constexpr void set(const T& val) { _val = val; }
		template <class T>
		constexpr void set(T&& val) { _val = std::move(val); }

		constexpr const auto& name() const noexcept { return _name; }

		constexpr const char* dxfName() const noexcept override { return _name.data(); }

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer) noexcept override;
	};
}