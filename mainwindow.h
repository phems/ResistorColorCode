#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
