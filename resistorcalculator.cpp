#include "resistorcalculator.h"
#include <cmath>

const int ResistorCalculator::maxDigitBands = 3;
const QString defaultQString = "%1 Ohm %2%"; // %1Ω %2%
const std::string suffixes[] = {"", "K", "M", "G"};

ResistorCalculator::ResistorCalculator(QObject *parent)
    : QObject(parent)
    , fiveBand(false)
    , multiplier(MultiplierBand::Black)
    , tolerance(ToleranceBand::Brown)
{
    digitBands = {DigitBand::Black, DigitBand::Black, DigitBand::Black};
    recalculateResistValue();
}

ResistorCalculator::~ResistorCalculator() {}

void ResistorCalculator::setFiveBand(bool fiveB)
{
    fiveBand = fiveB;
    this->recalculateResistValue();
}

void ResistorCalculator::setDigit(int digitIndex, DigitBand newColor)
{
    if (!isValidDigitIndex(digitIndex))
    {
        qInfo() << "Invalid!" ;
        return;
    }

    DigitBand oldColor = digitBands[digitIndex];
    digitBands[digitIndex] = newColor;
    emit digitChanged(digitIndex, newColor, oldColor);
    this->recalculateResistValue();
}

void ResistorCalculator::setDigit(int digitIndex, int bandIndex)
{

    if (!isValidDigitIndex(digitIndex))
    {
        qInfo() << "Invalid!" ;
        return;
    }

    DigitBand oldColor = digitBands[digitIndex];
    DigitBand newColor = ResistorBand::getDigitBandFromInt(bandIndex);
    digitBands[digitIndex] = newColor;
    emit digitChanged(digitIndex, newColor, oldColor);
    this->recalculateResistValue();
}

void ResistorCalculator::setMultiplier(MultiplierBand newColor)
{
    MultiplierBand oldColor = multiplier;
    multiplier = newColor;
    emit multiplierChanged(newColor, oldColor);
    this->recalculateResistValue();
}

void ResistorCalculator::setMultiplier(int bandIndex)
{
    MultiplierBand oldColor = multiplier;
    MultiplierBand newColor = ResistorBand::getMultiplierBandFromInt(bandIndex);
    multiplier = newColor;
    emit multiplierChanged(newColor, oldColor);
    this->recalculateResistValue();
}

void ResistorCalculator::setTolerance(ToleranceBand newColor)
{
    ToleranceBand oldColor = tolerance;
    tolerance = newColor;
    emit toleranceChanged(newColor, oldColor);
}

void ResistorCalculator::setTolerance(int bandIndex)
{
    ToleranceBand oldColor = tolerance;
    ToleranceBand newColor = ResistorBand::getToleranceBandFromInt(bandIndex);
    tolerance = newColor;
    emit toleranceChanged(newColor, oldColor);
}

QString ResistorCalculator::getMostCompactForm() const
{
    double newValue = resistValue;
    int suffixIndex = 0;
    while (newValue / 1000 >= 1)
    {
        suffixIndex++;
        newValue /= 1000;
    }

    return QString::number(newValue).append(suffixes[suffixIndex]);
}

bool ResistorCalculator::isValidDigitIndex(int digitIndex)
{
    return digitIndex >= 0 && digitIndex < maxDigitBands;
}

void ResistorCalculator::recalculateResistValue()
{

    int digit1Value = ResistorBand::getDigitValue(digitBands[0]);
    int digit2Value = ResistorBand::getDigitValue(digitBands[1]);
    double multiplierValue = ResistorBand::getMultiplierValue(multiplier);
    double oldResistValue = resistValue;

    if (fiveBand) {
        int digit3Value = ResistorBand::getDigitValue(digitBands[2]);
        resistValue = (digit1Value * 100 + digit2Value * 10 + digit3Value) * multiplierValue;
    } else {
        resistValue = (digit1Value * 10 + digit2Value) * multiplierValue;
    }
    emit resistValueChanged(resistValue, oldResistValue);
}

bool ResistorCalculator::getFiveBand() const
{
    return fiveBand;
}
double ResistorCalculator::getResistValue() const
{
    return resistValue;
}

ToleranceBand ResistorCalculator::getTolerance() const
{
    return tolerance;
}

QString ResistorCalculator::toQString() const
{
    return QString(defaultQString).arg(resistValue).arg(ResistorBand::getToleranceValue(tolerance));
}

QString ResistorCalculator::toQString(int suffixIndex) const
{

    if (suffixIndex < 0 || 3 < suffixIndex)
    {
        return QString("Invalid suffix index");
    }

    if (suffixIndex == 0)
    {
        return this->toQString();
    }

    double newValue = resistValue / (std::pow(1000.0, suffixIndex));
    QString result = QString::number(newValue).append(suffixes[suffixIndex]);
    return QString(defaultQString).arg(result).arg(ResistorBand::getToleranceValue(tolerance));
}

QString ResistorCalculator::toQStringMostCompact() const
{
    return QString(defaultQString).arg(getMostCompactForm()).arg(ResistorBand::getToleranceValue(tolerance));
}