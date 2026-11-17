#include "historymanager.h"

HistoryManager::HistoryManager()
{

}

void HistoryManager::addRecord(ResistorCalculator &info)
{
    resistorInfo newRecord;
    newRecord.fiveBand = info.getFiveBand();
}

HistoryManager::~HistoryManager()
{

}