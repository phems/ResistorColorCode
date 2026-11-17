#ifndef RESISTORCALCULATOR_H
#define RESISTORCALCULATOR_H
#include <iostream>
#include <QString>
#include <QStringList>
#include <array>

class ResistorCalculator
{
private:
    bool fiveBand;
    int digit1;
    int digit2;
    int digit3;
    double multiplier;
    double tolerance;
    double resistValue;

    void recalculateResistValue();
    QString getMostCompactForm() const;

    static const QStringList digitColors;
    static const QStringList multiplierColors;
    static const QStringList toleranceColors;

    static const std::array<double, 12> multiplierValues;
    static const std::array<double, 8> toleranceValues;

public:
    // Constructor
    ResistorCalculator();
    ~ResistorCalculator();

    // Setters
    void setFiveBand(bool fiveBand);
    void setDigit1(int digit1);
    void setDigit2(int digit2);
    void setDigit3(int digit3);
    void setMultiplier(double multiplier);
    void setTolerance(double tolerance);

    // Getters
    int getDigit1() const;
    int getDigit2() const;
    int getDigit3() const;
    double getMultiplier() const;
    double getTolerance() const;
    bool getFiveBand() const;
    double getResistValue() const;

    static const QStringList& getDigitColors();
    static const QStringList& getMultiplierColors();
    static const QStringList& getToleranceColors();

    static const std::array<double, 12>& getMultiplierValues();
    static const std::array<double, 8>& getToleranceValues();

    QString toQString() const;
    QString toQStringMostCompact() const;
    QString toQString(int suffixIndex) const;
};
#endif
