#include <cad/core/database/database.h>
#include <assert.h>
#include "../../translator/translator.hpp"
#include "./initializer/initializer.h"
#include <cad/core/database/containers/containers.hpp>


cad::Error::Code cad::Database::init()noexcept
{
	return Initializer::initDb(this);
}

bool cad::Database::isValidPath(const std::filesystem::path& path) const noexcept
{
	try
	{
		if (path.empty())
		{
			return false;
		}
		else if (path.is_absolute())
		{
			return std::filesystem::exists(path.parent_path());
		}
	}
	catch (...)
	{
		return false;
	}

	return true;
}

cad::enums::Version cad::Database::version() const noexcept
{
	return this->variables().generalVariables().version();
}

cad::enums::Locale cad::Database::locale() const noexcept
{
	return this->variables().generalVariables().locale();
}

cad::Database::Database(const std::filesystem::path& path, Error::Code* err)noexcept
{
	std::vector<types::byte> buffer;
	Error::Code codeErr = readFile(path, buffer);

	if (codeErr == Error::Code::NoErr)
	{
		this->Database::Database(buffer.data(), buffer.size(), err);
	}
	else
	{
		if (err)
			*err = codeErr;
		_isValid = false;
	}
}

cad::Database::Database(const types::byte* byteArrayData, size_t size, Error::Code* err) noexcept
{
	Error::Code localErr = init();

	localErr = readByteArray(byteArrayData, size);

	Initializer::fillHandles(this);

	if (err)
		*err = localErr;

	_isValid = localErr == Error::Code::NoErr;
}


cad::Database::~Database() noexcept
{
	clearDB();

	delete _variables;
	delete _classes;

	delete _linetypes; delete _layers; delete _appids; delete _styles;
	delete _views; delete _ucses; delete _vports; delete _dimstyles;

	delete _blocks;

	delete _objects;
}

size_t cad::Database::calculateApproximateFileSize(bool isBinary) const noexcept
{
	size_t res = 10000;

	res += variables().customCount() * 50;
	res += variables().generalCount() * 50;

	res += (size_t)layers().count() * 400;
	res += (size_t)appids().count() * 100;
	res += (size_t)dimstyles().count() * 1300;
	res += (size_t)linetypes().count() * 500;
	res += (size_t)styles().count() * 400;
	res += (size_t)ucses().count() * 400;
	res += (size_t)views().count() * 400;
	res += (size_t)vports().count() * 600;

	for (auto& blk : blocks().list())
	{
		res += 100;
		res += blk->entityCount() * 700;
	}

	if (isBinary)
		res *= 0.8;

	return res;
}

void cad::Database::clearDB() noexcept
{

}

cad::base::Handler* cad::Database::getObjectByHandle(size_t handle) noexcept
{
	return nullptr;
}

const cad::base::Handler* cad::Database::getObjectByHandle(size_t handle) const noexcept
{
	return nullptr;
}

bool cad::Database::save(const std::filesystem::path& path, const options::Save& options) noexcept
{
	std::vector<types::byte> buffer;

	if (save(buffer, options))
	{
		Error::Code errCode = writeFile(path, buffer);

		if (options.errorHolder())
			*options.errorHolder() = errCode;

		return errCode== Error::Code::NoErr;
	}

	return false;
}

bool cad::Database::save(std::vector<types::byte>& buffer, const options::Save& options) noexcept
{
	Error::Code errCode = Error::Code::NoErr;

	if (options.version() > enums::Version::Unknown)
	{
		if (options.locale() > enums::Locale::Unknown)
		{
			variables().generalVariables().setVersion(options.version());
			variables().generalVariables().setLocale(options.locale());

			errCode = writeByteArray(buffer, options->binaryMode());
		}
		else
			errCode = Error::Code::InvalidLocale;
	}
	else
		errCode = Error::Code::InvalidVersion;


	if (options.errorHolder())
		*options.errorHolder() = errCode;

	return errCode == Error::Code::NoErr;
}

cad::Error::Code cad::Database::readFile(const std::filesystem::path& path,
	std::vector<types::byte>& buffer) noexcept
{
	if (!isValidPath(path))
		return Error::Code::InvalidPath;

	const int MEMORY_RESERVE_FACTOR = 3;
	auto sizeFile = std::filesystem::file_size(path);

	if (sizeFile * MEMORY_RESERVE_FACTOR > buffer.max_size())
		return Error::Code::OutOfMemory;

	buffer.resize(sizeFile);

	auto file = _wfopen(path.wstring().c_str(), L"rb");

	if (file == nullptr)
		return Error::Code::CannotOpenFile;

	auto countReaded = fread(buffer.data(), sizeFile, 1, file);
	fclose(file);

	if (countReaded != 1)
		return Error::Code::IOStreamReadingError;

	return Error::Code::NoErr;
}

cad::Error::Code cad::Database::readByteArray(const types::byte* byteArrayData, size_t size) noexcept
{
	translator::DXFReader reader(this, locale(), version());

	return reader.read(byteArrayData,size);
}

cad::Error::Code cad::Database::writeFile(const std::filesystem::path& path,
	const std::vector<types::byte>& buffer) noexcept
{
	if (!isValidPath(path))
		return Error::Code::InvalidPath;

	auto file = _wfopen(path.wstring().c_str(), L"wb");

	if (file == nullptr)
		return Error::Code::CannotOpenFile;

	auto countReaded = fwrite(buffer.data(), buffer.size(), 1, file);
	auto closeStatus = fclose(file);

	if (countReaded != 1 || closeStatus != 0)
		return Error::Code::IOStreamWritingError;

	return Error::Code::NoErr;
}

cad::Error::Code cad::Database::writeByteArray(std::vector<types::byte>& buffer,bool isBinary) noexcept
{
	translator::DXFWriter writer(this, locale(), version());
	auto sizeFile = calculateApproximateFileSize(isBinary);

	if (sizeFile > buffer.max_size())
		return Error::Code::OutOfMemory;

	buffer.resize(sizeFile);

	return writer.write(buffer, isBinary);
}
