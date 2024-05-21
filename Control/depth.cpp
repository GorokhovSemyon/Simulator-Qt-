#include "depth.h"
#include "ui_depth.h"

Depth::Depth(Exchange_structures *_exch_str, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Depth)
{
    exch_str = _exch_str;
    depth = 0;

    ui->setupUi(this);
}

Depth::~Depth()
{
    delete ui;
}

void Depth::paintEvent(QPaintEvent *)
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
    font.setPointSize(7);
    painter.setFont(font);

    int newAltitude = (MAX_ATLITUDE - exch_str->from_data.params.Y) * koef;

    for (int i = 0; i <= MAX_ATLITUDE*koef; i += STEP) //для делений с числовыми пометками (0, 10, 20...)
    {

            painter.drawLine(-23, (-i + newAltitude),
                             0, (-i + newAltitude));
            painter.drawText(-45, (-i + newAltitude)-5, 20, 10,
                             Qt::AlignCenter,
                             QString::number(i/koef));
    }
    for (int i = STEP/2; i <= MAX_ATLITUDE*koef - STEP/2; i += STEP) //для промежуточных делений
    {
            painter.drawLine(-15, (-i + newAltitude),
                             0, (-i + newAltitude));
    }
    painter.restore();

//--------------------------------------------------
//Метка отстояния
//--------------------------------------------------

    painter.save();

    font.setPointSize(8);
    painter.setFont(font);

    painter.setBrush(Qt::white);
    painter.drawRect(15, -10, 35, 20);
    painter.drawText(16, -10, 35, 20,
                    Qt::AlignHCenter | Qt::AlignVCenter,
                    QString::number((int)(MAX_ATLITUDE - exch_str->from_data.params.Y)));

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.drawConvexPolygon(mark_depth, 4);

    painter.restore();
}

//--------------------------------------------------

void Depth::setDepth()
{
    update();
}
