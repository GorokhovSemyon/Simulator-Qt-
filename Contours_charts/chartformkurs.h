#ifndef CHARTFORMKURS_H
#define CHARTFORMKURS_H

#include <QWidget>
#include <QtCharts>

namespace Ui {
class ChartFormKurs;
}

class ChartFormKurs : public QWidget
{
    Q_OBJECT

public:
    explicit ChartFormKurs(QWidget *parent = nullptr);
    ~ChartFormKurs();

    QChartView * chartView;

private:
    Ui::ChartFormKurs *ui;

    QHBoxLayout *hlay;

    QChart *chart;
    QLineSeries *series;
    QValueAxis *xAxis;
    QValueAxis *yAxis;
    QTimer *timer;

public slots:
    void setYT(double Y, int T);
};

#endif // CHARTFORMKURS_H
