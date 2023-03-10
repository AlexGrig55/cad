#pragma once
#include "./handler.h"

namespace cad
{
	class Database;
}

namespace cad::base
{
	template <class IUser>
	class NamedObject;

	class IUser
	{
		template <class T>
		friend class NamedObject;

	protected:
		virtual void onUserKeeperNameChanged(const char* interfaceName,const types::String& name) = 0;
	};

	template <class User>
	class NamedObject :public Handler
	{
		friend class Database;

	private:
		util::Container<User*>	_users;

		types::String	_name;
		bool			_isStandard;

		void callChangeNameForUsers()
		{
			const char* iName = typeid(User).name();
			for (auto i = _users.data(), end = i + _users.count(); i < end; i++)
			{
				(*i)->onUserKeeperNameChanged(iName, _name);
			}
		}

	public:
		constexpr NamedObject(const types::String& name): _name(name), _isStandard(false) {
			static_assert(std::is_base_of<IUser,User>::value,"Invalid template");
		}
		constexpr NamedObject(const NamedObject& other) :
			Handler(other), _name(other._name), _isStandard(other._isStandard) {}
		
		constexpr NamedObject(NamedObject&& other) noexcept = default;

		constexpr NamedObject& operator=(const NamedObject& other)
		{
			Handler::operator=(other);
			setName(other._name);
			return *this;
		}

		constexpr auto& name()const noexcept { return _name; }
		constexpr void setName(const types::String& val) {
			if (_name == val)
				return;
			if (types::String::compare(_name, val, UString::CaseSens::Insensitive) && isStandard())
				throw std::exception("Cannot change the name of a standard object");
			_name = val;
			callChangeNameForUsers();
		}
		constexpr void setName(types::String&& val) {
			if (_name == val)
				return;
			if (types::String::compare(_name, val, UString::CaseSens::Insensitive)&& isStandard())
				throw std::exception("Cannot change the name of a standard object");
			_name = std::move(val);
			callChangeNameForUsers();
		}

		//if return true, this object can't del from db
		constexpr bool isStandard()const noexcept { return _isStandard; }

		constexpr auto userCount()const noexcept { return _users.count(); }
		constexpr auto& users()const noexcept { return _users; }
		constexpr auto& users()noexcept { return _users; }
	};
}
