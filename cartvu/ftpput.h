#ifndef FTPPUT_H
#define FTPPUT_H

#include <QThread>
#include <QDebug>
#include <QDateTime>
#include <QString>

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QEventLoop>
#include <QDateTime>




#include <QMutex>

#include "read_sys.h"
#include "serialMode.h"
#include "client.h"
#include "sensor.h"
#include "config_sys.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
//#include <linux/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/time.h>


#define CARTVU_DB   "/cartvu/basis/Cartvu.db"
//ÿ��60�뽫ͳ��д�����ݿ�
#define   WRITE_TIME        60    //sec


//ÿ��120�뽫���ݿ��еǼ�Ϊδ�ϴ���ͼƬ�ϴ�
#define FTPPUT_TIME      120       //sec
#define FTPPUT_COUNT     FTPPUT_TIME/WRITE_TIME

#define CARTVU_STATIS  "Statis"
#define CARTVU_ALERT_IMAGE  "AlertImage"

#define UNUPLOADED          0
#define UPLOADED            1

#define DATE_SIZE   12

#define FILE_SIZE  100  //23



//ɾ��30����ǰ�ĸ澯ͳ�����ݼ�ͼƬ
#define CLEAR_DAYS  30

//ɾ��90����ǰ��ͳ������
#define STATIS_CLEAR_DAYS  90    // save 3 mons


#define ADNODE_ALERT_DIR   "/AdNode/cartvu/images/"


//���ݿ��� alertimage��flag��4����־
#define MAKING_INFORMATION          0
#define INFORMATION_NOT_UPLOADED    1
#define IMAGE_UPLOADED              2
#define UPLOADED_OK                 3


//���뻹��update
#define INSERT_FLAG                 true


//Cartvu.db�е�statis��
struct statis {
    char statis_date[DATE_SIZE];
    unsigned int cart_num;
    unsigned int alert_num;
    unsigned int confirm_num;
    unsigned int upload_flag;
};

//Cartvu.db�е�alertimage��
struct alert_image {
    char file_name[FILE_SIZE];
    char alert_time[FILE_SIZE];
    char cashier[FILE_SIZE];
    char barcode[FILE_SIZE];
    char confirmed;
    char flag;
};


//˫�������ڱ����ϴ�����
struct alert_image_more {
    struct alert_image alert_image;
    struct alert_image_more *next;
    struct alert_image_more *front;
};


class ftpput : public QThread

{
    Q_OBJECT

public:
    ftpput();
    ~ftpput();
    //�߳���������
    void run();
    //д��statis����
    void write_statis();
    //�����������statis���Ƿ�Ҫ�����ϴ���
    void check_statis();
    //���AlertImage���Ƿ�Ҫ�����ϴ���
    void check_alarm_image();
    //ʱ���ת������
    int qstring_to_day_time(QString time);
    //�������ݿ������д���ṹ������
    void write_to_struct();
    //�ϴ�ͳ������
    void check_is_uploaded();
    //��δ�ϴ��ĸ澯��Ϣд���ϴ����л���ɾ�������ݿⲻƥ���ͼƬ
    void check_information_uploaded();
    //��ʾ�ϴ��澯�Ķ��� 
    void show_ftpput();
    //ɾ��ͳ������
    void delete_from_statis();
    //����ǰ�ĸ澯��Ϣд�����ݿ�
    bool update_sqlite_alert_image(struct alert_image *tmp_alert_image, bool flag);
    //����http����  ���͸澯��Ϣ��localserver
    void transmit_http_request(struct alert_image *tmp_alert_image);
    //��ʼִ���ϴ��澯���������Ϣ��localserver
    void update_alarm_image();

    void first_open_db();

public:
    QString StatisDate;
    unsigned int CartNum;
    unsigned int AlertNum;
    unsigned int ConfirmNum;
    char UploadFlag;
    client *http_client;
    client *alert_http_client;
    QString rec_string;
    QEventLoop *loop;
    QEventLoop *image_loop;

    QString now_time;
    int now_day;
    int compare_day;
    QString sqlite_file_name;


    char ftp_user[FTP_SIZE];//ftp user
    char ftp_passwd[FTP_SIZE];//ftp passwd
    char local_server[FTP_SIZE];//local server ip


    struct alert_image *record_tmp;

    bool receive_status;

private slots:
    //�ϴ�statis���ݸ�localserver��ı����ݿ�ı�־
    void change_sqlite_status();
    //�����ϴ��澯��Ϣ�󣬵ȴ�localserver�Ļ�Ӧ�Ƿ�Ҫ�ı����ݿ�
    void change_sqlite_alert_image();
    // ����ǰ�ĸ澯��Ϣд���ṹ��
    void making_alert_image();
    // Ϊ�����澯ʱ ����ĸ澯���ݽṹ�ռ�  ��ǰ�ĸ澯��Ϣ������cartvu_alert_image�ṹ����
    void malloc_size_for_alert();

};

#endif // FTPPUT_H
