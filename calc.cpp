#include "calc.h"

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
}

void Calc::setDigit1(int d1)
{
    digit1 = d1;
}

void Calc::setDigit2(int d2)
{
    digit2 = d2;
}

void Calc::setDigit3(int d3)
{
    digit3 = d3;
}

void Calc::setMultiplier(double m)
{
    multiplier = m;
}

void Calc::setTolerance(double t)
{
    tolerance = t;
}

double Calc::calculateResistValue()
{
    if (fiveBand) {
        resistValue = (digit1 * 100 + digit2 * 10 + digit3) * multiplier;
    } else {
        resistValue = (digit1 * 10 + digit2) * multiplier;
    }
    return resistValue;
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