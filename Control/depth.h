#ifndef DEPTH_H
#define DEPTH_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include "common/exchange_structures.h"

#define MAX_ATLITUDE 200
#define STEP 20

namespace Ui {
class Depth;
}

class Depth : public QWidget
{
    Q_OBJECT

public:
    explicit Depth(Exchange_structures *_exch_str, QWidget *parent = nullptr);
    ~Depth();

    void paintEvent(QPaintEvent *);

    Exchange_structures* exch_str;
    float depth;

private:
    Ui::Depth *ui;

    QPoint mark_depth[4] = {
        QPoint (0, 0),
        QPoint (15, 5),
        QPoint (15, -5),
        QPoint (0, 0)
    };

public slots:
    void setDepth();
};

#endif // DEPTH_H
