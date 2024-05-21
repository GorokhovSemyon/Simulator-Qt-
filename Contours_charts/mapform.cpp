#include "mapform.h"
#include "ui_mapform.h"

Mapform::Mapform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mapform)
{
    ui->setupUi(this);

    rovTrajectory = new QSplineSeries(this);
    rovOleg = new QScatterSeries(this);
    chart = new QChart();
    axisX = new QValueAxis(this);
    axisZ = new QValueAxis(this);
    chartView = new QChartView(chart, this);
    hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);

    font.setPixelSize(12);
    pen.setColor(Qt::gray);
    pen.setWidth(1);

    zeroLineX = new QLineSeries(this);
    zeroLineX->append(-20000,0);
    zeroLineX->append(20000,0);

    zeroLineY = new QLineSeries(this);
    zeroLineY->append(0,-20000);
    zeroLineY->append(0,20000);

    zeroLineX->setPen(pen);
    zeroLineY->setPen(pen);

    axisX->setLabelsFont(font);
    axisZ->setLabelsFont(font);

    target = new QScatterSeries();
    target->setBrush(QBrush(Qt::red));
    target->setMarkerSize(50);

    chart->legend()->setVisible(false);
    // Создание замены точки на фотку
    brushOleg = new QBrush();
    originalPixmap = QPixmap(":/icons/tnpa.png");

    rotatedPixmap = originalPixmap.transformed(QTransform().rotate(0));

    brushOleg->setTexture(rotatedPixmap.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    rovOleg->setBrush(*brushOleg);
    rovOleg->setMarkerSize(100);
    //rovOleg->setMarkerShape(QScatterSeries::MarkerShapeCircle);

    hLayout->addWidget(chartView);
    this->setLayout(hLayout);

    axisX->setRange(-100, 100);
    axisZ->setRange(-100, 100);
    axisX->setTickCount(11);
    axisZ->setTickCount(11);
    //axisX->setTitleText("X, м");
    //axisY->setTitleText("Y, м");

    rovOleg->append(0, 0);

    // Привязка series к chart
    chart->addSeries(zeroLineX);
    chart->addSeries(zeroLineY);
    chart->addSeries(rovTrajectory);
    //chart->add(target);
    chart->addSeries(rovOleg);


    chartView->chart()->setAxisX(axisX, zeroLineX);
    chartView->chart()->setAxisY(axisZ, zeroLineX);

    chartView->chart()->setAxisX(axisX, zeroLineY);
    chartView->chart()->setAxisY(axisZ, zeroLineY);

    // Привязка к системам координат чарта
    chartView->chart()->setAxisX(axisX, rovTrajectory);
    chartView->chart()->setAxisY(axisZ, rovTrajectory);

    chartView->chart()->setAxisX(axisX, rovOleg);
    chartView->chart()->setAxisY(axisZ, rovOleg);

    prev_X = 0;
    prev_Z = 0;
    prev_Y = 10;
    offset = 10;
}

Mapform::~Mapform()
{
    delete ui;
}

void Mapform::W_key()
{
    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axisY());
    qreal currentMin = axisY->min();
    qreal currentMax = axisY->max();

    axisY->setRange(currentMin + offset, currentMax + offset);
}

void Mapform::S_key()
{
    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axisY());
    qreal currentMin = axisY->min();
    qreal currentMax = axisY->max();

    axisY->setRange(currentMin - offset, currentMax - offset);
}

void Mapform::A_key()
{
    QValueAxis *axisX = qobject_cast<QValueAxis *>(chart->axisX());
    qreal currentMin = axisX->min();
    qreal currentMax = axisX->max();

    axisX->setRange(currentMin - offset, currentMax - offset);
}

void Mapform::D_key()
{
    QValueAxis *axisX = qobject_cast<QValueAxis *>(chart->axisX());
    qreal currentMin = axisX->min();
    qreal currentMax = axisX->max();

    axisX->setRange(currentMin + offset, currentMax + offset);
}

void Mapform::R_key()
{
    axisX->setRange(-100, 100);
    axisZ->setRange(-100, 100);
}

void Mapform::Plus_key()
{
    QValueAxis *axisX = qobject_cast<QValueAxis *>(chart->axisX());
    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axisY());

    qreal xRange = axisX->max() - axisX->min();
    qreal yRange = axisY->max() - axisY->min();

    if (xRange > 20 && yRange > 20)
    {
        axisX->setRange(axisX->min() + offset, axisX->max() - offset);
        axisY->setRange(axisY->min() + offset, axisY->max() - offset);
    }
}

void Mapform::Minus_key()
{
    QValueAxis *axisX = qobject_cast<QValueAxis *>(chart->axisX());
    QValueAxis *axisZ = qobject_cast<QValueAxis *>(chart->axisY());

    qreal xRange = axisX->max() - axisX->min();
    qreal yRange = axisZ->max() - axisZ->min();

    if (xRange < 20000 && yRange < 20000)
    {
        axisX->setRange(axisX->min() - offset, axisX->max() + offset);
        axisZ->setRange(axisZ->min() - offset, axisZ->max() + offset);
    }
}

void Mapform::set_anpa_position(float X, float Y, float Z, float yaw)
{
    rovOleg->remove(prev_Z,prev_X);

    rotatedPixmap = originalPixmap.transformed(QTransform().rotate(yaw));
    brushOleg->setTexture(rotatedPixmap.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    rovOleg->setBrush(*brushOleg);

    if (prev_X != X || prev_Z != Z)
    {
        *rovTrajectory << QPointF(Z, X);
        rovTrajectory->append(Z, X);
    }

    rovOleg->append(Z, X);
    prev_X = X;
    prev_Y = Y;
    prev_Z = Z;
}
