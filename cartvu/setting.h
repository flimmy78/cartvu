#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QLabel>

//#include "camThread.h"
#include "serialMode.h"
#include "login.h"
#include "revolveMode.h"
#include "read_sys.h"
#include "light.h"

#include "config_setting.h"

#include <QtGui/QApplication>
#include "MyInputPannelContext.h"

namespace Ui {
    class setting;
}

class setting : public QDialog {
    Q_OBJECT
public:
    setting(QWidget *parent = 0);
    ~setting();
    void setting_init();
    //获取ip函数
    void get_ip_fun(const char *cmd);
    //显示机器是什么时候开机的
    void show_reboot_time(const char *cmd);


public:
    bool telnet_flag;
    char buf[BUF_SIZE];
protected:
    void changeEvent(QEvent *e);

private:
    Ui::setting *ui;
    camThread *camera;
private slots:

    //void on_cam_type_button_clicked();
    void on_bt_config_setttings_clicked();
    void on_factory_button_clicked();
    void on_sensor_show_button_clicked();
    void on_setting_hide_button_clicked();
    void on_telnet_button_clicked();
    void on_reset_button_clicked();

    void on_return_button_clicked();
   // void on_serial_button_clicked();


    void show_recover_button(bool flag);
};

#endif // SETTING_H
