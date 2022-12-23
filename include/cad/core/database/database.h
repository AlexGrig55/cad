#pragma once
#include <filesystem>

#include "../../enums/enums.hpp"
#include "../../errors/errors.h"

namespace cad
{
	class DataBase
	{
	private:
		std::filesystem::path	_path;
		Error::Code				_lastErr;
		enums::Version			_dbVersion;
		bool					_isValid;

	private:
		bool read()noexcept;
		bool write()noexcept;
		void init()noexcept;

		size_t calculateApproximateFileSize()const noexcept;

		void clearDB()noexcept;

	public:
		DataBase()noexcept :DataBase("") {}
		explicit DataBase(const std::filesystem::path& pathToFile)noexcept;
		~DataBase()noexcept { clearDB(); }

		//Return path to file. It can be set when reading and saving the file
		constexpr const auto& path()const noexcept { return _path; }

		//Return version of this database. It can be set when reading and saving the file
		constexpr auto version()const noexcept { return _dbVersion; }

		//Return false if file read failed, see last error
		constexpr bool isValid()const noexcept { return _isValid; }

		bool save(const std::filesystem::path& path, enums::Version dbVersion, Error::Code* err = nullptr)noexcept;
		bool save(const std::filesystem::path& path, Error::Code* err = nullptr)noexcept { return save(_path, _dbVersion, err); }
		bool save(Error::Code* err = nullptr)noexcept { return save(_path, _dbVersion,err); }
	};
}