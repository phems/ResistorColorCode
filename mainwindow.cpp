#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->radioFour->setChecked(true);

    // arrays voor de lijst bij QComboBoxes
    QString digitColors[] = {"Black", "Brown", "Red", "Orange", "Yellow", "Green", "Blue", "Violet", "Gray", "White"};
    int digitValues[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    QString multiplierColors[] = {"Black", "Brown", "Red", "Orange", "Yellow", "Green", "Blue", "Violet", "Gray", "White", "Gold", "Silver"};
    double multiplierValues[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 0.1, 0.01};

    QString toleranceColors[] = {"Brown", "Red", "Green", "Blue", "Violet", "Gray", "Gold", "Silver"};
    double toleranceValues[] = {1.0, 2.0, 0.5, 0.25, 0.1, 0.05, 5.0, 10.0};

    for (int i = 0; i<10; i++)
    {
        ui->comboDig_1->addItem(digitColors[i], QVariant(digitValues[i]));
        ui->comboDig_2->addItem(digitColors[i], QVariant(digitValues[i]));
        ui->comboDig_3->addItem(digitColors[i], QVariant(digitValues[i]));
    }

    for (int i = 0; i < 12; i++)
    {
        ui->comboMultiplier->addItem(multiplierColors[i], QVariant(multiplierValues[i]));
    }

    for (int i = 0; i < 8; i++)
    {
        ui->comboTolerance->addItem(toleranceColors[i], QVariant(toleranceValues[i]));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
