

#include <QDebug>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "read_sys.h"
#include "revolveMode.h"
#include "serialMode.h"

extern  serialMode *global_serialMode;
extern  revolveMode *global_revo;


extern sensor_c *global_sensor ;

extern char *arg_main;

QString global_lane_no;
QString global_kings_name;
//unsigned int global_cashier_timeout;

extern global_config *global_conf_sys;


extern login *global_log;


extern camThread *global_camera;

extern watchdog *global_wdg;
extern int ftpflag;

synchTime  *global_syn_time;

light *global_lgt;

extern bool global_read_config_ok;


extern bool network_flag;

extern ftpput  *global_ftp;

//extern void fun_signal(int signo);

extern QSqlDatabase  cartvu_db;

struct version *version_head;


extern bool global_network_enter_flag;

extern char status[STATUS_SIZE];

extern void read_status(const char *);
extern void write_to_status(const char *);

extern bool global_mac_log_ok_flag;

read_sys::read_sys()
{

}

read_sys::~read_sys()
{

}

read_sys::read_sys(global_config * p)
{    
    out_config_sys = p;

    //////////////////////////////
    qDebug() << arg_main;
    QString app_name_temp(arg_main);
    app_name = app_name_temp;
    int s_pos;

    do {
        s_pos = app_name.indexOf("/");
        if (s_pos >= 0) {
            app_name = app_name.right(app_name.length() - s_pos -1);
        }
    } while(s_pos >=0);
    qDebug() << app_name;

    ///////////////////////////////////

    http_client = new client();
    // for test
    delay_client = new client();
    connect(this, SIGNAL(read_config_ok()), this, SLOT(initial_all_par()));
    //sys_decode(CFG_SYS);

    /*
    qDebug() << "\n\nstart the watchdog timer\n\n";
    connect(&watchdog_timer, SIGNAL(timeout()), this, SLOT(feed_dog_count()));
    //watchdog_timer.start(MAIN_FEED_TIMER*1000);
    watchdog_timer.start(1*1000);
*/

    version_head = (struct version *)malloc(sizeof(struct version));
    if (version_head == NULL) {
        perror("malloc version head fail");
        recordLog(1, 8, (char*)"malloc version head fail");
        exit(1);
    }
    version_head->next = NULL;
}

/*
void read_sys::feed_dog_count()
{
    global_wdg->count = 0;
    qDebug() << "int read_sys file and feed the dog count to 0"    ;

}
*/

void read_sys::zone_swap(char *p)
{
    if (p[0] == '-')
        p[0] = '+';
    else
        p[0] = '-';
}
unsigned int read_sys::qstring_to_sec_time(QString time)
{
    int hour;
    int min;
    int sec;
    int all_sec;
    hour = time.mid(0, 2).toInt();
    min = time.mid(3, 2).toInt();
    sec = time.mid(6, 2).toInt();
    //    qDebug("=================================\n");
    //    qDebug("hour is %d\n", hour);
    //    qDebug("min is %d\n", min);
    //    qDebug("sec is %d\n", sec);
    all_sec = hour*3600 + min*60 + sec;
    return all_sec;

}
void read_sys::par_analyse(QString line, global_config *config_sys)
{
    QString arg;
    QString value;
    QString tmp_value;

    int pos;
    // char *time_zone;
    char *str;
    char zone[ZONE_STR_SIZE];
    QByteArray tmp;
    pos = line.indexOf('=', 0);
    arg = line.left(pos).toLower().trimmed();
    value = line.right(line.length() - pos -1).trimmed();
    qDebug() << arg << "value is " << value;

    if (arg.compare("localserver") == 0) {
        tmp = value.toLatin1();
        str = tmp.data();
        strcpy(config_sys->sys_network.local_server, str);
        //config_sys->down_load(config_sys->sys_network.local_server, "/cartvu/config/config.sys", "/download/config.sys", "/var/log/down_load_error");
        //qDebug("=================================\n");
        //qDebug("local server is %s\n", config_sys->sys_network.local_server);
        //qDebug("=================================\n");
    } else if (arg.compare("openningtime") == 0) {
        config_sys->sys_global.openning_time = qstring_to_sec_time(value);
        strcpy(config_sys->sys_global.openning_time_str, value.toLatin1().data());
        //qDebug("openning time is %d\n", config_sys->sys_global.openning_time);
    } else if (arg.compare("closingtime") == 0) {
        config_sys->sys_global.closing_time = qstring_to_sec_time(value);
        strcpy(config_sys->sys_global.closing_time_str, value.toLatin1().data());
    } else if (arg.compare("timezone") == 0) {
        //        tmp = value.toLatin1();
        //        time_zone = tmp.data();
        //        //调换符号
        //        zone_swap(time_zone);
        bzero(zone, ZONE_STR_SIZE);
        //snprintf(zone, ZONE_STR_SIZE, "GMT%s", time_zone);
        config_sys->sys_global.time_zone = value.toInt();
        snprintf(zone, ZONE_STR_SIZE, "GMT%+d", -(config_sys->sys_global.time_zone));
        //qDebug("%s", zone);
        //my_system("date -R");
        //setenv("TZ", zone, 1);
        // my_system("date -R");
    } else if (arg.compare("savingtime") == 0) {
        config_sys->sys_global.saveing_time = value.toInt();
    } else if (arg.compare("brightness") == 0) {
        config_sys->sys_global.brightness= value.toInt();
    } else if (arg.compare("workingmode") == 0) {
        config_sys->sys_working_mode.working_mode = value.toInt();
    } else if (arg.compare("cameratype") == 0) {
        config_sys->sys_working_mode.camera_type = value.toInt();
    }else if (arg.compare("isnumber") == 0) {
        config_sys->sys_working_mode.I_number = value.toInt();
    } else if (arg.compare("e2timeout") == 0) {
        config_sys->sys_working_mode.E2_time_out = value.toInt();
    } else if (arg.compare("alarminterval") == 0) {
        config_sys->sys_working_mode.alarm_interval = value.toInt();
    } else if (arg.compare("blinkingtime") == 0) {
        config_sys->sys_alarm.blinking_time = value.toInt();
    } else if (arg.compare("imagetime") == 0) {
        config_sys->sys_alarm.image_time = value.toInt();
    } else if (arg.compare("alarmmode") == 0) {
        config_sys->sys_alarm.alarm_mode = value.toInt();
    } else if (arg.compare("alarmid") == 0) {
        config_sys->sys_alarm.alarm_id = value.toInt();
    } else if (arg.compare("alarmvolume") == 0) {
        config_sys->sys_alarm.alarm_volume = value.toInt();
    } else if (arg.compare("alarmmsg") == 0) {
        config_sys->sys_alarm.alarm_msg = value.toInt();
    } else if (arg.compare("standbymode") == 0) {
        config_sys->sys_standby.standby_mode = value.toInt();
    } else if (arg.compare("revolverange") == 0) {
        //from 0  to find the string "--"
        strcpy(config_sys->sys_standby.revolve_str, value.toLatin1().data());
        pos = value.indexOf("--", 0);
        if (pos < 0) {
            qDebug("using the '-' to separate\n");
            pos = value.indexOf("-", 0);
            config_sys->sys_standby.revolve_range.end= value.right(value.length() - pos - 1).toInt();
        } else {
            config_sys->sys_standby.revolve_range.end= value.right(value.length() - pos - 2).toInt();
        }
        config_sys->sys_standby.revolve_range.start= value.left(pos).toInt();
        //        qDebug("=================================\n");
        //        qDebug("pos is %d", pos);
        //        qDebug("start is %d",config_sys->sys_standby.revolve_range.start);
        //        qDebug("end is %d",config_sys->sys_standby.revolve_range.end);
    } else if (arg.compare("revolveperiod") == 0) {
        config_sys->sys_standby.revolve_period = value.toInt();
    } else if (arg.compare("imagequality") == 0) {
        config_sys->sys_other.image_quality = value.toInt();
    } else if (arg.compare("extraiteminfo") == 0) {
        config_sys->sys_other.extra_iteam_info = value.toInt();
    } else if (arg.compare("resettime") == 0) {
        config_sys->sys_other.reset_time = qstring_to_sec_time(value);
        strcpy(config_sys->sys_other.reset_time_str, value.toLatin1().data());
    } else if (arg.compare("storename") == 0) {
        tmp = value.toLatin1();
        str = tmp.data();
        strcpy(config_sys->sys_other.kings_name, str);
        //global_kings_name = QString(config_sys->sys_other.kings_name);
    } else if (arg.compare("cashiertimeout") == 0) {
        config_sys->sys_other.cashier_timeout = value.toInt();
        //global_cashier_timeout = config_sys->sys_other.cashier_timeout;
    } else if (arg.compare("settings") == 0) {
        config_sys->sys_other.settings = value.toInt();
    }
}

void read_sys::read_eth0(const char *arg)
{
    int pos;
    QString line;
    QString date;
    QFile sys_file(arg);
    QString left_string;
    QString right_string;

    if (sys_file.exists()) {
        if (sys_file.open(QIODevice::ReadOnly)) {
            QTextStream stream(&sys_file);
            do {
                line = stream.readLine().trimmed().toLower();             // 从文件中读入一行

                //不解析空字符
                if (line.compare("") == 0)
                    continue;
                pos = line.indexOf("=");
                if (pos < 0) {
                    continue;
                } else {
                    left_string = line.left(pos).trimmed();
                    right_string = line.right(line.length() - pos - 1).trimmed();
                    if (left_string.compare("mac") == 0) {
                        full_mac = right_string;
                        plain_mac = full_mac.replace(":", "");
                        qDebug() << "\n======mac=======";
                        qDebug() << plain_mac;
                    } else if (left_string.compare("lane_no") == 0){
                        lane_no = right_string;
                        qDebug() << "\n======lane_no=======";
                        qDebug() << lane_no;
                        global_lane_no = lane_no;
                    }
                }
            } while(!line.isNull());                // end of while
            sys_file.close();
        } else {
            perror("open file fail");
            //exit(1);
        }
    } else {
        perror("config.sys file is not exit");
        //exit(1);
    }

}

void read_sys::sys_decode(const char *arg, global_config *conf)
{
    int pos;
    QString line;
    QString date;
    QFile sys_file(arg);

    if (sys_file.exists()) {
        if (sys_file.open(QIODevice::ReadOnly)) {
            QTextStream stream(&sys_file);
            do {
                line = stream.readLine();             // 从文件中读入一行
                qDebug() << "!!!zero!!!!!";
                if (line.isNull()) {
                    qDebug() << "the line is null and the config.sys is error";
                    recordLog(1, 39, (char*)"the line is null and the config.sys is error");
                    return;
                }
            } while (line.compare("") == 0);
            //解析日期
            decode_date_line(line, conf);
            do {
                line = stream.readLine();             // 从文件中读入一行
                pos = line.indexOf(';', 0);              // 找到 ';'没找到则保留原来的值
                line = line.left(pos);                  //取左边的';'
                //line = line.replace(" ", "");       //去掉所有的' '
                line = line.replace("\t", "");          //去掉tab
                //line = line.toLower();                  // 转换成小写
                //跳过'#'
                pos = line.indexOf('#', 0);
                line = line.left(pos);
                //跳过'['
                pos = line.indexOf('[', 0);
                line = line.left(pos);         
                // qDebug() << line;
                //不解析空字符
                if (line.compare("") == 0)
                    continue;
                //解析
                par_analyse(line, conf);
            } while(!line.isNull());                // end of while
            sys_file.close();    // 关闭配置文件
        } else {
            perror("open file fail");
            recordLog(1, 17, (char*)"open config.sys fail");
            exit(1);
        }
        //unlink(CMD_FILE);         // 删除文件
    } else {
        perror("config.sys file is not exit");
        //exit(1);
    }
}

void read_sys::get_file_delay()
{
    QTime t;
    restart_flag = false;
    //int i = 10;
    // while (i--) {
    t= QTime::currentTime();
    //Returns the millisecond part (0 to 999) of the time
    //qDebug() << t.msec();
    //qDebug() << t.second();
    qsrand(t.msec()+t.second()*1000);

    delay_time = qrand()% RANDOM_SCOPE;
    qDebug("delay time is %d ", delay_time);
    // }
    
    connect(&random_timer, SIGNAL(timeout()), this, SLOT(random_delay()));
    //as the base time start and count in the random_delay() and judge the delay_time;
    random_timer.start(1*1000);

    //has already download the newest 'config.sys' file
    try_soft_count = 0;
    connect(this, SIGNAL(config_ok()),this, SLOT(check_update_app()));
    connect(this, SIGNAL(log_out_sig()), this, SLOT(log_out()));
}


void read_sys::check_update_app()
{
    QString cmd;


    cmd = "GET /cgi-bin/software.cgi HTTP/1.1\r\nConnection:Close\r\n\r\n";
    qDebug() << "log======================================log";
    qDebug() << cmd;
    http_client->transmit_info(this->l_server, HTTP_PORT, cmd, &rec_string);
    connect(http_client, SIGNAL(emit_receive()), this, SLOT(deal_update_app()));


}


void read_sys::deal_update_app()
{
    int start_pos;
    QString receive;
    QString tmp;
    disconnect(http_client, SIGNAL(emit_receive()), this, SLOT(deal_update_app()));

    char buf[BUF_MAXSIZE];

    //delete the temp file
    bzero(buf, BUF_MAXSIZE);
    snprintf(buf, BUF_MAXSIZE, "/bin/rm %s", COMMON_TMP);
    my_system(buf);
    qDebug() << buf;


    if (http_client->error_timeout == true) {
        try_soft_count++;
        if (try_soft_count < TEST_TIME_COUNT) {
            qDebug() << "try another times and sleep 1 secs";
            qDebug() << "\n******************************************\n";
            sleep(1);
            check_update_app();

        } else {
            network_flag = false;

            qDebug() << "connect to host error, http request error!please check the network!";
            sleep(1);
            qDebug() << "try sofware update fail 5 times and will show here!";
            if (config_flag_ok == false) {
                global_conf_sys = out_config_sys;
                qDebug() << "user the before config.sys";
            }
            sleep(1);
            qDebug() << "show screen here with not the newest config.sys";
            start_global_screen();
        }
    } else {



        rec_string = rec_string.trimmed();
        start_pos = rec_string.indexOf("HTTP/1.0");
        if (start_pos < 0) {
            qDebug() << "http request error! please check the local server";
        } else {
            start_pos = rec_string.indexOf("Connection: close");
            rec_string = rec_string.right(rec_string.length() - start_pos - 17);
            qDebug() << "now0000000000000000000000now";
            qDebug() << rec_string;
            start_pos = rec_string.indexOf("&");
            if (start_pos < 0) {
                qDebug() << "receive information is not right! please check what the local server send";

                try_soft_count++;
                if (try_soft_count < TEST_TIME_COUNT) {
                    qDebug() << "try another times and sleep 1 secs";
                    qDebug() << "\n***********local server send error*********************\n";
                    sleep(1);
                    check_update_app();

                } else {
                    network_flag = false;
                    qDebug() << "connect to host error, http request error!please check the network!";
                    sleep(1);
                    qDebug() << "try sofware update fail 5 times and will show here!";
                    if (config_flag_ok == false) {
                        global_conf_sys = out_config_sys;
                    }
                    sleep(1);
                    qDebug() << "show screen here with not the newest config.sys";
                    start_global_screen();
                }


            } else {
                receive = rec_string.trimmed();
                qDebug() << receive;
                while ((start_pos = receive.indexOf("&")) >= 0) {
                    tmp = receive.left(start_pos).trimmed();
                    receive = receive.right(receive.length() - start_pos -1).trimmed();
                    analyse_string(tmp);
                }
                //更新数据库
                update_sqlite3();

                //meant that is ok  and will logout
                emit log_out_sig();
            }

        }
        //qDebug() << "receive is ";
        //qDebug() << rec_string;
    }
}

void read_sys::analyse_string(QString tmp)
{
    int pos;
    //cartvu=2.1&cartvuzip=1.3&..=...&..=..&
    pos = tmp.indexOf("=");
    if (pos >= 0) {
        software_name = tmp.left(pos).trimmed();
        software_ver = tmp.right(tmp.length() - pos - 1).trimmed().toLower();
        qDebug() << "now the receive http #" + software_name + "#   version is " + software_ver;
        pos = software_ver.indexOf(".");
        if (pos < 0) {
            software_major = software_ver;
            software_minor = "0";
        } else {
            software_major = software_ver.left(pos);
            software_minor = software_ver.right(software_ver.length() - pos - 1);
        }
        compare_version();
    } else {
        software_name = "";
        software_ver = "";
        qDebug() << "local server has send error information!";
    }

}

#define MINOR_SIZE  4
void  read_sys::compare_version()
{

    char       buf[BUF_MAXSIZE];
    QSqlQuery query;


    QString    command;

    int column_num;
    int row_num;
    QString tmp;
    char tmp_minor[MINOR_SIZE];

    int try_count = 0;
    bool check_flag = false;
    struct version *software_tmp;
    int pos;
    char buf_echo[100];

    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        cartvu_db = QSqlDatabase::addDatabase("QSQLITE");
        qDebug() << "add QSQLITE here first here";
    }

    cartvu_db.setDatabaseName(CARTVUVERSION_DB);
    if (!cartvu_db.open())
    {
        //QMessageBox::critical(0, "Cannot open database", "Unabel to establise a database connection", QMessageBox::Cancel);
        perror("cartvu db open fail!!!!!\n");
        return  ;
    } else {
        qDebug() << "open CartvuVersion.db database ok!";
    }

    query = QSqlQuery(cartvu_db);
    bzero(buf, BUF_MAXSIZE);
    sprintf(buf, "select *from  %s", CARTVU_VERSION);
    //command = "select * from" + CARTVU_VERSION;
    command = QString(QLatin1String(buf));
    query.exec(command);

    query.last();
    row_num = query.at() + 1;

    column_num = query.record().count();
    //qDebug("row is %d  column is %d", row_num, column_num);

    //return to the first before
    query.first();
    query.previous();
    while(query.next())
    {
        //QByteArray	toLatin1 () const
        tmp = query.value(0).toString();
        major_ver = query.value(1).toString();
        bzero(tmp_minor, MINOR_SIZE);
        snprintf(tmp_minor, MINOR_SIZE, "%02d", query.value(2).toString().toInt());
        minor_ver = QString(tmp_minor);
        version = major_ver + "." + minor_ver;
        //version = major_ver * 1000 +;
        if (tmp.compare(software_name) == 0) {
            //revise
            qDebug("\n==================================%s=============================",software_name.toLatin1().data());
            if (version.toFloat() < software_ver.toFloat()) {



                qDebug("\n============datebase version is %f <  local send version is %f============\n", version.toFloat(), software_ver.toFloat());
                qDebug() << "will down load the newest file";
                bzero(remote_path, BUF_MAXSIZE);
                bzero(local_path, BUF_MAXSIZE);
                snprintf(remote_path, BUF_MAXSIZE, "%s", query.value(4).toByteArray().data());
                snprintf(local_path, BUF_MAXSIZE, "%s", query.value(5).toByteArray().data());


                //qDebug("%s", remote_path);
                qDebug("local path is %s", local_path);
                strcat(remote_path, software_name.toLatin1().data());
                qDebug("remote_path is %s", remote_path);
                global_config c_sys;



                do {
                    try_count++;

                    //根据数据库里面的信息及路径下载相关软件  download to "/tmp/tmp"
                    c_sys.down_load(ftp_user, ftp_passwd, local_server, COMMON_TMP, remote_path, ERROR_DOWNLOAD);

                    if (c_sys.down_load_ok == true) {
                        check_flag = software_check(COMMON_TMP);
                        if (check_flag == true) {
                            qDebug() << "check sum is ok!";
                            bzero(buf, BUF_MAXSIZE);
                            snprintf(buf, BUF_MAXSIZE, "/bin/chmod 755 %s", COMMON_TMP);
                            my_system(buf);
                            qDebug("%s",buf);
                            //decode_software(COMMON_TMP, DECODE_POS, DECODE_CHtmpAR, OK_TMP);
                            //decode_software(COMMON_TMP, DECODE_POS, DECODE_CHAR, local_path);

                            /*
                                char *ch;
                                QByteArray tmp = this->software_name.toLatin1();
                                ch = tmp.data();
                                */
                            pos = software_name.indexOf(ZIP_TYPE);
                            //if (file_type == ZIP_TYPE) {
                            if (pos >= 0) {
                                //software_name = software_name.left(pos);
                                unzip_file();
                            } else {

                                bzero(buf, BUF_MAXSIZE);

                                if (software_name.compare(app_name) == 0) {
                                    snprintf(buf, BUF_MAXSIZE, "/bin/mv %s %s", COMMON_TMP, DEFAULT_LOCAL_PATH);
                                    restart_flag = true;
                                } else {
                                    snprintf(buf, BUF_MAXSIZE, "/bin/mv %s %s%s", COMMON_TMP, local_path, software_name.toLatin1().data());
                                }

                                qDebug() << buf;
                                my_system(buf);
                            }
                            qDebug() << "download is ok ! update the sqlite3 ";

                            /////CARTVU_VERSION, software_major.toLatin1().data(), software_minor.toLatin1().data(), now_time.toLatin1().data(), software_name.toLatin1().data());

                            software_tmp = (struct version *)malloc(sizeof(struct version));
                            if (software_tmp == NULL) {
                                perror("malloc version head fail");
                                exit(1);
                            }
                            software_tmp->next = version_head->next;
                            version_head->next = software_tmp;
                            strncpy(software_tmp->software, software_name.toLatin1().data(), STRING_SIZE);
                            strncpy(software_tmp->major_ver, software_major.toLatin1().data(), STRING_SIZE);
                            strncpy(software_tmp->minor_ver, software_minor.toLatin1().data(), STRING_SIZE);

                            cartvu_db.close();
                            //qDebug() << "close the Cartvu.db";




                            //break the try count
                            break;
                        } else {
                            qDebug() << "check sum is error";
                            bzero(buf, BUF_MAXSIZE);
                            snprintf(buf, BUF_MAXSIZE, "/bin/rm %s", COMMON_TMP);
                            my_system(buf);
                            qDebug("delete the %s file", COMMON_TMP);
                            qDebug() << "download is maybe fail and will try to another time!";
                            sleep(1);
                            qDebug() << "sleep 1";
                            sleep(1);
                            qDebug() << "sleep 2";
                            sleep(1);
                            qDebug("try %d time", try_count);
                            sprintf(buf_echo, "check sum of %s is fail", software_name.toLatin1().data());
                            recordLog(1, 19, buf_echo);

                        }
                    } else {
                        sleep(1);
                        qDebug("try %d time", try_count);
                        qDebug("download error maybe local server did not has this file");
                    }
                } while (try_count < TEST_TIME_COUNT);




            } else {

                qDebug("\n============datebase version is %f >=  local send version is %f============\n", version.toFloat(), software_ver.toFloat());
                qDebug() << "\nno need to update and download the software\n";
                //sleep(2);
            }
            //break the sqlite3  query
            break;
        }

    }
    //cartvu_db.close();
}



void read_sys::unzip_file()
{
    char buf[BUF_MAXSIZE];
    /*
    char *ch;
    QByteArray tmp = this->software_name.toLatin1();
    ch = tmp.data();
*/
    bzero(buf, BUF_MAXSIZE);
    snprintf(buf, BUF_MAXSIZE, "/bin/mkdir %s -p", local_path);
    qDebug() << buf;
    my_system(buf);


    bzero(buf, BUF_MAXSIZE);
    snprintf(buf, BUF_MAXSIZE, "/bin/mkdir %s -p", COMMON_TMP_DIR);
    qDebug() << buf;
    my_system(buf);

    //delete the temp dir file
    bzero(buf, BUF_MAXSIZE);
    snprintf(buf, BUF_MAXSIZE, "/bin/rm %s* -rf", COMMON_TMP_DIR);
    my_system(buf);
    qDebug() << buf;


    bzero(buf, BUF_MAXSIZE);
    //overide and unzip to correct dir
    snprintf(buf, BUF_MAXSIZE, "/usr/bin/unzip -o %s -d %s", COMMON_TMP, COMMON_TMP_DIR);
    qDebug() << buf;
    my_system(buf);

    bzero(buf, BUF_MAXSIZE);
    snprintf(buf, BUF_MAXSIZE, "/bin/chmod 755  %s -R", COMMON_TMP_DIR);
    qDebug() << buf;
    my_system(buf);

    bzero(buf, BUF_MAXSIZE);   // cp /tmp/tmp_dir/*   -rf ....
    snprintf(buf, BUF_MAXSIZE, "/bin/cp %s* %s -rf", COMMON_TMP_DIR, local_path);
    qDebug() << buf;
    my_system(buf);

    bzero(buf, BUF_MAXSIZE);   // rm /tmp/tmp_dir/*  -rf ....
    snprintf(buf, BUF_MAXSIZE, "/bin/rm %s*  -rf", COMMON_TMP_DIR);
    qDebug() << buf;
    my_system(buf);


    //delete the temp file
    bzero(buf, BUF_MAXSIZE);
    snprintf(buf, BUF_MAXSIZE, "/bin/rm %s", COMMON_TMP);
    my_system(buf);
    qDebug() << buf;
}

bool  read_sys::software_check(const char *file)
{
    unsigned  char  sum = 0;
    char   character = '\0';
    //qint64 file_size;
    long long int file_size;
    QFile   fileASCII(file);


    if (!fileASCII.open(QIODevice::ReadOnly))
    {
        qDebug("%s open fail!", file);
        return  false;
    }

    qDebug("%s open succeed!", file);


    file_size = (long long int)fileASCII.size();
    //qDebug("now the %s is %lld", file, (long long int)file_size);
    qDebug("%s is %fM=%fK=%lld", file, (float)(file_size)/1024/1024, (float)(file_size)/1024, (long long int)file_size);

    if (file_size == 0) {
        qDebug("%s size is 0",file);
        return false;
    }


    // from 0  to  .....
    //    qDebug("%c is %d", character, fileASCII.pos());
    //    fileASCII.seek(3);
    //    qDebug("%c is %d", character, fileASCII.pos());
    QDataStream  stream(&fileASCII);
    while (stream.readRawData(&character, 1)) {
        //printf("%c ", character);
        //qDebug("%c is %d", character, fileASCII.pos());
        sum += character;
    }
    qDebug("the sum:%d\n",sum);
    fileASCII.close();
    if (sum == 0)
        return  true;
    else
        return  false;

}


void read_sys::update_sqlite3()
{
    QString now_time;
    char       buf[BUF_MAXSIZE];
    QString    command;
    bool ret;
    QSqlQuery query;
    struct version *software_tmp;
    struct version *free_software;

    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        cartvu_db = QSqlDatabase::addDatabase("QSQLITE");
        qDebug() << "add QSQLITE here second here";
        recordLog(1, 17, (char*)"add QSQLITE here second here");
    }

    cartvu_db.setDatabaseName(CARTVUVERSION_DB);
    if (!cartvu_db.open())
    {
        //QMessageBox::critical(0, "Cannot open database", "Unabel to establise a database connection", QMessageBox::Cancel);
        perror("cartvu db open fail!!!!!\n");
        recordLog(1, 17, (char*)"cartvu db open fail!!!!(update_sqlite3)");
        return  ;
    } else {
        qDebug() << "open CartvuVersion.db database ok!";
    }

    query = QSqlQuery(cartvu_db);

    /*
    bzero(buf, BUF_MAXSIZE);
    sprintf(buf, "select *from  %s", CARTVU_VERSION);
    //command = "select * from" + CARTVU_VERSION;
    command = QString(QLatin1String(buf));
    query.exec(command);
    */


    //update date
    current_time = QDateTime::currentDateTime();
    //current_time().toString("yyyy-MM-dd hh:mm:ss");
    qDebug() << current_time.toString("yyyy-MM-dd hh:mm:ss");
    now_time = current_time.toString("yyyy-MM-dd");

    free_software = version_head;
    software_tmp = version_head->next;
    free(free_software);
    while (software_tmp != NULL) {


        //update major  minor  date ;
        bzero(buf, BUF_MAXSIZE);
        //update Version set Version = '2', MinorVer = '1', UpdateDate = '2013-09-09' where Software = 'cartvu'
        sprintf(buf, "update %s set Version = %s, MinorVer = %s, UpdateDate = '%s' where Software = '%s'",
                CARTVU_VERSION, software_tmp->major_ver, software_tmp->minor_ver, now_time.toLatin1().data(), software_tmp->software);
        //command = "select * from" + CARTVU_VERSION;
        command = QString(QLatin1String(buf));
        qDebug() << command;
        ret = query.exec(command);
        if (ret == false) {
            recordLog(1, 34, strcat(buf, " is fail"));
            qDebug() << "query exec fail";
        } else {
            recordLog(1, 34, strcat(buf, " is ok"));
            qDebug() << "query exec ok!";
        }
        free_software = software_tmp;
        software_tmp = software_tmp->next;
        free(free_software);
    }

    cartvu_db.close();
    qDebug() << "close the Cartvu.db";
    qDebug() << "\n!!!!!!!!!!!!!!!!!!!update the CartvuVersion.db is ok!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
}


void read_sys::log_out()
{
    QString cmd;


    cmd = "GET /cgi-bin/logout.cgi HTTP/1.1\r\nConnection:Close\r\n\r\n";
    http_client->transmit_info(this->l_server, HTTP_PORT, cmd, &rec_string);
    connect(http_client, SIGNAL(emit_receive()), this, SLOT(is_logout_ok()));



}
void read_sys::reset_machine()
{



    write_to_status(NOW_ERROR_STATUS);
    qDebug() << "write to" << NOW_ERROR_STATUS << "is ok";





    disconnect(&reset_timer, SIGNAL(timeout()), this, SLOT(reset_machine()));

    qDebug() << "will reset the machine";
    sleep(1);

    current_time = QDateTime::currentDateTime();
    //current_time().toString("yyyy-MM-dd hh:mm:ss");
    qDebug() << current_time.toString("yyyy-MM-dd hh:mm:ss");

    my_system("/sbin/reboot");

}




void read_sys::closing_machine()
{
    unsigned int dif_value;

    closing_timer.stop();
    disconnect(&closing_timer, SIGNAL(timeout()), this, SLOT(closing_machine()));
    connect(&openning_timer, SIGNAL(timeout()), this, SLOT(openning_machine()));
    // qDebug() << "\nyou are in the closing time!";

    if (global_conf_sys->sys_global.closing_time > global_conf_sys->sys_global.openning_time) {
        dif_value = 24*3600 - global_conf_sys->sys_global.closing_time + global_conf_sys->sys_global.openning_time;
    } else {
        dif_value = global_conf_sys->sys_global.openning_time - global_conf_sys->sys_global.closing_time;
    }


    qDebug("the machine will open after %d sec", dif_value);
    //dif_value = 10;
    //dif_value = 3600*3;
    closing_light();
    openning_timer.start(dif_value*1000);


    //show the big button
    emit show_hide_button(false);

    //system("echo 'closing the machine'>/dev/ttySAC0");
}




void read_sys::closing_light()
{

    /*
    int fd = -1;
    int ret = -1;
    unsigned int fre;

    fd = open(PWM_BACK_LIGHT, O_RDWR);
    if(fd < 0) {
        perror("open back light fail");
        //exit(1);
    }
    fre = 100000;
    //ret = ioctl(fd, PWM_IOCTL_SET_FREQ, fre);
    ret = ioctl(fd, PWM_IOCTL_STOP, fre);
    if(ret < 0) {
        perror("ioctl fail");
        //exit(1);
    }
    close(fd);
    */
    lgt->closing_light_flag = true;
    recordLog(1, 24, (char*)"closeing light here");

}






void read_sys::openning_light()
{
    /*
    int fd = -1;
    int ret = -1;
    unsigned int fre;

    fd = open(PWM_BACK_LIGHT, O_RDWR);
    if(fd < 0) {
        perror("open back light fail");
        //exit(1);
    }
    fre = 1000000;
    ret = ioctl(fd, PWM_IOCTL_SET_FREQ, fre);
    if(ret < 0) {
        perror("ioctl fail");
        //exit(1);
    }
    close(fd);
    */
    lgt->closing_light_flag = false;
    recordLog(1, 25, (char*)"openning light here");
}

void read_sys::openning_machine()
{
    int dif_value;

    openning_timer.stop();

    if (global_conf_sys->sys_global.closing_time > global_conf_sys->sys_global.openning_time) {
        dif_value = global_conf_sys->sys_global.closing_time - global_conf_sys->sys_global.openning_time;
    } else {
        dif_value = 24*3600 - global_conf_sys->sys_global.openning_time + global_conf_sys->sys_global.closing_time;
    }




    //qDebug() << "\nyou are in the openning time!";
    //qDebug() << "dif_value is " << dif_value;
    disconnect(&openning_timer, SIGNAL(timeout()), this, SLOT(openning_machine()));
    connect(&closing_timer, SIGNAL(timeout()), this, SLOT(closing_machine()));

    //dif_value = 3600*3;
    qDebug("the machine will close after %d sec", dif_value);

    openning_light();


    closing_timer.start(dif_value*1000);

    //hide the big button
    emit show_hide_button(true);
    //system("echo 'openning the machine'>/dev/ttySAC0");
}
void read_sys::is_logout_ok()
{
    int start_pos;
    QString receive;
    QString tmp;
    disconnect(this->http_client, SIGNAL(emit_receive()), this, SLOT(is_logout_ok()));


    rec_string = rec_string.trimmed();
    start_pos = rec_string.indexOf("HTTP/1.0");
    if (start_pos < 0) {
        qDebug() << "http request error! please check the local server";
    } else {
        start_pos = rec_string.indexOf("Connection: close");
        rec_string = rec_string.right(rec_string.length() - start_pos - 17);
        receive = rec_string.trimmed();
        qDebug() << "log out information!!!!!!!!!!";
        qDebug() << receive;
        if (receive.compare("logout ok!") == 0) {
            qDebug() << "start main process";
            //start_main_qt();
        }
    }
    qDebug() << "@@@@@@@@@@@@@@@@@@@@@test@@@@@@@@@@@@@@@@@@@@@@@@";
    if (restart_flag == true) {
        sleep(1);
        qDebug() << "will start another cartvu and exit and sleep 1";
        /*
        global_wdg->set_watdog_time();
        my_system("/etc/init.d/chose-start.sh");
        global_wdg->set_watdog_time();
        */
        qDebug() << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~the last set watchdog~~~~~~~~~~~~~~~~~~~~~~~\n";
        my_system("/sbin/reboot");
        //will kill it in the shell
        //exit(1);
        //system("/sbin/reboot");
    } else {
        sleep(1);
        qDebug() << "no reboot";
        qDebug() << "will show here!";

        start_global_screen();



    }
}




void read_sys::start_global_screen()
{

    initial_all_global_config();

}


int read_sys::volume_state()
{
    int volume_level = 80;
    switch (global_conf_sys->sys_alarm.alarm_volume) {
    case 0:
        volume_level = 0;
        break;
    case 1:
        volume_level = 50;
        break;
    case 2:
        volume_level = 60;
        break;
    case 3:
        volume_level = 70;
        break;
    case 4:
        volume_level = 80;
        break;
    case 5:
        volume_level = 85;
        break;
    case 6:
        volume_level = 90;
        break;
    case 7:
        volume_level = 95;
        break;
    case 8:
        volume_level = 97;
        break;
    case 9:
        volume_level = 100;
        break;
    default:
        volume_level = 80;
        break;
    }

    return volume_level;
}
void read_sys::initial_all_global_config()
{
    char buf[BUF_SIZE] = {0};
    char buf_echo[BUF_SIZE] = {0};
    int volume_level;

    //signal(SIGSEGV,fun_signal);
    //qDebug() << "register the fun_signal is ok";

    // adjust the volume
    volume_level = volume_state();
    snprintf(buf, BUF_SIZE, "%s %d &", VOLUME_APP, volume_level);
    qDebug("now the volume is %s", buf);
    my_system(buf);

    qDebug() << "\nstart******************************************start\n";

    //light adjust
    lgt = new light(global_conf_sys->sys_global.brightness);
    connect(&lgt_timer, SIGNAL(timeout()), lgt,  SLOT(light_adjust()));
    lgt_timer.start(ADJUST_BAKLIGHT_INTERVAL*1000);
    global_lgt = lgt;





    image_quality_fun();

    // start when the config.sys is ok
    global_log->global_status.start(GLOBAL_TIMER*1000);

    read_status(NOW_ERROR_STATUS);

    global_log->now_local_server = QString(global_conf_sys->sys_network.local_server);

    global_mac_log_ok_flag = true;

    if (network_flag == true) {

        sprintf(buf_echo, "cat /cartvu/config/config.sys >> %s", filename);
        MY_SYSTEM(buf_echo);

        printf("\n~~~~~~~~~~~~~~~~ftpput the log!!!!here\n");
        sprintf(buf_echo, "cp  %s %s", filename, next_two_day);
        printf("%s\n", buf_echo);
        MY_SYSTEM(buf_echo);

        dealLog(ftp_user, ftp_passwd, local_server, 1);

        recordLog(1, 2, (char*)"network is ok!!!");
    } else {
        recordLog(1, 2, (char*)"network is error!!!");
    }



    qDebug() << "\n!!!!!!!!!!!!!!synchronization the system time!!!!!!!!!!!!\n";
    global_syn_time = new synchTime();
    connect(global_syn_time, SIGNAL(syn_time_ok()), this, SLOT(initial_part_global_config()));

    global_syn_time->getTimeInformation();
    //sleep(3);
    global_syn_time->timeSynchronization();
    qDebug() << "\n!!!!!!!!!!!!!!synchroni is ok!!!!!!!!!!!!!\n";





}


void read_sys::initial_part_global_config()
{
    unsigned int now_size_time;
    unsigned int dif_value;
    QDateTime now_time;
    QString tmp;
    struct tm *p;
    time_t timep;

    disconnect(global_syn_time, SIGNAL(syn_time_ok()), this, SLOT(initial_part_global_config()));


    //while(1);
    char buf_tmp[BUF_SIZE] = {0};
    snprintf(buf_tmp, BUF_SIZE, "/bin/date -R >>  %s", REBOOT_TIME);
    my_system(buf_tmp);

    time(&timep);
    p = localtime(&timep);
    if (p->tm_mday == 1) {
        snprintf(buf_tmp, BUF_SIZE, "/bin/rm %s -rf", REBOOT_TIME);
        my_system(buf_tmp);
    }



    now_time = QDateTime::currentDateTime();
    tmp = now_time.toString("hh:mm:ss");
    qDebug() << "now the time is " << tmp;
    now_size_time  = qstring_to_sec_time(tmp);

    if (global_conf_sys->sys_global.closing_time < now_size_time) {
        //dif_value = 10;
        dif_value = 24*3600 - now_size_time + global_conf_sys->sys_global.closing_time;
        qDebug() << "closing time is bigger than the current time";
    } else {
        dif_value = global_conf_sys->sys_global.closing_time - now_size_time;

        //dif_value = 10;
    }
    qDebug("the machine will close after %d sec", dif_value);

    qDebug() << "now the time@@@@@@@@@@@@@@@@@@@@@@is @@@@@@";
    qDebug() << global_conf_sys->sys_global.closing_time;
    qDebug() << global_conf_sys->sys_global.openning_time;

    connect(&closing_timer, SIGNAL(timeout()), this, SLOT(closing_machine()));

    qDebug() << "wait for the closing time!!!!!!!!";
    closing_timer.start(dif_value*1000);

    if (global_conf_sys->sys_other.reset_time > now_size_time) {
        dif_value = global_conf_sys->sys_other.reset_time - now_size_time;
    } else {
        dif_value = 24*3600 - now_size_time + global_conf_sys->sys_other.reset_time;
    }
    qDebug("the reset time is %d", dif_value);
    connect(&reset_timer, SIGNAL(timeout()), this, SLOT(reset_machine()));

    reset_timer.start(dif_value*1000);
    //    qDebug() << "will show here!";
    //    sleep(1);
    //    global_log->show();

    qDebug() << "\n\n------------------------------------------\n\n";
    qDebug() << "show the kings name and lane";
    global_kings_name = QString(global_conf_sys->sys_other.kings_name);
    tmp = global_kings_name + " " + "Lane:" + global_lane_no;
    global_log->kings_label->setText(tmp);
    //global_cashier_timeout = global_conf_sys->sys_other.cashier_timeout;
    qDebug() << tmp;
    //qDebug() << "global cashier timeout is " << global_cashier_timeout;

    show_version();


    //start the sensor thread!!
    global_sensor->start();
    
    qDebug() << "\n\n------------------------------------------\n\n";
    qDebug() << "!!!!!!!!!!!!!!show here!!!!!!!!!!!!!!!!!!!!!!!!!";
    qDebug() << "\n\n------------------------------------------\n\n";
    //delete &now_size_time;

    global_log->show();
    global_read_config_ok = true;
    emit read_config_ok();
}

void read_sys::show_version()
{
    //to solve the sqlite3 locked problem
    QSqlQuery query;
    char tmp_minor[MINOR_SIZE];
    QString now_software_version;
    int i = 0;
    char buf[2048] = {0};

    // no need to update the cartvu and show version
    if (restart_flag == false) {
        QString    command;
        bool ret;
        QString tmp;


        if (!QSqlDatabase::contains("qt_sql_default_connection")){
            cartvu_db = QSqlDatabase::addDatabase("QSQLITE");
            qDebug() << "add QSQLITE here third here";
        }

        cartvu_db.setDatabaseName(CARTVUVERSION_DB);
        if (!cartvu_db.open())
        {
            //QMessageBox::critical(0, "Cannot open database", "Unabel to establise a database connection", QMessageBox::Cancel);
            perror("cartvu db open fail!!!!!\n");
            return  ;
        } else {
            qDebug() << "open CartvuVersion.db database ok!";
        }

        query = QSqlQuery(cartvu_db);


        bzero(buf, BUF_MAXSIZE);
        //sprintf(buf, "select *from  %s where software='%s'", CARTVU_VERSION, app_name.toLatin1().data());
        sprintf(buf, "select *from  %s", CARTVU_VERSION);
        //command = "select * from" + CARTVU_VERSION;
        command = QString(QLatin1String(buf));
        ret = query.exec(command);
        if (ret == false) {
            qDebug("%s is fail", buf);
            recordLog(1, 34, strcat(buf, " is fail(show_version)"));
            cartvu_db.close();
            return;
        } else {
            qDebug("%s is ok", buf);
        }
        sprintf(buf, "***************version****************\n");
        while(query.next())
        {
            //QByteArray	toLatin1 () const
            tmp = query.value(0).toString();
            //qDebug() << tmp;
            major_ver = query.value(1).toString();
            bzero(tmp_minor, MINOR_SIZE);
            snprintf(tmp_minor, MINOR_SIZE, "%02d", query.value(2).toString().toInt());
            minor_ver = QString(tmp_minor);
            now_software_version = "Ver:"+  major_ver + "." + minor_ver;
            if (tmp.compare(app_name) == 0) {
                cartvu_version = now_software_version;
                global_log->version_label->setText(cartvu_version);
                qDebug() << "\n-------------show the version---------\n";
                qDebug() << cartvu_version;
            }
            sprintf(buf, "%ssoftware[%02d]:%25s:\t%s\n", buf, i++, tmp.toLatin1().data(), now_software_version.toLatin1().data());

        }
        //cartvu_db.removeDatabase(CARTVUVERSION_DB);
        cartvu_db.close();
        qDebug() << "cartvu:close the Cartvu.db ok";
        //qDebug() << "sorry the sqlite is error not found in the cartvu version!!";
        //sleep(3);
        recordLog(1, 7, buf);
    } else {
        qDebug() << "will update the version and restart the cartvu";

    }

}


void read_sys::initial_all_par()
{
    qDebug("!!!!!!!!!!!!!!!!!!!!!global read config.sys is ok!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    global_log->hide_big_button();
    connect(&log_delay_timer, SIGNAL(timeout()), global_log, SLOT(on_login_button_clicked()));
    log_delay_timer.start(LOG_DELAY_TIME*1000);
    qDebug() << "log delay start";

    global_camera->start(QThread::LowPriority);
    qDebug() << "new the serialMode and other mode here";
    global_ftp = new ftpput();

    global_serialMode = new serialMode(global_camera, "");
    global_revo = new revolveMode();

    global_serialMode->global_cartvu_title->setText(QString(global_conf_sys->sys_other.kings_name));
    global_serialMode->chose_screen();

    //because the reolvemode is not new so start the thread in the new revolvuMode();
    //global_ftp->start(QThread::LowPriority);
}
void read_sys::image_quality_fun()
{
    switch(global_conf_sys->sys_other.image_quality) {
    case IMAGE_QUALITY_H:
        global_camera->now_image_quality = IMAGE_QUALITY_H_PER;
        break;
    case IMAGE_QUALITY_M:
        global_camera->now_image_quality = IMAGE_QUALITY_M_PER;
        break;
    case IMAGE_QUALITY_L:
        global_camera->now_image_quality = IMAGE_QUALITY_L_PER;
        break;
    default:
        global_camera->now_image_quality = IMAGE_QUALITY_HH_PER;
        break;
    }

    qDebug("image qualite is %d", global_camera->now_image_quality);

}

void read_sys::random_delay()
{
    static int count = 0;
    count++;
    if (count > delay_time) {
        random_timer.stop();
        qDebug() << "start";
        qDebug() << "delay for" << delay_time;
        down_load_test();

    } else {
        qDebug() << "wait " << count << "second!";
    }
}

void read_sys::down_load_test()
{

    l_server = QString(out_config_sys->sys_network.local_server);
    bzero(local_server, FTP_SIZE);
    strcpy(local_server, out_config_sys->sys_network.local_server);
    qDebug() << "local server is ";
    qDebug() << l_server;
    //5*10=10sec
    delay_client->test_server_port(l_server, HTTP_PORT, TEST_TIME_OUT, TEST_START_TIME_COUNT);
    //delay_client->test_server_port("192.168.1.109", HTTP_PORT, TEST_TIME_OUT, TEST_TIME_COUNT);
    connect(delay_client, SIGNAL(now_sate()), this, SLOT(down_load_file()));

}


void read_sys::down_load_file()
{
    //QString cmd;
    QString tmp;
    //char length[CMD_LEN_SIZE];
    disconnect(delay_client, SIGNAL(now_sate()), this, SLOT(down_load_file()));
    //tmp = "";
    //snprintf(length, CMD_LEN_SIZE, "%d", tmp.length());
    //manager->get(QNetworkRequest(QUrl("http://192.168.1.59/cgi-bin/software.cgi")));
    //cmd = "GET /cgi-bin/dealRequest.cgi?MAC=18:90:18:00:00:00 HTTP/1.1\r\nConnection:Close\r\n\r\n";



    //cmd = "GET /cgi-bin/software.cgi HTTP/1.1\r\nConnection:Close\r\n\r\n";


    qDebug() << "here to going to try mac";


    tmp = plain_mac;
    qDebug() << "plain_mac is " << tmp;
    tmp = tmp.left(6);
    bzero(ftp_user, FTP_SIZE);
    //lower case
    snprintf(ftp_user, FTP_SIZE,"F%s", tmp.toLower().toLatin1().data());
    qDebug("user is %s\n", ftp_user);



    if (delay_client->connect_state == true) {
        recordLog(1, 2, (char*)"testing localserver is ok!!!");

        global_network_enter_flag = true;
        qDebug() << "delete the delay_client ok";
        delete delay_client;
        delay_client = NULL;
        qDebug() << "connect ok!";
        //qDebug() << "sleep 3!!!!!!!!!!!!!";
        //sleep(3);
        post_mac();


    } else {
        network_flag = false;
        //start the man interrupt
        qDebug() << "connect to local server fail and start another screen!";
        qDebug() << "start the original cartvu app";

        qDebug() << "no reboot";

        //point to the original config.sys
        global_conf_sys = out_config_sys;

        qDebug() << "will show here!";
        recordLog(1, 2, (char*)"network is error and show screen here");
        start_global_screen();

        global_network_enter_flag = false;


    }

}


void read_sys::post_mac()
{
    /*
    QString tmp;
    tmp = plain_mac;
    qDebug() << "plain_mac is " << tmp;
    tmp = tmp.left(6);
    bzero(ftp_user, FTP_SIZE);
    //lower case
    snprintf(ftp_user, FTP_SIZE,"F%s", tmp.toLower().toLatin1().data());
    qDebug("user is %s\n", ftp_user);
*/

    try_post_mac();

}

void read_sys::try_post_mac()
{
    QString tmp;
    QString cmd;
    char buf[BUF_SIZE];

    tmp = plain_mac;
    bzero(buf, BUF_SIZE);
    snprintf(buf, BUF_SIZE, "POST /cgi-bin/login.cgi HTTP/1.1\r\nContent-Length:%d\n\n%s\r\n\r\n",
             tmp.length(), tmp.toLatin1().data());
    cmd = QString(buf);
    qDebug() << cmd;
    http_client->transmit_info(l_server, HTTP_PORT, cmd, &rec_string);
    connect(http_client, SIGNAL(emit_receive()), this, SLOT(info_flash()));
}

void read_sys::info_flash()
{
    static int try_mac_count = 0;
    int start_pos;
    QString receive;
    QString tmp;

    disconnect(http_client, SIGNAL(emit_receive()), this, SLOT(info_flash()));
    //if (http_client != NULL) {
    //    http_client->deleteLater();
    //}
    //error time out
    if (http_client->error_timeout == true) {
        try_mac_count++;
        if (try_mac_count < TEST_TIME_COUNT) {
            qDebug("receive error try %d time", try_mac_count);
            sleep(1);
            try_post_mac();
        } else {
            network_flag = false;
            qDebug() << "try mac fail 5 times and will show here!";
            sleep(1);
            global_conf_sys = out_config_sys;
            sleep(1);
            qDebug() << "show screen here with not the newest config.sys";
            start_global_screen();
        }
        // normal
    } else {

        rec_string = rec_string.trimmed();
        start_pos = rec_string.indexOf("HTTP/1.0");
        if (start_pos < 0) {
            qDebug() << "http request error! mac log error please check the local server";
        } else {
            start_pos = rec_string.indexOf("Connection: close");
            rec_string = rec_string.right(rec_string.length() - start_pos - 17);
            qDebug() << "ok=========================ok";
            qDebug() << rec_string;
            start_pos = rec_string.indexOf("&");
            if (start_pos < 0) {
                qDebug() << "receive information is not right! please check what the local server send";
                try_mac_count++;
                if (try_mac_count < TEST_TIME_COUNT) {

                    qDebug("receive error try %d time", try_mac_count);
                    sleep(1);
                    try_post_mac();
                } else {
                    network_flag = false;
                    sleep(1);
                    qDebug() << "try send mac login !!!! fail 5 times and will show here!";
                    global_conf_sys = out_config_sys;
                    sleep(1);
                    qDebug() << "show screen here with not the newest config.sys";
                    start_global_screen();
                }
            } else {
                receive = rec_string.trimmed();
                qDebug() << receive;
                receive += "&";
                //ok!ftppwd=h5s6q7w1&userpwd=car1998&
                start_pos = receive.indexOf("ok!");
                if (start_pos >=0) {
                    receive = receive.right(receive.length() - start_pos -3);
                    qDebug() << receive;
                    while ((start_pos = receive.indexOf("&")) >= 0) {
                        tmp = receive.left(start_pos).trimmed();
                        receive = receive.right(receive.length() - start_pos -1).trimmed();
                        analyse_passwd(tmp);
                    }
                    //qDebug() << "ok!!!!!!!!!!!!!!!!!!!and sleep 3";
                    //sleep(3);
                    emit config_ok();
                } else {
                    qDebug() << "local server has not send the 'ok!'";
                }
                //meant that is ok  and will logout

            }

        }
    }
}

#define USERDEF_FILE    "userdef.zip"
#define SOFTWARE_DIR    "/AdNode/cartvu/software/"
#define USERDEF_DIR      "/cartvu/userdef/"

#define TMP_USERDEF     "cartvu/temp/userdef.zip"



int read_sys::download_userdef(void) {
    char buf[1024];

    sprintf(buf, "%s%s", SOFTWARE_DIR, USERDEF_FILE);

    global_conf_sys->down_load(ftp_user, ftp_passwd, local_server, TMP_USERDEF, buf, ERROR_DOWNLOAD);

    if (global_conf_sys->down_load_ok == true) {
        qDebug() << "download userdef.zip is ok here";
        recordLog(1, 5, (char*)"download userdef.zip is ok here");
    } else {
        qDebug() << "download userdef.zip fail here";
        recordLog(1, 5, (char*)"download userdef.zip fail here");
        return -1;
    }

    if(software_check(TMP_USERDEF) == false) {
        recordLog(1, 5, (char*)"checksum of userdef.zip fail here");
        return -1;
    }

    sprintf(buf, "/usr/bin/unzip -o %s -d %s", TMP_USERDEF, USERDEF_DIR);
    qDebug() << buf;
    my_system(buf);

    sprintf(buf, "/bin/chmod 755  %s -R", USERDEF_DIR);
    qDebug() << buf;
    my_system(buf);


    return 0;
}

void read_sys::analyse_passwd(QString tmp)
{
    int pos;
    QString left_string;
    QString right_string;
    struct tm now_conf_time;
    unsigned long int conf_time[2];
    char buf[BUF_SIZE];
    int try_count = 0;
    bool check_flag = false;
    int ret = -1;

    //ftppwd=h5s6q7w1&userpwd=car1998
    pos = tmp.indexOf("=");
    if (pos >= 0) {   
        left_string = tmp.left(pos).trimmed().toLower();
        right_string = tmp.right(tmp.length() - pos - 1).trimmed().toLower();
        if (left_string.compare("ftppwd") == 0) {
            bzero(ftp_passwd, FTP_SIZE);
            snprintf(ftp_passwd, FTP_SIZE, "%s", right_string.toLatin1().data());
            qDebug("ftp passwd is %s ", ftp_passwd);

            //now_conf_sys = global_conf_sys;
            //global_config now_conf_sys;
            do {
                try_count++;
                global_conf_sys->down_load(ftp_user, ftp_passwd, local_server, TMP_FILE, DOWN_LOAD_CONFIG_SYS, ERROR_DOWNLOAD);
                if (global_conf_sys->down_load_ok == true) {
                    qDebug() << "download from local server is ok!";
                    check_flag = software_check(TMP_FILE);
                    if (check_flag == true) {
                        this->sys_decode(TMP_FILE, global_conf_sys);

                        now_conf_time.tm_sec   = global_conf_sys->sys_mod_date.sec;
                        now_conf_time.tm_min   = global_conf_sys->sys_mod_date.min;
                        now_conf_time.tm_hour  = global_conf_sys->sys_mod_date.hour;
                        now_conf_time.tm_mday  = global_conf_sys->sys_mod_date.mday;
                        now_conf_time.tm_mon   = global_conf_sys->sys_mod_date.mon;
                        now_conf_time.tm_year  = global_conf_sys->sys_mod_date.year - 1900;
                        now_conf_time.tm_wday  = 0;
                        now_conf_time.tm_yday  = 0;
                        now_conf_time.tm_isdst = 0;
                        conf_time[0] = mktime(&now_conf_time);

                        now_conf_time.tm_sec   = out_config_sys->sys_mod_date.sec;
                        now_conf_time.tm_min   = out_config_sys->sys_mod_date.min;
                        now_conf_time.tm_hour  = out_config_sys->sys_mod_date.hour;
                        now_conf_time.tm_mday  = out_config_sys->sys_mod_date.mday;
                        now_conf_time.tm_mon   = out_config_sys->sys_mod_date.mon;
                        now_conf_time.tm_year  = out_config_sys->sys_mod_date.year - 1900;
                        now_conf_time.tm_wday  = 0;
                        now_conf_time.tm_yday  = 0;
                        now_conf_time.tm_isdst = 0;
                        conf_time[1] = mktime(&now_conf_time);

                        qDebug() << "now download is ================";
                        qDebug() << global_conf_sys->sys_mod_date.year << global_conf_sys->sys_mod_date.mon << global_conf_sys->sys_mod_date.mday << global_conf_sys->sys_mod_date.hour <<
                                global_conf_sys->sys_mod_date.min << global_conf_sys->sys_mod_date.sec;
                        qDebug() << "before is ================";
                        qDebug() << out_config_sys->sys_mod_date.year << out_config_sys->sys_mod_date.mon << out_config_sys->sys_mod_date.mday << out_config_sys->sys_mod_date.hour <<
                                out_config_sys->sys_mod_date.min << out_config_sys->sys_mod_date.sec;
                        qDebug("now %ld    before is %ld", conf_time[0], conf_time[1]);

                        if (out_config_sys->sys_other.settings == 1) {
                            global_conf_sys = out_config_sys;
                            bzero(buf, BUF_SIZE);
                            snprintf(buf, BUF_SIZE, "/bin/rm %s", TMP_FILE);
                            my_system(buf);
                            download_userdef();
                            qDebug() << "due to the settings is 1 so not update the config.sys and rm /cartvu/temp/tmp";
                        } else {
                            if (conf_time[0] > conf_time[1]) {

                                ret = download_userdef();
                                if (ret == 0) {
                                    bzero(buf, BUF_SIZE);
                                    snprintf(buf, BUF_SIZE, "/bin/mv %s %s", TMP_FILE, CFG_SYS);

                                    my_system(buf);
                                    qDebug() << "will mv the config.sys to /cartvu/config/config.sys";
                                    recordLog(1, 5, (char*)"will mv the config.sys to /cartvu/config/config.sys");
                                } else {
                                    qDebug() << "not mv the config.sys to destination";
                                    recordLog(1, 5, (char*)"will not mv the config.sys to /cartvu/config/config.sys due to the error download userdef.zip");

                                }


                            } else {
                                // not point to the new download config.sys file
                                global_conf_sys = out_config_sys;
                                bzero(buf, BUF_SIZE);
                                snprintf(buf, BUF_SIZE, "/bin/rm %s", TMP_FILE);
                                my_system(buf);
                                qDebug() << "not mv the config.sys to /cartvu/config/config.sys and rm /cartvu/temp/tmp";
                                recordLog(1, 5, (char*)"not mv the config.sys to /cartvu/config/config.sys");
                            }
                        }

                        config_flag_ok = true;

                        return;
                    } else {
                        bzero(buf, BUF_SIZE);
                        snprintf(buf, BUF_SIZE, "/bin/rm %s", TMP_FILE);
                        my_system(buf);
                        qDebug("delete the %s file",TMP_FILE);
                        qDebug() << "the check sum is error will download another time";

                    }
                } else {
                    qDebug() << "download error please check the local server or re initial the machine!";

                }


                qDebug("download error will try %d time", try_count);
                sleep(1);

            } while (try_count < TEST_TIME_COUNT);
            if (try_count == TEST_TIME_COUNT) {
                //point to the original config.sys
                global_conf_sys = out_config_sys;
                qDebug() << "use the config.sys before";
                config_flag_ok = false;
            }






        } else if (left_string.compare("userpwd") == 0) {
            bzero(user_passwd, FTP_SIZE);
            snprintf(user_passwd, FTP_SIZE, "%s", right_string.toLatin1().data());
            qDebug("user passwd is %s ", user_passwd);


        } else {
            qDebug() << "local server has send error left value!";
        }
    } else {
        qDebug() << "local server has send error information!";
    }

}

/*
 *passwd:meant the passwd you want to compare
 *dir:  meant the crypt passwd dir where you save
 */
void read_sys::decode_passwd(const char *passwd, const char *dir)
{
    int pos;
    QString line;
    QString date;
    QFile sys_file(dir);

    if (sys_file.exists()) {
        if (sys_file.open(QIODevice::ReadOnly)) {
            QTextStream stream(&sys_file);
            do {
                line = stream.readLine();             // 从文件中读入一行
                pos = line.indexOf("encry_passwd");
                qDebug() << "r===============r";
                qDebug() << line;
                if (pos >= 0) {
                    pos = line.indexOf(':', 0);
                    if (pos > 0) {
                        encode_passwd = line.right(line.length() - pos - 1);
                        qDebug() << encode_passwd;
                        break;
                    }
                }
                if (line.compare("") == 0)
                    continue;
            } while(!line.isNull());                // end of while
            sys_file.close();    // 关闭配置文件
        } else {
            perror("open file fail");
            exit(1);
        }
        //unlink(CMD_FILE);         // 删除文件
    } else {
        qDebug("%s is not exit\n", dir);
        //exit(1);
    }


    bzero(en_passwd, PASSWD_SIZE);
    strcpy(en_passwd, encode_passwd.toLatin1().data());
    qDebug("the file passwd  is %s\n", en_passwd);
    char now_passwd[30] = "car1998";
    char slat[2];
    slat[0] = now_passwd[0];
    slat[1] = now_passwd[1];
    strcpy(now_passwd, crypt(now_passwd, slat));
    qDebug("now the car1998 is %s\n", now_passwd);



    slat[0] = passwd[0];
    slat[1] = passwd[1];
    strcpy(now_passwd, crypt(passwd, slat));
    qDebug("now the input passwd is %s\n", now_passwd);
    if (strncmp(en_passwd, now_passwd, 13) == 0) {
        qDebug() << "equal";
    } else {
        qDebug() << "the passwd is not equal";
    }
}
//// 2013-11-22
//20131122
// 2013-11-22  10:10:10
// 20131122 101010
void read_sys::decode_date_line(QString line, global_config *config_sys)
{
    int pos;
    QString date;  

    pos = line.indexOf(';', 0);              // 找到 ';'没找到则保留原来的值
    line = line.left(pos);                  //取左边的';'
    line = line.replace(" ", "");       //去掉所有的' '
    line = line.toLower();                  // 转换成小写
    //line = line.trimmed();                   //去掉前后的空格
    qDebug() << endl << "now the modify time of config.sys file  is ";
    qDebug() << line;
    qDebug() << endl;
    // date = line.section(&line, 0, 3);
    //2013-08-16
    //2013-08-1617:43:00
    //20130816174300
    //20130816
    line = line.replace("-", "");
    line = line.replace(":", "");
    qDebug() << endl << "now the modify time of config.sys file  is ";
    qDebug() << line;
    qDebug() << endl;
    config_sys->sys_mod_date.year = line.mid(0, 4).toInt();
    config_sys->sys_mod_date.mon = line.mid(4, 2).toInt();
    config_sys->sys_mod_date.mday = line.mid(6, 2).toInt();

    if (line.length() >= 8) {
        config_sys->sys_mod_date.hour = line.mid(8, 2).toInt();
        config_sys->sys_mod_date.min = line.mid(10, 2).toInt();
        config_sys->sys_mod_date.sec = line.mid(12, 2).toInt();
    } else {
        config_sys->sys_mod_date.hour = 0;
        config_sys->sys_mod_date.min = 0;
        config_sys->sys_mod_date.sec = 0;

    }

#if 0
    date = line.mid(0, 4);
    date = line.mid(5, 2);
    date = line.mid(8, 2);
    date = line.mid(10, 2);
    date = line.mid(13, 2);
    date = line.mid(16, 2);
#endif
    qDebug() << "year is " << config_sys->sys_mod_date.year << "mon is " << config_sys->sys_mod_date.mon << "mday is " << config_sys->sys_mod_date.mday;
    qDebug() << "hour is " << config_sys->sys_mod_date.hour << "min is " << config_sys->sys_mod_date.min << "sec is " << config_sys->sys_mod_date.sec;


#if 0
    pos = line.indexOf('-', 0);
    date = line.left(pos);
    date = date.trimmed();
    qDebug() << "year is " << date;
    qDebug() << "length is " << line.length() << endl;
    date = line.right(line.length() - pos -1);
    qDebug() << date;
#endif
    

}


