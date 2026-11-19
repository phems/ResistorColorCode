#include "resistorcalculator.h"
#include <cmath>

const QString defaultQString = "%1 Ohm %2%"; // %1Ω %2%
const std::string suffixes[] = {"", "K", "M", "G"};

ResistorCalculator::ResistorCalculator()
    : fiveBand(false)
    , digit1(DigitBand::Black)
    , digit2(DigitBand::Black)
    , digit3(DigitBand::Black)
    , multiplier(MultiplierBand::Black)
    , tolerance(ToleranceBand::Brown)
{
    recalculateResistValue();
}

ResistorCalculator::~ResistorCalculator() {}

void ResistorCalculator::setFiveBand(bool fiveB)
{
    fiveBand = fiveB;
    this->recalculateResistValue();
}

void ResistorCalculator::setDigit1(DigitBand newColor)
{
    digit1 = newColor;
    this->recalculateResistValue();
}

void ResistorCalculator::setDigit2(DigitBand newColor)
{
    digit2 = newColor;
    this->recalculateResistValue();
}

void ResistorCalculator::setDigit3(DigitBand newColor)
{
    digit3 = newColor;
    this->recalculateResistValue();
}

void ResistorCalculator::setMultiplier(MultiplierBand newColor)
{
    multiplier = newColor;
    this->recalculateResistValue();
}

void ResistorCalculator::setTolerance(ToleranceBand newColor)
{
    tolerance = newColor;
}

QString ResistorCalculator::getMostCompactForm() const
{
    double newValue = this->resistValue;
    int suffixIndex = 0;
    while (newValue / 1000 >= 1)
    {
        suffixIndex++;
        newValue /= 1000;
    }

    return QString::number(newValue).append(suffixes[suffixIndex]);
}

void ResistorCalculator::recalculateResistValue()
{

    int digit1Value = ResistorBand::getDigitValue(digit1);
    int digit2Value = ResistorBand::getDigitValue(digit2);
    double multiplierValue = ResistorBand::getMultiplierValue(multiplier);

    if (fiveBand) {
        int digit3Value = ResistorBand::getDigitValue(digit3);
        resistValue = (digit1Value * 100 + digit2Value * 10 + digit3Value) * multiplierValue;
    } else {
        resistValue = (digit1Value * 10 + digit2Value) * multiplierValue;
    }
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
    return QString(defaultQString).arg(this->resistValue).arg(ResistorBand::getToleranceValue(tolerance));
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

    double newValue = this->resistValue / (std::pow(1000.0, suffixIndex));
    QString result = QString::number(newValue).append(suffixes[suffixIndex]);
    return QString(defaultQString).arg(result).arg(ResistorBand::getToleranceValue(tolerance));
}

QString ResistorCalculator::toQStringMostCompact() const
{
    return QString(defaultQString).arg(this->getMostCompactForm()).arg(ResistorBand::getToleranceValue(tolerance));
}