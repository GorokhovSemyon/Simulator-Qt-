#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    this->setWindowTitle("Interface");

///-------------------------------------------
///Контуры курса, марша и глубины
///-------------------------------------------

    MARSH = new Marsh_contour(0.05);
    DEPTH = new depth_contour(exch_str);
    KURS = new kurs_contour(0.05);

///-------------------------------------------
///Для верхней панели с метками времени
///-------------------------------------------

    superImportantVariable = false;
    operatingTime = new QTime();
    operatingTime->start();

    prevOperatingTime = operatingTime->elapsed();

    date = new QDate();

    time = new QTime();

    timerWidgetID = this->startTimer(100);

    id_1Hz = startTimer(1000); //Стуртуем таймер для обновления графиков

///-------------------------------------------
///Настройка страниц и кнопок графиков
///-------------------------------------------

    graphs_btns = new QButtonGroup();
    graphs_btns->setExclusive(true);
    graphs_btns->addButton(ui->btn_map,     0);
    graphs_btns->addButton(ui->btn_kurs,    1);
    graphs_btns->addButton(ui->btn_marsh,   2);
    graphs_btns->addButton(ui->btn_depth,   3);

    for (int i = 0; i < graphs_btns->buttons().size(); i++)
    {
        graphs_btns->button(i)->setCheckable(true);
    }

    graphs_btns->button(0)->setChecked(true); //Кнопка "карта"
    ui->stacked_graphs->setCurrentIndex(0); // Страница "Карта"

    connect(graphs_btns, static_cast<void (QButtonGroup:: *)(int)>(&QButtonGroup::buttonClicked), [=](int id)
    {
       ui->stacked_graphs->setCurrentIndex(id);
    });

///-------------------------------------------
///Настройка главных страниц и кнопок (Инструктор, Планировщик и Контроль)
///-------------------------------------------

    main_btns = new QButtonGroup();
    main_btns->setExclusive(true);
    main_btns->addButton(ui->btn_instr,         0);
    main_btns->addButton(ui->btn_planner,       1);
    main_btns->addButton(ui->btn_control,       2);
    main_btns->addButton(ui->btn_exchange,      3);

    for (int i = 0; i < main_btns->buttons().size(); i++)
    {
        main_btns->button(i)->setCheckable(true);
    }

    main_btns->button(0)->setChecked(true); //Кнопка "инструктор"
    ui->stacked_main->setCurrentIndex(0); // Страница "Инструктор"

    connect(main_btns, static_cast<void (QButtonGroup:: *)(int)>(&QButtonGroup::buttonClicked), [=](int id)
    {
       ui->stacked_main->setCurrentIndex(id);
    });

    ui->btn_stop->setDisabled(true);

///--------------------------------------------------
///Обмен и связанные с ним кнопки
///--------------------------------------------------

    ConfigList << "../Simulator_v4/config/protocols.conf" << "sim" << "initial";
    config = new ConfigData(ConfigList.at(0)); //считаем количество строк в файле
    exch_str = new Exchange_structures();

    //--------------------------------------------------
    //Основной обмен с Unity
    //--------------------------------------------------
    sim = new Protocol_Simulator(config, ConfigList.at(1)); // основной обмен с симулятором

    //--------------------------------------------------
    //Получаем пришедшие данные в общую структуру exch_str
    //--------------------------------------------------
    connect(sim, &Protocol_Simulator::set_data, [this]
    {
        if (sim->received != sim->preceived)
        {
            memcpy(&exch_str->from_data.params, &sim->from_data.params, sizeof(FromSimulator_data));

            ui->lbl_unity->setStyleSheet("background-color: rgb(0,255,0,200)");

            sim->preceived = sim->received;
        }
        else
        {
            ui->lbl_unity->setStyleSheet("background-color: rgb(255,0,0,200)");
        }
        ui->lbl_lost->setText(QString::number((long int)sim->lost_message_count));
        ui->lbl_received->setText(QString::number((long int)sim->received));
    });

    //--------------------------------------------------
    //Передаем данные для отправки из общей структуры exch_str
    //--------------------------------------------------
    connect(sim, &Protocol_Simulator::get_data, [this]
    {
        memcpy(&sim->to_data.voltage, &exch_str->to_data.voltage, sizeof(ToSimulator_data));
    });

    //--------------------------------------------------
    //Начальный обмен с Unity (обмен с инструктором)
    //--------------------------------------------------
    instr = new Protocol_Instructor(config, ConfigList.at(2)); // инициализация параметров сцены

    //--------------------------------------------------
    //По нажатию на кнопку "Задать сцену и начать" начинаем обмен
    //--------------------------------------------------
    connect(ui->btn_set_scene, &QPushButton::clicked, [this]
    {
        instr->to_data.anpa.X = ui->le_anpa_X->text().toFloat();
        instr->to_data.anpa.Y = ui->le_anpa_Y->text().toFloat();
        instr->to_data.anpa.Z = ui->le_anpa_Z->text().toFloat();

        instr->to_data.flow.direction = ui->cb_frow_dir->currentIndex();
        instr->to_data.flow.value = ui->sl_flow_val->value();
        instr->timer->start(int(1000./instr->frequency));

        ui->gb_anpa->setDisabled(true);
        ui->gb_flow->setDisabled(true);
        ui->btn_set_scene->setDisabled(true);
        ui->btn_stop->setDisabled(false);

        ui->stacked_main->setCurrentIndex(2);
        main_btns->button(2)->setChecked(true);
    });

    //--------------------------------------------------
    //По нажатию на кнопку "Задать положение" размещаем аппарат на карте
    //--------------------------------------------------
    connect(ui->btn_set_anpa, &QPushButton::pressed, [this]
    {
        ui->map->set_anpa_position(
                    ui->le_anpa_X->text().toFloat(),
                    ui->le_anpa_Y->text().toFloat(),
                    ui->le_anpa_Z->text().toFloat(),
                    exch_str->from_data.params.Psi);
    });

    //--------------------------------------------------
    //По нажатию на кнопку "Задать сцену и начать" начинаем обмен
    //--------------------------------------------------
    connect(instr, &Protocol_Instructor::start_main_exchange, [this]
    {
        if (instr->received != instr->preceived)
        {
            instr->timer->stop();       //Останавливаем таймер для начальной посылки

            sim->timer->start(int(1000./sim->frequency)); //Стартуем таймер для основного обмена
            id_10Hz = startTimer(100); //Стуртуем таймер на обновление карты,компаса и гирогоризонта
            id_1Hz = startTimer(1000); //Стуртуем таймер для обновления графиков

            ui->lbl_instr->setStyleSheet("background-color: rgb(0,255,0,200)");

            instr->preceived = instr->received;
        }
        else
        {
            ui->lbl_instr->setStyleSheet("background-color: rgb(255,0,0,200)");
        }
        ui->lbl_lost_instr->setText(QString::number((long int)instr->lost_message_count));
        ui->lbl_received_instr->setText(QString::number((long int)instr->received));

    });

    //--------------------------------------------------
    //По нажатию на кнопку "Остановить сцену" обмены прекращатся
    //--------------------------------------------------
    connect(ui->btn_stop, &QPushButton::clicked, [this]
    {
        instr->timer->stop(); //Вдруг решим остановить, когда работает начальный обмен
        sim->timer->stop();
        killTimer(id_10Hz); //Останавливаем таймер на обновление карты,компаса и гирогоризонта
        killTimer(id_1Hz); //Останавливаем таймер для обновления графиков

        ui->btn_stop->setDisabled(true);

        ui->gb_anpa->setDisabled(false);
        ui->gb_flow->setDisabled(false);
        ui->btn_set_scene->setDisabled(false);

        ui->stacked_main->setCurrentIndex(0);
        main_btns->button(0)->setChecked(true);
        ui->map->rovTrajectory->clear();
        superImportantVariable = false;
    });

    //--------------------------------------------------
    //Две кнопки для переключения между формами для обмена
    //--------------------------------------------------
    exch_btns = new QButtonGroup();
    exch_btns->setExclusive(true);
    exch_btns->addButton(ui->btn_instr_exchange,        0);
    exch_btns->addButton(ui->btn_main_exchange,         1);

    for (int i = 0; i < exch_btns->buttons().size(); i++)
    {
        exch_btns->button(i)->setCheckable(true);
    }

    connect(exch_btns, static_cast<void (QButtonGroup:: *)(int)>(&QButtonGroup::buttonClicked), [=](int id)
    {
       ui->stacked_exchange->setCurrentIndex(id);
    });

    exch_btns->button(0)->setChecked(true);
    ui->stacked_exchange->setCurrentIndex(0);

    //--------------------------------------------------
    //Заполняем IP, порты графических форм для обмена
    //--------------------------------------------------
    config -> getValue(ConfigList.at(1));
    ui->lbl_sender_ip->setText(QHostAddress(QHostAddress::LocalHost).toString());
    ui->lbl_sender_port->setText(QString::number(config -> data.sender_port));
    ui->lbl_receiver_port->setText(QString::number(config -> data.receiver_port));
    ui->lbl_received->setText(QString::number(0));
    ui->lbl_lost->setText(QString::number(0));
    ui->lbl_unity->setStyleSheet("background-color: rgb(0,0,0,150)");

    config -> getValue(ConfigList.at(2));
    ui->lbl_sender_ip_instr->setText(QHostAddress(QHostAddress::LocalHost).toString());
    ui->lbl_sender_port_instr->setText(QString::number(config -> data.sender_port));
    ui->lbl_receiver_port_instr->setText(QString::number(config -> data.receiver_port));
    ui->lbl_received_instr->setText(QString::number(0));
    ui->lbl_lost_instr->setText(QString::number(0));
    ui->lbl_instr->setStyleSheet("background-color: rgb(0,0,0,150)");

///--------------------------------------------------
///Компасс, гирогоризонт, высота, отстояние и ВМА
///--------------------------------------------------
    compass = new Compass(exch_str);
    ui->hlay_Compass->addWidget(compass);

    hyrohorizont = new HyroHorizont(exch_str);
    ui->hlay_HyroHorizont->addWidget(hyrohorizont);

    vma = new VMA(exch_str);
    ui->hlay_VMA->addWidget(vma);

    altitude = new Altitude(exch_str);
    ui->hlay_Altitude->addWidget(altitude);

///--------------------------------------------------
///Связь с формой для теста интерфейса (debug_form)
///--------------------------------------------------

    debug = new Debug_Form();
    debug->show();

    //Тестовое значение напряжения для курса
    connect(debug, &Debug_Form::change_Kurs, [=](float value)
    {
        KURS->U_kurs = value;
    });

    //Тестовое значение напряжения для марша
    connect(debug, &Debug_Form::change_Marsh, [=](float value)
    {
        MARSH->U_marsh = value;
    });

    //Тестовое значение напряжения для глубины
    connect(debug, &Debug_Form::change_Depth, [=](float value)
    {
        DEPTH->U_depth = value;
    });

    //Курс текущий
    connect(debug, &Debug_Form::setYaw, [=](int id)
    {
        compass->setYaw(id);
        ui->map->set_anpa_position(
                    ui->le_anpa_X->text().toFloat(),
                    ui->le_anpa_Y->text().toFloat(),
                    ui->le_anpa_Z->text().toFloat(),
                    id);
    });

    //Курс задающий
    connect(debug, &Debug_Form::setYawDes, compass, &Compass::setYawDes);

    //Напряжения на движиели
    connect(debug, &Debug_Form::setU1, vma, &VMA::setU1);
    connect(debug, &Debug_Form::setU2, vma, &VMA::setU2);
    connect(debug, &Debug_Form::setU3, vma, &VMA::setU3);
    connect(debug, &Debug_Form::setU4, vma, &VMA::setU4);
    connect(debug, &Debug_Form::setU5, vma, &VMA::setU5);

    //Инитация неисправностей движителей
    connect(debug, &Debug_Form::setFail_U1, vma, &VMA::setFail_U1);
    connect(debug, &Debug_Form::setFail_U2, vma, &VMA::setFail_U2);
    connect(debug, &Debug_Form::setFail_U3, vma, &VMA::setFail_U3);
    connect(debug, &Debug_Form::setFail_U4, vma, &VMA::setFail_U4);
    connect(debug, &Debug_Form::setFail_U5, vma, &VMA::setFail_U5);

    //Дифферент текущий
    connect(debug, &Debug_Form::setPitch, hyrohorizont, &HyroHorizont::setPitch);
//    //Глубина текущая
//    connect(debug, &Debug_Form::setDepth, hyrohorizont, &HyroHorizont::setDepth);
    //Отстояние текущее
    connect(debug, &Debug_Form::setAltitude, altitude, &Altitude::setAltitude);
}

//--------------------------------------------------

MainWidget::~MainWidget()
{
    delete ui;
    delete sim;
    delete instr;
    delete debug;
    delete MARSH;
    delete DEPTH;
    delete KURS;
    delete compass;
    delete hyrohorizont;
    delete altitude;
    delete vma;
}

//--------------------------------------------------

void MainWidget::BFS()
{
    /// Ux = U1+U2

    /// Uy = U5+U6+U7+U8
    /// Uz = U3+U4
    /// Upsi = U3-U4-U1+U2
    /// Utetta = -U5+U6-U7+U8
    /// Ugamma = -U7-U8+U6+U5

    /// Блок формирования сигналов на движители
    /// Упрощенный вариант

     //Для высоты
    exch_str->to_data.voltage[4].U = saturation(exch_str->target_params.depth_U,10);

 }

 //-------------------------------------------------------------------------------------

 float MainWidget::saturation(float input, float max)
 {
    if (fabs(input)>= max)
        return (input < 0 ? max : -max);
    else return input;
 }

//--------------------------------------------------

void MainWidget::timerEvent(QTimerEvent *e)
{
    //Дата и время
    if (e->timerId() == timerWidgetID)
    {
        *date = QDate::currentDate();
        ui->lblData->setText(date->toString("dddd dd/MM/yy"));

        *time = QTime::currentTime();
        ui->lblTime->setText(time->toString("hh:mm:ss.zzz"));
    }

    //Основление компаса, гирогоризонта и карты
    if (e->timerId() == id_10Hz)    ///--- 10 Гц
    {
        DEPTH->main_block(); //Расчет напряжения по глубине
        BFS(); //Формируем напряжения на каждый движитель


        //Гордость отечественного костылестроения
        if (ui->le_anpa_X->text().toFloat() == exch_str->from_data.params.X
            && ui->le_anpa_Y->text().toFloat() == exch_str->from_data.params.Y
            && ui->le_anpa_Z->text().toFloat() == exch_str->from_data.params.Z) {
            superImportantVariable = true;
        }

        if (superImportantVariable)
        {
            ui->map->set_anpa_position(
                        exch_str->from_data.params.X,
                        exch_str->from_data.params.Y,
                        exch_str->from_data.params.Z,
                        exch_str->from_data.params.Psi);
        }

        compass->update();
        hyrohorizont->update();
        altitude->update();
        vma->update();
    }

    //Графики курса, марша и глубины
    if (e->timerId() == id_1Hz)    ///--- 1 Гц
    {
        ui->chartFormDepth->setYT(exch_str->target_params.depth_U, operatingTime->elapsed());
        ui->chartFormMarch->setYT(MARSH->U_marsh, operatingTime->elapsed());
        ui->chartFormKurs->setYT(KURS->U_kurs, operatingTime->elapsed());
    }
    else
    {
        QWidget::timerEvent(e);
    }
}

//--------------------------------------------------

//Обработка нажатых кнопок для карты
void MainWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W)
    {
        ui->map->W_key();
    }
    if (event->key() == Qt::Key_S)
    {
        ui->map->S_key();
    }
    if (event->key() == Qt::Key_A)
    {
        ui->map->A_key();
    }
    if (event->key() == Qt::Key_D)
    {
        ui->map->D_key();
    }
    if (event->key() == Qt::Key_R)
    {
        ui->map->R_key();
    }
    if (event->key() == Qt::Key_Minus)
    {
        ui->map->Minus_key();
    }
    if (event->key() == Qt::Key_Plus)
    {
        ui->map->Plus_key();
    }
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        ui->map->set_anpa_position(
                    ui->le_anpa_X->text().toFloat(),
                    ui->le_anpa_Y->text().toFloat(),
                    ui->le_anpa_Z->text().toFloat(),
                    exch_str->from_data.params.Psi);
    }
}

