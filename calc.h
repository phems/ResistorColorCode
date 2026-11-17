#ifndef CALC_H
#define CALC_H
#include <iostream>
#include <QString>

class Calc
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

public:
    // Constructor
    Calc();
    ~Calc();

    // Setters
    void setFiveBand(bool fiveBand);
    void setDigit1(int digit1);
    void setDigit2(int digit2);
    void setDigit3(int digit3);
    void setMultiplier(double multiplier);
    void setTolerance(double tolerance);

    // Getters
    bool getFiveBand() const;
    double getResistValue() const;
    double getTolerance() const;
    QString toQString() const;
    QString toQStringMostCompact() const;
    QString toQString(int suffixIndex) const;
};
#endif