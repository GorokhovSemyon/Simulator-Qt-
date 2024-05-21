#include "debug_form.h"
#include "ui_debug_form.h"

#define U_MAX 10

Debug_Form::Debug_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Debug_Form)
{
    ui->setupUi(this);

    this->setWindowTitle("Debug");

    connect(ui->btn_setKurs, &QPushButton::clicked, [this]
    {
       emit change_Kurs(ui->le_kurs->text().toFloat());
    });

    connect(ui->btn_setMarsh, &QPushButton::clicked, [this]
    {
       emit change_Marsh(ui->le_marsh->text().toFloat());
    });

    connect(ui->btn_setDepth, &QPushButton::clicked, [this]
    {
        emit change_Depth(ui->le_depth->text().toFloat());
    });

    ui->sl_pitch->setValue(0);
    ui->sl_pitch->setMaximum(90);
    ui->sl_pitch->setMinimum(-90);

    ui->sl_alt->setValue(0);
    ui->sl_alt->setMaximum(200);
    ui->sl_alt->setMinimum(0);

    ui->lbl_pitch->setText("Дифферент");
    ui->lbl_alt->setText("Отстояние");

    ui->lbl_yaw->setText("Курс тек.");
    ui->lbl_yawDes->setText("Курс зад.");
    ui->lbl_U1->setText("U1");
    ui->lbl_U2->setText("U2");
    ui->lbl_U3->setText("U3");
    ui->lbl_U4->setText("U4");
    ui->lbl_U5->setText("U5");
    ui->rb_error_U1->setText("fail");
    ui->rb_error_U2->setText("fail");
    ui->rb_error_U3->setText("fail");
    ui->rb_error_U4->setText("fail");
    ui->rb_error_U5->setText("fail");

    ui->sl_yaw->setValue(0);
    ui->sl_yaw->setMaximum(360);
    ui->sl_yaw->setMinimum(0);

    ui->sl_yawDes->setValue(0);
    ui->sl_yawDes->setMaximum(360);
    ui->sl_yawDes->setMinimum(0);

    ui->sl_U1->setMaximum(U_MAX);
    ui->sl_U1->setMinimum(-U_MAX);
    ui->sl_U1->setValue(0);

    ui->sl_U2->setMaximum(U_MAX);
    ui->sl_U2->setMinimum(-U_MAX);
    ui->sl_U2->setValue(0);

    ui->sl_U3->setMaximum(U_MAX);
    ui->sl_U3->setMinimum(-U_MAX);
    ui->sl_U3->setValue(0);

    ui->sl_U4->setMaximum(U_MAX);
    ui->sl_U4->setMinimum(-U_MAX);
    ui->sl_U4->setValue(0);

    ui->sl_U5->setMaximum(U_MAX);
    ui->sl_U5->setMinimum(-U_MAX);
    ui->sl_U5->setValue(0);

    connect(ui->sl_yaw, &QSlider::valueChanged, this, &Debug_Form::setYaw);
    connect(ui->sl_yawDes, &QSlider::valueChanged, this, &Debug_Form::setYawDes);

    connect(ui->sl_U1, &QSlider::valueChanged, this, &Debug_Form::setU1);
    connect(ui->sl_U2, &QSlider::valueChanged, this, &Debug_Form::setU2);
    connect(ui->sl_U3, &QSlider::valueChanged, this, &Debug_Form::setU3);
    connect(ui->sl_U4, &QSlider::valueChanged, this, &Debug_Form::setU4);
    connect(ui->sl_U5, &QSlider::valueChanged, this, &Debug_Form::setU5);

    connect(ui->rb_error_U1, &QCheckBox::clicked, this, &Debug_Form::setFail_U1);
    connect(ui->rb_error_U2, &QCheckBox::clicked, this, &Debug_Form::setFail_U2);
    connect(ui->rb_error_U3, &QCheckBox::clicked, this, &Debug_Form::setFail_U3);
    connect(ui->rb_error_U4, &QCheckBox::clicked, this, &Debug_Form::setFail_U4);
    connect(ui->rb_error_U5, &QCheckBox::clicked, this, &Debug_Form::setFail_U5);

    connect(ui->sl_pitch, &QSlider::valueChanged, this, &Debug_Form::setPitch);
    connect(ui->sl_alt, &QSlider::valueChanged, [=] (int value)
    {
        emit setAltitude(value);
        emit setDepth();
    });
}

Debug_Form::~Debug_Form()
{
    delete ui;
}
