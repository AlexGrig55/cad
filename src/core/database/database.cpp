#include <cad/core/database/database.h>
#include <assert.h>

#include "../../dxf_translator/dxf_reader.h"
#include "../../dxf_translator/dxf_writer.h"

bool cad::DataBase::read() noexcept
{
	const int MEMORY_RESERVE_FACTOR = 2;
	dxf_buffer buffer;
	DXFReader reader(this);

	auto sizeFile = std::filesystem::file_size(_path);

	if (sizeFile * MEMORY_RESERVE_FACTOR > buffer.max_size())
	{
		_lastErr = Error::Code::OutOfMemory;
		return false;
	}

	buffer.resize(sizeFile);

	auto file = _wfopen(_path.wstring().c_str(), L"rb");
	if (file==nullptr)
	{
		_lastErr = Error::Code::CannotOpenFile;
		return false;
	}

	auto countReaded = fread(buffer.data(), sizeFile, 1, file);
	fclose(file);

	if (countReaded!= 1)
	{
		_lastErr = Error::Code::IOStreamReadingError;
		return false;
	}

	_lastErr = reader.read(buffer);

	return _lastErr== Error::Code::NoErr;
}

bool cad::DataBase::write() noexcept
{
	dxf_buffer buffer;
	DXFWriter writer(this);
	auto sizeFile = calculateApproximateFileSize();

	if (sizeFile > buffer.max_size())
	{
		_lastErr = Error::Code::OutOfMemory;
		return false;
	}

	buffer.resize(sizeFile);

	_lastErr = writer.write(buffer);
	sizeFile = buffer.size();

	auto file = _wfopen(_path.wstring().c_str(), L"wb");
	if (file == nullptr)
	{
		_lastErr = Error::Code::CannotOpenFile;
		return false;
	}

	auto countReaded = fwrite(buffer.data(), sizeFile, 1, file);
	auto closeStatus = fclose(file);

	if (countReaded != 1|| closeStatus!=0)
	{
		_lastErr = Error::Code::IOStreamWritingError;
		return false;
	}

	return _lastErr == Error::Code::NoErr;
}

void cad::DataBase::init()noexcept
{

}

cad::DataBase::DataBase(const std::filesystem::path& path)noexcept:
	_path(path),
	_dbVersion(enums::Version::V2018),
	_isValid(true),
	_lastErr(Error::Code::NoErr)
{
	init();

	if (!_path.empty())
	{
		if (!std::filesystem::exists(_path)|| !std::filesystem::is_regular_file(_path))
			_lastErr = Error::Code::NotValidPath;

		if (_lastErr == Error::Code::NoErr)
			read();

		_isValid = _lastErr == Error::Code::NoErr;
	}
}

size_t cad::DataBase::calculateApproximateFileSize() const noexcept
{
	size_t res = 0;



	return res*2;
}

void cad::DataBase::clearDB() noexcept
{

}

bool cad::DataBase::save(const std::filesystem::path& path, enums::Version dbVersion, Error::Code* err) noexcept
{
	assert(dbVersion!=enums::Version::Unknown);

	bool isOk = true;

	if (path!=_path)
		_path = path;

	if(dbVersion!= _dbVersion)
		_dbVersion = dbVersion;

	isOk = std::filesystem::exists(_path.parent_path());

	if (!isOk)
		_lastErr = Error::Code::NotValidPath;
	else
	{
		isOk = write();
	}

	if (err)
		*err = _lastErr;

    return isOk;
}
