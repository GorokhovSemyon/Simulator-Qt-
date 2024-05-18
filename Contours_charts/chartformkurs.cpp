#include "chartformkurs.h"
#include "ui_chartformkurs.h"

ChartFormKurs::ChartFormKurs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartFormKurs)
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
    yAxis->setTitleText("Напряжение курса, В");


    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setAxisX(xAxis, series);
    chartView->chart()->setAxisY(yAxis, series);

    hlay = new QHBoxLayout();
    hlay->addWidget(chartView);
    hlay->setContentsMargins(0, 0, 0, 0);
    setLayout(hlay);

    series->setName("Курс");
    series->append(-10, 0);

}

ChartFormKurs::~ChartFormKurs()
{

}

void ChartFormKurs::setYT(double Y, int T)
{
    series->append(T/1000, Y);
    xAxis->setRange(T/1000-10,T/1000);
}
