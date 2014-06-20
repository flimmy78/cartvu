#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QByteArray>
#include <QLineEdit>
#include <QPalette>
#include <QTimer>


#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "camThread.h"

#include "revolveMode.h"

#include "client.h"
#include "read_sys.h"

#include "ftpput.h"
#include "watchdog.h"

//每隔10秒发送传感器和camera,help信息给localserver
#define GLOBAL_TIMER    10


#define CASHIER_SIZE   40

#define STATUS_SIZE    20
//八个状态信息
#define STATUS_SENSOR_SIZE        8


//重复登录的间隔    此处已取消
#define LOG_INTERVAL  1



#define SOUND_BUF   100

#define CLICK_SOUND  "/cartvu/sound/"
#define COMMON_SOUND  "common"



// 复位 wl330设备的时间间隔 当登录失败时
#define ROUTER_COUNT  18    //180 sec


//恢复到待机界面时的时间间隔
#define MODE_TIMER   15




namespace Ui {
    class login;
}

class login : public QDialog {
    Q_OBJECT
public:
    login(camThread *cam, QWidget *parent = 0);
    ~login();
    void login_init();
    void setstr(QString);
    //重复登录函数
    void re_login();
    //隐藏大的按钮 为关闭背光灯设计
    void hide_big_button();
    bool write_to_sendinfo(QString rec_string, struct send_info *info);
    void write_info_string(QString tmp, struct send_info *info);
    void confirmed_post();
    void show_post();


protected:
    void changeEvent(QEvent *e);

private:
    Ui::login *ui;
    camThread *camera;
public:
    QString inputstring;
    int count;


    QTimer global_status;
    QString rec_string;

    client *http_client;

    client *info_client;
    //bool mac_log_ok_flag;
    char buf[SOUND_BUF];

    QLabel *version_label;
    QLabel *kings_label;
    QTimer mode_timer;
    QString now_local_server;
    QMessageBox box;
    QTimer  close_box;
    QAbstractButton * confirmButton;
    bool sendinfo_timeout;
    bool confirmed_flag;

private slots:

    void on_pushButton_ac_released();
    void on_pushButton_ac_clicked();
    void on_big_button_clicked();
    /*
    void on_exit_button_released();
    void on_exit_button_pressed();
    void on_exit_button_clicked();
*/
    void on_login_button_released();
    void on_login_button_pressed();
    void on_pushButton_del_released();
    void on_pushButton_del_pressed();
    void on_pushButton_0_released();
    void on_pushButton_0_pressed();
    void on_pushButton_9_released();
    void on_pushButton_9_pressed();
    void on_pushButton_8_released();
    void on_pushButton_8_pressed();
    void on_pushButton_7_released();
    void on_pushButton_7_pressed();
    void on_pushButton_6_released();
    void on_pushButton_6_pressed();
    void on_pushButton_5_released();
    void on_pushButton_5_pressed();
    void on_pushButton_4_released();
    void on_pushButton_4_pressed();
    void on_pushButton_3_released();
    void on_pushButton_3_pressed();
    void on_pushButton_2_released();
    void on_pushButton_2_pressed();
    void on_pushButton_1_released();
    void on_pushButton_1_pressed();

    void on_login_button_clicked();

    void on_pushButton_del_clicked();
    void on_pushButton_ac_pressed();
    void on_pushButton_0_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_1_clicked();
    /*
    void on_setting_released();
    void on_setting_pressed();
    void on_setting_clicked();
*/
//定时发送给localserver
    void send_status_to_s();
    //发送状态给localserver收到ok时
    void judge_ok() ;


    void show_big_button(bool flag);
//从非待机到待机时，选择某种模式去显示
    void select_mode_start();

    void close_box_slot();

    void receive_message();
    void confirmed_message();
    void confirmed2_message();
};

#endif // LOGIN_H
