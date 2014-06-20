/**************************************************************************
  Program Name:cartvu
  Description:

  Author:Zhihao Zeng
  Date:2013-11-27

  Change log:


  Date:2013-12-28    add record log here
  Date:2014-01-06    modify the record log of ftpput,modify the light sensor record
  Date:2014-01-08    VERSION:1.18   modify the record log of network error
  Date:2014-02-10    VERSION:1.19   modify the ftpput.cpp  when the network is error
  Date:2014-03-20    VERSION:1.20   modify the driver of camera and app  and the ui of confirmed
  Date:2014-04-09    VERSION:1.23   modify the config setting  add test the volume and sound id
  Date:2014-05-16    VERSION:1.24   add next two day's log
  Date:2014-05-16    VERSION:1.25   add record receive message from localserver
  Date:2014-05-23    VERSION:1.26   add extra sensor detect
  Date:2014-05-26    VERSION:1.27   remove the cashier number when log out
  Date:2014-05-27    VERSION:1.28   add log in and log out to revolve mode and modify the messages tip from "Confirmed" to "OK"
  Date:2014-05-29    VERSION:1.29   modify the backup of logout
  Date:2014-06-06    VERSION:1.30   add judge i sensor when the s is trigger
  Date:2014-06-10    VERSION:1.31   add record pos alert image fail
                                    remove all sensor judge and mis judge
  Date:2014-06-11    VERSION:1.32   modify THE E2 STATUS  when i3 i2 i1 has signal
  Date:2014-06-11    VERSION:1.33   modify the status to I STATUS
  Date:2014-06-11    VERSION:1.38
  Date:2014-06-12    VERSION:1.39   modify the stop image time add lost of e2 signal add extern mode recordLog
                                    modify the single and extern mode ,the image will show static when alarm happen

  Date:2014-06-13    VERSION:1.40   add record config.sys to log here
  Date:2014-06-13    VERSION:1.41   add alert plus in single or extern mode
  Date:2014-06-19    VERSION:1.42   modify userdef.zip
                     VERSION:1.43   update userdef.zip whern setting=1
***************************************************************************/


#define CARTVU_NOW_VERSION                1.43

#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/if.h>
#include <string.h>
#include <linux/sockios.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#include <QtGui/QApplication>
#include <QTranslator>
#include <QWSServer>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlRecord>

#include <QMutex>

#include "strseparate.h"
#include "recordLog.h"
#include "recordLog.inc"


#include "MyInputPannelContext.h"

#include "config_sys.h"
//#include "cartvu.h"
#include "read_sys.h"
#include "camThread.h"
#include "sensor.h"
#include "serialMode.h"
#include "login.h"
#include "revolveMode.h"
#include <stdio.h>
#include <stdlib.h>

#include "watchdog.h"
#include "ftpput.h"

//保存用户密码的文件
#define CONFIG_ADMIN        "/etc/admin"




/**************** Global varibles********************************/
unsigned char *global_buffer;                                    // buffer of camera
char *arg_main;
int global_camfd;

global_config *global_conf_sys = new global_config();            // class for processing config.sys(config_sys.cpp)
//创建局部变量 为了读取config.sys
global_config   *config_sys = new global_config();

sensor_c *global_sensor        = new sensor_c();                 // class for sensor(sensor.cpp)

camThread *global_camera;                                        // class for camera(camThread.cpp)
revolveMode *global_revo;                                        // class for revolving standby mode(revolveMode.cpp)
login *global_log;                                               // class for login interface(login.cpp)
read_sys *global_rsys;                                           //

watchdog *global_wdg =new watchdog();


bool global_serial_flag = false;
serialMode *global_serialMode = NULL;

bool global_construct_flag = false;

//ftp上传的类  上传统计，告警图片，清理数据库
ftpput *global_ftp;

//读取到config.sys成功
bool global_read_config_ok = false;

//每10秒检查网络是否连通
bool network_flag = true;


QMutex global_statis_lock;
QMutex global_database_lock;

QMutex global_ftpput_lock;

QMutex global_passwd_lock;

//初始化静态统计数据
struct statis  cartvu_statis = {"20130101",0,0,0,0};

bool global_network_enter_flag = false;


bool global_mac_log_ok_flag = false;

int ftpflag = 0;

//段错误处理函数
void func(int signo);

//恢复出厂设置时所要删除的文件
void initial_machine();

//定时发送状态给localserver
//保存E1 S I1 I2 I3 E2 camera help信息
char status[STATUS_SIZE] = "00000000";
void read_status(const char *arg);
void write_to_status(const char *arg);

void funk(int signo);
void funm(int signo);
//void sigalrm_fn(int sig);
/******************Global varibles********************************/

/******************************************************************
  Function: main(int, char **)
  description: main program

  Entry:
  Return:
*******************************************************************/

QSqlDatabase  cartvu_db;

QApplication  *global_app;

void setting_timezone()
{
    FILE *fp;
    char buf[BUF_SIZE] = {0};
    paraStruc para[2];
    int timeZone = 100;

    fp = fopen(CFG_SYS, "r");
    if (fp == NULL) {
        printf("open %s fail ", CFG_SYS);
        return;
    }

    while (fgets(buf,BUF_SIZE, fp)) {

        buf[strlen(buf) - 1] = '\0';
        if (strlen(buf) == 0) break;
        if (!index(buf, '=')) continue;
        //printf("%s", buf);
        stringSeparate(buf, para, 2);
        //printf("key:%s value: %s\n", para->key, para->value);
        if (strcmp(para->key, "TimeZone") == 0) {
            timeZone = atoi(para->value);
            break;
        }
    }
    fclose(fp);

    if (timeZone != 100) {
        sprintf(buf, "GMT%+02d", -timeZone);
        printf("set TZ=%s\n", buf);
        setenv("TZ", buf, 1);

    }
    //my_system("date -R");

}

unsigned  long int read_self_size(char *filename) {
    FILE *fp;
    unsigned long int sum;
    char oneChar;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("open self main fail");
        return -1;
    }


    sum = 0;

    while (fread(&oneChar, 1, 1, fp) > 0) {
        sum += 1;
    }
    fclose(fp);

    return sum;

}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    char buf[400];

    global_app = &a;
    //enable the watchdog
    global_wdg->start(QThread::HighPriority);
    //global_wdg->watchdog_timer.start(45*1000);

    //drawPrimitive();
    // QWSServer::setCursorVisible(false);
    //no valid
    //a.setOverrideCursor(Qt::BlankCursor);

    //system("/bin/rm /var/log/eth0-setting.log");
    //system("/bin/rm /etc/rebootTime");
    //register segment default
    signal(SIGSEGV,func);

    //my_system("ps");

    arg_main = argv[0];
    //camThread camera;
    //camera.start(QThread::LowPriority);

    setting_timezone();
    
    dealLog(0, 0, 0, 0);
    
    sprintf(buf, "\n**************Cartvu:VERSION:%4.2f**********************\n", CARTVU_NOW_VERSION);
    qDebug() << buf;
    recordLog(1, 1, buf);

    sprintf(buf, "df >>%s", filename);
    my_system(buf);


    recordLog(1, 1, (char*)"reboot time here!!!");

    sprintf(buf, "%s size is %ld", argv[0], read_self_size(argv[0]));
    printf("%s\n", buf);
    recordLog(1, 1, buf);


    global_buffer = (unsigned char *)malloc(CAMERA_WIDTH * CAMERA_HEIGHT * CAM_LINELEN);   // allocate memory for camera
    if (!global_buffer) {
        perror("shmat shm_buffer fail");
        recordLog(1, 1, (char*)"malloc camera buffer fail!!");
        //exit(1);
    }

    global_camera = new camThread(global_buffer);              // instance of a camera class
    //global_camera->start(QThread::LowPriority);
    qDebug() << "camera start";
    qDebug() << global_camera;


    //global_sensor->start();




    global_rsys = new read_sys(config_sys);
    //download config.sys file  read local server ip
    //读取当前的config.sys的信息
    global_rsys->sys_decode(CFG_SYS, config_sys);
    //读取eth0-setting中的mac及lane number
    global_rsys->read_eth0(ETH0SETTING); //read mac  and lane number
    //程序启动后的随机延时，延时后进去登陆下载等步骤

    //显示登陆窗口
    //cartvu *w = new cartvu(global_camera);
    global_log = new login(global_camera);
    //系统开机的随机延时
    global_rsys->get_file_delay();//need local server ip
    //解码    将user密码与接收到的加密的密码比较
    global_rsys->decode_passwd("car1998", CONFIG_ADMIN);


    // QTranslator translator;
    // translator.load("zh_CN",".");
    // a.installTranslator(&translator);


#if 1
    //global_log->show();
    ;
#else
    w->showFullScreen();
#endif
    return a.exec();
}

#if 0
//用 my_system()替换system()
int my_system(const char* cmd)
{
    FILE *fp;
    char buffer[BUF_SIZE] = {0};

    /*
    if (strncmp(cmd, "/bin/aplay", 10)== 0) {
        return -1 ;
    }
*/

    fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("open fail maybe malloc fail");
        qDebug() << "popen  fail and die here";
        return -1;
        //while(1);
    }

    while(fgets(buffer, sizeof(buffer), fp) !=NULL) {
        printf("%s", buffer);
    }
    printf("\n");
    pclose(fp);
    return 0;

}
#else
int my_system(const char* cmd)
{

    /*
    if (strncmp(cmd, "/bin/aplay", 10)== 0) {
        return;
    }
*/

    int status = 0;
    pid_t pid;

    if ((pid = vfork()) < 0) {
        printf("vfork process error! \n");
        printf("execute %s fail please check", cmd);
        perror("my system error");
        status = -1;
    } else if (pid == 0) {//child progress
        struct sigaction sa_cld;
        sa_cld.sa_handler = SIG_DFL;
        sa_cld.sa_flags = 0;

        /* SIGINT */
        sigemptyset(&sa_cld.sa_mask);
        sigaction(SIGINT, &sa_cld, NULL);
        sigaction(SIGQUIT, &sa_cld, NULL);

        //execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        if (execl("/bin/sh","sh", "-c", cmd, (char*)0) <0)
        {
            printf("fail to execve %s! errno: %d\n", cmd, errno);
            exit(1);
        }
        else
        {
            exit(0);
        }
    } else {// parent progress
        while(waitpid(pid, &status, 0) < 0){
            if(errno != EINTR){
                status = -1;
                break;
            }
        }
    }

    return status;
}
#endif

void func(int signo) {
    qDebug("now signal is  %d\n", signo);

    char buf[100] = {0};
    snprintf(buf, 100, "/bin/echo 'receive %d signal in main thread' >> %s", signo, REBOOT_TIME);
    recordLog(1, 80, buf);
    my_system(buf);
    qDebug() << buf;

    if (signo == 11) {
        //sleep(3);
        qDebug() << "invalid memory error here !";
        //qDebug() << "sleep 1";
        //sleep(1);
        //while(1);
    }
    qDebug() << "you are in main thread and receive error";
    //qDebug() << "receive unexpect signal ?????";
    //qDebug() << "will stop the camera and stop";
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    // if (signo == 2) {
    //停止摄像头驱动中申请的资源
    if (ioctl (global_camfd, VIDIOC_STREAMOFF, &type) < 0) {          //
        fprintf(stderr, "\n~~~~~~~~~~~~~cannot stop stream~~~~~~~~~~~~~~~~\n");
        perror("stop fail?");
    } else {
        fprintf(stderr, "stop stream ok\n");
        perror("stop ok?");
        close(global_camfd);
        qDebug() << "\n!!!!!!!!!!!!close the camera fd!!!!!!!!!\n";
    }

    write_to_status(NOW_ERROR_STATUS);

    //  }
    exit(1);
}

void funk(int signo) {
    qDebug("now signal is  %d\n", signo);

    qDebug() << "you are in camera thread and receive error";

    char buf[100] = {0};
    snprintf(buf, 100, "/bin/echo 'receive %d signal in camera thread' >> %s", signo, REBOOT_TIME);
    recordLog(1, 80, buf);
    my_system(buf);
    qDebug() << buf;

    if (signo == 11) {
        //sleep(3);
        qDebug() << "invalid memory error here !";
        //qDebug() << "sleep 1";
        //sleep(1);
        //while(1);
    }

    //qDebug() << "receive unexpect signal ?????";
    //qDebug() << "will stop the camera and stop";
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    // if (signo == 2) {
    if (ioctl (global_camfd, VIDIOC_STREAMOFF, &type) < 0) {          //
        fprintf(stderr, "\n~~~~~~~~~~~~~cannot stop stream~~~~~~~~~~~~~~~~\n");
        perror("stop fail?");
    } else {
        fprintf(stderr, "stop stream ok\n");
        perror("stop ok?");
    }

    write_to_status(NOW_ERROR_STATUS);

    //  }
    exit(1);
}

void funm(int signo) {
    qDebug("now signal is  %d\n", signo);

    qDebug() << "you are in sensor thread and receive error";
    char buf[100] = {0};
    snprintf(buf, 100, "/bin/echo 'receive %d signal in sensor thread' >> %s", signo, REBOOT_TIME);
    recordLog(1, 80, buf);
    my_system(buf);
    qDebug() << buf;
    if (signo == 11) {
        //sleep(3);
        qDebug() << "invalid memory error here !";
        //qDebug() << "sleep 1";
        //sleep(1);
        //while(1);
    }
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    // if (signo == 2) {
    if (ioctl (global_camfd, VIDIOC_STREAMOFF, &type) < 0) {          //
        fprintf(stderr, "\n~~~~~~~~~~~~~cannot stop stream~~~~~~~~~~~~~~~~\n");
        perror("stop fail?");
    } else {
        fprintf(stderr, "stop stream ok\n");
        perror("stop ok?");
    }

    write_to_status(NOW_ERROR_STATUS);

    exit(1);
}

/*
void fun_signal(int signo) {
    qDebug("now signal is  %d\n", signo);

    qDebug() << "you are in download the file ok";
    if (signo == 11) {
        qDebug() << "invalid memory error here !";
    }
    exit(1);
}

*/
/*
void sigalrm_fn(int sig)
{
    qDebug("\n~~~~~~~~~~~~~~~~~~alarm!~~~~~~~~~~~~~~~~~~\n");
    alarm(1);
    return;
}
*/

#define IPADDR_SIZE   50
//获取自身ip的函数
char * get_ip(char * ipaddr)
{

    int sock_get_ip;
    struct   sockaddr_in *sin;
    struct   ifreq ifr_ip;
    char buf[BUF_SIZE] = {0};

    if ((sock_get_ip=socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        recordLog(1, 2, (char*)"socket create fail...GetLocalIp!");
        printf("socket create failse...GetLocalIp!/n");
        strncpy(ipaddr, "socket create fail...GetLocalIp!", IPADDR_SIZE);
        return ipaddr;
    }

    memset(&ifr_ip, 0, sizeof(ifr_ip));
    strncpy(ifr_ip.ifr_name, "eth0", sizeof(ifr_ip.ifr_name) - 1);
    if( ioctl( sock_get_ip, SIOCGIFADDR, &ifr_ip) < 0 )
    {
        recordLog(1, 2, (char*)"ioctl fail...GetLocalIp!");
        perror("ioctl fail");
        strncpy(ipaddr, "ioctl fail to get ip", IPADDR_SIZE);
        return ipaddr;
    }


    sin = (struct sockaddr_in *)&ifr_ip.ifr_addr;
    strcpy(ipaddr,inet_ntoa(sin->sin_addr));

    printf("ip:%s \n",ipaddr);
    snprintf(buf, BUF_SIZE, "ip:%s", ipaddr);
    strcpy(ipaddr, buf);
    close(sock_get_ip);



    return ipaddr;
}


//恢复到出厂设置
void initial_machine()
{
    my_system("/bin/rm /etc/eth0-setting");

    my_system("/bin/rm /cartvu -rf");
    my_system("/bin/rm /advertising -rf");

    char buf_tmp[BUF_SIZE] = {0};
    snprintf(buf_tmp, BUF_SIZE, "/bin/rm  %s", REBOOT_TIME);
    my_system(buf_tmp);

    my_system("/bin/rm /var/log/eth0-setting.log");

    qDebug() << "delete the /etc/eth0-setting and re initial the machine!";



}

void read_status(const char *arg)
{

    char buf[BUF_SIZE] = {0};
    FILE *fp;
    char *p;

    fp = fopen(arg, "r");
    if (fp == NULL) {
        perror("open status file fail or did not has this file");
        return;
    }

    bzero(buf, BUF_SIZE);
    if ((p = fgets(buf,BUF_SIZE, fp)) == NULL) {
        perror("gets error");
    }
    buf[strlen(buf) - 1] = '\0';
    fclose(fp);

    printf("%s content is %s\n", arg, p);

    //status=00000000;
    strcpy(status, p+7);
    printf("############################now the status is %s########################\n", status);
    sprintf(buf, "read status:%s", status);
    recordLog(1, 49, buf);
    status[0] = '0';//not 0 but '0';
    status[1] = '0';

}



void write_to_status(const char *arg)
{

    char buf[BUF_SIZE] = {0};
    FILE *fp;
    int ret;


    fp = fopen(arg, "w");
    if (fp == NULL) {
        perror("open status file fail");
        return;
    }

    if (strlen(status) != 8) {
        bzero(status, STATUS_SIZE);
        strncpy(status,"00000000", 8);
    }

    status[0] = '0';//not 0 but '0';
    status[1] = '0';

    bzero(buf, BUF_SIZE);
    snprintf(buf, BUF_SIZE, "status=%s\n", status);


    printf("now the content of %s is %s\n", arg, status);
    ret = fputs(buf, fp);
    if (ret < 0) {
        perror("puts error");
    }


    fclose(fp);


    sprintf(buf, "write status:%s", status);
    recordLog(1, 49, buf);

}
