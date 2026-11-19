#ifndef RESISTORBAND_H
#define RESISTORBAND_H

#include <QStringList>
#include <QString>

enum class DigitBand {
    Black,
    Brown,
    Red,
    Orange,
    Yellow,
    Green,
    Blue,
    Violet,
    Gray,
    White,
    _Count,
    Illegal
};

enum class MultiplierBand {
    Black,
    Brown,
    Red,
    Orange,
    Yellow,
    Green,
    Blue,
    Violet,
    Gray,
    White,
    Gold,
    Silver,
    _Count,
    Illegal
};

enum class ToleranceBand {
    Brown,
    Red,
    Green,
    Blue,
    Violet,
    Gray,
    Gold,
    Silver,
    _Count,
    Illegal
};

class ResistorBand
{

private:

    template <typename EnumType>
    static EnumType getBandFromInt(int bandIndex);

    template <typename EnumType, typename Value>
    static Value getValueFromInt(int bandIndex, EnumType (*intToColorFunction)(int), Value (*colorToValueFunction)(EnumType));


    template <typename EnumType>
    static QStringList getBandList(QString (*colorToStringFunction)(EnumType));

    template <typename EnumType>
    static EnumType getBandFromQString(QString string, QStringList& colorList);

    template <typename EnumType, typename Value>
    static Value getValueFromQString(QString string, QStringList& colorList, Value (*colorToValueFunction)(EnumType));

public:
    // All the digit band functions
    static int getDigitValue(DigitBand color);
    static int getDigitValueFromInt(int bandIndex);

    static DigitBand getDigitBandFromInt(int bandIndex);

    static QString getDigitBand(DigitBand color);
    static const QStringList getDigitBandList();


    // All the multiplier band functions
    static double getMultiplierValue(MultiplierBand color);
    static double getMultiplierValueFromInt(int bandIndex);

    static MultiplierBand getMultiplierBandFromInt(int bandIndex);

    static QString getMultiplierBand(MultiplierBand color);
    static const QStringList getMultiplierBandList();

    // All the tolerance band functions
    static double getToleranceValue(ToleranceBand color);
    static double getToleranceValueFromInt(int bandIndex);

    static ToleranceBand getToleranceBandFromInt(int bandIndex);

    static QString getToleranceBand(ToleranceBand color);
    static const QStringList getToleranceBandList();


};

#endif // RESISTORBAND_H
