#include "chartformdepth.h"
#include "ui_chartformdepth.h"

ChartFormDepth::ChartFormDepth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartFormDepth)
{
    ui->setupUi(this);

    chart = new QChart();
    chartView = new QChartView(chart);
    series = new QLineSeries;
    xAxis = new QValueAxis();
    yAxis = new QValueAxis();

    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->legend()->setVisible(false);

    //установка максимального и минимального значения по оси
    xAxis->setRange(0,10);
    //установка количества градаций на оси (по умолчанию =5)
    xAxis->setTickCount(11);
    xAxis->setTitleText("T, c");


    yAxis->setRange(-50,50);
    yAxis->setTickCount(11);
    yAxis->setTitleText("Напряжение глубины, В");


    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setAxisX(xAxis, series);
    chartView->chart()->setAxisY(yAxis, series);

    hlay = new QHBoxLayout();
    hlay->addWidget(chartView);
    hlay->setContentsMargins(0, 0, 0, 0);
    setLayout(hlay);

    series->setName("Глубина");
    series->append(-10, 0);

}

ChartFormDepth::~ChartFormDepth()
{

}

void ChartFormDepth::setYT(double Y, int T)
{
    series->append(T/1000, Y);
    xAxis->setRange(T/1000-10,T/1000);
}

