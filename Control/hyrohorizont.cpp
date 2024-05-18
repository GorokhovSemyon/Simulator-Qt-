#include "hyrohorizont.h"
#include "ui_hyrohorizont.h"

HyroHorizont::HyroHorizont(Exchange_structures *_exch_str, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HyroHorizont)
{
    ui->setupUi(this);

    exch_str = _exch_str;

    Hblue = QColor(0,0,200,150);
    Hgreen = QColor(0,255,0,180);
}

HyroHorizont::~HyroHorizont()
{
    delete ui;
}

void HyroHorizont::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QFont font;


    painter.setRenderHint(QPainter::Antialiasing,true);

    painter.translate(width()/2,height()/2);

    int side = qMin(width(),height());
    painter.scale(side/170.0, side/170.0);

//--------------------------------------------------
//Расчет коэффициента масштабирования для расстояния между делениями дифферента
//--------------------------------------------------
    float koef = STEP/10;

//--------------------------------------------------
//Двухцветный маркер фона для дифферента
//--------------------------------------------------

    painter.save();
    painter.setPen(Qt::NoPen);

    float newPitch = exch_str->from_data.params.Tetta * koef;
    if (newPitch > 90)
        newPitch = 90;
    else if (newPitch < -90)
        newPitch = -90;

    painter.setBrush(Hgreen);
    painter.drawChord(-60,-60,120,120,
                      16*(-newPitch),
                      16*(180 + 2*newPitch));


    painter.setBrush(Hblue);
    painter.drawChord(-60,-60,120,120,
                      16*(-newPitch),
                      16*(-180 + 2*newPitch));

    painter.restore();

//--------------------------------------------------
//Сам гирокомпас: деления, подписи к ним и окружности
//--------------------------------------------------

    painter.save();
    painter.drawEllipse(-60,-60,120,120);
    painter.drawEllipse(-70,-70,140,140);

    painter.rotate(-180.0);

    for(int j = -30; j < 30; ++j)
    {
        if ((j % 5) != 0)
            painter.drawLine(0, -55, 0, -60);
        else
        {
            painter.drawLine(0, -50, 0, -60);
            font.setPointSize(4);
            painter.setFont(font);

            if (j == -30)
                painter.drawText(-20, -85, 40, 40,
                                Qt::AlignCenter | Qt::AlignTop,
                                QString("\u00B1") + QString::number(180));
            else
                painter.drawText(-20, -85, 40, 40,
                                Qt::AlignCenter | Qt::AlignTop,
                                QString::number(j*6));
        }
        painter.rotate(6.0);
    }
    painter.restore();

//--------------------------------------------------
//Отображение делений для дифферента
//--------------------------------------------------

    painter.save();
    font.setPointSize(5);
    painter.setFont(font);

    newPitch = exch_str->from_data.params.Tetta * koef;

    for (int i = -90*koef; i <= 90*koef; i += STEP) //для делений с числовыми пометками (0, 10, 20...)
    {
        if ((i + newPitch) <= 30 && (i + newPitch) >= -30)
        {

            painter.drawLine(-sqrt(pow(40,2) - pow((i + newPitch),2)), (i + newPitch),
                             -8, (i + newPitch));
            painter.drawLine(8, (i + newPitch), sqrt(pow(40,2) - pow((i + newPitch),2)), (i + newPitch));
            painter.drawText(-7, (i + newPitch)-5, 15, 10,
                             Qt::AlignCenter,
                             QString::number(-i/koef));
        }
    }
    for (int i = -90*koef + STEP/2; i <= 90*koef - STEP/2; i += STEP) //для промежуточных делений
    {
        if ((i + newPitch) <= 30 && (i + newPitch) >= -30)
        {
            painter.drawLine(-15, (i + newPitch),
                             15, (i + newPitch));
        }
    }
    painter.restore();

//--------------------------------------------------
//Метка аппарата в виде прицела
//--------------------------------------------------

    painter.save();
    painter.rotate(exch_str->from_data.params.Gamma);
    painter.setBrush(Qt::yellow);
    painter.drawRect(-40,-1, 30,2);
    painter.drawRect(10,-1, 30,2);
    painter.drawPolyline(mark_pitch, 5);
    painter.drawEllipse(-1,6,2,2);
    painter.restore();

//--------------------------------------------------
//Вывод значений дифферента
//--------------------------------------------------
    painter.save();

    font.setPointSize(6);
    painter.setFont(font);
    painter.setBrush(Qt::white);

    font.setPointSize(8);
    painter.setFont(font);

    painter.drawRect(-15, -72, 30, 20);
    painter.drawText(QRect(-20,-72, 40,20), Qt::AlignCenter, QString::number(exch_str->from_data.params.Tetta));

    painter.restore();
}

//--------------------------------------------------

void HyroHorizont::setPitch(int _pitch)
{
    exch_str->from_data.params.Tetta = _pitch;
    update();
}
