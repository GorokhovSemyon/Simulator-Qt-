#include "altitude.h"
#include "ui_altitude.h"

Altitude::Altitude(Exchange_structures *_exch_str, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Altitude)
{
    exch_str = _exch_str;

    ui->setupUi(this);
}

Altitude::~Altitude()
{
    delete ui;
}

void Altitude::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QFont font;


    painter.setRenderHint(QPainter::Antialiasing,true);

    painter.translate(width()/2,height()/2);

    int side = qMin(width(),height());
    painter.scale(side/100.0, side/100.0);

//--------------------------------------------------
//Расчет коэффициента масштабирования для расстояния между делениями шкалы
//--------------------------------------------------
    float koef = STEP/10;

//--------------------------------------------------
//Отображение шкалы отстояния
//--------------------------------------------------

    painter.save();
    font.setPointSize(5);
    painter.setFont(font);

    int newAltitude = exch_str->from_data.params.Z * koef;

    for (int i = 0; i <= MAX_ATLITUDE*koef; i += STEP) //для делений с числовыми пометками (0, 10, 20...)
    {

            painter.drawLine(-60, (i - newAltitude),
                             0, (i - newAltitude));
            painter.drawText(-77, (i - newAltitude)-5, 15, 10,
                             Qt::AlignCenter,
                             QString::number(i/koef));
    }
    for (int i = STEP/2; i <= MAX_ATLITUDE*koef - STEP/2; i += STEP) //для промежуточных делений
    {
            painter.drawLine(-40, (i - newAltitude),
                             0, (i - newAltitude));
    }
    painter.restore();

//--------------------------------------------------
//Метка отстояния
//--------------------------------------------------

    painter.save();

    font.setPointSize(8);
    painter.setFont(font);

    painter.setBrush(Qt::white);
    painter.drawRect(15, -15, 40, 20);
    painter.drawText(16, -15, 40, 20,
                    Qt::AlignHCenter | Qt::AlignVCenter,
                    QString::number((int)exch_str->from_data.params.Z));

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.drawConvexPolygon(mark_altitude, 4);

    painter.restore();
}

//--------------------------------------------------

void Altitude::setAltitude(int _altitude)
{
    exch_str->from_data.params.Z = _altitude;
    update();
}
