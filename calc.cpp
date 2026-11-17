#include "calc.h"
#include <cmath>

const QString defaultQString = "%1 Ohm %2%"; // %1Ω %2%
const std::string suffixes[] = {"", "K", "M", "G"};

Calc::Calc()
    : fiveBand(false)
    , digit1(0)
    , digit2(0)
    , digit3(0)
    , multiplier(0)
    , tolerance(0.0)
    , resistValue(0.0)
{}

Calc::~Calc() {}

void Calc::setFiveBand(bool fiveB)
{
    fiveBand = fiveB;
    this->recalculateResistValue();
}

void Calc::setDigit1(int d1)
{
    digit1 = d1;
    this->recalculateResistValue();
}

void Calc::setDigit2(int d2)
{
    digit2 = d2;
    this->recalculateResistValue();
}

void Calc::setDigit3(int d3)
{
    digit3 = d3;
    this->recalculateResistValue();
}

void Calc::setMultiplier(double m)
{
    multiplier = m;
    this->recalculateResistValue();
}

void Calc::setTolerance(double t)
{
    tolerance = t;
}

QString Calc::getMostCompactForm() const
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

void Calc::recalculateResistValue()
{
    if (fiveBand) {
        resistValue = (digit1 * 100 + digit2 * 10 + digit3) * multiplier;
    } else {
        resistValue = (digit1 * 10 + digit2) * multiplier;
    }
}

bool Calc::getFiveBand() const
{
    return fiveBand;
}
double Calc::getResistValue() const
{
    return resistValue;
}

double Calc::getTolerance() const
{
    return tolerance;
}

QString Calc::toQString() const
{
    return QString(defaultQString).arg(this->resistValue).arg(this->tolerance);
}

QString Calc::toQString(int suffixIndex) const
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

QString Calc::toQStringMostCompact() const
{
    return QString(defaultQString).arg(this->getMostCompactForm()).arg(this->tolerance);
}