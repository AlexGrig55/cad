#include <cad/core/class/class.h>
#include "../../translator/translator.hpp"

cad::Error::Code cad::Class::readDXF(translator::DXFInput& reader) noexcept
{

	return cad::Error::Code::NoErr;
}

cad::Error::Code cad::Class::writeDXF(translator::DXFOutput& writer) noexcept
{
	auto errCode = writer.writeData(0, dxfName());
	if (errCode == cad::Error::Code::NoErr)
	{
		writer.writeData(1, _recoedName);
		writer.writeData(2, _name);
		writer.writeData(3, _appName);

		writer.writeData(90, _proxyCapabilitiesFlag);
		writer.writeData(91, _inctanceCount);
		writer.writeData(280, _wasProxyFlag);

		errCode = writer.writeData(281, _isEntityFlag);
	}

	return errCode;
}
