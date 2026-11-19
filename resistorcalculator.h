#ifndef RESISTORCALCULATOR_H
#define RESISTORCALCULATOR_H
#include <QObject>
#include <QDebug>
#include <iostream>
#include <QString>
#include <QStringList>
#include <array>
#include "resistorband.h"

class ResistorCalculator : public QObject
{

Q_OBJECT

private:
    static const int maxDigitBands;
    bool fiveBand;
    std::array<DigitBand, 3> digitBands;
    MultiplierBand multiplier;
    ToleranceBand tolerance;
    double resistValue;

    void recalculateResistValue();
    QString getMostCompactForm() const;
    bool isValidDigitIndex(int digitIndex);

public:
    // Constructor
    explicit ResistorCalculator(QObject *parent = nullptr);
    ~ResistorCalculator();

    // Getters
    DigitBand getDigitBandOf(int digitIndex) const;
    MultiplierBand getMultiplier() const;
    ToleranceBand getTolerance() const;

    bool getFiveBand() const;
    double getResistValue() const;

    QString toQString() const;
    QString toQStringMostCompact() const;
    QString toQString(int suffixIndex) const;

    signals:
    void resistValueChanged(double newValue, double oldValue);
    void digitChanged(int index, DigitBand newValue, DigitBand oldValue);
    void multiplierChanged(MultiplierBand newValue, MultiplierBand oldValue);
    void toleranceChanged(ToleranceBand newValue, ToleranceBand oldValue);

    public slots:
    // Setters
    void setFiveBand(bool fiveBand);
    void setDigit(int digitIndex, DigitBand color);
    void setDigit(int digitIndex, int bandIndex);
    void setMultiplier(MultiplierBand color);
    void setMultiplier(int bandIndex);
    void setTolerance(ToleranceBand color);
    void setTolerance(int bandIndex);
};
#endif
