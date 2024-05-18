#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QTime>
#include <QtMath>

#include "Contours_SU/depth_contour.h"
#include "Contours_SU/kurs_contour.h"
#include "Contours_SU/marsh_contour.h"
#include "debug_form.h"

#include "common/exchange_structures.h"
#include "protocols/protocol_simulator.h"
#include "protocols/protocol_instructor.h"

#include "common/configdata.h"

#include "Control/compass.h"
#include "Control/hyrohorizont.h"
#include "Control/vma.h"
#include "Control/altitude.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    depth_contour* DEPTH = nullptr;
    Marsh_contour* MARSH = nullptr;
    kurs_contour* KURS = nullptr;

    Debug_Form* debug = nullptr;

    Compass* compass = nullptr;
    HyroHorizont* hyrohorizont = nullptr;
    VMA* vma = nullptr;
    Altitude* altitude = nullptr;

    QStringList ConfigList;
    ConfigData* config = nullptr;
    Exchange_structures* exch_str = nullptr;
    Protocol_Simulator* sim = nullptr;
    Protocol_Instructor* instr = nullptr;

    bool superImportantVariable;

    void BFS();
    float saturation(float input, float max);

private:
    Ui::MainWidget *ui;

    QDate *date;
    QTime *time;
    QTime *operatingTime;
    QTime *timer;
    double prevOperatingTime;

    int timerWidgetID;
    int id_10Hz;
    int id_1Hz;

    QButtonGroup* graphs_btns = nullptr;
    QButtonGroup* main_btns = nullptr;
    QButtonGroup* exch_btns = nullptr;

    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWIDGET_H
