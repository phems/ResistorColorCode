#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "calc.h"

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


    // for loops om de kleuren en waarden in de combo boxes te plaatsen
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

    // Sturen signals om de calculateValue function te roepen wanneer radio buttons worden gedrukt
    connect(ui->radioFour, &QRadioButton::clicked, this, &MainWindow::calculateValue);
    connect(ui->radioFive, &QRadioButton::clicked, this, &MainWindow::calculateValue);

    // Sturen signals om de calculateValue function te roepen wanneer combo box inhoud verandert
    connect(ui->comboDig_1, &QComboBox::currentTextChanged, this, &MainWindow::calculateValue);
    connect(ui->comboDig_2, &QComboBox::currentTextChanged, this, &MainWindow::calculateValue);
    connect(ui->comboDig_3, &QComboBox::currentTextChanged, this, &MainWindow::calculateValue);
    connect(ui->comboMultiplier, &QComboBox::currentTextChanged, this, &MainWindow::calculateValue);
    connect(ui->comboTolerance, &QComboBox::currentTextChanged, this, &MainWindow::calculateValue);

    // calculateValue function bij het opstarten
    calculateValue();
}

void MainWindow::calculateValue() // Hier wordt de logica voor het berekenen geplaatst
{
    Calc resistorCalculator; // creeer object om de waarden te plaatsen en om berekeningen uit te voeren

    // boolean die checkt als het een 5 ring resistor is
    bool  isFiveRing = ui->radioFive->isChecked();
    resistorCalculator.setFiveBand(isFiveRing);

    ui->comboDig_3->setVisible(isFiveRing); // de derde digit wijst alleen als wij 5 ring resistor kiezen

    // setter wordt gebruikt om kleur code waarden van de combo boxes te plaatsen
    resistorCalculator.setDigit1(ui->comboDig_1->currentData().toInt());
    resistorCalculator.setDigit2(ui->comboDig_2->currentData().toInt());

    if (isFiveRing)
    {
        resistorCalculator.setDigit3(ui->comboDig_3->currentData().toInt());
    }

    resistorCalculator.setMultiplier(ui->comboMultiplier->currentData().toInt());
    resistorCalculator.setTolerance(ui->comboTolerance->currentData().toInt());

    resistorCalculator.calculateResistValue(); // waarden zijn geset dus weerstand waarde can worden berekend.

    // waarden worden geplaatst buiten het object
    double resistorValue = resistorCalculator.getResistValue();
    double toleranceValue = resistorCalculator.getTolerance();

    // Resultaat wordt weergegeven
    QString result = ("Resistance value: " + QString::number(resistorValue) + "Ω " + QString::number(toleranceValue) + "%");

    ui->label->setText(result);
};

MainWindow::~MainWindow()
{
    delete ui;
}
