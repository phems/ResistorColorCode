#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , resistorCalculator(new ResistorCalculator(this))
    , historyWidget(new HistoryWidget(this))
    , resistorWidget(new ResistorWidget(this))
{

    ui->setupUi(this);
    ui->radioFour->setChecked(true);
    ui->comboDig_3->hide();
    this->historyManager = HistoryManager();

    // arrays voor de lijst bij QComboBoxes
    QStringList digitColors = ResistorBand::getDigitBandList();
    QStringList multiplierColors = ResistorBand::getMultiplierBandList();
    QStringList toleranceColors = ResistorBand::getToleranceBandList();

    // for loops om de kleuren en waarden in de combo boxes te plaatsen
    for (int i = 0; i < digitColors.size(); i++) {
        ui->comboDig_1->addItem(digitColors[i], QVariant(i));
        ui->comboDig_2->addItem(digitColors[i], QVariant(i));
        ui->comboDig_3->addItem(digitColors[i], QVariant(i));
    }

    for (int i = 0; i < multiplierColors.size(); i++) {
        ui->comboMultiplier->addItem(multiplierColors[i], QVariant(ResistorBand::getMultiplierValueFromInt(i)));
    }

    for (int i = 0; i < toleranceColors.size(); i++) {
        ui->comboTolerance->addItem(toleranceColors[i], QVariant(ResistorBand::getToleranceValueFromInt(i)));
    }

    // Connecting RadioButtons with the resistorCalculator
    connect(ui->radioFour, &QRadioButton::clicked, this, [this](){resistorCalculator->setFiveBand(false);
        ui->comboDig_3->hide();});
    connect(ui->radioFive, &QRadioButton::clicked, this, [this](){resistorCalculator->setFiveBand(true);
        ui->comboDig_3->show();});

    // Connecting ComboBoxes with the resistorCalculator
    connect(ui->comboDig_1, &QComboBox::currentIndexChanged, this, [this](int index){resistorCalculator->setDigit(0, index);});
    connect(ui->comboDig_2, &QComboBox::currentIndexChanged, this, [this](int index){resistorCalculator->setDigit(1, index);});
    connect(ui->comboDig_3, &QComboBox::currentIndexChanged, this, [this](int index){resistorCalculator->setDigit(2, index);});
    connect(ui->comboMultiplier, &QComboBox::currentIndexChanged, this, [this](int index){resistorCalculator->setMultiplier(index);});
    connect(ui->comboTolerance, &QComboBox::currentIndexChanged, this, [this](int index){resistorCalculator->setTolerance(index);});

    connect(resistorCalculator, &ResistorCalculator::resistValueChanged, this, &MainWindow::updateDisplay);

    // Connecting resistorCalculator to resistorWidget
    connect(resistorCalculator, &ResistorCalculator::fiveBandChanged, resistorWidget, ResistorWidget::setFiveBand);
    connect(resistorCalculator, &ResistorCalculator::digitChanged, resistorWidget, ResistorWidget::changeDigitBand);
    connect(resistorCalculator, &ResistorCalculator::multiplierChanged, resistorWidget, ResistorWidget::changeMultiplierBand);
    connect(resistorCalculator, &ResistorCalculator::toleranceChanged, resistorWidget, ResistorWidget::changeToleranceBand);

    resistorWidget->move(240, 160);
    //historyWidget->setGeometry(0, 0, 400, 300);
    historyWidget->hide();
    resistorWidget->show();
    resistorWidget->raise();
    // verander de window titel
    QWidget::setWindowTitle("Color Code Calculator");
}

void MainWindow::radioButtonChange()
{
    bool isFiveRing = ui->radioFive->isChecked();
    this->resistorCalculator->setFiveBand(isFiveRing);
    this->updateDisplay();
}

void MainWindow::comboBoxChange(int indexChange)
{
    qInfo() << QString::number(indexChange);
    // this->resistorCalculator.setDigit1(ui->comboDig_1->currentData().toInt());
    // this->resistorCalculator.setDigit2(ui->comboDig_2->currentData().toInt());
    // this->resistorCalculator.setDigit3(ui->comboDig_2->currentData().toInt());
    // this->resistorCalculator.setMultiplier(ui->comboMultiplier->currentData().toDouble());
    // this->resistorCalculator.setTolerance(ui->comboTolerance->currentData().toDouble());
    this->updateDisplay();
}

void MainWindow::updateDisplay()
{
    qInfo() << "Resistance value:" << this->resistorCalculator->toQString(0);
    //std::cout << "Resistance value: " << this->resistorCalculator.toQString(0).toStdString() << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}
