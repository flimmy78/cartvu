#ifndef READ_SYS_H
#define READ_SYS_H


#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <QTimer>

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlRecord>

#include <QDateTime>
#include <time.h>


#include "recordLog.h"

#include "sensor.h"
#include "client.h"
#include "config_sys.h"

#include "login.h"
#include "camThread.h"
#include "synchTime.h"

#include "light.h"
#include "watchdog.h"
#include "ftpput.h"


#define HTTP_PORT       80

#define LOG_DELAY_TIME   15


#define CARTVU_VERSION          "Version"
#define CARTVU_ALERTIMAGE       "AlertImage"
#define CARTVU_STATIS           "Statis"
#define BUF_MAXSIZE     200

#define DEFAULT_LOCAL_PATH   "/cartvu/temp/cartvu"

#define CARTVUVERSION_DB         "/cartvu/basis/CartvuVersion.db"


//cartvu�������ļ����λ��
#define         CFG_SYS         "/cartvu/config/config.sys"
#define         DEF_CFG_SYS      "/cartvu/config/bak_config.sys"
#define         TMP_CFG_SYS      "/cartvu/config/tmp_config.sys"


//�����ļ���ʱ��ŵ�λ��
#define         TMP_FILE            "/cartvu/temp/tmp"

#define COMMON_TMP  "/tmp/tmp"
#define COMMON_TMP_DIR  "/tmp/tmp_dir/"

//cartvu�������ļ����λ��
#define CONFIG_SYS    "/cartvu/config/config.sys"
//#define DOWN_LOAD_CONFIG_SYS "/AdNode/cartvu/basis/config.sys"
//��������config.sys�ļ�����λ��
#define DOWN_LOAD_CONFIG_SYS "/AdNode/cartvu/config/config.sys"
//ÿ�����س���ʱ����ŵĴ�����Ϣ
#define ERROR_DOWNLOAD  "/etc/error_download"




#define ZONE_STR_SIZE   10

//delay time scope
#define RANDOM_SCOPE   10

#define PASSWD_SIZE  30








//the  interval of time to adjust  back light
#define ADJUST_BAKLIGHT_INTERVAL   1




//#define DOWNLOAD_COUNT   5
#define ZIP_TYPE     ".zip"


#define CMD_LEN_SIZE   10




#define STRING_SIZE  30


#define NOW_ERROR_STATUS   "/cartvu/proc/cartvu/now_error_status"

struct version {
    char software[STRING_SIZE];
    char major_ver[STRING_SIZE];
    char minor_ver[STRING_SIZE];
    struct version *next;
};




class read_sys: public QObject{
    Q_OBJECT
public:
    read_sys();
    read_sys(global_config *);
    ~read_sys();
    //����config.sys�ļ�
        void sys_decode(const char *arg, global_config *conf);
    //��eth0-setting�ļ�
        void read_eth0(const char *arg);
    //����config.sys�ļ��е�ʱ��һ��
        void decode_date_line(QString line, global_config *config_sys);
    //����config.sys�ļ��е�ÿһ��
        void par_analyse(QString line, global_config *config_sys);
    //�Ӽ����滻����ʧЧ
        void zone_swap(char *p);
    //��openningtime��closing time��ת��Ϊ�� 
        unsigned int qstring_to_sec_time(QString time);
    //���������ָ���ļ����������
        void decode_passwd(const char *passwd, const char *dir);
    //�������ڵ�¼����ǰ�������ʱ
        void get_file_delay();
    //���Է���������ͨ��
        void down_load_test();
    //����http��¼����  ����mac  ��ȡftp passwd ��user passwd
        void post_mac();
        //���passwd���õ�ǰ��config.sys�����ص�config.sys�����ļ�����ʱ��ԱȾ����Ƿ񸲸ǵ�ǰ����
        void analyse_passwd(QString tmp);
        //�������ܵ�������İ汾��Ϣ
        void analyse_string(QString tmp);
        //�Ƚ�����İ汾��Ϣ
        void compare_version();
        //�������ݿ�
        void update_sqlite3();
        //set the  parameters  of config.sys
        void initial_all_global_config();
    //���ñ���ĸ澯ͼƬ����
        void image_quality_fun();
        //�رձ���
        void closing_light();
        //�򿪱���
        void openning_light();

        //��ʾlogin����
        void start_global_screen();
        //��ѹzip��
        void unzip_file();
        //����������
        bool software_check(const char *file);
        void try_post_mac();
        //��ʾ��ǰ����İ汾��
        void show_version();
        //���������ȼ�
        int volume_state();
        int download_userdef();


public:
        QString encode_passwd;
        char en_passwd[PASSWD_SIZE];
        client *delay_client;
        QString rec_string;

        QString full_mac;
        QString plain_mac;
        QString lane_no;
        client *http_client;
        QString l_server;

        QSqlDatabase  cartvu_version_db;
        //QSqlQuery query;
        QString software;
        QString  version;
        QString major_ver;
        QString minor_ver;

        QString software_name;
        QString software_ver;
        QString software_major;
        QString software_minor;
        
        char ftp_user[FTP_SIZE];//ftp user
        char ftp_passwd[FTP_SIZE];//ftp passwd
        char local_server[FTP_SIZE];//local server ip
        char user_passwd[FTP_SIZE]; // user passwd
        QDateTime current_time;
        bool restart_flag;
        QString app_name;
        light *lgt;
        QTimer lgt_timer;
        int try_soft_count;
        char remote_path[BUF_MAXSIZE];
        char local_path[BUF_MAXSIZE];
        bool config_flag_ok;
        QString cartvu_version;
        //QTimer watchdog_timer;


    //��login���浽serial����ĳ�ʱʱ��
        QTimer log_delay_timer;

private:

        global_config   *out_config_sys;

        //global_config *now_conf_sys;
        QTimer random_timer;
        int delay_time;

        QTimer closing_timer;
        QTimer openning_timer;
        QTimer reset_timer;
private slots:
        void is_logout_ok();//���ǳ����
        void log_out();//�ǳ�
        void deal_update_app();//�Խ��յ��������Ϣ����ѡ��������
        void check_update_app();//���������������
        void random_delay();//�����ʱ
        void down_load_file();//����������ȷ����ʱ�Ĳ���
        void info_flash();//�Խ��ܵ�����Ϣ���д���
        
        void closing_machine();//�رջ������ص�����
        void openning_machine();//�򿪱���

        void reset_machine();//ȫ�ֶ�ʱ��λ��������

        //void feed_dog_count();

        //struct sys_time sys_mod_date;

        void initial_part_global_config();//���粻ͨ���߸��������֮��ĺ���

        void initial_all_par();// /���粻ͨ���߸��������֮��ĺ���
signals:
        void config_ok();//���������ļ�����ok���ź�
        void log_out_sig();//�����ǳ����ź�
        void show_hide_button(bool flag);// �������ذ������źţ�Ϊ�رձ���ʹ��
        void read_config_ok();//�����Ѿ���ɶ�ȡconfig.sys�ļ����ź�

};



#endif
