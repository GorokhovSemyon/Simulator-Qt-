#ifndef HYROHORIZONT_H
#define HYROHORIZONT_H

#include <QWidget>
#include <QPaintDevice>
#include <QPaintEngine>
#include <QtMath>
#include "common/exchange_structures.h"

#define STEP 20

namespace Ui {
class HyroHorizont;
}

class HyroHorizont : public QWidget
{
    Q_OBJECT

public:
    explicit HyroHorizont(Exchange_structures *_exch_str, QWidget *parent = nullptr);
    ~HyroHorizont();

    void paintEvent(QPaintEvent *);
    void setPitch(int _pitch);

    Exchange_structures* exch_str;

private:
    Ui::HyroHorizont *ui;

    QColor Hblue;
    QColor Hgreen;

    QPoint mark_pitch[5] = {
        QPoint (-10, 0),
        QPoint (-5, 5),
        QPoint (0, 7),
        QPoint (5, 5),
        QPoint (10, 0),
    };
};

#endif // HYROHORIZONT_H
