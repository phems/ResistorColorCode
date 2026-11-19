#include "resistorband.h"

int ResistorBand::getDigitValue(DigitBand color)
{
    switch (color) {
        case DigitBand::Black:  return 0;
        case DigitBand::Brown:  return 1;
        case DigitBand::Red:    return 2;
        case DigitBand::Orange: return 3;
        case DigitBand::Yellow: return 4;
        case DigitBand::Green:  return 5;
        case DigitBand::Blue:   return 6;
        case DigitBand::Violet: return 7;
        case DigitBand::Gray:   return 8;
        case DigitBand::White:  return 9;
        default:                return -1;
    }
}

int ResistorBand::getDigitValueFromInt(int bandIndex)
{
    return getValueFromInt<DigitBand, int>(bandIndex, &ResistorBand::getDigitBandFromInt, &ResistorBand::getDigitValue);
}

DigitBand ResistorBand::getDigitBandFromInt(int bandIndex)
{
    return getBandFromInt<DigitBand>(bandIndex);
}

QString ResistorBand::getDigitBand(DigitBand color)
{
    switch (color) {
        case DigitBand::Black:  return "Black";
        case DigitBand::Brown:  return "Brown";
        case DigitBand::Red:    return "Red";
        case DigitBand::Orange: return "Orange";
        case DigitBand::Yellow: return "Yellow";
        case DigitBand::Green:  return "Green";
        case DigitBand::Blue:   return "Blue";
        case DigitBand::Violet: return "Violet";
        case DigitBand::Gray:   return "Gray";
        case DigitBand::White:  return "White";
        default:                return "";
    }
}

const QStringList ResistorBand::getDigitBandList()
{
    return getBandList<DigitBand>(&ResistorBand::getDigitBand);
}

double ResistorBand::getMultiplierValue(MultiplierBand color)
{
    switch (color) {
        case MultiplierBand::Black:     return 1.0;
        case MultiplierBand::Brown:     return 1e1;     // 10
        case MultiplierBand::Red:       return 1e2;     // 100
        case MultiplierBand::Orange:    return 1e3;     // 1,000
        case MultiplierBand::Yellow:    return 1e4;     // 10,000
        case MultiplierBand::Green:     return 1e5;     // 100,000
        case MultiplierBand::Blue:      return 1e6;     // 1,000,000
        case MultiplierBand::Violet:    return 1e7;     // 10,000,000
        case MultiplierBand::Gray:      return 1e8;     // 100,000,000
        case MultiplierBand::White:     return 1e9;     // 1,000,000,000
        case MultiplierBand::Gold:      return 1e-1;    // 0.1
        case MultiplierBand::Silver:    return 1e-2;    // 0.01
        default:                        return -1.0;
    }
}

QString ResistorBand::getMultiplierBand(MultiplierBand color)
{
    switch (color) {
        case MultiplierBand::Black:  return "Black";
        case MultiplierBand::Brown:  return "Brown";
        case MultiplierBand::Red:    return "Red";
        case MultiplierBand::Orange: return "Orange";
        case MultiplierBand::Yellow: return "Yellow";
        case MultiplierBand::Green:  return "Green";
        case MultiplierBand::Blue:   return "Blue";
        case MultiplierBand::Violet: return "Violet";
        case MultiplierBand::Gray:   return "Gray";
        case MultiplierBand::White:  return "White";
        case MultiplierBand::Gold:   return "Gold";
        case MultiplierBand::Silver: return "Silver";
        default:                     return "Unknown";
    }
}

MultiplierBand ResistorBand::getMultiplierBandFromInt(int bandIndex)
{
    return getBandFromInt<MultiplierBand>(bandIndex);
}

double ResistorBand::getMultiplierValueFromInt(int bandIndex)
{
    return getValueFromInt<MultiplierBand, double>(bandIndex, &ResistorBand::getMultiplierBandFromInt, &ResistorBand::getMultiplierValue);
}

const QStringList ResistorBand::getMultiplierBandList()
{
    return getBandList<MultiplierBand>(&ResistorBand::getMultiplierBand);
}

double ResistorBand::getToleranceValue(ToleranceBand color)
{
    switch (color) {
        case ToleranceBand::Brown:  return 1.0;
        case ToleranceBand::Red:    return 2.0;
        case ToleranceBand::Green:  return 0.5;
        case ToleranceBand::Blue:   return 0.25;
        case ToleranceBand::Violet: return 0.1;
        case ToleranceBand::Gray:   return 0.05;
        case ToleranceBand::Gold:   return 5.0;
        case ToleranceBand::Silver: return 10.0;
        default:                    return -1.0;
    }
}

double ResistorBand::getToleranceValueFromInt(int bandIndex)
{
    return getValueFromInt<ToleranceBand, double>(bandIndex, &ResistorBand::getToleranceBandFromInt, &ResistorBand::getToleranceValue);
}

ToleranceBand ResistorBand::getToleranceBandFromInt(int bandIndex)
{
    return getBandFromInt<ToleranceBand>(bandIndex);
}

QString ResistorBand::getToleranceBand(ToleranceBand color)
{
    switch (color) {
        case ToleranceBand::Brown:  return "Brown";
        case ToleranceBand::Red:    return "Red";
        case ToleranceBand::Green:  return "Green";
        case ToleranceBand::Blue:   return "Blue";
        case ToleranceBand::Violet: return "Violet";
        case ToleranceBand::Gray:   return "Gray";
        case ToleranceBand::Gold:   return "Gold";
        case ToleranceBand::Silver: return "Silver";
        default:                    return "Unknown";
    }
}

const QStringList ResistorBand::getToleranceBandList()
{
    return getBandList<ToleranceBand>(&ResistorBand::getToleranceBand);
}

template<typename EnumType>
EnumType ResistorBand::getBandFromInt(int bandIndex)
{
    if (bandIndex < 0 || bandIndex >= static_cast<int>(EnumType::_Count))
    {
        return EnumType::Illegal;
    }

    return static_cast<EnumType>(bandIndex);
}

template<typename EnumType>
QStringList ResistorBand::getBandList(QString (*colorToStringFunction)(EnumType))
{
    QStringList list;

    for(int i = 0; i < static_cast<int>(EnumType::_Count); i++)
    {
        EnumType band = static_cast<EnumType>(i);
        list.append(colorToStringFunction(band));
    }

    return list;
}

template<typename EnumType>
EnumType ResistorBand::getBandFromQString(QString string, QStringList &colorList)
{
    int bandIndex = colorList.indexOf(string, Qt::CaseInsensitive);
    return getBandFromInt<EnumType>(bandIndex);
}


template<typename EnumType, typename Value>
Value ResistorBand::getValueFromInt(int bandIndex, EnumType (*intToColorFunction)(int), Value (*colorToValueFunction)(EnumType))
{
    EnumType band = intToColorFunction(bandIndex);
    return colorToValueFunction(band);
}

template<typename EnumType, typename Value>
Value ResistorBand::getValueFromQString(QString string, QStringList &colorList, Value (*colorToValueFunction)(EnumType))
{
    EnumType band = getBandFromQString<EnumType>(string, colorList);
    return colorToValueFunction(band);
}
