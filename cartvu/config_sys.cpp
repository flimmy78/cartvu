#include <string.h>
#include "config_sys.h"
//#include "read_sys.h"


extern watchdog *global_wdg;
extern int ftpflag;

extern  void recordLog(int type, int code, char *info);


global_config::global_config()
{
    qDebug() << " global_conf_sys global start";
    //down_load("/etc/config.sys", "/download/config.sys", "/etc/error_download");
    //down_load(CFG_SYS, "/download/config.sys", "/etc/error_download");
    //down_load("/etc/eth0-setting", "/download/eth0-setting", "/etc/error_download");
}




void global_config::down_load(const char * user, const char * passwd, const char * local_server, const char * des_file, const char * sour_file, const char *des_error)
{
    char cmd[CMD_SIZE] = {0};

    global_wdg->count = 0;
    ftpflag = 1;
    qDebug() << "feed the dog count to 0";

    down_load_ok = false;
    //./down_load.sh 192.168.1.59 root hsq1998 /download/eth0-setting
    //snprintf(cmd, CMD_SIZE, "./down_load.sh %s %s %s %s", DEFAULT_LOCAL_SERVER, DEFAULT_USER, DEFAULT_PASSWD, des_file);

    // ftpget -u root -p hsq1998 192.168.1.59  /etc/eth0-setting /download/eth0-setting 2>>/error_download
    //snprintf(cmd, CMD_SIZE, "ftpget -u %s -p %s %s %s %s 2>%s", DEFAULT_USER, DEFAULT_PASSWD, DEFAULT_LOCAL_SERVER, des_file, sour_file, des_error);
    snprintf(cmd, CMD_SIZE, "ftpget -u %s -p %s %s %s %s 2>%s", user, passwd, local_server, des_file, sour_file, des_error);
    //system(cmd);
    my_system(cmd);



    show_error(des_file, sour_file, des_error);
    printf("%s\n", cmd);
    // printf("strlenlen is %d\n", strlen(cmd));
    // printf("now is downloading %s\n", sour_file);


    global_wdg->count = 0;
    ftpflag = 0;
    qDebug() << "feed the dog count to 0";
}

void global_config::ftpput_to_server(const char * user, const char * passwd, const char * local_server, const char * des_file, const char * sour_file, const char *des_error)
{
    char cmd[CMD_SIZE] = {0};

    global_wdg->count = 0;
    ftpflag = 1;
    qDebug() << "feed the dog count to 0";

    down_load_ok = false;
    snprintf(cmd, CMD_SIZE, "ftpput -u %s -p %s %s %s %s 2>%s", user, passwd, local_server, des_file, sour_file, des_error);
    //system(cmd);
    my_system(cmd);



    ftpput_error(des_file, sour_file, des_error);
    printf("%s\n", cmd);
    // printf("strlenlen is %d\n", strlen(cmd));
    // printf("now is downloading %s\n", sour_file);

    ftpflag = 0;
    global_wdg->count = 0;
    qDebug() << "feed the dog count to 0";
}


void global_config::down_load( const char * des_file, const char * sour_file, const char *des_error)
{
    char cmd[CMD_SIZE] = {0};

    global_wdg->count = 0;
    ftpflag = 1;
    snprintf(cmd, CMD_SIZE, "ftpget -u %s -p %s %s %s %s 2>%s", DEFAULT_USER, DEFAULT_PASSWD, DEFAULT_LOCAL_SERVER, des_file, sour_file, des_error);
    //system(cmd);
    my_system(cmd);
    show_error(des_file, sour_file, des_error);

    global_wdg->count = 0;
    ftpflag = 0;
    //printf("%s\n", cmd);
}





void global_config::show_error(const char * des_file, const char *sour_file, const char * arg)
{
    QString line;
    QFile sys_file(arg);
    bool error_flag = false;
    down_load_ok = false;
    char buf[400];

    if (sys_file.exists()) {
        if (sys_file.open(QIODevice::ReadOnly)) {
            QTextStream stream(&sys_file);
            do {
                line = stream.readLine();
                if (line.compare("") == 0) {
                    if (error_flag == false) {
                        qDebug("download file  %s to %s is ok", sour_file, des_file);
                        down_load_ok = true;
                        sprintf(buf, "download file  %s to %s is ok", sour_file, des_file);
                        recordLog(1, 32, buf);
                    }
                    else {
                        qDebug("download file %s to %s is error", sour_file, des_file);
                        down_load_ok = false;
                        sprintf(buf, "download file %s to %s is error", sour_file, des_file);
                        recordLog(1, 32, buf);
                        break;
                    }
                }
                else {
                    qDebug() << line;
                    error_flag = true;
                }
            } while(!line.isNull());
            sys_file.close();
        } else {
            perror("open file fail");
            exit(1);
        }
    } else {
        printf("%s is not exit", arg);
        exit(1);
    }

}
//#define TMP_BUF_SIZE 400

void global_config::ftpput_error(const char * des_file, const char *sour_file, const char * arg)
{
    QString line;
    QFile sys_file(arg);
    bool error_flag = false;
    down_load_ok = false;

    char buf[400] = {0};
    if (sys_file.exists()) {
        if (sys_file.open(QIODevice::ReadOnly)) {
            QTextStream stream(&sys_file);
            //snprintf(buf, TMP_BUF_SIZE, "cat %s", arg);
           // my_system(buf);
            //qDebug() << buf;
            do {
                line = stream.readLine();
                if (line.compare("") == 0) {
                    if (error_flag == false) {
                        qDebug("ftpput  file  %s to %s is ok", des_file, sour_file);
                        down_load_ok = true;
                        sprintf(buf, "ftpput  file  %s to %s is ok", des_file, sour_file);
                        recordLog(1, 33, buf);
                    }
                    else {
                        qDebug("ftpput file %s to %s is error", des_file, sour_file);
                        down_load_ok = false;
                        sprintf(buf, "ftpput file %s to %s is error", des_file, sour_file);
                        recordLog(1, 33, buf);
                        break;
                    }
                }
                else {
                    qDebug() << line;
                    error_flag = true;
                }
               // qDebug() << "now the line is ";
                //qDebug() << line;
            } while(!line.isNull());
            sys_file.close();
        } else {
            perror("open file fail");
            exit(1);
        }
    } else {
        printf("%s is not exit", arg);
        exit(1);
    }

}
