#ifndef SERIALMODE_H
#define SERIALMODE_H

#include <QDialog>
#include <QPixmap>
#include <QImage>
#include <QTimer>
#include <QDateTime>
#include <sys/shm.h>
#include <QLabel>

#include <QProcess>
#include <QStringList>
#include <stdlib.h>
#include <stdio.h>
#include <QPushButton>
#include <QMutex>

//#include <QPainter>
#include "sensor.h"
#include "camThread.h"

#include "config_sys.h"
#include "revolveMode.h"
#include "read_sys.h"

#include "setting.h"

// do you need to show the sensor on the title ?
#define SENSOR_SHOW_HIDE  true

#define VOLUME_APP   "/test/volume_test"

#if 1///////////////////

#define AUDIO_APP   "/bin/aplay"
//#define ALARM_SOUND_PATH  "/test/beep.wav"
#define ALARM_SOUND_PATH  "/cartvu/alarm/"


#else/////////////////


#define AUDIO_APP   "/bin/madplay"
//#define ALARM_SOUND_PATH  "/test/BEEP.mp3"
#define ALARM_SOUND_PATH  "/test/just_like_me.mp3"


#endif/////////////////

//#define SHARE_APP    "/setting_qt"

#define SERIAL_BG_PIC            "/cartvu/logocartvu/standby.png"

#define IMG_SHOW_WIDTH      784
#define IMG_SHOW_HEIGHT     580




#define LABEL_NUM          9

#define SINGLE_ALARM  0
#define CYCLE_ALARM  1

namespace Ui {
    class serialMode;
}

class serialMode : public QDialog {
    Q_OBJECT
public:
    //serialMode(QWidget *parent = 0);
    //no return value
    serialMode(camThread *cam, QString b, QWidget *parent = 0);
    ~serialMode();
    void serila_init(void);
    //��ʼ���������澯Id��
    void play_audio_init(void);
    //�����澯��
    void play_audio();
    //int volume_state();
    //��ʼ��merchandise
    void merchandise_init();
    //����ģʽ������������ʾһ��ģʽ  ������ʾ
    void chose_screen();
    //��ʼ����revolveģʽ
    void init_revolve_pic();
    //����ģʽ������������ʾһ��ģʽ   �Ժ󴥷�����ʾ
    void now_chose_screen();

protected:
    void changeEvent(QEvent *e);

public:


    bool play_flag;
    QString aplayer_path;
    QStringList music_type;
    QProcess *process;
    QTimer cashier_timer;
    QLabel *global_cashier_label;
    QPushButton *global_cartvu_title;
    QString passwd;

    bool show_sensor_status_hide;
    int  switch_time;
    int  range_start;
    int  range_stop;
    QTimer image_timer;
    QTimer revolve_timer;
    bool alarm_flag;
private:
    Ui::serialMode *ui;
    //QPainter *painter;
   // QPixmap  video_pic;
    QImage  video_img;
    QTimer  date_timer;
    QTimer  tick_timer;
    QString cashier_no;
    camThread *camera;
    bool cam_flag;
    bool switch_flag;

    unsigned char *buffer;
    QPixmap pixmapToShow;

public slots:
    void on_logout_button_clicked();


private slots:
    void on_lane_button_clicked();
    void on_time_button_clicked();
    void on_title_button_clicked();
    void on_recover_button_clicked();
    void on_pushButton_hide_pressed();
    void on_pushButton_hide_clicked();
    void on_check_button_released();
    void on_check_button_pressed();
    void on_logout_button_released();
    void on_logout_button_pressed();
    void on_list_button_released();
    void on_list_button_pressed();
    void on_check_button_clicked();
    void on_list_button_clicked();
    //void on_logout_button_clicked();
    void date_time_flash();
    void tick_time_flash();
    void cam_flash();
    void show_sensor_state(struct sensor_all_att *);
    void show_alarm_and_twinkle(void);
    //qprocess������ɺ�Ĳۺ���
    void finished_playing(int,QProcess::ExitStatus);

//cashier timeout����ʾhelp
    void cashier_update(void);
//�澯��ʱ�󣬻��ߵ��check��ָ�������״̬
    void return_cam_status(void);
//����ر�ʱʹ��
    void show_recover_button(bool flag);
    //void paintEvent(QPaintEvent *);
    //��revolve��ʾ
    void revolve_pic();
signals:
    void sig_take_pic(void);
    void record_ok(void);
};

#endif // SERIALMODE_H
