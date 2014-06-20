#include <QDebug>
#include "serialMode.h"
#include "ui_serialMode.h"
#include "login.h"

extern unsigned char *global_buffer;


extern sensor_c *global_sensor;

extern QString global_lane_no;
//extern unsigned int global_cashier_timeout;

extern global_config *global_conf_sys;

extern login *global_log;

extern revolveMode *global_revo;

extern int now_pic_nu;

extern read_sys *global_rsys;

extern light *global_lgt;

extern char status[STATUS_SIZE];

extern struct alert_image cartvu_alert_image;


QLabel *sensor_label[LABEL_NUM];

extern struct statis  cartvu_statis;
extern QMutex global_statis_lock;



/*
serialMode::serialMode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serialMode)
{
    qDebug("hello");
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    serila_init();
}
*/
serialMode::serialMode(camThread *cam, QString b, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::serialMode)
{
    cashier_no = b;
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->merchan_text->setHidden(true);
    //    QPalette palette = ui->time_label->palette();
    //    palette.setColor(QPalette::WindowText,QColor(255,153,51));
    //    ui->time_label->setPalette(palette);
    //
    //    palette = ui->lane_label->palette();
    //    palette.setColor(QPalette::WindowText,QColor(255,153,51));
    //    ui->lane_label->setPalette(palette);

    //avoid the buttons can not close and make error
    //system("");

    show_sensor_status_hide = SENSOR_SHOW_HIDE;

    passwd = "none";

    camera = cam;
    qDebug() << "construct serial here!";
    qDebug() << camera;
    //camera = new camThread(global_buffer);
    //camera->start(QThread::LowPriority);

    connect(global_sensor , SIGNAL(show_led(struct sensor_all_att*)), this, SLOT(show_sensor_state(struct sensor_all_att*)));
    connect(global_sensor, SIGNAL(take_alarm_pic()), camera, SLOT(take_pic()));
    connect(global_sensor, SIGNAL(last_alarm_pic()), camera, SLOT(show_last_pic()));
    connect(global_sensor, SIGNAL(start_alarm()), this, SLOT(show_alarm_and_twinkle()));
    connect(&image_timer, SIGNAL(timeout()), this, SLOT(return_cam_status()));

    connect(global_sensor, SIGNAL(image_time_ok()), this, SLOT(return_cam_status()));

    sensor_label[0] = ui->label_E1;
    sensor_label[1] = ui->label_S;
    sensor_label[2] = ui->label_I1;
    sensor_label[3] = ui->label_I2;
    sensor_label[4] = ui->label_I3;
    sensor_label[5] = ui->label_E2;
    sensor_label[6] = ui->label_EXT;
    sensor_label[7] = ui->label_state;
    sensor_label[8] = ui->label_error;


    int i = 0;
    for (i = 0; i < LABEL_NUM; i++) {
        sensor_label[i]->setHidden(show_sensor_status_hide);
    }

    qDebug() << "connect the serial ok!";
    play_audio_init();
    //painter = new QPainter(this);
    serila_init();


}

void serialMode::show_alarm_and_twinkle(void)
{
    this->alarm_flag = true;
    play_flag = false;
}

void serialMode::show_sensor_state(struct sensor_all_att *all_sensor)
{
    int i = 0;
    unsigned char state;
    //    qDebug() << "show sensor state!";
    //    qDebug() << sizeof(*sensor);
    for (i = 0; i < ALL_SENSOR_NUM; i++) {
        if (all_sensor->sensor[i].state == 1) {
            sensor_label[i]->setStyleSheet("background-color: red");
        } else {
            sensor_label[i]->setStyleSheet("background-color: white");
        }


    }

    for (i = 0; i < ALL_SENSOR_NUM; i++) {
        if (all_sensor->sensor[i].error_flag == SENSOR_ERROR) {
            ui->label_error->setText(all_sensor->sensor[i].name);
            break;
        } else {
            ui->label_error->setText("good");
        }

    }
    state = all_sensor->sensor_position_state;
    switch (all_sensor->sensor_position_state) {
    case 0:
        ui->label_state->setText("E1_STATE");
        break;
    case 1:
        ui->label_state->setText("S_STATE");
        break;
    case 2:
        ui->label_state->setText("I_STATE");
        break;
    case 3:
        ui->label_state->setText("E2_STATE");
        break;
    default:
        break;
    }



}


serialMode::~serialMode()
{
    qDebug() << "\n?????delete the serial ui???\n";
    delete ui;

}

void serialMode::changeEvent(QEvent *e)
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


void serialMode::play_audio_init()
{
    //char buf[BUF_SIZE] = {0};

    play_flag = false;
    qDebug() << "initialize the beep.wav";
    qDebug() <<"/*************************QProcess**************/";
    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
    connect(process,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(finished_playing(int,QProcess::ExitStatus)));







}



void serialMode::play_audio()
{
    static int alarm_max = 0;
    QStringList music_type_tmp;
    //QString alarm_sound_type;
    char buf[BUF_SIZE] = {0};
    /*
int volume_level;

    // adjust the volume
    volume_level = volume_state();
    snprintf(buf, BUF_SIZE, "%s %d &", VOLUME_APP, volume_level);
    qDebug("now the volume is %s", buf);
*/
    //  /test/volume_test 80 &
    // system(buf);
    //FILE *fp;
    //fp = popen(buf, "r");
    //pclose(fp);


    aplayer_path = AUDIO_APP;

    if (global_conf_sys->sys_alarm.alarm_mode == SINGLE_ALARM) {
        // /test/1.wav
        snprintf(buf, BUF_SIZE, "%s%d.wav", ALARM_SOUND_PATH, global_conf_sys->sys_alarm.alarm_id);
        qDebug("!!!!!now the alarm_id is %s", buf);
        music_type_tmp << QString(buf);
    } else if (global_conf_sys->sys_alarm.alarm_mode == CYCLE_ALARM) {
        // /test/1.wav
        //while (alarm_max < 6) {
        bzero(buf, BUF_SIZE);
        snprintf(buf, BUF_SIZE, "%s%d.wav", ALARM_SOUND_PATH, alarm_max);
        qDebug("!!!!!now the alarm_id is %s", buf);
        music_type_tmp << QString(buf);
        alarm_max++;
        if(alarm_max == 6) {
            alarm_max = 0;
        }
        //  }
    }

    process->start(aplayer_path, music_type_tmp);
    qDebug() << "start to play===========!!\n";
    if(!process->waitForStarted(3000))
    {
        qDebug() << "@@@@@@@@@@@check the bug@@@@@@@@@@@@@@@";
    } else {
        //qDebug() << "@@@@@@@@@play ok@@@@@@@@@@@@@@@";
    }

}



void serialMode::finished_playing(int,QProcess::ExitStatus)
{
    static int play_count = 0;
    //char buf[BUF_SIZE] = {0};
    qDebug() << "the alarm  has over!";

    if (alarm_flag == true) {
        if (global_conf_sys->sys_alarm.alarm_mode == SINGLE_ALARM) {
            if (++play_count < 1) {
                process->start(aplayer_path, music_type);
                qDebug() << "start to play===========!!\n";
                if(!process->waitForStarted(3000))
                {
                    qDebug() << "check the bug :isplay=0";
                } else {
                    //qDebug() << "@@@@@@@@@play ok@@@@@@@@@@@@@@@";
                }
            } else {
                play_count = 0;

                //avoid the buttons can not close and make error
                //system("");
            }
        } else if (global_conf_sys->sys_alarm.alarm_mode == CYCLE_ALARM) {

            //process->start(aplayer_path, music_type);
            qDebug() << "start to play===========!!\n";
            //if(!process->waitForStarted(3000))
            //{
            //   qDebug() << "check the bug :isplay=0";
            //} else {
            //qDebug() << "@@@@@@@@@play ok@@@@@@@@@@@@@@@";
            // }

        }
        qDebug() << "stop the sound";

    } else {
        qDebug() << "check is clicked";
    }
}




extern QLineEdit *global_lane_edit;

void serialMode::on_logout_button_clicked()
{
    //login *a = new login(camera);
    login *a = global_log;

    global_lane_edit->setText("");
    global_log->inputstring = "";
    //qDebug()<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~ok~~~~~~~~~~~~~~~";
    //camera->cam_timer->stop();
    a->show();

    //    login a;
    //    a.show();
    //    this->close();
    //date_timer.stop();
    //tick_timer.stop();

    //release source
    //delete this;
    char buf[SOUND_BUF];
    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%s.wav", AUDIO_APP, CLICK_SOUND, COMMON_SOUND);
    my_system(buf);
    
    
    global_log->mode_timer.stop();;
    global_rsys->log_delay_timer.start(LOG_DELAY_TIME*1000);


    this->close();

}


void serialMode::serila_init(void)
{


    connect(camera, SIGNAL(play()), this, SLOT(cam_flash()));
    //connect(camera, SIGNAL(play()), this, SLOT(update()));
    connect(this, SIGNAL(sig_take_pic()), camera, SLOT(take_pic()));


    connect(&date_timer, SIGNAL(timeout()), this, SLOT(date_time_flash()));
    connect(&tick_timer, SIGNAL(timeout()), this, SLOT(tick_time_flash()));
    // if (cashier_no == "") {
    //cashier_no = "";
    //cashier_no = "no Num";
    //} else {
    connect(&cashier_timer, SIGNAL(timeout()), this, SLOT(cashier_update()));
    qDebug() << "now the global cashier timeout is " << global_conf_sys->sys_other.cashier_timeout;
    //        cashier_timer.start(global_cashier_timeout*1000);
    cashier_timer.start(global_conf_sys->sys_other.cashier_timeout*1000);

    // }
    ui->cashier_label->setText(cashier_no);
    global_cashier_label = ui->cashier_label;
    global_cartvu_title = ui->title_button;



    ui->lane_label->setText(global_lane_no);
    //set the text in the center
    ui->cashier_label->setAlignment(Qt::AlignCenter);
    ui->lane_label->setAlignment(Qt::AlignCenter);
    ui->time_label->setAlignment(Qt::AlignCenter);
    ui->tick_button->setHidden(true);

    ui->recover_button->setHidden(true);
    connect(global_rsys, SIGNAL(show_hide_button(bool)), this, SLOT(show_recover_button(bool)));



    cam_flag = false;
    switch_flag = false;
    alarm_flag = false;
    date_timer.start(500);

    merchandise_init();

    switch_time = global_conf_sys->sys_standby.revolve_period;
    range_start = global_conf_sys->sys_standby.revolve_range.start;
    range_stop = global_conf_sys->sys_standby.revolve_range.end;
    now_pic_nu = range_start;

    connect(&revolve_timer, SIGNAL(timeout()), this, SLOT(revolve_pic()));
}
void serialMode::merchandise_init()
{
    ui->merchan_text->append("BarCode\t\tItem\t\tPrice\n");
    ui->merchan_text->append("001\t\tcoca-cola\t\t2$");
    ui->merchan_text->append("002\t\tpencil\t\t2$");
    ui->merchan_text->append("003\t\twahaha\t\t2$");
    ui->merchan_text->append("001\t\tapple\t\t2$");
    ui->merchan_text->append("001\t\tbanana\t\t2$");
    ui->merchan_text->append("001\t\tmouse\t\t2$");
    ui->merchan_text->append("001\t\tcoca-cola\t\t2$");
    ui->merchan_text->append("001\t\tcoca-cola\t\t2$");
    ui->merchan_text->append("001\t\tcoca-cola\t\t2$");
    ui->merchan_text->append("001\t\trubbish\t\t5$");
    ui->merchan_text->append("001\t\tbrush\t\t4$");

}

void serialMode::cashier_update()
{
    cashier_timer.stop();
    ui->cashier_label->setText("HELP");
}

//void serialMode::paintEvent(QPaintEvent *)
//{
//    if ((camera->lock_flag == false) || (camera->take_pic_flag == true)) {
//        if (camera->take_pic_flag == true) {
//            camera->take_pic_flag = false;
//        }
//        QImage image((unsigned char *)global_buffer, VIDEO_WIDTH, VIDEO_HEIGHT, QImage::Format_RGB32);
//        pixmapToShow = QPixmap::fromImage(image.scaled(IMG_SHOW_WIDTH,IMG_SHOW_HEIGHT,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
//        ui->cam_label->setPixmap(pixmapToShow);
//        ui->cam_label->show();
//
//    } else if (camera->lock_flag == true){
//        QPixmap video_pic;
//        video_img.load(SERIAL_BG_PIC);
//        //stretch  or reduce
//        video_pic = QPixmap::fromImage(video_img.scaled(IMG_SHOW_WIDTH, IMG_SHOW_HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
//        //stretch image
//        ui->cam_label->setPixmap(video_pic);
//        ui->cam_label->show();
//
//    }
//    qDebug() << "in falsh2";



//}

void serialMode::return_cam_status(void)
{
    image_timer.stop();

    ui->check_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/check_green_up.png);"));

    qDebug() << "image time stop";
    if (camera->lock_flag == false) {
        camera->cam_timer->start(SHOW_VIDEO_DELAY);
        qDebug() << "make the serial camera start";
    } else {
        qDebug() << "keep static status";
    }
    //cam_flash();

    if (show_sensor_status_hide == false) {
        qDebug() << "develop mode and not start the big screen";
    } else {
        /*
        if (global_conf_sys->sys_standby.standby_mode != SERIAL_MODE) {
            global_revo->show();
            if (global_conf_sys->sys_standby.standby_mode == REVOLVE_MODE) {
                now_pic_nu--;
                if (now_pic_nu < global_serialMode->range_start) {
                    now_pic_nu = range_stop;
                }
                global_revo->internalTimer.start(0);
            }

            this->close();
        }
*/
        qDebug() << "start the mode_timer";
        global_log->mode_timer.start(MODE_TIMER*1000);

        qDebug() << "return before status";
    }
    chose_screen();

    if (alarm_flag == true) {
        bzero(cartvu_alert_image.barcode, FILE_SIZE);
        //strncpy(cartvu_alert_image.barcode, "imageTime happen", FILE_SIZE);
        emit record_ok();
    }
    alarm_flag = false;

}

void serialMode::cam_flash()
{
    revolve_timer.stop();
    QPixmap video_pic;

    //qDebug() << "in flash";
    if ((camera->lock_flag == false) || (camera->take_pic_flag == true)) {
        if (camera->take_pic_flag == true) {
            camera->take_pic_flag = false;
            qDebug() << "image timer start!";
            if (global_conf_sys->sys_alarm.image_time != 0) {
                image_timer.start(global_conf_sys->sys_alarm.image_time*1000);
            }
            //stop the standby big screen
            global_log->mode_timer.stop();
        }
        QImage image((unsigned char *)global_buffer, CAMERA_WIDTH, CAMERA_HEIGHT, QImage::Format_RGB32);
        pixmapToShow = QPixmap::fromImage(image.scaled(IMG_SHOW_WIDTH,IMG_SHOW_HEIGHT,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        //pixmapToShow = QPixmap::fromImage(image);
        ui->cam_label->setPixmap(pixmapToShow);
        ui->cam_label->show();

    } else if (camera->lock_flag == true){

        /*
        if (video_img.load(SERIAL_BG_PIC) == false) {
            qDebug("load the %s fail", SERIAL_BG_PIC);
        }
        //stretch  or reduce
        video_pic = QPixmap::fromImage(video_img.scaled(IMG_SHOW_WIDTH, IMG_SHOW_HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        //stretch image
        ui->cam_label->setPixmap(video_pic);
        ui->cam_label->show();
        */
        qDebug() << "in cam flash";
        chose_screen();
    }




    //this->repaint();
}

void serialMode::chose_screen()
{
    QPixmap video_pic;

    qDebug() << "chose the mode to show";

    if (global_conf_sys->sys_standby.standby_mode == CARTVU_MODE) {
        if (video_img.load(CARTVU_MODE_PIC) == false) {
            qDebug("load the %s fail", CARTVU_MODE_PIC);
        }
        //stretch  or reduce
        video_pic = QPixmap::fromImage(video_img.scaled(IMG_SHOW_WIDTH, IMG_SHOW_HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        //qDebug() << "error here";
        //stretch image
        ui->cam_label->setPixmap(video_pic);
        ui->cam_label->show();

    } else if (global_conf_sys->sys_standby.standby_mode == SELFDF_MODE) {
        if (video_img.load(SELF_MODE_PIC) == false) {
            qDebug("load the %s fail", SELF_MODE_PIC);
        }
        //stretch  or reduce
        video_pic = QPixmap::fromImage(video_img.scaled(IMG_SHOW_WIDTH, IMG_SHOW_HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        //stretch image
        ui->cam_label->setPixmap(video_pic);
        ui->cam_label->show();
    } else if (global_conf_sys->sys_standby.standby_mode == REVOLVE_MODE) {
        init_revolve_pic();
    } else /*if (global_conf_sys->sys_standby.standby_mode == SERIAL_MODE) */{
        camera->lock_flag = false;
        camera->mutex_video.unlock();
        camera->cam_timer->start(SHOW_VIDEO_DELAY);
        qDebug() << "unlock  the video!!!!";
    }
}


void serialMode::now_chose_screen()
{
    QPixmap video_pic;

    qDebug() << "chose the mode to show";

    if (global_conf_sys->sys_standby.standby_mode == CARTVU_MODE) {
        if (video_img.load(CARTVU_MODE_PIC) == false) {
            qDebug("load the %s fail", CARTVU_MODE_PIC);
        }
        //stretch  or reduce
        video_pic = QPixmap::fromImage(video_img.scaled(IMG_SHOW_WIDTH, IMG_SHOW_HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        //qDebug() << "error here";
        //stretch image
        ui->cam_label->setPixmap(video_pic);
        ui->cam_label->show();

    } else if (global_conf_sys->sys_standby.standby_mode == SELFDF_MODE) {
        if (video_img.load(SELF_MODE_PIC) == false) {
            qDebug("load the %s fail", SELF_MODE_PIC);
        }
        //stretch  or reduce
        video_pic = QPixmap::fromImage(video_img.scaled(IMG_SHOW_WIDTH, IMG_SHOW_HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        //stretch image
        ui->cam_label->setPixmap(video_pic);
        ui->cam_label->show();
    } else if (global_conf_sys->sys_standby.standby_mode == REVOLVE_MODE) {
        revolve_pic();
    } else /*if (global_conf_sys->sys_standby.standby_mode == SERIAL_MODE) */{
        camera->lock_flag = false;
        camera->mutex_video.unlock();
        camera->cam_timer->start(SHOW_VIDEO_DELAY);
        qDebug() << "unlock  the video!!!!";
    }
}



void serialMode::revolve_pic()
{
    QPixmap video_pic;
    char pic[PIC_SIZE];
    revolve_timer.stop();


    revolve_timer.start(switch_time * 1000);
    now_pic_nu++;
    if (now_pic_nu == (range_stop + 1)) {
        now_pic_nu = range_start;
    }


    snprintf(pic, PIC_SIZE, "%s%02d.jpg", REVOLVE_PIC_DIR, now_pic_nu);
    //qDebug("in small String is %s", pic);


    if (video_img.load(pic) == false) {
        qDebug("load the %s fail", pic);
        recordLog(16, 27, (char*)"load the pic  fail");
        return;
    }
    //stretch  or reduce
    video_pic = QPixmap::fromImage(video_img.scaled(IMG_SHOW_WIDTH, IMG_SHOW_HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    //stretch image
    ui->cam_label->setPixmap(video_pic);
    ui->cam_label->show();


}

void serialMode::init_revolve_pic()
{
    QPixmap video_pic;
    char pic[PIC_SIZE];


    now_pic_nu++;
    if (now_pic_nu == (range_stop + 1)) {
        now_pic_nu = range_start;
    }

    snprintf(pic, PIC_SIZE, "%s%02d.jpg", REVOLVE_PIC_DIR, range_start);
    //qDebug("in small String is %s", pic);

    if (video_img.load(pic) == false) {
        qDebug("load the %s fail", pic);
        recordLog(16, 27, (char*)"load the pic  fail(init)");
        return;
    }
    //stretch  or reduce
    video_pic = QPixmap::fromImage(video_img.scaled(IMG_SHOW_WIDTH, IMG_SHOW_HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    //stretch image
    ui->cam_label->setPixmap(video_pic);
    ui->cam_label->show();


}



void serialMode::on_list_button_clicked()
{
    if (cam_flag == false)
    {   
        cam_flag = true;


        ui->merchan_text->setHidden(false);

        //alarm_flag = true;
        //system("/bin/aplay  /test/BEEP.WAV &");
        /*
        camera->lock_flag = false;
        camera->mutex_video.unlock();
        camera->cam_timer->start(SHOW_VIDEO_DELAY);
        qDebug() << "unlock  the video!!!!";
        */
    } else {
        cam_flag = false;

        ui->merchan_text->setHidden(true);

        //ui->list_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/list_up.png);"));
        /*
        camera->cam_timer->stop();
        // you should set the cam_flash to change the view;
        camera->lock_flag = true;
        camera->fetch_video.unlock();
        */
        //ui->cam_label->setText("shop list here");
    }

    char buf[SOUND_BUF];
    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%s.wav", AUDIO_APP, CLICK_SOUND, COMMON_SOUND);
    my_system(buf);

    global_log->mode_timer.start(MODE_TIMER*1000);
}


void serialMode::date_time_flash()
{
    static int time_count = 0;
    QString a;
    QDateTime tmp;

    // ui->date_lcdnumber->setNumDigits(19);
    //ui->date_lcdnumber->setSegmentStyle(QLCDNumber::Flat);
    time_count++;
    if (time_count == 2) {
        a = tmp.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        ui->time_label->setText(a);
        time_count = 0;
    }
    if (alarm_flag == true)
    {
        if (switch_flag == false)
        {
            ui->check_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/check_red.png);"));
            switch_flag = true;
        } else {
            ui->check_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/check_yellow.png);"));
            switch_flag = false;
        }
        //system("/bin/aplay  /test/alarm.wav &");
        if (play_flag == false) {
            play_flag = true;
            play_audio();

            qDebug() << "start the audio";
            //system("/leds_test &");
        }
        //system("/rtc_app");
        //system("/bin/madplay  /test/just_like_me.mp3 &");
        //system("/bin/madplay  /test/BEEP.mp3 &");
        //system("/bin/aplay  /test/beep.wav");
        /*
        FILE *fp;
        fp = popen("/bin/aplay  /test/beep.wav", "r");
        pclose(fp);
*/
    }
    //qDebug() << a;
}





void serialMode::tick_time_flash()
{

    ui->tick_button->setHidden(true);
    tick_timer.stop();
    qDebug() << "setHidden";
}


void serialMode::on_check_button_clicked()
{
    if (alarm_flag == true)
    {
        //close the fresh pic
        alarm_flag = false;

        //camera->take_pic_flag = true;
        //camera->mutex_video.unlock();
        //camera->lock_flag = true;

        qDebug() << "check clicked";
        //ui->check_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/check_green.png);"));

        ui->tick_button->setHidden(false);
        tick_timer.start(2000);
        my_system("killall -9 aplay");


        cartvu_alert_image.confirmed = 1;
        bzero(cartvu_alert_image.barcode, FILE_SIZE);
        //strncpy(cartvu_alert_image.barcode, "check happen", FILE_SIZE);
        emit record_ok();

        qDebug() << "locked the global statis in sensor thread";
        global_statis_lock.lock();
        cartvu_statis.confirm_num++;
        qDebug() << "confirm num add here!!!!!!!!!!!";
        global_statis_lock.unlock();

    }

    char buf[SOUND_BUF];
    bzero(buf, SOUND_BUF);
    snprintf(buf, SOUND_BUF, "%s %s%s.wav", AUDIO_APP, CLICK_SOUND, COMMON_SOUND);
    qDebug() << buf;
    my_system(buf);

    passwd = "1";

    global_log->mode_timer.start(MODE_TIMER*1000);
}

void serialMode::on_list_button_pressed()
{

    ui->list_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/list_down.png);"));

}

void serialMode::on_list_button_released()
{
    ui->list_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/list_up.png);"));

}

void serialMode::on_logout_button_pressed()
{
    ui->logout_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/logout_down.png);"));
}

void serialMode::on_logout_button_released()
{
    ui->logout_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/logout_up.png);"));
}

void serialMode::on_check_button_pressed()
{
    ui->check_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/check_green_down.png);"));
}

void serialMode::on_check_button_released()
{
    ui->check_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/check_green_up.png);"));
}

void serialMode::on_pushButton_hide_clicked()
{
    ui->cashier_label->setText("!!!help!!!");
    qDebug() << "!!!help!!!";


    status[0] = '1';
    //ui->pushButton_hide->clearFocus();

    global_log->mode_timer.start(MODE_TIMER*1000);
}

void serialMode::on_pushButton_hide_pressed()
{
    //ui->pushButton_hide->clearFocus();

}


void serialMode::on_recover_button_clicked()
{
    qDebug() << "hide the big button";
    ui->recover_button->setHidden(true);
    global_rsys->openning_light();
    global_lgt->light_adjust();
}

void serialMode::show_recover_button(bool flag)
{
    if (flag == true) {
        qDebug() << "set the recover button bak";
    } else {

        qDebug() << "set the recover button front" ;
    }
    ui->recover_button->setHidden(flag);

}



void serialMode::on_title_button_clicked()
{


    if (passwd.compare("123") == 0) {
        qDebug() << "passwd is ok";
        qDebug() << "will enter the supper setting";

        global_log->mode_timer.stop();
        setting *a = new setting();
        a->show();

        this->close();
        global_log->mode_timer.stop();
    } else {
        qDebug() << "passwd is error";
        qDebug() << passwd;
        global_log->mode_timer.start(MODE_TIMER*1000);
        recordLog(16, 43, (char*)"passwd is error(in button clicked)");
    }
    passwd = "none";

}

void serialMode::on_time_button_clicked()
{
    passwd = passwd + "2";
    global_log->mode_timer.start(MODE_TIMER*1000);
}

void serialMode::on_lane_button_clicked()
{
    passwd = passwd + "3";
    global_log->mode_timer.start(MODE_TIMER*1000);
}
