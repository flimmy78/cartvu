#include "setting.h"
#include "ui_setting.h"




extern  serialMode *global_serialMode;
extern global_config *global_conf_sys;
extern bool global_serial_flag;

extern read_sys *global_rsys;
extern light *global_lgt;

extern QLabel *sensor_label[LABEL_NUM];

extern login *global_log;


extern void initial_machine();

extern char * get_ip(char * ipaddr);

setting::setting(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::setting)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //camera = cam;
    telnet_flag = true;

    setting_init();
}

setting::~setting()
{
    qDebug() << "delete setting ui";
    delete ui;


}

void setting::changeEvent(QEvent *e)
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


void setting::setting_init()
{
    QString tmp;
    //int pos;


    connect(global_rsys, SIGNAL(show_hide_button(bool)), this, SLOT(show_recover_button(bool)));

    /*
    bzero(buf, BUF_SIZE);
    snprintf(buf, BUF_SIZE, "ifconfig|grep 'inet addr:' | sed -n 1p | cut -d : -f 2");
    //snprintf(buf, BUF_SIZE, "ifconfig|grep 'inet addr:' | sed -n 1p | cut -d : -f 2|cut -b 1-14");
    get_ip_fun(buf);
    */

    get_ip(buf);
    qDebug("now the ip is %s", buf);
    strcpy(buf, &buf[3]);
    tmp = QString(buf);
    /*
    pos = tmp.indexOf("  ");
    if (pos >= 0) {
        tmp = tmp.left(pos);
    } else {
       qDebug() << "error ip";
    }
    */
    ui->show_text->setText(tmp);
    ui->show_label->setText("information:");
    ui->setting_hide_button->setHidden(true);


#if 0
    bzero(buf, BUF_SIZE);
    snprintf(buf, BUF_SIZE, "cat %s", REBOOT_TIME);
    show_reboot_time(buf);
#else
    show_reboot_time(REBOOT_TIME);
#endif

}

#if 0

void setting::show_reboot_time(const char *cmd)
{
    FILE *fp;
    char buffer[BUF_SIZE] = {0};

    fp = popen(cmd, "r");
    if (fp == NULL) {
        qDebug() << "popen  fail ans die here";
        perror("show reboot time fail here");
        return;
        //while(1);
    }
    ui->show_label->append("the machine reboot time is below:");
    while(fgets(buffer, sizeof(buffer), fp) !=NULL) {
        printf("%s", buffer);
        buffer[strlen(buffer) - 1] = '\0';
        ui->show_label->append(QString(buffer));
        bzero(buffer, BUF_SIZE);
    }
    printf("\n");
    pclose(fp);


}
#else
void setting::show_reboot_time(const char *arg)
{
    char buf[BUF_SIZE] = {0};
    FILE *fp;


    fp = fopen(arg, "r");
    if (fp == NULL) {
        printf("open %s fail ", arg);
        return;
    }

    while (fgets(buf,BUF_SIZE, fp)) {
        printf("%s", buf);
        buf[strlen(buf) - 1] = '\0';
        ui->show_label->append(QString(buf));
    }
    fclose(fp);

}
#endif


void setting::get_ip_fun(const char *cmd)
{
    FILE *fp;
    char buffer[BUF_SIZE] = {0};

    fp = popen(cmd, "r");
    if (fp == NULL) {
        qDebug() << "popen  fail ans die here";
        perror("get ip fail!!!");
        //while(1);
    }

    while(fgets(buffer, sizeof(buffer), fp) !=NULL) {
        printf("%s", buffer);
    }
    strcpy((char*)cmd, (const char*)buffer);
    printf("\n");
    pclose(fp);

}
/*
void setting::on_serial_button_clicked()
{

    if (global_serial_flag == false) {
        global_serial_flag = true;
        global_serialMode = new serialMode(camera, "");
        qDebug() << "false";
    } else {
        global_serialMode->global_cashier_label->setText("");
        global_serialMode->cashier_timer.start(global_conf_sys->sys_other.cashier_timeout*1000);
        qDebug() << "true";
    }
    global_serialMode->show();
    //serialMode *a = new serialMode(camera, "");
    //a->show();
    this->close();
    delete this;
}
*/
void setting::on_return_button_clicked()
{

    //global_serialMode->global_cashier_label->setText("setting?");
    global_serialMode->cashier_timer.start(global_conf_sys->sys_other.cashier_timeout*1000);

    global_serialMode->show();


    if (global_serialMode->show_sensor_status_hide == false) {
        global_log->mode_timer.stop();
        qDebug() << "not start the big screen stop the mode_timer ok";
    } else {
        qDebug() << "start the mode_timer";
        global_log->mode_timer.start(MODE_TIMER*1000);
    }

    this->close();
    delete this;

}





void setting::on_factory_button_clicked()
{
    ui->show_label->append("will delete the /etc/eth0-setting\nand initialize the machine after 2 sec");
    initial_machine();
    recordLog(1, 22, (char*)"initial machine due to factory clicked!");
    //my_system("/bin/date -R >> /var/log/eth0-setting.log");
    //my_system("echo 'delete eth0-setting due to factory clicked' >>/var/log/eth0-setting.log");
    my_system("/sbin/reboot");

}











void setting::on_reset_button_clicked()
{
    ui->show_label->setText("will reset the machine");
    qDebug() << "will reset the machine";
    sleep(2);
    my_system("/sbin/reboot");

}

void setting::on_telnet_button_clicked()
{
    if (telnet_flag == true) {
        telnet_flag = false;
        my_system("/usr/sbin/telnetd -l /bin/login");
        my_system("/usr/bin/vsftpd &");
        qDebug() << "start the telnet ok!";
        ui->show_label->append("start the telnet ok!");
        ui->show_label->append("start the vsftpd ok!");
    } else {
        telnet_flag = true;
        my_system("/usr/bin/killall telnetd");
        my_system("/usr/bin/killall vsftpd");
        qDebug() << "stop the telnet ok!";
        ui->show_label->append("stop the telnet ok!");
        ui->show_label->append("stop the vsftpd ok!");
    }
}
/*
void setting::on_cam_type_button_clicked()
{

}
*/

void setting::on_setting_hide_button_clicked()
{

    qDebug() << "hide the setting big button";
    ui->setting_hide_button->setHidden(true);
    global_rsys->openning_light();
    global_lgt->light_adjust();
}

void setting::show_recover_button(bool flag)
{
    if (flag == true) {
        qDebug() << "set the setting button bak";
    } else {

        qDebug() << "set the setting button front" ;
    }
    ui->setting_hide_button->setHidden(flag);

}


void setting::on_sensor_show_button_clicked()
{
    int i = 0;

    if (global_serialMode->show_sensor_status_hide == true) {
        global_serialMode->show_sensor_status_hide = false;
        qDebug() << "show the sensor status!";
        //ui->show_label->setText("show the sensor status! ok!");
        ui->show_label->append("show the sensor status! ok!");


    } else {
        global_serialMode->show_sensor_status_hide = true;
        qDebug() << "hide the sensor status!";
        ui->show_label->append("hide the sensor status! ok!");
    }
    for (i = 0; i < LABEL_NUM; i++) {
        sensor_label[i]->setHidden(global_serialMode->show_sensor_status_hide);
    }
}




extern QApplication *global_app;
void setting::on_bt_config_setttings_clicked()
{

    config_setting *a = new config_setting();

    MyInputPannelContext *input=new MyInputPannelContext;
    global_app->setInputContext(input);

    input->widget = NULL;
    connect(a, SIGNAL(sendChar(QChar)), input, SLOT(charSlot(QChar)));
    connect(a,SIGNAL(sendInt(int)),input,SLOT(intSlot(int)));
    //connect(input, SIGNAL(now_line_string(QString)), a, SLOT(update_now_string(QString)));
    /**/

    a->show();
    this->close();

    qDebug() << "delete setting ui in config setting";
    delete this;


}
