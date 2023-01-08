#pragma once
#include "../../util/defines/defines.hpp"
#include "../../enums/enums.hpp"
#include "../base/cad_obj.hpp"

#include <variant>
#include <geom/geom.hpp>
#include <string>

namespace cad::header
{
	class CAD_API Variable:public base::ICadObject
	{
	public:
		enum class TypeData :char
		{
			String,
			Float,
			Int,
			Point2,
			Point3
		};

	private:
		std::variant<util::cad_int64,util::cad_float,geom::Point2_d, geom::Point3_d, std::string> _val;
		const char*	_name;
		char _dataCode[4];
		TypeData _dataType;

	/*private:
		constexpr void chekIsDataValid(TypeData data) const{
			if (typeData() != data)throw std::exception("Wrong data type of var");
		}*/

	public:
		template <class T>
		constexpr Variable(const char* name, const T& val,TypeData dataType, uint16_t dataCode) noexcept :
			_name(name), _dataCode{}, _dataType(dataType),_val(val){
			std::to_chars(_dataCode, _dataCode + 4, dataCode);

			switch (dataType)
			{
			case cad::header::Variable::TypeData::Float:
				_val = static_cast<util::cad_float>(val);
				break;
			case cad::header::Variable::TypeData::Int:
				_val = static_cast<util::cad_int64>(val);
				break;
			}
#if _DEBUG
			switch (dataType)
			{
			case cad::header::Variable::TypeData::String:
				assert(std::is_same<std::string,T>::val);
				break;
			case cad::header::Variable::TypeData::Float:
				assert(std::is_floating_point<T>::val);
				break;
			case cad::header::Variable::TypeData::Int:
				assert(std::is_integral<T>::val);
				break;
			case cad::header::Variable::TypeData::Point2:
				assert(std::is_same<geom::Point2<util::cad_float>, T>::val);
				break;
			case cad::header::Variable::TypeData::Point3:
				assert(std::is_same<geom::Point3<util::cad_float>, T>::val);
				break;
			default:
				assert(false);
				break;
			}
#endif
		}

		constexpr TypeData typeData()const noexcept { return _dataType; }

		constexpr const auto& toString()const { return std::get<std::string>(_val); }
		constexpr const auto& toPoint3()const { return std::get<geom::Point3_d>(_val); }
		constexpr const auto& toPoint2()const { return std::get<geom::Point2_d>(_val); }
		constexpr auto toFloating()const { return std::get<util::cad_float>(_val); }
		constexpr auto toInt()const { return std::get<util::cad_int64>(_val); }

		template <class T>
		constexpr void setVal(const T& val) { _val = val; }

		constexpr const char* dxfObjectName() const noexcept override { return _name; }

	protected:
		uint32_t fromDXF(std::string_view& buffer, enums::Version ver)noexcept override;
		void toDXF(const std::string& buffer, enums::Version ver)noexcept override;
	};
}