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


//cartvu的配置文件存放位置
#define         CFG_SYS         "/cartvu/config/config.sys"
#define         DEF_CFG_SYS      "/cartvu/config/bak_config.sys"
#define         TMP_CFG_SYS      "/cartvu/config/tmp_config.sys"


//下载文件临时存放的位置
#define         TMP_FILE            "/cartvu/temp/tmp"

#define COMMON_TMP  "/tmp/tmp"
#define COMMON_TMP_DIR  "/tmp/tmp_dir/"

//cartvu的配置文件存放位置
#define CONFIG_SYS    "/cartvu/config/config.sys"
//#define DOWN_LOAD_CONFIG_SYS "/AdNode/cartvu/basis/config.sys"
//服务器的config.sys文件所在位置
#define DOWN_LOAD_CONFIG_SYS "/AdNode/cartvu/config/config.sys"
//每次下载出错时，存放的错误信息
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
    //解析config.sys文件
        void sys_decode(const char *arg, global_config *conf);
    //读eth0-setting文件
        void read_eth0(const char *arg);
    //解析config.sys文件中的时间一行
        void decode_date_line(QString line, global_config *config_sys);
    //解析config.sys文件中的每一行
        void par_analyse(QString line, global_config *config_sys);
    //加减号替换，已失效
        void zone_swap(char *p);
    //将openningtime及closing time等转换为秒 
        unsigned int qstring_to_sec_time(QString time);
    //解析传入的指定文件保存的密码
        void decode_passwd(const char *passwd, const char *dir);
    //主程序在登录下载前的随机延时
        void get_file_delay();
    //测试服务器的连通性
        void down_load_test();
    //发起http登录请求，  发送mac  获取ftp passwd 及user passwd
        void post_mac();
        //获得passwd后用当前的config.sys与下载的config.sys配置文件进行时间对比决定是否覆盖当前配置
        void analyse_passwd(QString tmp);
        //分析接受到的软件的版本信息
        void analyse_string(QString tmp);
        //比较软件的版本信息
        void compare_version();
        //更新数据库
        void update_sqlite3();
        //set the  parameters  of config.sys
        void initial_all_global_config();
    //设置保存的告警图片质量
        void image_quality_fun();
        //关闭背光
        void closing_light();
        //打开背光
        void openning_light();

        //显示login界面
        void start_global_screen();
        //解压zip包
        void unzip_file();
        //检查软件更新
        bool software_check(const char *file);
        void try_post_mac();
        //显示当前软件的版本号
        void show_version();
        //设置音量等级
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


    //从login界面到serial界面的超时时间
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
        void is_logout_ok();//检查登出情况
        void log_out();//登出
        void deal_update_app();//对接收到的软件信息进行选择更新软件
        void check_update_app();//发起软件更新请求
        void random_delay();//随机延时
        void down_load_file();//服务器能正确连上时的操作
        void info_flash();//对接受到的信息进行处理
        
        void closing_machine();//关闭机器，关掉背光
        void openning_machine();//打开背光

        void reset_machine();//全局定时复位机器函数

        //void feed_dog_count();

        //struct sys_time sys_mod_date;

        void initial_part_global_config();//网络不通或者更新完软件之后的函数

        void initial_all_par();// /网络不通或者更新完软件之后的函数
signals:
        void config_ok();//发送配置文件更新ok的信号
        void log_out_sig();//发出登出的信号
        void show_hide_button(bool flag);// 发出隐藏按键的信号，为关闭背光使用
        void read_config_ok();//发出已经完成读取config.sys文件的信号

};



#endif
