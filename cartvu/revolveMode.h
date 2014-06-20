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
//cartvuģʽ��ʼ��
    void cartvu_mode_init();
    //selfģʽ��ʼ��
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
    //������ƹر�ʱ�������Ļ�ķ�ӳ
    void on_log_in_out_button_clicked();

    void on_return_button_clicked();
    //revolveģʽ����
    void revolve_pic_start();
    //��ʾĳ��ģʽ
    void init_mode();
    //���и澯����ʱ���ر�revolveģʽ������ģʽ����ʾ�澯ͼƬ
    void return_serial_mode();
};

#endif // REVOLVEMODE_H
