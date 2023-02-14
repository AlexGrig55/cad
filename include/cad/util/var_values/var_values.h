#pragma once

#include "../../enums/enums.hpp"
#include <vector>

namespace cad::util
{
	class VersionsList
	{
		static const std::vector<types::String> _list;

	public:
		static const types::String& getVersionName(enums::Version ver)noexcept;
		static enums::Version		getVersionNum(const types::String& val)noexcept;
	};

	//DXF 2007(AC1021) and later use utf8
	class LocalesList
	{
		static const std::vector<types::String> _localeNames;
		static const std::vector<std::locale> _locales;

	public:
		static const types::String&	getLocaleName(enums::Locale ver)noexcept;
		static enums::Locale		getLocaleNum(const types::String& loc)noexcept;
		//if unknown, return classi locale
		static const std::locale&	getLocale(enums::Locale ver)noexcept;
	};
}
