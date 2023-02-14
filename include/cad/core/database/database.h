#pragma once
#include <filesystem>

#include "../../enums/enums.hpp"
#include "../../errors/errors.h"
#include "../block/block.h"
#include "../table/tables.hpp"

namespace cad
{
	namespace options
	{
		//default values:
		//version=2018; locale = Cyrillic; err = nullptr; binary = false
		class SaveDB
		{
			enums::Version			_version;
			enums::Locale			_locale;
			Error::Code*			_err;
			bool					_binary;

		public:
			constexpr SaveDB()noexcept :_version(enums::Version::V2018),
				_locale(enums::Locale::Cyrillic),
				_err(nullptr), _binary(false){}

			constexpr auto& setVersion(enums::Version val)noexcept { _version = val; return *this; }
			constexpr auto version()const noexcept { return _version;}

			constexpr auto& setLocale(enums::Locale val)noexcept { _locale = val; return *this;	}
			constexpr auto locale()const noexcept { return _locale; }

			constexpr auto& setErrorHolder(Error::Code* val)noexcept { _err = val; return *this; }
			constexpr auto errorHolder()const noexcept { return _err; }

			constexpr auto& setBinaryMode(bool val)noexcept { _binary = val; return *this; }
			constexpr auto binaryMode()const noexcept { return _binary; }

			auto operator->()noexcept { return this; }
			auto operator->()const noexcept { return this; }
		};
	}

	class Database
	{
	private:
		template<class T>
		class NamedContainer;

		class Variables;
		class Classes;
		class Blocks;
		class Objects;
		template<class T>
		class Table;

	private:
		Variables*	_variables;
		Classes*	_classes;

		NamedContainer<table::Appid>*	_appids;
		NamedContainer<table::Linetype>*_linetypes;
		NamedContainer<table::Layer>*	_layers;
		NamedContainer<table::Style>*	_styles;
		NamedContainer<table::UCS>*		_UCSes;
		NamedContainer<table::View>*	_views;
		NamedContainer<table::Vport>*	_vports;
		NamedContainer<table::Dimstyle>*_dimstyles;

		NamedContainer<Block>*			_blocks;

		Objects*	_objects;

		bool		_isValid;

	public:
		//Create default db
		explicit Database(Error::Code* err = nullptr)noexcept :Database(std::filesystem::path()) {}
		//Create db by file
		explicit Database(const std::filesystem::path& pathToFile, Error::Code* err = nullptr)noexcept;
		//Create db by byte buffer
		Database(const types::byte* byteArrayData, size_t size, Error::Code* err = nullptr)noexcept;

		~Database()noexcept;


#pragma region getters_setters
		constexpr Variables& variables()noexcept { return *_variables; }
		constexpr const Variables& variables()const noexcept { return *_variables; }

		constexpr Classes& classes()noexcept { return *_classes; }
		constexpr const Classes& classes()const noexcept { return *_classes; }

		constexpr auto& appids()noexcept { return *_appids; }
		constexpr auto& appids()const noexcept { return *_appids; }

		constexpr auto& linetypes()noexcept { return *_linetypes; }
		constexpr auto& linetypes()const noexcept { return *_linetypes; }

		constexpr auto& layers()noexcept { return *_layers; }
		constexpr auto& layers()const noexcept { return *_layers; }

		constexpr auto& styles()noexcept { return *_styles; }
		constexpr auto& styles()const noexcept { return *_styles; }
		
		constexpr auto& UCSes()noexcept { return *_UCSes; }
		constexpr auto& UCSes()const noexcept { return *_UCSes; }

		constexpr auto& views()noexcept { return *_views; }
		constexpr auto& views()const noexcept { return *_views; }

		constexpr auto& vports()noexcept { return *_vports; }
		constexpr auto& vports()const noexcept { return *_vports; }

		constexpr auto& blocks()noexcept { return *_blocks; }
		constexpr auto& blocks()const noexcept { return *_blocks; }

		constexpr Objects& objects()noexcept { return *_objects; }
		constexpr const Objects& objects()const noexcept { return *_objects; }

		//Must be called to check whether the database has been created.
		//If it returns false, you cannot use this database
		constexpr bool isValid()const noexcept { return _isValid; }

		//return null if handle not exsist
		base::Handler* getObjectByHandle(size_t handle)noexcept;
		//return null if handle not exsist
		const base::Handler* getObjectByHandle(size_t handle)const noexcept;
#pragma endregion getters_setters


#pragma region actions
		bool save(const std::filesystem::path& path,
			const options::SaveDB& options= options::SaveDB() )noexcept;
		bool save(std::vector<types::byte>& buffer,
			const options::SaveDB& options = options::SaveDB())noexcept;

	private:
		Error::Code readFile(const std::filesystem::path& path,std::vector<types::byte>& buffer)noexcept;
		Error::Code readByteArray(const types::byte* byteArrayData, size_t size)noexcept;
		Error::Code writeFile(const std::filesystem::path& path, const std::vector<types::byte>& byteArr)noexcept;
		Error::Code writeByteArray(std::vector<types::byte>& buffer, bool isBinary)noexcept;

		void init()noexcept;
		bool isContainersCreated()const noexcept;
		bool isValidPath(const std::filesystem::path& path)const noexcept;

		enums::Version version()const noexcept;
		enums::Locale locale()const noexcept;

		size_t calculateApproximateFileSize()const noexcept;

		void clearDB()noexcept;
#pragma endregion actions
	};
}