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
//每隔60秒将统计写入数据库
#define   WRITE_TIME        60    //sec


//每隔120秒将数据库中登记为未上传的图片上传
#define FTPPUT_TIME      120       //sec
#define FTPPUT_COUNT     FTPPUT_TIME/WRITE_TIME

#define CARTVU_STATIS  "Statis"
#define CARTVU_ALERT_IMAGE  "AlertImage"

#define UNUPLOADED          0
#define UPLOADED            1

#define DATE_SIZE   12

#define FILE_SIZE  100  //23



//删除30天以前的告警统计数据及图片
#define CLEAR_DAYS  30

//删除90天以前的统计数据
#define STATIS_CLEAR_DAYS  90    // save 3 mons


#define ADNODE_ALERT_DIR   "/AdNode/cartvu/images/"


//数据库中 alertimage的flag的4个标志
#define MAKING_INFORMATION          0
#define INFORMATION_NOT_UPLOADED    1
#define IMAGE_UPLOADED              2
#define UPLOADED_OK                 3


//插入还是update
#define INSERT_FLAG                 true


//Cartvu.db中的statis表
struct statis {
    char statis_date[DATE_SIZE];
    unsigned int cart_num;
    unsigned int alert_num;
    unsigned int confirm_num;
    unsigned int upload_flag;
};

//Cartvu.db中的alertimage表
struct alert_image {
    char file_name[FILE_SIZE];
    char alert_time[FILE_SIZE];
    char cashier[FILE_SIZE];
    char barcode[FILE_SIZE];
    char confirmed;
    char flag;
};


//双链表用于保存上传队列
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
    //线程启动函数
    void run();
    //写进statis表函数
    void write_statis();
    //开机启动检查statis表是否要清理，上传等
    void check_statis();
    //检查AlertImage表是否要清理，上传等
    void check_alarm_image();
    //时间戳转换函数
    int qstring_to_day_time(QString time);
    //将从数据库读到的写进结构体里面
    void write_to_struct();
    //上传统计数据
    void check_is_uploaded();
    //将未上传的告警信息写进上传队列或者删除与数据库不匹配的图片
    void check_information_uploaded();
    //显示上传告警的队列 
    void show_ftpput();
    //删除统计数据
    void delete_from_statis();
    //将当前的告警信息写进数据库
    bool update_sqlite_alert_image(struct alert_image *tmp_alert_image, bool flag);
    //发送http请求  发送告警信息给localserver
    void transmit_http_request(struct alert_image *tmp_alert_image);
    //开始执行上传告警队列里的信息给localserver
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
    //上传statis数据给localserver后改变数据库的标志
    void change_sqlite_status();
    //发起上传告警信息后，等待localserver的回应是否要改变数据库
    void change_sqlite_alert_image();
    // 将当前的告警信息写进结构体
    void making_alert_image();
    // 为产生告警时 分配的告警数据结构空间  当前的告警信息保存在cartvu_alert_image结构体里
    void malloc_size_for_alert();

};

#endif // FTPPUT_H
