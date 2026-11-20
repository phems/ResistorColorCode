#ifndef RESISTORWIDGET_H
#define RESISTORWIDGET_H

#include <QWidget>
#include <functional>
#include <QDebug>
#include <QString>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPoint>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <array>
#include "resistorband.h"

namespace Ui {
class ResistorWidget;
}

class ResistorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResistorWidget(QWidget *parent = nullptr);
    ~ResistorWidget();

public slots:
    void setFiveBand(bool value);
    void changeDigitBand(int index, DigitBand newColor, DigitBand oldColor);
    void changeMultiplierBand(MultiplierBand newColor, MultiplierBand oldColor);
    void changeToleranceBand(ToleranceBand newColor, ToleranceBand oldColor);

private:
    bool fiveBand;
    QGraphicsOpacityEffect *band3OpacityEffect;
    Ui::ResistorWidget *ui;
    bool isValidIndex(int bandIndex);

    // Default values
    static const std::array<int, 4> bandxPositionsFourBand;
    static const std::array<int, 5> bandxPositionsFiveBand;

    // Css color getters
    QString getCssColor(DigitBand band);
    QString getCssColor(MultiplierBand band);
    QString getCssColor(ToleranceBand band);

    // Animation helpers
    void transitionToFourBand();
    void transitionToFiveBand();
    void moveBandToPosition(QLabel *band, const QPoint &start, const QPoint &end, const int &duration, std::function<void()> callback= nullptr);
    void swapBandEffect(QLabel *band, const QString &cssColor, bool up); // Up being the direction of the swap tween
};

#endif // RESISTORWIDGET_H
