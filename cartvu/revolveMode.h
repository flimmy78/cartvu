#ifndef REVOLVEMODE_H
#define REVOLVEMODE_H

#include <QDialog>
#include <QtGui/QPixmap>
#include <QTimer>
#include "camThread.h"
#include "config_sys.h"
#include "sensor.h"
#include "serialMode.h"
#include "read_sys.h"
#include "light.h"
#include "login.h"
//#define    X86


#ifndef     X86
#define         REVOLVE_PIC_DIR     "/cartvu/revolve/"
#else
#define         REVOLVE_PIC_DIR     "../cartvu/revolve_pic/"
#endif

#define PIC_SIZE   40
#define     CARTVU_MODE_PIC         "/cartvu/logocartvu/logocartvu.png"


#define     SELF_MODE_PIC         "/cartvu/userdef/userdef.png"



namespace Ui {
    class revolveMode;
}

class revolveMode : public QDialog {
    Q_OBJECT
public:
    revolveMode(QWidget *parent = 0);
    ~revolveMode();
//cartvu模式初始化
    void cartvu_mode_init();
    //self模式初始化
    void self_init();
    void set_button_back();
    void time_pic_init();

protected:
    void changeEvent(QEvent *e);

public:
    int standby_mode;
    QTimer start_timer;
    QTimer internalTimer;
private:
    Ui::revolveMode *ui;
    //bool revolve_flag;
    int i;

    char pic[PIC_SIZE];
    QPixmap re_pic;
    QPixmap self_pic;
    QPixmap cartvu_pic;

    int switch_time;
    int  range_start;
    int  range_stop;
    camThread *camera;

private slots:
    //void on_return_button_clicked();
    //当背光灯关闭时，点击屏幕的反映
    void on_log_in_out_button_clicked();

    void on_return_button_clicked();
    //revolve模式启动
    void revolve_pic_start();
    //显示某种模式
    void init_mode();
    //当有告警产生时，关闭revolve模式等其他模式，显示告警图片
    void return_serial_mode();
};

#endif // REVOLVEMODE_H
