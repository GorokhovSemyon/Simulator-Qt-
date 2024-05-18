#ifndef VMA_H
#define VMA_H

#include <QWidget>
#include <QPaintDevice>
#include <QPaintEngine>
#include "common/exchange_structures.h"

#define U_MAX 10

namespace Ui {
class VMA;
}

class VMA : public QWidget
{
    Q_OBJECT

public:
    explicit VMA(Exchange_structures *_exch_str, QWidget *parent = nullptr);
    ~VMA();

    void paintEvent(QPaintEvent *);

    Exchange_structures* exch_str;

    struct vint {
        bool dir;	// направление вращения (true - вниз, false - вверх)
        QString state;	// состояние ВМА (fail - off - operate)
        int power;  // текущая мощность - %

        QPoint center;	// центр объекта
        int size; // радиус - для вертикальных ВМА, высота - для маршевых ВМА, ширина для лаговых
        int distance; //Для вертикального движителя показывает от центра расстояние, где будут рисоваться треугольники

        QPoint powerOffsetDirect;    // где писать мощность - для прямого вращения
        QString text;   // название ВМА - для вывода на экран
        QPoint textOffset;   // где писать этот самый текст
    };

    struct Rov_vma
    {
        Rov_vma()
        {
            vma_crossUp.center = QPoint(0,-50);
            vma_crossUp.size = 25;
            vma_crossUp.distance = 0;
            vma_crossUp.dir = true;
            vma_crossUp.state = "operate";
            vma_crossUp.power = 0;
            vma_crossUp.powerOffsetDirect = QPoint(-5,40);
            vma_crossUp.text = "ВМА 1";
            vma_crossUp.textOffset = QPoint(-15,-30);

            vma_crossDown.center = QPoint(0,50);
            vma_crossDown.size = 25;
            vma_crossDown.distance = 0;
            vma_crossDown.dir = true;
            vma_crossDown.state = "operate";
            vma_crossDown.power = 0;
            vma_crossDown.powerOffsetDirect = QPoint(-5,40);
            vma_crossDown.text = "ВМА 2";
            vma_crossDown.textOffset = QPoint(-15,-30);

            vma_crossLeft.center = QPoint(-50,0);
            vma_crossLeft.size = 25;
            vma_crossLeft.distance = 0;
            vma_crossLeft.dir = false;
            vma_crossLeft.state = "operate";
            vma_crossLeft.power = 0;
            vma_crossLeft.powerOffsetDirect = QPoint(-15,40);
            vma_crossLeft.text = "ВМА 3";
            vma_crossLeft.textOffset = QPoint(-25,-30);

            vma_crossRight.center = QPoint(50,0);
            vma_crossRight.size = 25;
            vma_crossRight.distance = 0;
            vma_crossRight.dir = false;
            vma_crossRight.state = "operate";
            vma_crossRight.power = 0;
            vma_crossRight.powerOffsetDirect = QPoint(0,40);
            vma_crossRight.text = "ВМА 4";
            vma_crossRight.textOffset = QPoint(0,-30);

            vma_depth.center = QPoint(0,0);
            vma_depth.size = 25;
            vma_depth.distance = 100;
            vma_depth.dir = false;
            vma_depth.state = "operate";
            vma_depth.power = 0;
            vma_depth.powerOffsetDirect = QPoint(-55,0);
            vma_depth.text = "ВМА 5";
            vma_depth.textOffset = QPoint(30,0);
        }

        vint vma_crossUp;
        vint vma_crossDown;
        vint vma_crossLeft;
        vint vma_crossRight;
        vint vma_depth;

    } rovVMA;

private:
    Ui::VMA *ui;

    QColor myGreen;
    QColor myBlue;
    QColor myRed;
    QColor myRed2;
    QColor myGreenFill;
    QColor myRedFill;
    QColor myYellow;

    QPoint arrow_SC[6] = {
        QPoint (0, 0),
        QPoint (0, -30),
        QPoint (3, -20),
        QPoint (0, -30),
        QPoint (-3, -20),
        QPoint (0, -30)
    };

    void crossVMA(vint vma, QPainter *vPainter);
    void vertVMA(vint vma, QPainter *vPainter);

    void VMA_Data();

public slots:
    void setU1(int _U1);
    void setU2(int _U2);
    void setU3(int _U3);
    void setU4(int _U4);
    void setU5(int _U5);

    void setFail_U1(bool fail);
    void setFail_U2(bool fail);
    void setFail_U3(bool fail);
    void setFail_U4(bool fail);
    void setFail_U5(bool fail);
};

#endif // VMA_H
