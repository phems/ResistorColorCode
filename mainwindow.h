#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "resistorcalculator.h"
#include "historymanager.h"
#include "historywidget.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void calculateValue(); // function die called wordt wanneer een kleur wordt verandert en er 4 of 5 ringen wordt gekozen
    void radioButtonChange();
    void comboBoxChange();

private:
    void updateDisplay();
    ResistorCalculator resistorCalculator;
    HistoryManager historyManager;
    HistoryWidget *historyWidget;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
