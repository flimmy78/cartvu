#ifndef CONFIG_SYS_H
#define CONFIG_SYS_H

#include <stdio.h>
#include <stdlib.h>
#include <QDebug>
#include <QString>
#include <QFile>

#define REBOOT_TIME          "/etc/rebootTime"

#include "watchdog.h"

//保存的eth0-setting的位置
#define ETH0SETTING   "/etc/eth0-setting"



#define READ_SIZE   50

#define IP_SIZSE                        16
#define DEFAULT_LOCAL_SERVER            "192.168.1.59"
#define CMD_SIZE                        300
#define DEFAULT_USER                    "root"
#define  DEFAULT_PASSWD                 "hsq1998"

//#define   DEFAULT_FILE      "/download/eth0-setting"

#define NAME_SIZE   100





//4 standby mode
#define CARTVU_MODE   0
#define SERIAL_MODE   1
#define  REVOLVE_MODE   2
#define SELFDF_MODE   3



// the image of the camera snashot !! 80 = 80%
#define IMAGE_QUALITY_H   0  //80
#define IMAGE_QUALITY_M   1  //60
#define IMAGE_QUALITY_L   2  //30


#define IMAGE_QUALITY_HH_PER   80


#define IMAGE_QUALITY_H_PER   80
#define IMAGE_QUALITY_M_PER   60
#define IMAGE_QUALITY_L_PER   30


#define SINGLE_MODE     0
#define CARTVU_FULL_MODE     1


#define FTP_SIZE   40




extern int my_system(const char *);


struct sys_time {
    int year;
    int mon;
    int mday;
    int hour;
    int min;
    int sec;
};

struct sys_network {
    char local_server[IP_SIZSE];
};





struct sys_global {
    unsigned int openning_time;
    char openning_time_str[READ_SIZE];
    unsigned int closing_time;
    char closing_time_str[READ_SIZE];
    int time_zone;
    char saveing_time;
    char brightness;
};



struct sys_working_mode {
    char working_mode;
    char camera_type;//0-PAL, 1-NTSC
    char I_number;
    unsigned int E2_time_out;
    unsigned int alarm_interval;
};


struct sys_alarm {
    char blinking_time;
    unsigned int image_time;
    char alarm_mode;
    char alarm_id;
    char alarm_volume;
    char alarm_msg;
};

struct revolve_range {
    unsigned int start;
    unsigned int end;
};

struct sys_standby {
    char standby_mode;
    struct revolve_range revolve_range;
    char revolve_str[READ_SIZE];
    unsigned int revolve_period;
};


struct sys_other {
    char image_quality;
    char extra_iteam_info;
    unsigned int reset_time;
    char reset_time_str[READ_SIZE];
    char kings_name[NAME_SIZE];
    unsigned int cashier_timeout;
    char settings;
};

class global_config {

public:
    global_config();
    //~global_config();
    void down_load(const char *, const char *, const char *);
    //ftpget函数
    void down_load(const char *, const char *, const char *, const char *, const char *, const char *);
    //上传ftpput函数
    void ftpput_to_server(const char *, const char *, const char *, const char *, const char *, const char *);
// 显示是下载成功还是失败
    void show_error(const char * des_file, const char *sour_file, const char * arg);
//显示是上传成功还是失败
    void ftpput_error(const char * des_file, const char *sour_file, const char * arg);
public:
    struct sys_time sys_mod_date;
    struct sys_network sys_network;
    struct sys_global sys_global;
    struct sys_working_mode sys_working_mode;
    struct sys_alarm sys_alarm;
    struct sys_standby sys_standby;
    struct sys_other sys_other;
public:
    bool down_load_ok;
};











#endif // CONFIG_SYS_H
