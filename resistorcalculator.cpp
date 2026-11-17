#include "resistorcalculator.h"
#include <cmath>


const QStringList ResistorCalculator::digitColors = {"Black", "Brown", "Red", "Orange", "Yellow", "Green", "Blue", "Violet", "Gray", "White"};
const QStringList ResistorCalculator::multiplierColors = {"Black", "Brown", "Red", "Orange", "Yellow", "Green", "Blue", "Violet", "Gray",
                                    "White", "Gold", "Silver"};
const QStringList ResistorCalculator::toleranceColors = {"Brown", "Red", "Green", "Blue", "Violet", "Gray", "Gold", "Silver"};

const std::array<double, 12> ResistorCalculator::multiplierValues = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 0.1, 0.01};
const std::array<double, 8> ResistorCalculator::toleranceValues = {1.0, 2.0, 0.5, 0.25, 0.1, 0.05, 5.0, 10.0};

const QString defaultQString = "%1 Ohm %2%"; // %1Ω %2%
const std::string suffixes[] = {"", "K", "M", "G"};

ResistorCalculator::ResistorCalculator()
    : fiveBand(false)
    , digit1(0)
    , digit2(0)
    , digit3(0)
    , multiplier(0)
    , tolerance(0.0)
    , resistValue(0.0)
{}

ResistorCalculator::~ResistorCalculator() {}

void ResistorCalculator::setFiveBand(bool fiveB)
{
    fiveBand = fiveB;
    this->recalculateResistValue();
}

void ResistorCalculator::setDigit1(int d1)
{
    digit1 = d1;
    this->recalculateResistValue();
}

void ResistorCalculator::setDigit2(int d2)
{
    digit2 = d2;
    this->recalculateResistValue();
}

void ResistorCalculator::setDigit3(int d3)
{
    digit3 = d3;
    this->recalculateResistValue();
}

void ResistorCalculator::setMultiplier(double m)
{
    multiplier = m;
    this->recalculateResistValue();
}

void ResistorCalculator::setTolerance(double t)
{
    tolerance = t;
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
    if (fiveBand) {
        resistValue = (digit1 * 100 + digit2 * 10 + digit3) * multiplier;
    } else {
        resistValue = (digit1 * 10 + digit2) * multiplier;
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

double ResistorCalculator::getTolerance() const
{
    return tolerance;
}

const QStringList& ResistorCalculator::getDigitColors()
{
    return ResistorCalculator::digitColors;
}

const QStringList& ResistorCalculator::getMultiplierColors()
{
    return ResistorCalculator::multiplierColors;
}

const QStringList& ResistorCalculator::getToleranceColors()
{
    return ResistorCalculator::toleranceColors;
}

const std::array<double, 12>& ResistorCalculator::getMultiplierValues()
{
    return ResistorCalculator::multiplierValues;
}

const std::array<double, 8>& ResistorCalculator::getToleranceValues()
{
    return ResistorCalculator::toleranceValues;
}

QString ResistorCalculator::toQString() const
{
    return QString(defaultQString).arg(this->resistValue).arg(this->tolerance);
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
    return QString(defaultQString).arg(result).arg(this->tolerance);
}

QString ResistorCalculator::toQStringMostCompact() const
{
    return QString(defaultQString).arg(this->getMostCompactForm()).arg(this->tolerance);
}