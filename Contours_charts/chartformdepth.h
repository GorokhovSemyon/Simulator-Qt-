#ifndef CHARTFORMDEPTH_H
#define CHARTFORMDEPTH_H

#include <QWidget>
#include <QtCharts>

namespace Ui {
class ChartFormDepth;
}

class ChartFormDepth : public QWidget
{
    Q_OBJECT

public:
    explicit ChartFormDepth(QWidget *parent = nullptr);
    ~ChartFormDepth();

    QChartView * chartView;

private:
    Ui::ChartFormDepth *ui;

    QHBoxLayout *hlay;
    QChart *chart;
    QLineSeries *series;
    QValueAxis *xAxis;
    QValueAxis *yAxis;
    QTimer *timer;

public slots:
    void setYT(double Y, int T);

};

#endif // CHARTFORMDEPTH_H
