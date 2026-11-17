#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QDateTime>
#include <QString>
#include <vector>
#include "resistorcalculator.h"

struct resistorInfo {
    bool fiveBand;
    int digit1;
    int digit2;
    int digit3;
    double multiplier;
    double tolerance;
};

struct HistoryItem {
    resistorInfo info;
    QDateTime timeOfChange;
};

class HistoryManager
{

private:
    std::vector<HistoryItem> historyVector;

public:
    HistoryManager();
    ~HistoryManager();

    void addRecord(ResistorCalculator &info);
    void printAll();
};

#endif // HISTORYMANAGER_H
