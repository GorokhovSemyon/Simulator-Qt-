#ifndef DEBUG_FORM_H
#define DEBUG_FORM_H

#include <QWidget>

namespace Ui {
class Debug_Form;
}

class Debug_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Debug_Form(QWidget *parent = nullptr);
    ~Debug_Form();

signals:
    void change_Kurs(float value);
    void change_Marsh(float value);
    void change_Depth(float value);

    void setYawDes(int _yawDes);
    void setYaw(int _yaw);
    void setU1(int _U1);
    void setU2(int _U2);
    void setU3(int _U3);
    void setU4(int _U4);
    void setU5(int _U5);
    void setU6(int _U6);
    void setU7(int _U7);
    void setU8(int _U8);

    void setFail_U1(bool fail);
    void setFail_U2(bool fail);
    void setFail_U3(bool fail);
    void setFail_U4(bool fail);
    void setFail_U5(bool fail);
    void setFail_U6(bool fail);
    void setFail_U7(bool fail);
    void setFail_U8(bool fail);

    void setRoll(int _roll);
    void setPitch(int _pitch);
    void setAltitude(int _Altitude);
    void setDepth();

private:
    Ui::Debug_Form *ui;
};

#endif // DEBUG_FORM_H
