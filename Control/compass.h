#ifndef COMPASS_H
#define COMPASS_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include "common/exchange_structures.h"

namespace Ui {
class Compass;
}

class Compass : public QWidget
{
    Q_OBJECT

public:
    explicit Compass(Exchange_structures *_exch_str, QWidget *parent = nullptr);
    ~Compass();

    void paintEvent(QPaintEvent *);

    Exchange_structures* exch_str;

private:
    Ui::Compass *ui;

    QPoint arrow_SC[6] = {
        QPoint (0, 0),
        QPoint (0, -30),
        QPoint (3, -20),
        QPoint (0, -30),
        QPoint (-3, -20),
        QPoint (0, -30)
    };

    QPoint arrow_Compass[6] = {
        QPoint (0, 50),
        QPoint (0, -50),
        QPoint (3, -40),
        QPoint (0, -50),
        QPoint (-3,-40),
        QPoint (0, -50)
    };

    QPoint mark_Desirable [4] = {
        QPoint (0, -70),
        QPoint (5, -85),
        QPoint (-5, -85),
        QPoint (0, -70)
    };

    QPoint mark_Carrier [9] = {
        QPoint (-4, -65),
        QPoint (4, -65),
        QPoint (10, -70),
        QPoint (6, -70),
        QPoint (6, -73),
        QPoint (-1, -73),
        QPoint (-1, -69),
        QPoint (-10, -69),
        QPoint (-4, -65)
    };

    QPoint mark_MDS [5] = {
        QPoint (-7, - 65),
        QPoint (7, - 65),
        QPoint (4, -71),
        QPoint (-4, -71),
        QPoint (-7, -65)
    };

public slots:
    void setYawDes(int _yawDes);
    void setYaw(int _yaw);
};

#endif // COMPASS_H
