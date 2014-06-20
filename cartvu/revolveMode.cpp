#include "revolveMode.h"
#include "ui_revolveMode.h"
#include "setting.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>


extern global_config *global_conf_sys;

extern sensor_c *global_sensor;

extern  serialMode *global_serialMode;

extern read_sys *global_rsys;
extern light *global_lgt;

int now_pic_nu = 0;

extern login *global_log;

extern int global_cashier_null;

revolveMode::revolveMode( QWidget *parent) :
    QDialog(parent),
    ui(new Ui::revolveMode)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //camera = cam;

    connect(&start_timer, SIGNAL(timeout()), this, SLOT(init_mode()));

    //revolve_pic_start();

    connect(global_sensor, SIGNAL(return_to_serial_mode()), this, SLOT(return_serial_mode()));

    bzero(pic, PIC_SIZE);
//初始化配置文件的信息
    switch_time = global_conf_sys->sys_standby.revolve_period;
    range_start = global_conf_sys->sys_standby.revolve_range.start;
    range_stop = global_conf_sys->sys_standby.revolve_range.end;
    now_pic_nu = range_start;
    //ms

    connect(&internalTimer, SIGNAL(timeout()), this, SLOT(revolve_pic_start()));

}




revolveMode::~revolveMode()
{
    qDebug() << "delete the revolve Mode??";
    //delete ui;
}

void revolveMode::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void revolveMode::return_serial_mode()
{
    //close the current revolve
    this->internalTimer.stop();


    //show serial
    global_serialMode->show();
    global_serialMode->global_cashier_label->setText("!!alarm!!");
    global_serialMode->cashier_timer.stop();
    global_serialMode->cashier_timer.start(global_conf_sys->sys_other.cashier_timeout*1000);

    //close stand screen
    this->close();
}
void revolveMode::init_mode()
{
    start_timer.stop();
    switch (standby_mode) {
    case CARTVU_MODE:
        cartvu_mode_init();
        break;
    case SELFDF_MODE:
        self_init();
        break;
    case REVOLVE_MODE:
        time_pic_init();
        break;
    default:
        time_pic_init();
        break;
    }

}


void revolveMode::cartvu_mode_init(void)
{
    bool ret = false;
    ret = cartvu_pic.load(CARTVU_MODE_PIC);
    if (ret == false) {
        qDebug() << "load cartvu mode pic fail";
        recordLog(15, 27, (char*)"load cartvu mode pic fail");
        return;
    }
    ui->revolve_label->setPixmap(cartvu_pic);

    set_button_back();


    ui->revolve_label->show();

}

void revolveMode::set_button_back(void)
{
    if (global_cashier_null == 1) {
        ui->log_in_out_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/login.png);"));
        printf("cahser num is null here !!!!!!!!!!!!!\n");
    } else {
        ui->log_in_out_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/logout.png);"));
        printf("cahser num is not null here !!!!!!!!!!!!!\n");
    }
}

void revolveMode::self_init(void)
{
    bool ret = false;
    ret = self_pic.load(SELF_MODE_PIC);
    if (ret == false) {
        qDebug() << "load self mode pic fail";
        recordLog(15, 27, (char*)"load self mode pic fail");
        return;
    }
    ui->revolve_label->setPixmap(self_pic);

    set_button_back();


    ui->revolve_label->show();
}

/*
void revolveMode::on_return_button_clicked()
{
    revolve_flag = false;
    setting *a = new setting(camera);
    a->show();
    this->close();
    internalTimer.stop();
    delete this;
}
*/

void revolveMode::time_pic_init()
{


    internalTimer.start(0);
}

void revolveMode::revolve_pic_start()
{
    bool ret = false;
    internalTimer.stop();



    ui->revolve_label->setFocus();
    ui->return_button->clearFocus();

    //internalTimer.setInterval(switch_time * 1000);
    internalTimer.start(switch_time * 1000);
    now_pic_nu++;
    if (now_pic_nu >= (range_stop + 1)) {
        now_pic_nu = range_start;
    }


    snprintf(pic, PIC_SIZE, "%s%02d.jpg", REVOLVE_PIC_DIR, now_pic_nu);
    //qDebug("in big String is %s", pic);
    ret = re_pic.load(pic);
    if (ret == false) {
        qDebug() << "load pic fail";
        qDebug() << pic;
        recordLog(15, 27, (char*)"load pic fail");
        return;
    }
    //re_pic.load(REVOLVE_PIC_DIR"01.jpg");
    // re_pic.load("/cartvu/proc/cartvu/revolve_pic/01.jpg");
    //re_pic.load("../cartvu/revolve_pic/01.jpg");
    //system("pwd");
    ui->revolve_label->setPixmap(re_pic);
    ui->revolve_label->show();


}

void revolveMode::on_return_button_clicked()
{
    qDebug() << "click the revolve button";
    global_rsys->openning_light();
    global_lgt->light_adjust();

    internalTimer.stop();
    now_pic_nu--;
    if (now_pic_nu < global_serialMode->range_start) {
        now_pic_nu = range_stop;
    }

    global_serialMode->now_chose_screen();
    global_serialMode->show();


    if (global_serialMode->show_sensor_status_hide == false) {
        global_log->mode_timer.stop();
        qDebug() << "not start standby mode to big screen";
    } else {
        qDebug() << "start the mode_timer to big screen";
        global_log->mode_timer.start(MODE_TIMER*1000);
    }
    this->close();
}



void revolveMode::on_log_in_out_button_clicked()
{
    // char buf[SOUND_BUF];

    //bzero(buf, SOUND_BUF);
   // snprintf(buf, SOUND_BUF, "%s %s%s.wav", AUDIO_APP, CLICK_SOUND, COMMON_SOUND);
   // my_system(buf);

    // enter logout here
    global_serialMode->on_logout_button_clicked();

    qDebug() << "click the revolve button";
    global_rsys->openning_light();
    global_lgt->light_adjust();

    internalTimer.stop();
    now_pic_nu--;
    if (now_pic_nu < global_serialMode->range_start) {
        now_pic_nu = range_stop;
    }



    this->close();
    //this->close;


}
