#ifndef MAPFORM_H
#define MAPFORM_H

#include <QWidget>
#include <QtCharts>
#include <QSplineSeries>
#include <QPointF>
#include <QScatterSeries>
#include <QChart>
#include <QValueAxis>
#include <QChartView>
#include <QHBoxLayout>

using namespace QtCharts;

namespace Ui {
class Mapform;
}

class Mapform : public QWidget
{
    Q_OBJECT

public:
    explicit Mapform(QWidget *parent = nullptr);

    QSplineSeries *rovTrajectory = nullptr;
    QScatterSeries *rovOleg = nullptr;
    QChart *chart = nullptr;
    QValueAxis *axisX = nullptr, *axisY = nullptr;
    QChartView *chartView = nullptr;
    QHBoxLayout *hLayout = nullptr;
    QBrush *brushOleg=nullptr;
    QPixmap originalPixmap;
    QPixmap rotatedPixmap;
    QFont font;
    QPen pen;
    QLineSeries *zeroLineX = nullptr;
    QLineSeries *zeroLineY = nullptr;
    QScatterSeries *target;

    float prev_X;
    float prev_Y;
    float prev_Z;
    float offset;

    ~Mapform();

    void W_key();
    void S_key();
    void A_key();
    void D_key();
    void R_key();
    void Plus_key();
    void Minus_key();

public slots:

    void set_anpa_position(float X, float Y, float Z, float yaw);
private:
    Ui::Mapform *ui;

};

#endif // MAPFORM_H
