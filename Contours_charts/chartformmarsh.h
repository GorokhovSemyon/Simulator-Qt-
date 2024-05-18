#ifndef CHARTFORMMARSH_H
#define CHARTFORMMARSH_H

#include <QWidget>
#include <QtCharts>

namespace Ui {
class ChartFormMarsh;
}

class ChartFormMarsh : public QWidget
{
    Q_OBJECT

public:
    explicit ChartFormMarsh(QWidget *parent = nullptr);
    ~ChartFormMarsh();

    QChartView * chartView;

private:
    Ui::ChartFormMarsh *ui;

    QHBoxLayout *hlay;

    QChart *chart;
    QLineSeries *series;
    QValueAxis *xAxis;
    QValueAxis *yAxis;
    QTimer *timer;

public slots:
    void setYT(double Y, int T);
};

#endif // CHARTFORMMARSH_H
