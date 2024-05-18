#include "vma.h"
#include "ui_vma.h"

VMA::VMA(Exchange_structures *_exch_str, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VMA)
{
    ui->setupUi(this);

    exch_str = _exch_str;

    myGreen = QColor(0, 204, 102);
    myBlue = QColor(0, 102, 204);
    myRed = QColor(255, 102, 102);
    myRed2 = QColor(255, 51, 51);
    myGreenFill = QColor(0, 204, 0);
    myRedFill = QColor(204, 0, 0);
    myYellow = QColor(250, 220, 19);
}

VMA::~VMA()
{
    delete ui;
}

///--------------------------------------------------
///Отрисовка компаса
///--------------------------------------------------

void VMA::paintEvent(QPaintEvent *)
{
    VMA_Data();

    QPainter painter(this);

    QFont font;

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.translate(width() / 2, height() / 2 );

    int side = qMin(width(), height());
    painter.scale(side / 160.0, side / 160.0);

//--------------------------------------------------
//Отрисовка контура аппарата
//--------------------------------------------------

    painter.save();
    painter.drawEllipse(-40,-40, 80, 80);
    painter.restore();

//--------------------------------------------------
//Отображение движителей
//--------------------------------------------------

    painter.save();
    painter.scale(0.8, 0.8);

    crossVMA(rovVMA.vma_crossDown, &painter);
    crossVMA(rovVMA.vma_crossLeft, &painter);
    crossVMA(rovVMA.vma_crossRight, &painter);
    crossVMA(rovVMA.vma_crossUp, &painter);

    vertVMA(rovVMA.vma_depth, &painter);

    painter.restore();
}

///--------------------------------------------------
///Отображение вертикального движителя
///--------------------------------------------------

void VMA::crossVMA(vint vma, QPainter *vPainter)
{
    QString percent_str = QString::number(vma.power) + "%";
    QPen paint_pen;

    int inner_radius = vma.size;  // радиус внутреннего кружка
    int outer_radius = vma.size;// + 8;  // радиус внешнего кружка

    if (vma.dir == true && vma.power != 0)
    {

        if (vma.state == "operate")
        {
            // DOWN
            paint_pen.setColor(Qt::white);
            vPainter->setPen(paint_pen);

            vPainter->setBrush(Qt::white);
            vPainter->drawEllipse(vma.center, (int)round(inner_radius) , (int)round(inner_radius));

            paint_pen.setColor(myBlue);
            vPainter->setPen(paint_pen);
            vPainter->setBrush(myBlue);
            vPainter->drawEllipse(vma.center, inner_radius - 15 , inner_radius - 15);

            float coef = vma.power / 100.0; // у нас приходит power 0..100
            vPainter->drawEllipse(vma.center, (int)round(inner_radius * coef) , (int)round(inner_radius * coef));

        }
        else if (vma.state == "fail")
        {
            // DOWN
            paint_pen.setColor(Qt::white);
            vPainter->setPen(paint_pen);

            vPainter->setBrush(Qt::white);
            vPainter->drawEllipse(vma.center, (int)round(inner_radius) , (int)round(inner_radius));

            paint_pen.setColor(myRed);
            vPainter->setPen(paint_pen);
            vPainter->setBrush(myRed);
            vPainter->drawEllipse(vma.center, inner_radius - 15 , inner_radius - 15);

            float coef = vma.power / 100.0; // у нас приходит power 0..100
            vPainter->drawEllipse(vma.center, (int)round(inner_radius * coef) , (int)round(inner_radius * coef));

        }

        // INNER CIRCLE FOR SHOWING DIRECTION
        paint_pen.setColor(Qt::black);
        vPainter->setPen(paint_pen);

        vPainter->setBrush(Qt::NoBrush);

        paint_pen.setWidth(1);
        vPainter->drawEllipse(vma.center, inner_radius - 10 , inner_radius - 10);

        vPainter->setBrush(Qt::black);
        vPainter->drawEllipse(vma.center, inner_radius - 15 , inner_radius - 15);
    }
    else if (vma.dir == false && vma.power != 0) // reversed
    {

        if (vma.state == "operate") {
            //UP
            paint_pen.setColor(myGreen);
            vPainter->setPen(paint_pen);
            vPainter->setBrush(myGreen);

            float coef = vma.power / 100.0; // у нас приходит power 0..100
            vPainter->drawEllipse(vma.center, inner_radius , inner_radius);

            paint_pen.setColor(Qt::white);
            vPainter->setPen(paint_pen);
            vPainter->setBrush(Qt::white);
            vPainter->drawEllipse(vma.center, (int)round(inner_radius * (1 - coef)) , (int)round(inner_radius * (1 -coef)));

        }
        else if (vma.state == "fail") {
            //UP
            paint_pen.setColor(myRed2);
            vPainter->setPen(paint_pen);
            vPainter->setBrush(myRed2);

            float coef = vma.power / 100.0; // у нас приходит power 0..100
            vPainter->drawEllipse(vma.center, inner_radius , inner_radius);

            paint_pen.setColor(Qt::white);
            vPainter->setPen(paint_pen);
            vPainter->setBrush(Qt::white);
            vPainter->drawEllipse(vma.center, (int)round(inner_radius * (1 - coef)) , (int)round(inner_radius * (1 -coef)));
        }


        // INNER CIRCLE FOR SHOWING DIRECTION
        paint_pen.setColor(Qt::black);
        vPainter->setPen(paint_pen);

        vPainter->setBrush(Qt::NoBrush);

        paint_pen.setWidth(1);
        vPainter->drawEllipse(vma.center, inner_radius - 10 , inner_radius - 10);

        const QPointF points[6] = {
            QPointF(vma.center.x() - (inner_radius-15) / sqrt(2), vma.center.y() + (inner_radius-15) / sqrt(2)),
            QPointF(vma.center.x() + (inner_radius-15) / sqrt(2),vma.center.y() - (inner_radius-15) / sqrt(2)),
            QPointF(vma.center.x() , vma.center.y() ),
            QPointF(vma.center.x() - (inner_radius-15) / sqrt(2), vma.center.y() - (inner_radius-15) / sqrt(2)),
            QPointF(vma.center.x() + (inner_radius-15) / sqrt(2), vma.center.y() + (inner_radius-15) / sqrt(2)),
            QPointF(vma.center.x() , vma.center.y() )
        };

        vPainter->drawConvexPolygon(points, 6);
    }
    else
    {
        // NO POWER

        paint_pen.setColor(Qt::white);
        vPainter->setPen(paint_pen);

        vPainter->setBrush(Qt::white);
        vPainter->drawEllipse(vma.center, (int)round(inner_radius) , (int)round(inner_radius));

        // INNER CIRCLE FOR SHOWING DIRECTION
        paint_pen.setColor(Qt::black);
        vPainter->setPen(paint_pen);

        vPainter->setBrush(Qt::NoBrush);

        paint_pen.setWidth(1);
        vPainter->drawEllipse(vma.center, inner_radius - 10 , inner_radius - 10);
    }

    // и вокруг него

    vPainter->setBrush(Qt::NoBrush);

    if (vma.state == "fail")
    {
        paint_pen.setColor(myRedFill);
        //percent_str = "нет связи"; // в случае потери связи % не выводим
    }
    else if (vma.state == "operate")
    {
        paint_pen.setColor(myGreenFill);
    }
    else if (vma.state == "off")
    {
        paint_pen.setColor(Qt::darkGray);
    }
    else
    {
        paint_pen.setColor(Qt::lightGray);
    }

    paint_pen.setWidth(3);
    vPainter->setPen(paint_pen);
    vPainter->drawEllipse(vma.center, outer_radius, outer_radius);

    // текст
    paint_pen.setColor(Qt::black);
    vPainter->setPen(paint_pen);
    vPainter->drawText(vma.center.x() + vma.textOffset.x(), vma.center.y() + vma.textOffset.y(), vma.text);
    vPainter->drawText(vma.center.x() + vma.powerOffsetDirect.x(), vma.center.y() + vma.powerOffsetDirect.y(), percent_str);

}

///--------------------------------------------------
///Отображение вертикального движителя
///--------------------------------------------------

void VMA::vertVMA(vint vma, QPainter *vPainter)
{
    QString percent_str = QString::number(vma.power) + "%";

    QPen paint_pen;
    QBrush brush;
    QPainterPath path;

    // размер прямоугольника
    int width = vma.size * 2;

    // прямоугольник строится от левого верхнего угла
    QPointF corner(vma.center.x() - width / 2, vma.center.y() - vma.size / 2);

    if (vma.state == "fail")
    {
        brush.setColor(myRedFill);
        paint_pen.setColor(myRedFill);
        //percent_str = "нет связи"; // в случае потери связи % не выводим
    }
    else if (vma.state == "operate")
    {
        brush.setColor(myGreenFill);
        paint_pen.setColor(myGreenFill);
    }
    else if (vma.state == "off")
    {
        brush.setColor(Qt::darkGray);
        paint_pen.setColor(Qt::darkGray);
    }
    else
    {
        paint_pen.setColor(Qt::lightGray);
    }

    // треугольник

    int delta = 2; // поправка на отстояние треугольника от прямоугольника
    float coef = vma.power / 100.0; // у нас приходит power 0..100
    int h_triangle = (int)round(30 * coef); // высота треугольника

    QPointF p1(vma.center.x() - width / 2, vma.center.y() - vma.distance - delta);
    QPointF p2(vma.center.x(), vma.center.y() - vma.distance - h_triangle - delta);
    QPointF p3(vma.center.x() + width / 2, vma.center.y() - vma.distance - delta);

    QPointF p4(vma.center.x() - width / 2, vma.center.y() + vma.distance + delta);
    QPointF p5(vma.center.x(), vma.center.y() + vma.distance + h_triangle + delta);
    QPointF p6(vma.center.x() + width / 2, vma.center.y() + vma.distance + delta);

    if ((vma.dir == true) && (vma.power != 0))
    {
        if (vma.state == "operate")
        {
            paint_pen.setColor(myBlue);
            vPainter->setPen(paint_pen);

            brush.setColor(myBlue);

            path.moveTo(p4);
            path.lineTo(p5);
            path.lineTo(p6);
            path.lineTo(p4);

            vPainter->fillPath(path, brush.color());
        }
        else if (vma.state == "fail")
        {
            paint_pen.setColor(myRed);
            vPainter->setPen(paint_pen);

            brush.setColor(myRed);

            path.moveTo(p4);
            path.lineTo(p5);
            path.lineTo(p6);
            path.lineTo(p4);

            vPainter->fillPath(path, brush.color());
        }

        // текст
        paint_pen.setColor(Qt::black);
        vPainter->setPen(paint_pen);
        vPainter->drawText(vma.center.x() + vma.textOffset.x(), vma.center.y() + vma.distance, vma.text);
        vPainter->drawText(vma.center.x() + vma.powerOffsetDirect.x(), vma.center.y() + vma.distance, percent_str);

    }
    else if ((vma.dir == false) && (vma.power !=0)) // reversed
    {
        if (vma.state == "operate")
        {
            paint_pen.setColor(myGreen);
            vPainter->setPen(paint_pen);

            brush.setColor(myGreen);

            path.moveTo(p1);
            path.lineTo(p2);
            path.lineTo(p3);
            path.lineTo(p1);

            vPainter->fillPath(path, brush.color());
        }
        else if (vma.state == "fail")
        {
            paint_pen.setColor(myRed2);
            vPainter->setPen(paint_pen);

            brush.setColor(myRed2);

            path.moveTo(p1);
            path.lineTo(p2);
            path.lineTo(p3);
            path.lineTo(p1);

            vPainter->fillPath(path, brush.color());
        }

        // текст
        paint_pen.setColor(Qt::black);
        vPainter->setPen(paint_pen);
        vPainter->drawText(vma.center.x() + vma.textOffset.x(), vma.center.y() - vma.distance, vma.text);
        vPainter->drawText(vma.center.x() + vma.powerOffsetDirect.x(), vma.center.y() - vma.distance, percent_str);
    }

    if ((vma.state == "fail") && (vma.power == 0))
    {
        paint_pen.setColor(myRed);
        vPainter->setPen(paint_pen);

        brush.setColor(myRed);

        h_triangle = 30; // высота треугольника
        p1 = QPoint(vma.center.x() - width / 2, vma.center.y() - vma.distance - delta);
        p2 = QPoint(vma.center.x(), vma.center.y() - vma.distance - h_triangle - delta);
        p3 = QPoint(vma.center.x() + width / 2, vma.center.y() - vma.distance - delta);

        p4 = QPoint(vma.center.x() - width / 2, vma.center.y() + vma.distance + delta);
        p5 = QPoint(vma.center.x(), vma.center.y() + vma.distance + h_triangle + delta);
        p6 = QPoint(vma.center.x() + width / 2, vma.center.y() + vma.distance + delta);

        path.moveTo(p4);
        path.lineTo(p5);
        path.lineTo(p6);
        path.lineTo(p4);

        path.moveTo(p1);
        path.lineTo(p2);
        path.lineTo(p3);
        path.lineTo(p1);

        vPainter->fillPath(path, brush.color());

        // текст
        paint_pen.setColor(Qt::black);
        vPainter->setPen(paint_pen);
        vPainter->drawText(vma.center.x() + vma.textOffset.x(), vma.center.y() - vma.distance, vma.text);
        vPainter->drawText(vma.center.x() + vma.powerOffsetDirect.x(), vma.center.y() - vma.distance, percent_str);
    }

}

///--------------------------------------------------
///Расчет параметров компаса
///--------------------------------------------------

void VMA::VMA_Data()
{
//    qDebug() << "---------------------";
//    qDebug() << "PSI == " << exch->from_rov.coordStruct.PSI;
//    qDebug() << "X == " << exch->from_rov.coordStruct.X;
//    qDebug() << "Y == " << exch->from_rov.coordStruct.Y;
//    qDebug() << "Vx == " << exch->from_rov.coordStruct.VX;
//    qDebug() << "Vy == " << exch->from_rov.coordStruct.VY;
//    qDebug() << "Vz == " << exch->from_rov.coordStruct.VZ;
//    qDebug() << "---------------------";

//--------------------------------------------------
//Крест
//--------------------------------------------------

    //Верхний
    if (exch_str->from_data.vma[0].SensorVMA != 0)
        rovVMA.vma_crossUp.state = "fail";
//    else if (exch_str->from_rov.vma[0].desiredValue == 0)
//        rovVMA.marshL.state = "off";
    else
    {
        rovVMA.vma_crossUp.state = "operate";
        rovVMA.vma_crossUp.dir = (exch_str->from_data.vma[0].U > 0) ? false:true;
        rovVMA.vma_crossUp.power = 100 * fabs(exch_str->from_data.vma[0].U / U_MAX);
    }

    //Нижний
    if (exch_str->from_data.vma[1].SensorVMA != 0)
        rovVMA.vma_crossDown.state = "fail";
//    else if (exch_str->from_rov.vma[1].desiredValue == 0)
//        rovVMA.marshR.state = "off";
    else
    {
        rovVMA.vma_crossDown.state = "operate";
        rovVMA.vma_crossDown.dir = (exch_str->from_data.vma[1].U > 0) ? false:true;
        rovVMA.vma_crossDown.power = 100 * fabs(exch_str->from_data.vma[1].U / U_MAX);
    }

    //Левый
    if (exch_str->from_data.vma[2].SensorVMA != 0)
        rovVMA.vma_crossLeft.state = "fail";
//    else if (exch_str->from_rov.vma[2].desiredValue == 0)
//        rovVMA.vertRL.state = "off";
    else
    {
        rovVMA.vma_crossLeft.state = "operate";
        rovVMA.vma_crossLeft.dir = (exch_str->from_data.vma[2].U > 0) ? false:true;
        rovVMA.vma_crossLeft.power = 100 * fabs(exch_str->from_data.vma[2].U / U_MAX);
    }

    //Правый
    if (exch_str->from_data.vma[3].SensorVMA != 0)
        rovVMA.vma_crossRight.state = "fail";
//    else if (exch_str->from_rov.vma[3].desiredValue == 0)
//        rovVMA.vertRR.state = "off";
    else
    {
        rovVMA.vma_crossRight.state = "operate";
        rovVMA.vma_crossRight.dir = (exch_str->from_data.vma[3].U > 0) ? false:true;
        rovVMA.vma_crossRight.power = 100 * fabs(exch_str->from_data.vma[3].U / U_MAX);
    }

//--------------------------------------------------
//Высота
//--------------------------------------------------

    if (exch_str->from_data.vma[4].SensorVMA != 0)
        rovVMA.vma_depth.state = "fail";
//    else if (exch_str->from_rov.vma[4].desiredValue == 0)
//        rovVMA.vertFL.state = "off";
    else
    {
        rovVMA.vma_depth.state = "operate";
        rovVMA.vma_depth.dir = (exch_str->from_data.vma[4].U > 0) ? false:true;
        rovVMA.vma_depth.power = 100 * fabs(exch_str->from_data.vma[4].U / U_MAX);
    }
}

///--------------------------------------------------
///Тестовые установки (удобно соединять коннектом к слайдерам)
///--------------------------------------------------

//--------------------------------------------------

void VMA::setU1(int _U1)
{
    exch_str->from_data.vma[0].U = _U1;
    update();
}

//--------------------------------------------------

void VMA::setU2(int _U2)
{
    exch_str->from_data.vma[1].U = _U2;
    update();
}

//--------------------------------------------------

void VMA::setU3(int _U3)
{
    exch_str->from_data.vma[2].U = _U3;
    update();
}

//--------------------------------------------------

void VMA::setU4(int _U4)
{
    exch_str->from_data.vma[3].U = _U4;
    update();
}

//--------------------------------------------------

void VMA::setU5(int _U5)
{
    exch_str->from_data.vma[4].U = _U5;
    update();
}

//--------------------------------------------------

void VMA::setFail_U1(bool fail)
{
    exch_str->from_data.vma[0].SensorVMA = (fail == true) ? 1 : 0;
    update();
}

//--------------------------------------------------

void VMA::setFail_U2(bool fail)
{
    exch_str->from_data.vma[1].SensorVMA = (fail == true) ? 1 : 0;
    update();
}

//--------------------------------------------------

void VMA::setFail_U3(bool fail)
{
    exch_str->from_data.vma[2].SensorVMA = (fail == true) ? 1 : 0;
    update();
}

//--------------------------------------------------

void VMA::setFail_U4(bool fail)
{
    exch_str->from_data.vma[3].SensorVMA = (fail == true) ? 1 : 0;
    update();
}

//--------------------------------------------------

void VMA::setFail_U5(bool fail)
{
    exch_str->from_data.vma[4].SensorVMA = (fail == true) ? 1 : 0;
    update();
}
