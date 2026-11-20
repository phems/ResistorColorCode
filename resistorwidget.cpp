#include "resistorwidget.h"
#include "ui_resistorwidget.h"

const int transitionDuration = 250;
const QString bandQStyleArgs = "background: %1; border-radius: 2px;";

const std::array<int, 4> ResistorWidget::bandxPositionsFourBand = {70, 140, 210, 305};
const std::array<int, 5> ResistorWidget::bandxPositionsFiveBand = {70, 120, 170, 255, 305};

ResistorWidget::ResistorWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ResistorWidget)
    , fiveBand(false)
{
    ui->setupUi(this);

    ui->body->setStyleSheet(QString(bandQStyleArgs).arg("#D1B894"));

    // initializing the appearing/disappearing effect of the third digitband
    band3OpacityEffect = new QGraphicsOpacityEffect(ui->band_3);
    band3OpacityEffect->setOpacity(1.0);
    ui->band_3->setGraphicsEffect(band3OpacityEffect);

    // initializing positions
    ui->band_1->move(bandxPositionsFourBand[0], 0);
    ui->band_2->move(bandxPositionsFourBand[1], 0);
    ui->band_3->hide();
    ui->band_4->move(bandxPositionsFourBand[2], 0);
    ui->band_5->move(bandxPositionsFourBand[3], 0);

    // initializing colors
    QString cssDigit = getCssColor(DigitBand::Black);
    QString cssMultiplier = getCssColor(MultiplierBand::Black);
    QString cssTolerance = getCssColor(MultiplierBand::Brown);
    ui->band_1->setStyleSheet(QString(bandQStyleArgs).arg(cssDigit));
    ui->band_2->setStyleSheet(QString(bandQStyleArgs).arg(cssDigit));
    ui->band_3->setStyleSheet(QString(bandQStyleArgs).arg(cssDigit));
    ui->band_4->setStyleSheet(QString(bandQStyleArgs).arg(cssMultiplier));
    ui->band_5->setStyleSheet(QString(bandQStyleArgs).arg(cssTolerance));

}



ResistorWidget::~ResistorWidget()
{
    delete ui;
}

void ResistorWidget::setFiveBand(bool value)
{

    if(value == fiveBand){
        qInfo() << "Doing nothing, because the fiveband value hasn't changed";
        return;
    }

    fiveBand = value;

    if(value)   transitionToFiveBand();
    else        transitionToFourBand();

}

void ResistorWidget::changeDigitBand(int index, DigitBand newColor, DigitBand oldColor)
{
    if(!isValidIndex(index))
    {
        qInfo() << "Invalid index";
        return;
    }

    QLabel *bandToChange = nullptr;

    switch(index)
    {
        case 0: bandToChange = ui->band_1; break;
        case 1: bandToChange = ui->band_2; break;
        case 2: bandToChange = ui->band_3; break;
        default: bandToChange = nullptr; return;
    }

    bool up = static_cast<int>(newColor) > static_cast<int>(oldColor);
    QString cssColor = getCssColor(newColor);
    if (bandToChange) swapBandEffect(bandToChange, cssColor, up);
}

void ResistorWidget::changeMultiplierBand(MultiplierBand newColor, MultiplierBand oldColor)
{
    bool up = static_cast<int>(newColor) > static_cast<int>(oldColor);
    QString cssColor = getCssColor(newColor);
    swapBandEffect(ui->band_4, cssColor, up);
}

void ResistorWidget::changeToleranceBand(ToleranceBand newColor, ToleranceBand oldColor)
{
    bool up = static_cast<int>(newColor) > static_cast<int>(oldColor);
    QString cssColor = getCssColor(newColor);
    swapBandEffect(ui->band_5, cssColor, up);
}

void ResistorWidget::transitionToFourBand()
{
    // Make band 3 disappear and turn show off
    // Move band 2 and 4 to new positions

    QPropertyAnimation *band3FadeOut = new QPropertyAnimation(band3OpacityEffect, "opacity", this);
    band3FadeOut->setDuration(transitionDuration);
    band3FadeOut->setStartValue(1.0);
    band3FadeOut->setEndValue(0.0);

    connect(band3FadeOut, QPropertyAnimation::finished, ui->band_3, &QLabel::hide);

    band3FadeOut->start(QAbstractAnimation::DeleteWhenStopped);
    moveBandToPosition(ui->band_2, QPoint(bandxPositionsFiveBand[1], 0), QPoint(bandxPositionsFourBand[1], 0), transitionDuration);
    moveBandToPosition(ui->band_4, QPoint(bandxPositionsFiveBand[3], 0), QPoint(bandxPositionsFourBand[2], 0), transitionDuration);
}

void ResistorWidget::transitionToFiveBand()
{
    // Move band 2 and 4 to new positions
    // Show band 3 and turn opacity down
    ui->band_3->show();
    QPropertyAnimation *band3FadeIn = new QPropertyAnimation(band3OpacityEffect, "opacity", this);
    band3FadeIn->setDuration(transitionDuration);
    band3FadeIn->setStartValue(0.0);
    band3FadeIn->setEndValue(1.0);

    band3FadeIn->start(QAbstractAnimation::DeleteWhenStopped);
    moveBandToPosition(ui->band_2, QPoint(bandxPositionsFourBand[1], 0), QPoint(bandxPositionsFiveBand[1], 0), transitionDuration);
    moveBandToPosition(ui->band_4, QPoint(bandxPositionsFourBand[2], 0), QPoint(bandxPositionsFiveBand[3], 0), transitionDuration);
}

bool ResistorWidget::isValidIndex(int bandIndex)
{
    if (fiveBand) return bandIndex >= 0 && bandIndex < 3;
    else return bandIndex >= 0 && bandIndex < 2;
}

QString ResistorWidget::getCssColor(DigitBand band)
{
    switch (band) {
        case DigitBand::Black:  return "#141414";
        case DigitBand::Brown:  return "#8B4513";
        case DigitBand::Red:    return "#DC143C";
        case DigitBand::Orange: return "#FF8C00";
        case DigitBand::Yellow: return "#FFD700";
        case DigitBand::Green:  return "#228B22";
        case DigitBand::Blue:   return "#1E90FF";
        case DigitBand::Violet: return "#8A2BE2";
        case DigitBand::Gray:   return "#808080";
        case DigitBand::White:  return "#F5F5F5";
        default:                return "transparent";
    }
}

QString ResistorWidget::getCssColor(MultiplierBand band)
{
    switch (band) {
            case MultiplierBand::Black:  return "#141414";
            case MultiplierBand::Brown:  return "#8B4513";
            case MultiplierBand::Red:    return "#DC143C";
            case MultiplierBand::Orange: return "#FF8C00";
            case MultiplierBand::Yellow: return "#FFD700";
            case MultiplierBand::Green:  return "#228B22";
            case MultiplierBand::Blue:   return "#1E90FF";
            case MultiplierBand::Violet: return "#8A2BE2";
            case MultiplierBand::Gray:   return "#808080";
            case MultiplierBand::White:  return "#F5F5F5";
            case MultiplierBand::Gold:   return "#D4AF37";
            case MultiplierBand::Silver: return "#C0C0C0";
            default:                     return "transparent";
    }
}

QString ResistorWidget::getCssColor(ToleranceBand band)
{
    switch (band) {
        case ToleranceBand::Brown:  return "#8B4513";
        case ToleranceBand::Red:    return "#DC143C";
        case ToleranceBand::Green:  return "#228B22";
        case ToleranceBand::Blue:   return "#1E90FF";
        case ToleranceBand::Violet: return "#8A2BE2";
        case ToleranceBand::Gray:   return "#808080";
        case ToleranceBand::Gold:   return "#D4AF37";
        case ToleranceBand::Silver: return "#C0C0C0";
        default:                    return "transparent";
    }
}

void ResistorWidget::moveBandToPosition(QLabel *band, const QPoint &start, const QPoint &end, const int &duration, std::function<void ()> callback)
{
    QPropertyAnimation *bandMove = new QPropertyAnimation(band, "pos", this);
    bandMove->setDuration(duration);
    bandMove->setStartValue(start);
    bandMove->setEndValue(end);

    connect(bandMove, QPropertyAnimation::finished, this, [callback]() {
        if (callback) callback();
    });

    bandMove->start(QAbstractAnimation::DeleteWhenStopped);
}

void ResistorWidget::swapBandEffect(QLabel *band, const QString &cssColor, bool up)
{
    QLabel *dummyLabel = new QLabel(this);
    dummyLabel->setText("");
    dummyLabel->setGeometry(band->geometry());
    dummyLabel->setStyleSheet(QString(bandQStyleArgs).arg(cssColor));
    dummyLabel->show();

    QPoint bandPosition = band->pos();

    int height = band->geometry().height();
    int yStartingPosition = up ? bandPosition.y() + height : bandPosition.y() - height;

    QPoint startPos = QPoint(bandPosition.x(), yStartingPosition);
    QPoint endPos = QPoint(bandPosition.x(), bandPosition.y());
    dummyLabel->move(startPos);

    moveBandToPosition(dummyLabel, startPos, endPos, 100, [this, band, dummyLabel, cssColor](){
        band->setStyleSheet(QString(bandQStyleArgs).arg(cssColor));
        dummyLabel->deleteLater();
    });
}





