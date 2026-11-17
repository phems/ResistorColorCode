#ifndef CALC_H
#define CALC_H

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

    // Calculating + getters
    double calculateResistValue();
    bool getFiveBand() const;
    double getResistValue() const;
    double getTolerance() const;
};
#endif