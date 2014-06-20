#include "config_setting.h"
#include "ui_config_setting.h"









extern int my_system(const char* cmd);








config_setting::config_setting(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::config_setting)
{

    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    config_form = ui;
    first_volume = true;
    first_id = true;
    config_init();
}

config_setting::~config_setting()
{
    qDebug() << "delete config setting";
    delete ui;
}

void config_setting::changeEvent(QEvent *e)
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



void config_setting::config_init()
{
    qDebug() << "config.sys settings is construct ok!";

    //ui->lineEdit_openning_time->setFocus();
    //ui->lineEdit_openning_time->setFocus();
    //ui->lineEdit_openning_time->setCursor(Qt::IBeamCursor);
    read_config_to_show(CFG_SYS);
}


void config_setting::read_config_to_show(const char *cfg_sys)
{
    char buf[NOW_SIZE];
    global_config tmp_config_sys;
    read_sys tmp_read_sys;



    tmp_read_sys.sys_decode(cfg_sys, &tmp_config_sys);



    // network
    ui->lineEdit_local_server->setText(QString(tmp_config_sys.sys_network.local_server));
    //global
    ui->lineEdit_store_name->setText(QString(tmp_config_sys.sys_other.kings_name));
    ui->lineEdit_openning_time->setText(QString(tmp_config_sys.sys_global.openning_time_str));
    ui->lineEdit_closing_time->setText(QString(tmp_config_sys.sys_global.closing_time_str));

    bzero(buf, NOW_SIZE);
    snprintf(buf, NOW_SIZE, "%d", tmp_config_sys.sys_global.time_zone);
    ui->lineEdit_time_zone->setText(QString(buf));



    ui->cb_savingtime->setCurrentIndex(tmp_config_sys.sys_global.saveing_time);
    //qDebug() << "current index is " <<ui->cb_savingtime->currentIndex();
    //qDebug() << ui->cb_savingtime->itemText(ui->cb_savingtime->currentIndex());//0 1 2


    ui->lineEdit_reset_time->setText(QString(tmp_config_sys.sys_other.reset_time_str));

    ui->cb_brightness->setCurrentIndex(tmp_config_sys.sys_global.brightness - 1);;
    // working mode
    ui->cb_working_mode->setCurrentIndex(tmp_config_sys.sys_working_mode.working_mode);

    ui->cb_camera_type->setCurrentIndex(tmp_config_sys.sys_working_mode.camera_type);

    ui->cb_is_number->setCurrentIndex(tmp_config_sys.sys_working_mode.I_number - 1);


    bzero(buf, NOW_SIZE);
    snprintf(buf, NOW_SIZE, "%d", tmp_config_sys.sys_working_mode.E2_time_out);
    ui->lineEdit_e2_timeout->setText(QString(buf));

    bzero(buf, NOW_SIZE);
    snprintf(buf, NOW_SIZE, "%d", tmp_config_sys.sys_working_mode.alarm_interval);
    ui->lineEdit_alarm_interval->setText(QString(buf));
    //alarm
    bzero(buf, NOW_SIZE);
    snprintf(buf, NOW_SIZE, "%d", tmp_config_sys.sys_alarm.image_time);
    ui->lineEdit_image_time->setText(QString(buf));

    ui->cb_alarm_mode->setCurrentIndex(tmp_config_sys.sys_alarm.alarm_mode);


    ui->cb_alarm_id->setCurrentIndex(tmp_config_sys.sys_alarm.alarm_id);


    ui->cb_alarm_volume->setCurrentIndex(tmp_config_sys.sys_alarm.alarm_volume);

    // standby mode
    ui->cb_standby_mode->setCurrentIndex(tmp_config_sys.sys_standby.standby_mode);

    ui->lineEdit_revolve_range->setText(QString(tmp_config_sys.sys_standby.revolve_str));

    bzero(buf, NOW_SIZE);
    snprintf(buf, NOW_SIZE, "%d", tmp_config_sys.sys_standby.revolve_period);
    ui->lineEdit_revolve_period->setText(QString(buf));

    //other
    ui->cb_image_quality->setCurrentIndex(tmp_config_sys.sys_other.image_quality);

    ui->cb_extra_item_info->setCurrentIndex(tmp_config_sys.sys_other.extra_iteam_info);

    bzero(buf, NOW_SIZE);
    snprintf(buf, NOW_SIZE, "%d", tmp_config_sys.sys_other.cashier_timeout);
    ui->lineEdit_cashier_timeout->setText(QString(buf));


    ui->cb_settings->setCurrentIndex(tmp_config_sys.sys_other.settings);


}

void config_setting::on_button_return_clicked()
{
    setting *a = new setting();
    a->show();

    this->close();

    delete this;
}

void config_setting::on_button_modify_settings_clicked()
{
    char buf[BUF_SIZE] = {0};
    qDebug() << "modify the config is ok will reboot the system";
    recordLog(10, 21, (char*)"modify the config is ok will reboot the system");

    save_to_config(TMP_CFG_SYS);

    snprintf(buf, BUF_SIZE, "/bin/mv %s %s", TMP_CFG_SYS, CFG_SYS);
    my_system(buf);
    qDebug() << buf;


    my_system("/sbin/reboot");
}



void config_setting::save_to_config(const char * arg)
{

    char buf[BUF_SIZE] = {0};

    QFile sys_file(arg);

    QDateTime tmp;
    QString write_time;



    write_time = tmp.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");



    snprintf(buf, BUF_SIZE, "/bin/touch %s", arg);
    my_system(buf);

    if (sys_file.exists()) {
        if (sys_file.open(QIODevice::WriteOnly | QIODevice::Truncate) | QIODevice::Text) {
            QTextStream write_stream(&sys_file);

            // write the modify time to config.sys
            write_stream << write_time << endl;

            write_stream << "[NETWORK]" << endl;
            write_stream << "LocalServer=" << ui->lineEdit_local_server->text() << endl;             

            write_stream << "[GLOBAL]" << endl;
            write_stream << "StoreName=" << ui->lineEdit_store_name->text() << endl;
            write_stream << "OpenningTime=" << ui->lineEdit_openning_time->text() << endl;
            write_stream << "ClosingTime=" << ui->lineEdit_closing_time->text() << endl;
            write_stream << "TimeZone=" << ui->lineEdit_time_zone->text() << endl;
            write_stream << "SavingTime=" << ui->cb_savingtime->currentIndex() << endl;
            write_stream << "ResetTime=" << ui->lineEdit_reset_time->text() << endl;
            write_stream << "Brightness=" << ui->cb_brightness->currentIndex() + 1 << endl;

            write_stream << "[WORKINGMODE]" << endl;
            write_stream << "WorkingMode=" << ui->cb_working_mode->currentIndex() << endl;
            write_stream << "CameraType=" << ui->cb_camera_type->currentIndex() << endl;
            write_stream << "ISNumber=" << ui->cb_is_number->currentIndex() + 1 << endl;
            write_stream << "E2Timeout=" << ui->lineEdit_e2_timeout->text() << endl;
            write_stream << "AlarmInterval=" << ui->lineEdit_alarm_interval->text() << endl;

            write_stream << "[ALARM]" << endl;
            write_stream << "ImageTime=" << ui->lineEdit_image_time->text() << endl;
            write_stream << "AlarmMode=" << ui->cb_alarm_mode->currentIndex() << endl;
            write_stream << "AlarmID=" << ui->cb_alarm_id->currentIndex() << endl;
            write_stream << "AlarmVolume=" << ui->cb_alarm_volume->currentIndex() << endl;

            write_stream << "[STANDBY]" << endl;
            write_stream << "StandbyMode=" << ui->cb_standby_mode->currentIndex() << endl;
            write_stream << "RevolveRange=" << ui->lineEdit_revolve_range->text() << endl;
            write_stream << "RevolvePeriod=" << ui->lineEdit_revolve_period->text() << endl;

            write_stream << "[OTHER]" << endl;
            write_stream << "ImageQuality=" << ui->cb_image_quality->currentIndex() << endl;
            write_stream << "ExtraItemInfo=" << ui->cb_extra_item_info->currentIndex() << endl;
            write_stream << "CashierTimeout=" << ui->lineEdit_cashier_timeout->text() << endl;
            write_stream << "Settings=" << ui->cb_settings->currentIndex() << endl;



        } else {
            sprintf(buf, "%s is open fail!!", arg);
            recordLog(10, 17, buf);
            qDebug("%s is open fail!!", arg);
            return;
        }

        sys_file.close();
    } else {
        sprintf(buf, "the %s is not exit!!!", arg);
        recordLog(10, 17, buf);
        qDebug("the %s is not exit!!!", arg);
        return;
    }



}


void config_setting::on_button_read_default_settings_clicked()
{
    static bool default_flag = true;
    read_sys tmp_read_sys;

    first_volume = true;
    first_id = true;
    qDebug() << "set the true";


    if (default_flag == true) {
        ui->button_read_default_settings->setText("Read Now Settings");
        default_flag = false;
        qDebug() << "read the default settings is ok";
        //tmp_read_sys.sys_decode(CFG_SYS, &default_config_sys);


        read_config_to_show(DEF_CFG_SYS);

    } else {
        ui->button_read_default_settings->setText("Read Default Settings");
        default_flag = true;
        qDebug() << "read the now settings is ok";

        // tmp_read_sys.sys_decode(CFG_SYS, &now_config_sys);

        read_config_to_show(CFG_SYS);
    }


}


void config_setting::update_now_string(QString info)
{
    now_lineEdit_string = info;
    qDebug() << "the line Edit string has change to:";
    qDebug() << now_lineEdit_string;


}


void config_setting::on_pushButton_0_clicked()
{
    //now_lineEdit_string += "0";
    emit sendChar('0');

}

void config_setting::on_pushButton_1_clicked()
{
    /*
    QWidget *widget;
    QString name;
    
    
    qDebug() << "now string is ";
    widget = focusWidget();
    
    name = widget->objectName();
    qDebug() << "now the widget is "<< name;
    */
    //now_lineEdit_string += "1";
    emit sendChar('1');
}



void config_setting::on_pushButton_2_clicked()
{

    emit sendChar('2');
}

void config_setting::on_pushButton_3_clicked()
{
    emit sendChar('3');

}

void config_setting::on_pushButton_4_clicked()
{
    emit sendChar('4');
}

void config_setting::on_pushButton_5_clicked()
{
    emit sendChar('5');
}

void config_setting::on_pushButton_6_clicked()
{
    emit sendChar('6');
}

void config_setting::on_pushButton_7_clicked()
{
    emit sendChar('7');
}

void config_setting::on_pushButton_8_clicked()
{
    emit sendChar('8');
}

void config_setting::on_pushButton_9_clicked()
{
    emit sendChar('9');
}

void config_setting::on_pushButton_ac_clicked()
{
    //emit sendChar('del');
    int count = 10;
    while (count--) {
        emit sendInt(54);
    }
}

void config_setting::on_pushButton_del_clicked()
{
    emit sendInt(54);
}

void config_setting::on_pushButton_colon_clicked()
{
    emit sendChar(':');
}

void config_setting::on_pushButton_minus_clicked()
{
    emit sendChar('-');
}

void config_setting::on_pushButton_1_pressed()
{
    ui->pushButton_1->setStyleSheet("border-image: url(:/pic/bt1_down.png);");
}

void config_setting::on_pushButton_1_released()
{
    ui->pushButton_1->setStyleSheet("border-image: url(:/pic/bt1_up.png);");
}

void config_setting::on_pushButton_2_pressed()
{
    ui->pushButton_2->setStyleSheet("border-image: url(:/pic/bt2_down.png);");
}

void config_setting::on_pushButton_2_released()
{
    ui->pushButton_2->setStyleSheet("border-image: url(:/pic/bt2_up.png);");
}

void config_setting::on_pushButton_3_pressed()
{
    ui->pushButton_3->setStyleSheet("border-image: url(:/pic/bt3_down.png);");
}

void config_setting::on_pushButton_3_released()
{
    ui->pushButton_3->setStyleSheet("border-image: url(:/pic/bt3_up.png);");
}

void config_setting::on_pushButton_4_pressed()
{
    ui->pushButton_4->setStyleSheet("border-image: url(:/pic/bt4_down.png);");
}

void config_setting::on_pushButton_4_released()
{
    ui->pushButton_4->setStyleSheet("border-image: url(:/pic/bt4_up.png);");
}

void config_setting::on_pushButton_5_pressed()
{
    ui->pushButton_5->setStyleSheet("border-image: url(:/pic/bt5_down.png);");
}

void config_setting::on_pushButton_5_released()
{
    ui->pushButton_5->setStyleSheet("border-image: url(:/pic/bt5_up.png);");
}

void config_setting::on_pushButton_6_pressed()
{
    ui->pushButton_6->setStyleSheet("border-image: url(:/pic/bt6_down.png);");
}

void config_setting::on_pushButton_6_released()
{
    ui->pushButton_6->setStyleSheet("border-image: url(:/pic/bt6_up.png);");
}

void config_setting::on_pushButton_7_pressed()
{
    ui->pushButton_7->setStyleSheet("border-image: url(:/pic/bt7_down.png);");
}

void config_setting::on_pushButton_7_released()
{
    ui->pushButton_7->setStyleSheet("border-image: url(:/pic/bt7_up.png);");
}

void config_setting::on_pushButton_8_pressed()
{
    ui->pushButton_8->setStyleSheet("border-image: url(:/pic/bt8_down.png);");
}

void config_setting::on_pushButton_8_released()
{
    ui->pushButton_8->setStyleSheet("border-image: url(:/pic/bt8_up.png);");
}

void config_setting::on_pushButton_9_pressed()
{
    ui->pushButton_9->setStyleSheet("border-image: url(:/pic/bt9_down.png);");
}

void config_setting::on_pushButton_9_released()
{
    ui->pushButton_9->setStyleSheet("border-image: url(:/pic/bt9_up.png);");
}

void config_setting::on_pushButton_0_pressed()
{
    ui->pushButton_0->setStyleSheet("border-image: url(:/pic/bt0_down.png);");
}

void config_setting::on_pushButton_0_released()
{
    ui->pushButton_0->setStyleSheet("border-image: url(:/pic/bt0_up.png);");
}

void config_setting::on_pushButton_del_pressed()
{
    ui->pushButton_del->setStyleSheet("border-image: url(:/pic/btdel_down.png);");
}

void config_setting::on_pushButton_del_released()
{
    ui->pushButton_del->setStyleSheet("border-image: url(:/pic/btdel_up.png);");
}


void config_setting::on_pushButton_ac_pressed()
{
    ui->pushButton_ac->setStyleSheet("border-image: url(:/pic/btac_down.png);");
}

void config_setting::on_pushButton_ac_released()
{
    ui->pushButton_ac->setStyleSheet("border-image: url(:/pic/btac_up.png);");
}


void config_setting::on_pushButton_colon_pressed()
{
    ui->pushButton_colon->setStyleSheet("border-image: url(:/pic/colon_down.png);");

}

void config_setting::on_pushButton_colon_released()
{
    ui->pushButton_colon->setStyleSheet("border-image: url(:/pic/colon_up.png);");
}

void config_setting::on_pushButton_minus_pressed()
{
    ui->pushButton_minus->setStyleSheet("border-image: url(:/pic/minus_down.png);");
}

void config_setting::on_pushButton_minus_released()
{
    ui->pushButton_minus->setStyleSheet("border-image: url(:/pic/minus_up.png);");
}


int config_setting::volume_state(int index)
{
    int volume_level = 80;
    switch (index) {
    case 0:
        volume_level = 0;
        break;
    case 1:
        volume_level = 50;
        break;
    case 2:
        volume_level = 60;
        break;
    case 3:
        volume_level = 70;
        break;
    case 4:
        volume_level = 80;
        break;
    case 5:
        volume_level = 85;
        break;
    case 6:
        volume_level = 90;
        break;
    case 7:
        volume_level = 95;
        break;
    case 8:
        volume_level = 97;
        break;
    case 9:
        volume_level = 100;
        break;
    default:
        volume_level = 80;
        break;
    }

    return volume_level;
}

void config_setting::on_cb_alarm_volume_currentIndexChanged(int index)
{

    char buf[SOUND_BUF];
    int volume_level;

    if (first_volume == true) {
        first_volume = false;
        return;
    }

    volume_level = volume_state(index);
    snprintf(buf, SOUND_BUF, "%s %d &", VOLUME_APP, volume_level);
    qDebug("now the volume is %s", buf);
    my_system(buf);

    bzero(buf, SOUND_BUF);


    snprintf(buf, SOUND_BUF, "%s %s%d.wav", AUDIO_APP, ALARM_SOUND_PATH, ui->cb_alarm_id->currentIndex());


    my_system(buf);


}

void config_setting::on_cb_alarm_id_currentIndexChanged(int index)
{
    char buf[SOUND_BUF];


    if (first_id == true) {
        first_id = false;
        return;
    }

    bzero(buf, SOUND_BUF);


    snprintf(buf, SOUND_BUF, "%s %s%d.wav", AUDIO_APP, ALARM_SOUND_PATH, index);


    my_system(buf);
}
