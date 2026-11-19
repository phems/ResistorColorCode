#ifndef RESISTORCALCULATOR_H
#define RESISTORCALCULATOR_H
#include <iostream>
#include <QString>
#include <QStringList>
#include <array>
#include "resistorband.h"

class ResistorCalculator
{
private:
    bool fiveBand;
    DigitBand digit1;
    DigitBand digit2;
    DigitBand digit3;
    MultiplierBand multiplier;
    ToleranceBand tolerance;
    double resistValue;

    void recalculateResistValue();
    QString getMostCompactForm() const;

public:
    // Constructor
    ResistorCalculator();
    ~ResistorCalculator();

    // Setters
    void setFiveBand(bool fiveBand);
    void setDigit1(DigitBand color);
    void setDigit2(DigitBand color);
    void setDigit3(DigitBand color);
    void setMultiplier(MultiplierBand color);
    void setTolerance(ToleranceBand color);

    // Getters
    DigitBand getDigit1() const;
    DigitBand getDigit2() const;
    DigitBand getDigit3() const;
    MultiplierBand getMultiplier() const;
    ToleranceBand getTolerance() const;

    bool getFiveBand() const;
    double getResistValue() const;

    QString toQString() const;
    QString toQStringMostCompact() const;
    QString toQString(int suffixIndex) const;
};
#endif
