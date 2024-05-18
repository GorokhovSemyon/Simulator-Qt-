#ifndef ALTITUDE_H
#define ALTITUDE_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include "common/exchange_structures.h"

#define MAX_ATLITUDE 100
#define STEP 20

namespace Ui {
class Altitude;
}

class Altitude : public QWidget
{
    Q_OBJECT

public:
    explicit Altitude(Exchange_structures *_exch_str, QWidget *parent = nullptr);
    ~Altitude();

    void paintEvent(QPaintEvent *);

    Exchange_structures* exch_str;

private:
    Ui::Altitude *ui;

    QPoint mark_altitude[4] = {
        QPoint (0, 0),
        QPoint (15, 5),
        QPoint (15, -5),
        QPoint (0, 0)
    };

public slots:
    void setAltitude(int _altitude);


};

#endif // ALTITUDE_H
