#pragma once
#include "./table_record.h"

#include <variant>
#include <string_view>

namespace cad::table
{
	class IDimstyleUser :public base::IUser
	{
	public:
		virtual constexpr const types::String& dimstyle()const noexcept = 0;
		virtual constexpr void setDimstyle(const types::String& name) = 0;
	};

	class CAD_API Dimstyle : public TableRecord<IDimstyleUser>
	{
	public:
		class Variable
		{
			std::variant<types::String, types::real, types::int16> _val;
			std::string_view	_name;
			int16_t				_dataCode;
			enums::Version		_startVer;
			enums::Version		_endVer;

		public:
			//Can use:	types::string, types::real, types::int16, types::int32, types::int64, types::boolean
			template <class T>
			constexpr Variable(std::string_view name, const T& val,
				int16_t dxfCode, enums::Version startVer = enums::Version::R12, enums::Version endVer = enums::Version::V2018) :
				_name(name), _dataCode(dxfCode), _val(val), _startVer(startVer), _endVer(endVer) {

				auto eType = types::Type::getByDxfCode(_dataCode);

				if (eType > types::EType::Bool)
					throw std::exception("This type can't be used for variables");

				if (_val.index() != size_t(eType))
					throw std::exception("Dxf code does not match the data type");
			}
			constexpr auto startVersion()const noexcept { return _startVer; }
			constexpr auto endVersion()const noexcept { return _endVer; }

			constexpr auto code()const noexcept { return _dataCode; }
			constexpr auto typeData()const noexcept { return types::EType(_val.index()); }

			//throw exception if set wrong data type
			template<class T>
			constexpr auto& get()const { return std::get<T>(_val); }

			template <class T>
			constexpr void set(const T& val) { _val = val; }
			template <class T>
			constexpr void set(T&& val) { _val = val; }

			constexpr auto name() const noexcept { return _name; }
		};

	private:
		util::Container<Variable> _variables;

	private:
		void init();

	public:
		Dimstyle(const types::String& name)noexcept;

#pragma region getters_setters
		constexpr const util::ConstContainer<Variable>& variables()const noexcept { return _variables; }
		//Get var by name, return null if not exists, find general and custom vars
		Variable* variableByName(std::string_view name)noexcept;
		//Get var by name, return null if not exists, find general and custom vars
		const Variable* variableByName(std::string_view name)const noexcept;
		//Get var by code, return null if not exists, find general and custom vars
		Variable* variableByCode(uint16_t code)noexcept;
		//Get var by code, return null if not exists, find general and custom vars
		const Variable* variableByCode(uint16_t code)const noexcept;
#pragma endregion getters_setters

#pragma region overrides
		constexpr const char* dxfName() const noexcept { return "DIMSTYLE"; }

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader, char auxilData = -1) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer, char auxilData = -1) noexcept override;
#pragma endregion overrides
	};
}
