#include <cad/util/var_values/var_values.h>

const std::vector<cad::types::String> cad::util::VersionsList::_list{
    "Unknown",
    "AC1009",
    "AC1015",
    "AC1018",
    "AC1021",
    "AC1024",
    "AC1027",
    "AC1032"
};

const cad::types::String& cad::util::VersionsList::getVersionName(enums::Version ver) noexcept
{
    auto i = int(ver);
    if (i >= _list.size())
        return _list[(int)enums::Version::Unknown];
    else
        return _list[i];
}

cad::enums::Version cad::util::VersionsList::getVersionNum(const cad::types::String& ver) noexcept
{
    for (int j = 0; auto & i : _list)
    {
        if (i== ver)
            return cad::enums::Version(j);

        ++j;
    }

    return enums::Version::Unknown;
}


const std::vector<cad::types::String> cad::util::LocalesList::_localeNames{
    "Unknown",
    "ANSI_874",
    "ANSI_932",
    "ANSI_936",
    "ANSI_949",
    "ANSI_950",
    "ANSI_1250",
    "ANSI_1251",
    "ANSI_1252",
    "ANSI_1253",
    "ANSI_1254",
    "ANSI_1255",
    "ANSI_1256",
    "ANSI_1257",
    "ANSI_1258"
};

const std::vector<std::locale> cad::util::LocalesList::_locales{
    std::locale::classic(),
    std::locale("th_TH"),
    std::locale("ja_JP"),
    std::locale("zn_CN"),
    std::locale("ko_KR"),
    std::locale("zh_TW"),
    std::locale("pl_PL"),
    std::locale("ru_RU"),
    std::locale("en_US"),
    std::locale("el_GR"),
    std::locale("tr_TR"),
    std::locale("he_IL"),
    std::locale("ar_EG"),
    std::locale("lt_LT"),
    std::locale("vi_VN")
};

const cad::types::String& cad::util::LocalesList::getLocaleName(enums::Locale locale) noexcept
{
    auto i = int(locale);
    if (i >= _localeNames.size())
        return _localeNames[int(enums::Locale::Unknown)];
    else
        return _localeNames[i];
}

cad::enums::Locale cad::util::LocalesList::getLocaleNum(const cad::types::String& local) noexcept
{
    for (int j=0;auto& i : _localeNames)
    {
        if (i== local)
            return cad::enums::Locale(j);

        ++j;
    }

    return enums::Locale::Unknown;
}

const std::locale& cad::util::LocalesList::getLocale(enums::Locale ver) noexcept
{
    auto i = int(ver);
    if (i >= _locales.size())
        return _locales[int(enums::Locale::Unknown)];
    else
        return _locales[i];
}
