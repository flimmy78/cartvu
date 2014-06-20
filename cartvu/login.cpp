#include "login.h"
#include "ui_login.h"
#include "setting.h"

#include "serialMode.h"

extern QString global_lane_no;
//extern QString global_kings_name;
//extern unsigned int global_cashier_timeout;

extern  serialMode *global_serialMode;


extern global_config *global_conf_sys;
extern bool global_serial_flag;

extern bool global_construct_flag;

extern read_sys *global_rsys;
extern revolveMode *global_revo;

extern char status[STATUS_SIZE];

extern bool global_read_config_ok;

extern light *global_lgt;

extern int now_pic_nu;

extern ftpput *global_ftp;

extern bool network_flag;


extern QMutex global_passwd_lock;

extern watchdog *global_wdg;

char global_cashier_nu[CASHIER_SIZE] = {0};



extern bool global_network_enter_flag;
extern bool global_mac_log_ok_flag;

extern void initial_machine();


int global_cashier_null = 0;

#define INFO_TEXT_SIZE     2048
struct send_info {
    char cashier[50];
    int not_confirmed;
    char request[50];
    char info_text[INFO_TEXT_SIZE];
    int lane;
    int flag;
};

struct send_info  info;


QLineEdit *global_lane_edit;

login::login(camThread *cam,QWidget *parent) :
        QDialog(parent),
        ui(new Ui::login)
{
    QString a;
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowFlags(Qt::WindowTitleHint);


    http_client = new client();
    info_client = new client();
    global_serial_flag = false;

    version_label = ui->version_label;


    qDebug() << "construct login ui";


    //ui->lineEdit->setStyleSheet(QString::fromUtf8("font-color: rgb(255, 153, 51);"));
    //    QLineEdit *lineEdit = ui->lineEdit;
    //    QPalette palette = lineEdit->palette();
    //
    //    palette.setColor(QPalette::Text,QColor(255,153,51));
    //    lineEdit->setPalette(palette);

    ui->lineEdit->setText("");

    global_lane_edit = ui->lineEdit;

    a = ui->lineEdit->text();
    inputstring = a;
    count = a.length();
    login_init();
    camera = cam;




    connect(&global_status, SIGNAL(timeout()), this, SLOT(send_status_to_s()));



    //connect(global_rsys, SIGNAL(read_config_ok()), this, SLOT(hide_big_button()));
    connect(global_rsys, SIGNAL(show_hide_button(bool)), this,SLOT(show_big_button(bool)));

    // start when the config.sys is ok  start in the read_sys.cpp
    //global_status.start(GLOBAL_TIMER*1000);


    connect(&close_box, SIGNAL(timeout()), this, SLOT(close_box_slot()));




}




void login::close_box_slot()
{




    char post_buf[BUF_SIZE];
    char buf[BUF_SIZE];
    QString cmd;


    this->sendinfo_timeout = true;
    close_box.stop();

    bzero(buf, BUF_SIZE);
    sprintf(buf, "lane=%s&cashier=%s&request=%s", global_lane_no.toLatin1().data(), global_cashier_nu, "Timeout");
    snprintf(post_buf, BUF_SIZE, "POST /cgi-bin/SendInfo.cgi HTTP/1.1\r\nContent-Length:%d\n\n%s\r\n\r\n",
             strlen(buf), buf);
    cmd = QString(post_buf);
    qDebug() << cmd;
    //qDebug() << status;
    http_client->transmit_info(now_local_server, HTTP_PORT, cmd, &rec_string);
    connect(http_client, SIGNAL(emit_receive()), this, SLOT(confirmed2_message()));

    qDebug() << "~~~~~~~~~~~~~~~~~~close the close box here~~~~~~~~~~~~~~~";
    box.close();
}



void login::send_status_to_s()
{
    char buf[BUF_SIZE] = {0};
    char tmp_buf[BUF_SIZE] = {0};

    int send_length;
    QString cmd;


    if (global_mac_log_ok_flag == true) {
        bzero(tmp_buf, BUF_SIZE);
        //E1 S I1 I2 I3 E2 Camera  //s=0000000
        status[STATUS_SENSOR_SIZE]='\0';
        snprintf(tmp_buf, BUF_SIZE, "s=%s",status);
        send_length = strlen(tmp_buf);

        bzero(buf, BUF_SIZE);
        //http://~/status.cgi?s=xxxx
        snprintf(buf, BUF_SIZE, "POST /cgi-bin/status.cgi HTTP/1.1\r\nContent-Length:%d\n\n%s\r\n\r\n",
                 send_length, tmp_buf);
        cmd = QString(buf);
        qDebug() << cmd;
        //qDebug() << status;
        http_client->transmit_info(now_local_server, HTTP_PORT, cmd, &rec_string);
        connect(http_client, SIGNAL(emit_receive()), this, SLOT(judge_ok()));
    } else {
        re_login();
    }

}



void login::judge_ok()
{
    QString tmp_ok;
    static int reset_router = 0;
    int pos;
    char buf_echo[1024] = {0};
    static int send_count = 0;
    static int error_count = 0;

    //http_client->deleteLater();
    disconnect(http_client, SIGNAL(emit_receive()), this, SLOT(judge_ok()));

    //delete http_client;


    pos = rec_string.trimmed().toLower().indexOf("connection: close");
    if (pos >= 0) {
        rec_string = rec_string.right(rec_string.length() - pos - 17 - 3);
    }

    rec_string = rec_string.trimmed().toLower();
    qDebug() << rec_string;
    pos = rec_string.indexOf("ok");
    if (pos >= 0) {
        // clear the count;
        reset_router = 0;
        send_count = 0;
        if (global_mac_log_ok_flag == false) {
            global_mac_log_ok_flag = true;
            qDebug() << "re log in is ok!";
            qDebug() << "set the global_mac_log_ok_flag to false and interval to 10 sec";
            //global_status.start(GLOBAL_TIMER*1000);
        } else {

            qDebug() << "send to local server is ok!";
        }

        if (global_network_enter_flag == false) {
            //global_wdg->set_watdog_time();

            qDebug() << "\n!!!!!!!!!!!!!!!!!!restart the cartvu here due to the network is ok!!!!!!!!!\n";
            recordLog(1, 2, (char*)"restart the cartvu here due to the network is ok!");
            //my_system("/etc/init.d/chose-start.sh");
            my_system("/sbin/reboot");
            //my_system("/etc/init.d/chose-start.sh");
            //qDebug() << "use system to start";
            //system("/etc/init.d/chose-start.sh");

            //my_system("/etc/init.d/ifconfig-eth0-setting.sh &");

            //global_wdg->set_watdog_time();
            qDebug() << "restart the cartvu here due to the network is ok";
            return;
        }


        if (rec_string.contains("ftppwd")) {
            QString  tmp_passwd;
            int start_pos;
            QString receive;
            QString left_string;
            QString right_string;

            start_pos = rec_string.indexOf("ok!");
            if (start_pos >= 0) {
                receive = rec_string.right(rec_string.length() - start_pos -3).trimmed().toLower();
                qDebug() << receive;
                //////////////////////////
                //ftppwd=h5s6q7w1&userpwd=car1998
                while ((start_pos = receive.indexOf("&")) >= 0) {
                    tmp_passwd = receive.left(start_pos).trimmed();
                    receive = receive.right(receive.length() - start_pos -1).trimmed();
                    // ftppwd=h5s6q7w1
                    pos = tmp_passwd.indexOf("=");
                    if (pos >= 0) {
                        left_string = tmp_passwd.left(pos).trimmed().toLower();
                        right_string = tmp_passwd.right(tmp_passwd.length() - pos - 1).trimmed().toLower();
                        if (left_string.compare("ftppwd") == 0) {
                            global_passwd_lock.lock();

                            bzero(global_rsys->ftp_passwd, FTP_SIZE);
                            snprintf(global_rsys->ftp_passwd, FTP_SIZE, "%s", right_string.toLatin1().data());
                            qDebug("ftp passwd is %s ", global_rsys->ftp_passwd);
                            global_passwd_lock.unlock();

                            network_flag = true;

                            recordLog(1, 2, (char*)"relog the local server is ok!");
                        } else if (left_string.compare("userpwd") == 0) {
                            bzero(global_rsys->user_passwd, FTP_SIZE);
                            snprintf(global_rsys->user_passwd, FTP_SIZE, "%s", right_string.toLatin1().data());
                            qDebug("user passwd is %s ", global_rsys->user_passwd);
                        }
                    }
                }
                ///////////////
            }

        }

    } else {// restart reset  enable
        //////////////////////////////////
        pos = rec_string.indexOf("restart");
        if (pos >= 0) {
            char buf_tmp[BUF_SIZE] = {0};
            snprintf(buf_tmp, BUF_SIZE, "/bin/echo 'receive restart from the localserver' >> %s", REBOOT_TIME);
            //my_system("/bin/echo 'receive restart from the localserver' >> /etc/rebootTime");
            my_system(buf_tmp);
            recordLog(1, 2, (char*)"receive restart from the localserver");
            my_system("/sbin/reboot");
        } else {

            pos = rec_string.indexOf("reset");
            if (pos >= 0) {

                initial_machine();
                recordLog(1, 22, (char*)"initial machine due to receive reset here !");
                //my_system("/bin/date -R >> /var/log/eth0-setting.log");
                //my_system("echo 'delete eth0-setting due to receive reset' >>/var/log/eth0-setting.log");
                my_system("/sbin/reboot");

            } else {

                pos = rec_string.indexOf("enable");
                if (pos >= 0) {
                    my_system("/usr/sbin/telnetd -l /bin/login");
                    my_system("/usr/bin/vsftpd &");

                    recordLog(1, 2, (char*)"receive enable telnetd vsftpd  from the localserver");
                    qDebug() << "start the telnet ok!";
                } else {




                    //global_status.start(LOG_INTERVAL*1000);
                    qDebug() << "!!!!cannot connect to local server!!!";
                    qDebug() << rec_string;
                    qDebug() << "try to re log in!";

                    reset_router++;
                    qDebug() << "now the reset_route count is " << reset_router;
                    if (reset_router > ROUTER_COUNT) {
                        my_system("/test/set_router");

                        my_system("/test/set_route");
                        my_system("usr/bin/killall udhcpc");
                        my_system("/sbin/udhcpc &");
                        qDebug() << "reset the router and wait 50sec to reset the router";
                        reset_router = 0;
                    }

                    send_count++;
                    if (send_count >= 3) {
                        send_count = 0;
                        global_mac_log_ok_flag = false;
                        network_flag = false;


                        pos = rec_string.indexOf("connection: close");
                        if (pos >= 0) {
                            rec_string = rec_string.right(rec_string.length() - pos - 17 - 3);
                            qDebug() << rec_string;
                        }
                        strcpy(buf_echo, rec_string.toLatin1().data());

                        //recordLog(1, 2, (char*)"receive error or time out in sending status");
                        error_count++;
                        if (error_count == 3) {
                            recordLog(1, 2, strcat(buf_echo, " [receive error or time out in sending status]"));
                        }
                        if (error_count >= 120) {
                            error_count = 0;
                        }
                    }
                    //sleep(1);
                    //re_login();
                }
            }

        }
        /////////////////////////
    }

}

void login::re_login()
{

    QString cmd;
    QString tmp;
    char buf[BUF_SIZE];

    //global_status.stop();

    tmp = global_rsys->plain_mac;
    qDebug() << "re_login_mac is " << tmp;

    bzero(buf, BUF_SIZE);
    snprintf(buf, BUF_SIZE, "POST /cgi-bin/login.cgi HTTP/1.1\r\nContent-Length:%d\n\n%s\r\n\r\n",
             tmp.length(), tmp.toLatin1().data());
    cmd = QString(buf);
    qDebug() << cmd;
    http_client->transmit_info(now_local_server, HTTP_PORT, cmd, &rec_string);
    connect(http_client, SIGNAL(emit_receive()), this, SLOT(judge_ok()));
}



//char buf[BUF_SIZE] = {0};
//char tmp_buf[BUF_SIZE] = {0};
//char file_name[BUF_SIZE] = "helloasdf";
//char alarm_time[BUF_ZIZE] = "2013-09-24 15:57";//YYYYMMDDhhmmss
//int confirm = 1;//0 or 1
//char cashier[BUF_SIZE] = "1234";
//char barcode[BUF_SIZE] = "1xxxxxxxxx1";
//int send_length;
//
//
//bzero(tmp_buf, BUF_SIZE);
//snprintf(tmp_buf, BUF_SIZE, "filename=%s&alarmtime=%s&confirm=%d&cashier=%s&barcode=%s",
//         file_name, alarm_time, confirm, cashier, barcode);
//send_length = strlen(tmp_buf);
//
//bzero(buf, BUF_SIZE);
////http://~/image.cgi?filename=xxx&alarmtime=YYYYMMDDhhmmss&confirm=0/1&cashier=xxxx&barcode=xxxxxxxxxxxx
//snprintf(buf, BUF_SIZE, "POST /cgi-bin/image.cgi HTTP/1.1\r\nContent-Length:%d\n\n%s\r\n\r\n",
//        send_length, tmp_buf);
//cmd = QString(buf);
//qDebug() << cmd;
//http_client->transmit_info(QString(global_conf_sys->sys_network.local_server), HTTP_PORT, cmd, &rec_string);
////connect(http_client, SIGNAL(emit_receive()), this, SLOT(info_flash()));




login::~login()
{
    qDebug() << "delete the login ui";
    //delete ui;
}

void login::changeEvent(QEvent *e)
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

void login::login_init()
{
    kings_label = ui->label_kings;



}

void login::setstr(QString s)
{
    ui->lineEdit->setText(s);
}

void login::on_pushButton_1_clicked()
{
    //    QLineEdit *lineEdit = ui->lineEdit;
    //    QPalette palette = lineEdit->palette();
    //
    //    palette.setColor(QPalette::Text,QColor(255,153,51));
    //    lineEdit->setPalette(palette);

    this->inputstring = this->inputstring + "1";
    count++;
    setstr(inputstring);

    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%d.wav", AUDIO_APP, CLICK_SOUND, 1);
    my_system(buf);
    
    global_rsys->log_delay_timer.start(LOG_DELAY_TIME*1000);
}

void login::on_pushButton_2_clicked()
{
    this->inputstring = this->inputstring + "2";
    count++;
    setstr(inputstring);

    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%d.wav", AUDIO_APP, CLICK_SOUND, 2);
    my_system(buf);
    
    global_rsys->log_delay_timer.start(LOG_DELAY_TIME*1000);
}

void login::on_pushButton_3_clicked()
{
    this->inputstring = this->inputstring + "3";
    count++;
    setstr(inputstring);

    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%d.wav", AUDIO_APP, CLICK_SOUND, 3);
    my_system(buf);
    
    global_rsys->log_delay_timer.start(LOG_DELAY_TIME*1000);
}

void login::on_pushButton_4_clicked()
{
    this->inputstring = this->inputstring + "4";
    count++;
    setstr(inputstring);

    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%d.wav", AUDIO_APP, CLICK_SOUND, 4);
    my_system(buf);
    
    global_rsys->log_delay_timer.start(LOG_DELAY_TIME*1000);
}

void login::on_pushButton_5_clicked()
{
    this->inputstring = this->inputstring + "5";
    count++;
    setstr(inputstring);

    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%d.wav", AUDIO_APP, CLICK_SOUND, 5);
    my_system(buf);
    
    global_rsys->log_delay_timer.start(LOG_DELAY_TIME*1000);
}

void login::on_pushButton_6_clicked()
{
    this->inputstring = this->inputstring + "6";
    count++;
    setstr(inputstring);

    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%d.wav", AUDIO_APP, CLICK_SOUND, 6);
    my_system(buf);
    
    global_rsys->log_delay_timer.start(LOG_DELAY_TIME*1000);
}

void login::on_pushButton_7_clicked()
{
    this->inputstring = this->inputstring + "7";
    count++;
    setstr(inputstring);

    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%d.wav", AUDIO_APP, CLICK_SOUND, 7);
    my_system(buf);
    
    global_rsys->log_delay_timer.start(LOG_DELAY_TIME*1000);
}

void login::on_pushButton_8_clicked()
{
    this->inputstring = this->inputstring + "8";
    count++;
    setstr(inputstring);

    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%d.wav", AUDIO_APP, CLICK_SOUND, 8);
    my_system(buf);
    
    global_rsys->log_delay_timer.start(LOG_DELAY_TIME*1000);
}

void login::on_pushButton_9_clicked()
{
    this->inputstring = this->inputstring + "9";
    count++;
    setstr(inputstring);

    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%d.wav", AUDIO_APP, CLICK_SOUND, 9);
    my_system(buf);
    
    global_rsys->log_delay_timer.start(LOG_DELAY_TIME*1000);
}




void login::on_pushButton_0_clicked()
{

    this->inputstring = this->inputstring + "0";
    count++;
    setstr(inputstring);


    // /bin/aplay  /cartvu/sound/0.wav
    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%d.wav", AUDIO_APP, CLICK_SOUND, 0);
    my_system(buf);

    
    global_rsys->log_delay_timer.start(LOG_DELAY_TIME*1000);
}


void login::on_pushButton_ac_clicked()
{

    while (count)
    {
        if (this->count < 0)
        {
            count = 0;
        }
        //  qDebug("count is %d\n", count);
        this->inputstring = this->inputstring.left(--count);
        setstr(inputstring);
    }

    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%s.wav", AUDIO_APP, CLICK_SOUND, COMMON_SOUND);
    my_system(buf);

    global_rsys->log_delay_timer.start(LOG_DELAY_TIME*1000);
}




void login::on_pushButton_del_clicked()
{
    if (this->count < 0)
    {
        count = 0;
    }
    //  qDebug("count is %d\n", count);
    this->inputstring = this->inputstring.left(--count);
    setstr(inputstring);

    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%s.wav", AUDIO_APP, CLICK_SOUND, COMMON_SOUND);
    my_system(buf);

    global_rsys->log_delay_timer.start(LOG_DELAY_TIME*1000);
}

/*
void login::on_exit_button_clicked()
{
    cartvu *a = new cartvu(camera);
    a->show();
    this->close();
    //delete this;
}
*/
void login::on_login_button_clicked()
{
    char post_buf[BUF_SIZE];
    char buf[BUF_SIZE];
    QString cmd;
    //mode_timer.stop();
    //disconnect(&global_rsys->log_delay_timer, SIGNAL(timeout()), this, SLOT(on_login_button_clicked()));
    global_rsys->log_delay_timer.stop();

    QString a;



    //获取当前的cashier的号码
    a = ui->lineEdit->text();
    QByteArray str = a.toAscii();
    char *b = str.data();

    if (*b == '\0') {
        global_cashier_null = 1;
        printf("cahser num is null here !!!!!!!!!!!!!\n");
    } else {
        global_cashier_null = 0;
        printf("cahser num is not null here !!!!!!!!!!!!!\n");
    }

    //qDebug("%s\n", b);
    count = strlen(b);
    //qDebug() << "count is " << count;
    inputstring = a;

    bzero(global_cashier_nu, CASHIER_SIZE);
    strncpy(global_cashier_nu, b, CASHIER_SIZE);

    //in order to show the sensor state
    //system("");

    qDebug("now the mode is %d\n", global_conf_sys->sys_standby.standby_mode);


    if (global_construct_flag == false) {

        global_construct_flag = true;


        qDebug() << "start calculate the Statis!!!";
        //当点击login按钮时启动上传线程
        global_ftp->start(QThread::LowPriority);
        //启动非待机到待机的超时时间
        connect(&mode_timer, SIGNAL(timeout()), this, SLOT(select_mode_start()));

        //confirmButton = box.addButton(tr("Confirmed"), QMessageBox::ActionRole);
        confirmButton = box.addButton(tr("OK"), QMessageBox::ActionRole);
    } else {
        qDebug() << "already new the mode";
    }

    qDebug() << "EEEEEEEEEEEEEEEEEEEEEEEselect mode to show hereEEEEEEEEEEEEEEEEEEEEEEEE";



    mode_timer.start(MODE_TIMER*1000);


    //设置serial界面的cashier num
    global_serialMode->global_cashier_label->setText(inputstring);

    global_serialMode->cashier_timer.stop();
    global_serialMode->cashier_timer.start(global_conf_sys->sys_other.cashier_timeout*1000);


    //qDebug() << "show!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";




    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%s.wav", AUDIO_APP, CLICK_SOUND, COMMON_SOUND);
    my_system(buf);



    global_serialMode->show();
    //如果是revolve模式，则启动serialmoshixia的revolve图片切换
    if (global_conf_sys->sys_standby.standby_mode == REVOLVE_MODE) {
        global_serialMode->revolve_timer.start(global_conf_sys->sys_standby.revolve_period * 1000);
    }


    // lane = 123&cashier=2343&request=Need
    // lane = 123&cashier=2343&request=NoNeed
    bzero(buf, BUF_SIZE);
    sprintf(buf, "lane=%s&cashier=%s&request=%s", global_lane_no.toLatin1().data(), global_cashier_nu, "Need");
    snprintf(post_buf, BUF_SIZE, "POST /cgi-bin/SendInfo.cgi HTTP/1.1\r\nContent-Length:%d\n\n%s\r\n\r\n",
             strlen(buf), buf);
    cmd = QString(post_buf);
    qDebug() << cmd;
    //qDebug() << status;
    info_client->transmit_info(now_local_server, HTTP_PORT, cmd, &rec_string);
    connect(info_client, SIGNAL(emit_receive()), this, SLOT(receive_message()));






    this->close();
}



bool login::write_to_sendinfo(QString rec_string, struct send_info *info)
{
    int pos;
    int start_pos;
    QString receive;
    QString tmp;


    pos = rec_string.indexOf("Connection: close");
    if (pos < 0) {
        qDebug() << "network error here";
        return false;
    } else {
        receive = rec_string.right(rec_string.length() - pos - 17 - 3).trimmed();
        qDebug() << receive;
        //status=need&notconfirmed=10&text=hi i say you should confirmed the button&end here
        start_pos = receive.indexOf("&");
        if (start_pos >=0 ) {
            do {
                tmp = receive.left(start_pos).trimmed();
                receive = receive.right(receive.length() - start_pos -1).trimmed();
                write_info_string(tmp, info);
                //qDebug() << receive;
            } while((start_pos = receive.indexOf("&")) >= 0);
        } else {
            write_info_string(receive, info);
        }

    }
    printf("info.request=%s not_confirmed=%d  text=%s\n", info->request, info->not_confirmed, info->info_text);

    return true;
}

void login::write_info_string(QString tmp, struct send_info *info)
{
    int pos;
    QString key;
    QString values;

    pos = tmp.indexOf("=");
    if (pos >= 0) {
        key = tmp.left(pos).trimmed().toLower();
        values = tmp.right(tmp.length() - pos - 1).trimmed().toLower();
        if (key.compare("status") == 0) {
            strcpy(info->request, values.toLatin1().data());
        } else if (key.compare("notconfirmed") == 0) {
            info->not_confirmed = values.toInt();
        } else if (key.compare("text") == 0) {
            strcpy(info->info_text, values.toLatin1().data());
        } else {
            qDebug() << "no key equal here " << tmp;
        }

    } else {
        qDebug() << "no = here";
    }

}
void login::show_post()
{
    char post_buf[BUF_SIZE];
    char buf[BUF_SIZE];
    QString cmd;


    bzero(buf, BUF_SIZE);
    sprintf(buf, "lane=%s&cashier=%s&request=%s", global_lane_no.toLatin1().data(), global_cashier_nu, "NoNeed");
    snprintf(post_buf, BUF_SIZE, "POST /cgi-bin/SendInfo.cgi HTTP/1.1\r\nContent-Length:%d\n\n%s\r\n\r\n",
             strlen(buf), buf);
    cmd = QString(post_buf);
    qDebug() << cmd;
    //qDebug() << status;
    http_client->transmit_info(now_local_server, HTTP_PORT, cmd, &rec_string);
    connect(http_client, SIGNAL(emit_receive()), this, SLOT(confirmed2_message()));
}



void login::receive_message()
{

    disconnect(info_client, SIGNAL(emit_receive()), this, SLOT(receive_message()));

    //status=need&notconfirmed=10&text=you should confirmed the button sended by manager
    if (write_to_sendinfo(rec_string, &info) == true) {
        if (strcmp(info.request, "need") == 0) {
            //sleep(2);
            show_post();
#if 1
            /*
    QMessageBox message(QMessageBox::NoIcon, "please click the Yes here", "manage said:you shou confirmed the button here", QMessageBox::Yes, NULL);
    if (message.exec() == QMessageBox::Yes) {
        //QMessageBox::aboutQt(NULL, "About Qt");
        qDebug() << "click yes here";
    }
    */
#else
            QMessageBox::StandardButton rb = (QMessageBox::StandardButton)QMessageBox::question(NULL, "show qt", "manage said", QMessageBox::Yes,QMessageBox::Yes);
            if (rb == QMessageBox::Yes) {
                ;
            }
#endif

            // timer start to close the box
            //close_box.start(30*1000);
            sendinfo_timeout = false;
            // remove the cursor
            box.setCursor(QCursor(Qt::BlankCursor));;

            box.setWindowTitle("Alert");
            //box.setWindowIconText("hello");
            //box.setWindowFlags(Qt::FramelessWindowHint);
            //box.setWindowFlags(Qt::Drawer);
            box.setIcon(QMessageBox::Warning);
            box.setGeometry(QRect(400, 200, 200, 400));
            box.setText(QString(info.info_text));
            //box.setStandardButtons(QMessageBox::Ok);
            //QAbstractButton * confirmButton = box.addButton(tr("Confirmed"), QMessageBox::ActionRole);
            box.exec();
            qDebug() << "close here";
            if (box.clickedButton() == confirmButton) {
                if (sendinfo_timeout == false) {
                    qDebug() << "click confirmed here";
                    close_box.stop();
                    confirmed_flag = true;
                    confirmed_post();
                }
            }
            qDebug() << "close here~~~~~~~~~~~~~~~~~";

            //QMessageBox::critical(0, "please click the ok here", "manage said:you shou confirmed the button here", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
    }
}
void login::confirmed_post()
{
    char buf[BUF_SIZE];
    char post_buf[BUF_SIZE];
    QString cmd;



    bzero(buf, BUF_SIZE);
    sprintf(buf, "lane=%s&cashier=%s&request=%s", global_lane_no.toLatin1().data(), global_cashier_nu, "Confirmed");
    snprintf(post_buf, BUF_SIZE, "POST /cgi-bin/SendInfo.cgi HTTP/1.1\r\nContent-Length:%d\n\n%s\r\n\r\n",
             strlen(buf), buf);
    cmd = QString(post_buf);
    qDebug() << cmd;
    //qDebug() << status;
    info_client->transmit_info(now_local_server, HTTP_PORT, cmd, &rec_string);
    connect(info_client, SIGNAL(emit_receive()), this, SLOT(confirmed_message()));

}
void login::confirmed_message() {
    static int count = 0;


    disconnect(info_client, SIGNAL(emit_receive()), this, SLOT(confirmed_message()));
    //qDebug() << "here string:" << rec_string;
    if (write_to_sendinfo(rec_string, &info) == true) {
        if (strcmp(info.request, "confirmed") == 0) {
            printf("localserver receive confirmed here\n");
        } else  if (strcmp(info.request, "noneed") == 0) {
            printf("localserver receive noeed here\n");
        } else {
            confirmed_flag = false;
        }
    } else {
        confirmed_flag = false;
    }

    if (confirmed_flag == false) {
        while(++count < 5) {
            qDebug("confirmed post here for %d times", count);
            confirmed_post();
        }
    }

}
void login::confirmed2_message() {

    disconnect(http_client, SIGNAL(emit_receive()), this, SLOT(confirmed2_message()));
    //qDebug() << "here string:" << rec_string;
    if (write_to_sendinfo(rec_string, &info) == true) {
        if (strcmp(info.request, "confirmed") == 0) {
            printf("localserver receive confirmed here\n");

        } else  if (strcmp(info.request, "noneed") == 0) {
            printf("localserver receive noeed here\n");

        }else  if (strcmp(info.request, "timeout") == 0) {
            printf("localserver receive timeout here\n");

        }
    }

}

void login::select_mode_start()
{
    mode_timer.stop();
    //disconnect(&mode_timer, SIGNAL(timeout()), this, SLOT(select_mode_start()));

    qDebug() << "\n!!!!!!!!!!!!!!!select mode to big screen!!!!!!!!!!!!\n";
    /*
    if (global_conf_sys->sys_standby.standby_mode == SERIAL_MODE) {
        global_serialMode->global_cartvu_title->setText(QString(global_conf_sys->sys_other.kings_name));
        global_serialMode->global_cashier_label->setText(inputstring);
        global_serialMode->cashier_timer.stop();
        global_serialMode->cashier_timer.start(global_conf_sys->sys_other.cashier_timeout*1000);
        global_serialMode->show();

    } else { //other mode REVOLVE_MODE  SELFDF_MODE  CARTVU_MODE
        global_revo->standby_mode = global_conf_sys->sys_standby.standby_mode;
        qDebug() << "error here ??????";
        global_revo->start_timer.start(100);
        global_revo->show();

    }

    */
    global_revo->standby_mode = global_conf_sys->sys_standby.standby_mode;
    if (global_conf_sys->sys_standby.standby_mode == CARTVU_MODE) {
        qDebug() << "cartvu mode";
        global_serialMode->close();

        global_revo->start_timer.start(0);
        
        
        global_revo->show();



    } else if (global_conf_sys->sys_standby.standby_mode == SELFDF_MODE) {
        qDebug() << "selfde mode";
        global_serialMode->close();

        global_revo->start_timer.start(0);
        global_revo->show();
    } else if (global_conf_sys->sys_standby.standby_mode == REVOLVE_MODE) {
        qDebug() << "revolve mode";
        global_serialMode->revolve_timer.stop();
        now_pic_nu--;
        if (now_pic_nu < global_serialMode->range_start) {
            now_pic_nu = global_serialMode->range_stop;
        }

        global_serialMode->close();

        global_revo->start_timer.start(0);
        global_revo->show();
    } else /*if (global_conf_sys->sys_standby.standby_mode == SERIAL_MODE) */{
        qDebug() << "serial mode";
        qDebug() << "doing nothing for the standby mode";
    }


}
void login::on_pushButton_1_pressed()
{
    ui->pushButton_1->setStyleSheet("border-image: url(:/pic/bt1_down.png);");
}

void login::on_pushButton_1_released()
{
    ui->pushButton_1->setStyleSheet("border-image: url(:/pic/bt1_up.png);");
}

void login::on_pushButton_2_pressed()
{
    ui->pushButton_2->setStyleSheet("border-image: url(:/pic/bt2_down.png);");
}

void login::on_pushButton_2_released()
{
    ui->pushButton_2->setStyleSheet("border-image: url(:/pic/bt2_up.png);");
}

void login::on_pushButton_3_pressed()
{
    ui->pushButton_3->setStyleSheet("border-image: url(:/pic/bt3_down.png);");
}

void login::on_pushButton_3_released()
{
    ui->pushButton_3->setStyleSheet("border-image: url(:/pic/bt3_up.png);");
}

void login::on_pushButton_4_pressed()
{
    ui->pushButton_4->setStyleSheet("border-image: url(:/pic/bt4_down.png);");
}

void login::on_pushButton_4_released()
{
    ui->pushButton_4->setStyleSheet("border-image: url(:/pic/bt4_up.png);");
}

void login::on_pushButton_5_pressed()
{
    ui->pushButton_5->setStyleSheet("border-image: url(:/pic/bt5_down.png);");
}

void login::on_pushButton_5_released()
{
    ui->pushButton_5->setStyleSheet("border-image: url(:/pic/bt5_up.png);");
}

void login::on_pushButton_6_pressed()
{
    ui->pushButton_6->setStyleSheet("border-image: url(:/pic/bt6_down.png);");
}

void login::on_pushButton_6_released()
{
    ui->pushButton_6->setStyleSheet("border-image: url(:/pic/bt6_up.png);");
}

void login::on_pushButton_7_pressed()
{
    ui->pushButton_7->setStyleSheet("border-image: url(:/pic/bt7_down.png);");
}

void login::on_pushButton_7_released()
{
    ui->pushButton_7->setStyleSheet("border-image: url(:/pic/bt7_up.png);");
}

void login::on_pushButton_8_pressed()
{
    ui->pushButton_8->setStyleSheet("border-image: url(:/pic/bt8_down.png);");
}

void login::on_pushButton_8_released()
{
    ui->pushButton_8->setStyleSheet("border-image: url(:/pic/bt8_up.png);");
}

void login::on_pushButton_9_pressed()
{
    ui->pushButton_9->setStyleSheet("border-image: url(:/pic/bt9_down.png);");
}

void login::on_pushButton_9_released()
{
    ui->pushButton_9->setStyleSheet("border-image: url(:/pic/bt9_up.png);");
}

void login::on_pushButton_0_pressed()
{
    ui->pushButton_0->setStyleSheet("border-image: url(:/pic/bt0_down.png);");
}

void login::on_pushButton_0_released()
{
    ui->pushButton_0->setStyleSheet("border-image: url(:/pic/bt0_up.png);");
}

void login::on_pushButton_del_pressed()
{
    ui->pushButton_del->setStyleSheet("border-image: url(:/pic/btdel_down.png);");
}

void login::on_pushButton_del_released()
{
    ui->pushButton_del->setStyleSheet("border-image: url(:/pic/btdel_up.png);");
}

void login::on_login_button_pressed()
{
    ui->login_button->setStyleSheet("border-image: url(:/pic/log_down.png);");
}

void login::on_login_button_released()
{
    ui->login_button->setStyleSheet("border-image: url(:/pic/log_up.png);");
}

void login::on_pushButton_ac_pressed()
{
    ui->pushButton_ac->setStyleSheet("border-image: url(:/pic/btac_down.png);");
}

void login::on_pushButton_ac_released()
{
    ui->pushButton_ac->setStyleSheet("border-image: url(:/pic/btac_up.png);");
}

/*
void login::on_setting_pressed()
{
    ui->setting->setStyleSheet("border-image: url(:/pic/reset_down.png);");
}

void login::on_setting_released()
{
    ui->setting->setStyleSheet("border-image: url(:/pic/reset_up.png);");
}


void login::on_setting_clicked()
{
    setting *a = new setting(camera);
    a->show();

    this->close();
    //delete this;
}


void login::on_exit_button_pressed()
{
    ui->exit_button->setStyleSheet("border-image: url(:/pic/cancel-button.png);");
}

void login::on_exit_button_released()
{
    ui->exit_button->setStyleSheet("border-image: url(:/pic/cancel_up.png);");
}
*/
void login::on_big_button_clicked()
{
    if (global_read_config_ok == true) {
        qDebug() << "hide the big button";
        ui->big_button->setHidden(true);
        global_rsys->openning_light();
        global_lgt->light_adjust();
        // in order to avoid the focus to line_text
        ui->login_button->setFocus();

    } else {
        qDebug() << "do nothing";
    }

}
void login::hide_big_button()
{
    ui->big_button->setHidden(true);
    qDebug() << "hide the log big button ok";
}


void login::show_big_button(bool flag)
{

    if (flag == true) {
        qDebug() << "set the login button bak";
    } else {
        qDebug() << "set the login button front" ;
    }

    ui->big_button->setHidden(flag);

}





