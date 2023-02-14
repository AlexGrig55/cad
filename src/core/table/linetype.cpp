#include <cad/core/table/linetype.h>
#include "../../translator/translator.hpp"

enum Codes
{
    DescriptiveText = 3,
    PatternLength = 40,

    Text=9,
    PtrToStyle=340,
    SpaceLength=49,
    Scale=46,
    Rotation=50,
    ElementType=74,
    ShapeNumber=75
};

using tr = cad::translator::BaseDxfTranslator;

cad::table::Linetype::Element* cad::table::Linetype::getCurrentElementForRead(uint32_t& auxilFlag, uint32_t flagCurrentCode)
{
    if (_elements.count() == 0 || auxilFlag & flagCurrentCode)
    {
        auxilFlag = 0;
        try
        {
            _elements.add(Element(0));
        }
        catch (...)
        {
            return nullptr;
        }
    }
    auxilFlag |= flagCurrentCode;
    return &_elements.back();
}

cad::Error::Code cad::table::Linetype::readDXF(translator::DXFInput& reader) noexcept
{
    int16_t dxfCode=-1;
    std::string_view str;
    Error::Code errCode = Error::Code::NoErr;
    bool stop = false;

    uint32_t auxilFlag = 0;
    Element* currentElement = nullptr;

    while (reader.isGood() && !stop)
    {
        reader.readCode(&dxfCode);

        switch (dxfCode)
        {
        case tr::DXF_DATA_NAMES[tr::Endtab].first:
            reader.readValue(str);
            if (str == tr::DXF_DATA_NAMES[tr::Endtab].second)
                stop = true;
            else
                errCode = Error::Code::InvalidDataInFile;
            break;

        case Codes::DescriptiveText:
            reader.readValue(_descriptiveText);
            break;

        case Codes::PatternLength:
            reader.readValue(_patternLength);
            break;

        case Codes::Text:
            currentElement = getCurrentElementForRead(auxilFlag, 1);
            if (currentElement)
                reader.readValue(currentElement->_text);
            else
                errCode = Error::Code::OutOfMemory;
            break;

        case Codes::PtrToStyle:
            currentElement = getCurrentElementForRead(auxilFlag, 2);
            if (currentElement)
                reader.readValue(currentElement->_ptrToStyle, 16);
            else
                errCode = Error::Code::OutOfMemory;
            break;

        case Codes::SpaceLength:
            currentElement = getCurrentElementForRead(auxilFlag, 2 * 2);
            if(currentElement)
                reader.readValue(currentElement->_spaceLength);
            else
                errCode = Error::Code::OutOfMemory;
            break;

        case Codes::Scale:
            currentElement = getCurrentElementForRead(auxilFlag, 2 * 3);
            if (currentElement)
                reader.readValue(currentElement->_scale);
            else
                errCode = Error::Code::OutOfMemory;
            break;

        case Codes::Rotation:
            currentElement = getCurrentElementForRead(auxilFlag, 2 * 4);
            if (currentElement)
                reader.readValue(currentElement->_rotation);
            else
                errCode = Error::Code::OutOfMemory;
            break;

        case Codes::ElementType:
            currentElement = getCurrentElementForRead(auxilFlag, 2 * 5);
            if (currentElement)
                reader.readValue(currentElement->_elementType);
            else
                errCode = Error::Code::OutOfMemory;
            break;

        case Codes::ShapeNumber:
            currentElement = getCurrentElementForRead(auxilFlag, 2 * 6);
            if (currentElement)
                reader.readValue(currentElement->_shapeNumber);
            else
                errCode = Error::Code::OutOfMemory;
            break;

        default:
            errCode=TableObject::readDXF(reader);
            break;
        }
    }

    return errCode;
}

cad::Error::Code cad::table::Linetype::writeDXF(translator::DXFOutput& writer) noexcept
{
    Error::Code errCode = TableObject::writeDXF(writer);

    if (errCode!= Error::Code::NoErr)
        return errCode;

    if (writer.version() > enums::Version::R12)
        writer.writeData(100, "AcDbLinetypeTableRecord");

    writer.writeData(72, types::int16(65));
    writer.writeData(73, types::int16(countElements()));
    writer.writeData(Codes::PatternLength, patternLength());

    for (auto& e : elements())
    {
        errCode = writer.writeData(Codes::SpaceLength, e.spaceLength());
        errCode = writer.writeData(Codes::ElementType, e.elementType());

        if (e.elementType()&4)
            errCode = writer.writeData(Codes::ShapeNumber, e.shapeNumber()); 
        else if (e.elementType() & 2)
            errCode = writer.writeData(Codes::ShapeNumber, 0);

        if (e.elementType() > 0)
            errCode = writer.writeData(Codes::PtrToStyle, e.ptrToStyle(), 16);

        if (e.scale() != 0 && e.scale() != 1)
            errCode = writer.writeData(Codes::Scale, e.scale());

        if (e.elementType() > 1)
            errCode = writer.writeData(Codes::Rotation, e.rotation());

        if (e.elementType() & 2)
            errCode = writer.writeData(Codes::Text, e.text());
    }

    return errCode;
}
