#include "compass.h"
#include "ui_compass.h"

Compass::Compass(Exchange_structures *_exch_str, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Compass)
{
    ui->setupUi(this);

    exch_str = _exch_str;
}

Compass::~Compass()
{
    delete ui;
}

///--------------------------------------------------
///Отрисовка компаса
///--------------------------------------------------

void Compass::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QFont font;

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.translate(width() / 2, height() / 2 );

    int side = qMin(width(), height());
    painter.scale(side / 170.0, side / 170.0);

//--------------------------------------------------
//Отрисовка самого компаса
//--------------------------------------------------

    painter.save();
    painter.drawEllipse(-70,-70, 140, 140);
    painter.drawEllipse(-60, -60, 120, 120);


    for (int i = 0; i < 60; ++i)
    {
        if ((i % 5) != 0)
            painter.drawLine(0, -55, 0, -60);
        else {
            painter.drawLine(0, -50, 0, -60);
            font.setPointSize(5);
            painter.setFont(font);
            painter.drawText(-20, -70, 40, 40, Qt::AlignHCenter | Qt::AlignTop, QString::number(i*6));
        }
        painter.rotate(6.0);
    }
    painter.restore();

//--------------------------------------------------
//Отрисовка системы координат
//--------------------------------------------------

    painter.save();
    painter.setPen(Qt::DotLine);
    painter.setPen(Qt::lightGray);

    painter.drawText(-5, -35, 40, 40, Qt::AlignHCenter | Qt::AlignTop, "X");
    painter.drawText(15, 0, 40, 40, Qt::AlignHCenter | Qt::AlignTop, "Z");

    painter.drawConvexPolygon(arrow_SC, 6);
    painter.rotate(90);
    painter.drawConvexPolygon(arrow_SC, 6);

    painter.restore();

//--------------------------------------------------
//Стрелка компаса
//--------------------------------------------------

    painter.save();
    painter.rotate(exch_str->from_data.params.Psi);
    QPixmap pixmap(":/icons/tnpa.png");
    pixmap = pixmap.scaled(90, 90, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(-45, -45, pixmap);
    painter.restore();

//--------------------------------------------------
//Отображение значения курса
//--------------------------------------------------

    painter.save();
    font.setPointSize(8);
    painter.setFont(font);
    painter.setBrush(Qt::white);
    painter.drawRect(-15, -10, 30, 20);
    painter.drawText(QRect(-20, -10, 40, 20), Qt::AlignCenter, QString::number((int)exch_str->from_data.params.Psi));
    painter.restore();

//--------------------------------------------------
//Метка желаемого курса
//--------------------------------------------------

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.rotate(exch_str->target_params.des_Yaw);
    painter.drawConvexPolygon(mark_Desirable, 4);
    painter.restore();
}

///--------------------------------------------------
///Тестовые установки (удобно соединять коннектом к слайдерам)
///--------------------------------------------------

void Compass::setYawDes(int _yawDes)
{
    exch_str->target_params.des_Yaw = _yawDes;
    update();
}

//--------------------------------------------------

void Compass::setYaw(int _yaw)
{
    exch_str->from_data.params.Psi = _yaw;
    update();
}
