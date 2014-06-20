#ifndef CONFIG_SETTING_H
#define CONFIG_SETTING_H

#include <QDialog>
#include <QVariant>
#include <QFile>
#include <QString>
#include <QDateTime>
#include <QWidget>

#include "setting.h"
#include "read_sys.h"
#include "config_sys.h"







#define NOW_SIZE   50





namespace Ui {
    class config_setting;
}

class config_setting : public QDialog {
    Q_OBJECT
public:
    config_setting(QWidget *parent = 0);
    ~config_setting();
    //����settings����ʱ������ʾ��ǰcofig.sys����Ϣ���
    void config_init();
    //���벻ͬ��config.sys�ļ���ʾ��settings����
    void read_config_to_show(const char *cfg_sys);
    //����ǰsettings�������Ϣд�� /cartvu/config/config.sys
    void save_to_config(const char * config_file);

    int volume_state(int index);
public:

    bool first_volume;
    bool first_id;

    global_config now_config_sys;
    global_config default_config_sys;
    QString now_lineEdit_string;

    Ui::config_setting *config_form;
protected:
    void changeEvent(QEvent *e);

private:
    Ui::config_setting *ui;

private slots:
    void on_cb_alarm_id_currentIndexChanged(int index);
    void on_cb_alarm_volume_currentIndexChanged(int index);
    void update_now_string(QString info);



//��ȡĬ�����õİ�ť  ���ߵ�ǰ���õİ�ť
    void on_pushButton_minus_released();
    void on_pushButton_minus_pressed();
    void on_pushButton_colon_released();
    void on_pushButton_colon_pressed();
    void on_pushButton_del_released();
    void on_pushButton_del_pressed();
    void on_pushButton_ac_released();
    void on_pushButton_ac_pressed();
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
    void on_pushButton_0_released();
    void on_pushButton_0_pressed();
    void on_pushButton_minus_clicked();
    void on_pushButton_colon_clicked();
    void on_pushButton_del_clicked();
    void on_pushButton_ac_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_0_clicked();

    void on_button_read_default_settings_clicked();
//�ǵ�ǰ��������Ч������ϵͳ
    void on_button_modify_settings_clicked();
//������һ������
    void on_button_return_clicked();

signals:
     void sendChar(QChar ch);
     void sendInt(int);
};

#endif // CONFIG_SETTING_H
