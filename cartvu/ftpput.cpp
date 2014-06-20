#include "ftpput.h"





extern read_sys *global_rsys;
extern serialMode *global_serialMode;

extern QSqlDatabase  cartvu_db;

extern struct statis  cartvu_statis;
struct alert_image_more   *alert_image_head = NULL;

//struct alert_image_more *alert_image_tmp;


// record for tmp image;
struct alert_image cartvu_alert_image;

extern QMutex global_statis_lock;
extern QMutex global_database_lock;
extern QMutex global_ftpput_lock;
extern QMutex global_passwd_lock;


extern bool network_flag;

extern sensor_c *global_sensor;

extern char global_cashier_nu[CASHIER_SIZE];
extern char global_image_filename[FILE_SIZE];

bool update_alarm_image_flag = false;


bool first_open_db = false;

extern bool global_mac_log_ok_flag;

extern int ftpflag;

ftpput::ftpput()
{
    
    QDateTime tmp;
    now_time = tmp.currentDateTime().toString("yyyyMMdd");
    qDebug() << "\n!!!!now before write to statis the time is below!!!!!\n";
    qDebug() << now_time;

    // 1 获取当前的时间并转换为天数，为清理数据库做准备
    now_day = qstring_to_day_time(now_time);


    /*
    strncpy(ftp_user, global_rsys->ftp_user, FTP_SIZE);
    strncpy(ftp_passwd, global_rsys->ftp_passwd, FTP_SIZE);
    strncpy(local_server, global_rsys->local_server, FTP_SIZE);
    qDebug() << "ftp user:" << ftp_user;
    qDebug() << "ftp passwd:" << ftp_passwd;
    qDebug() << "local_server:" << local_server;
    */
    // initial the head
    alert_image_head = (struct alert_image_more *)malloc(sizeof(struct alert_image_more));
    if (alert_image_head == NULL) {
        perror("malloc for alert image head fail");
        recordLog(2, 8, (char*)"malloc for alert image head fail");
        exit(1);
    }
    alert_image_head->next = alert_image_head;
    alert_image_head->front = alert_image_head;






    qDebug() << "ftpput construct ok!";
    /* // move to run thread
    http_client = new client();
    loop = new QEventLoop();
    qDebug() << "global_database_lock is locked here";
    global_database_lock.lock();
    //2 开机检查statis表  和告警表
    check_statis();
    check_alarm_image();
    global_database_lock.unlock();
    qDebug() << "global_database_lock unlocked is ok";
    */

}

//  20130402
int ftpput::qstring_to_day_time(QString time)
{


    int year;
    int mon;
    int day;
    int all_day;
    int all_sec;
    year = time.mid(0, 4).toInt();
    mon = time.mid(4, 2).toInt();
    day = time.mid(6, 2).toInt();



    struct tm tm;
    tm.tm_year = year - 1900;//
    tm.tm_mon = mon - 1;
    tm.tm_mday = day;
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    all_sec = mktime(&tm);

    all_day = all_sec/(24*3600);
    return all_day;
}
void ftpput::check_statis()
{
    //QString now_time;
    QString tmp_time;
    QDateTime tmp;

    char       buf[BUF_SIZE];
    QSqlQuery query;

    QString command;


    bool ret;
    bool has_nowday_flag = false;

    //now_time = tmp.currentDateTime().toString("yyyyMMdd");
    //qDebug() << "\n!!!!now before write to statis the time is below!!!!!\n";
    //qDebug() << now_time;



    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        cartvu_db = QSqlDatabase::addDatabase("QSQLITE");
        qDebug() << "add QSQLITE here !four here";
        recordLog(2, 17, (char*)"add QSQLITE here !four here");
    }

    /**/

    cartvu_db.setDatabaseName(CARTVU_DB);

    if (!cartvu_db.open())
    {
        //QMessageBox::critical(0, "Cannot open database", "Unabel to establise a database connection", QMessageBox::Cancel);
        perror("open cartvu.db fail!!!!!!!!!");
        recordLog(2, 17, (char*)"open cartvu.db fail!!!!(check_statis)!");
        return  ;
    } else {
        qDebug() << "open cartvu.db database ok!";
    }

    query = QSqlQuery(cartvu_db);
    bzero(buf, BUF_SIZE);
    sprintf(buf, "select *from  %s", CARTVU_STATIS);
    command = QString(QLatin1String(buf));

    ret = query.exec(command);
    if (ret == false) {
        recordLog(2, 17, strcat(buf, " fail(check_statis)"));
        qDebug("%s is fail", buf);
        cartvu_db.close();
        return;
    } else {
        qDebug("%s is ok", buf);
    }

    while(query.next())
    {
        //StatisDate  CartNum     AlertNum    ConfirmNum  UploadFlag
        //20130905    10          1           1           1
        tmp_time = query.value(0).toString();
        compare_day = qstring_to_day_time(tmp_time);
        StatisDate = tmp_time;
        CartNum = query.value(1).toInt();
        AlertNum = query.value(2).toInt();
        ConfirmNum = query.value(3).toInt();
        UploadFlag = query.value(4).toInt();

        if (compare_day < now_day) {
            check_is_uploaded();
        } else if(compare_day == now_day) {
            //save the day is statis to structure
            write_to_struct();
            has_nowday_flag = true;

        } else {
            qDebug() << "the system time maybe error please check!!!!";
        }
    }

    // 如果没有当天的statis表信息则插入一个数据
    if (has_nowday_flag == false) {
        bzero(buf, BUF_SIZE);
        // snprintf(buf, BUF_SIZE, "update Statis set StatisDate='20131101',CartNum=3,AlertNum=4,ConfirmNum=5,UploadFlag=0 where StatisDate='20131101'");
        snprintf(buf, BUF_SIZE, "insert into Statis values('%s',0,0,0,0)", now_time.toLatin1().data());
        command = QString(QLatin1String(buf));

        ret = query.exec(command);
        if (ret == false) {
            qDebug("%s is fail~~~", buf);
            recordLog(2, 34, strcat(buf, " execute fail(check_statis)"));
            cartvu_db.close();
            return;
        } else {
            qDebug("%s is ok~~~", buf);

            global_statis_lock.lock();
            bzero(cartvu_statis.statis_date, DATE_SIZE);
            snprintf(cartvu_statis.statis_date, DATE_SIZE, "%s", now_time.toLatin1().data());
            cartvu_statis.cart_num = 0;
            cartvu_statis.cart_num = 0;
            cartvu_statis.alert_num = 0;
            cartvu_statis.confirm_num = 0;
            cartvu_statis.upload_flag = 0;
            global_statis_lock.unlock();
        }
        qDebug() << "insert into statis is ok!!!!!!!!!!";
        //while(1);
    }
    /**/
    cartvu_db.close();
    qDebug() << "close the cartvu database ok";

}

//"POST /cgi-bin/login.cgi HTTP/1.1\r\nContent-Length:%d\n\n%s\r\n\r\n"
//cmd = "GET /cgi-bin/software.cgi HTTP/1.1\r\nConnection:Close\r\n\r\n";
//https://~/statis.cgi?cartdate=yyyymmdd&cartcount=xx&alarmcount=xx&confirmcount=xx
//https://~/statis.cgi?cartdate=yyyymmdd&cartcount=xx&alarmcount=xx&confirmcount=xx
void ftpput::check_is_uploaded()
{
    QString cmd;
    char buf[BUF_SIZE];
    char tmp[BUF_SIZE];
    int length;

    if (UploadFlag == UNUPLOADED) {
        qDebug() << StatisDate << "will uploading !!!!";
        bzero(tmp, BUF_SIZE);
        snprintf(tmp, BUF_SIZE, "cartdate=%s&cartcount=%d&alarmcount=%d&confirmcount=%d&", StatisDate.toLatin1().data(), CartNum, AlertNum, ConfirmNum);
        length = strlen(tmp);

        bzero(buf, BUF_SIZE);
        snprintf(buf, BUF_SIZE, "POST /cgi-bin/statis.cgi HTTP/1.1\r\nContent-Length:%d\n\n%s\r\n\r\n", length, tmp);
        //"POST /cgi-bin/login.cgi HTTP/1.1\r\nContent-Length:%d\n\n%s\r\n\r\n",
        cmd = QString(buf);
        qDebug() << cmd;
        http_client->transmit_info(global_rsys->local_server, HTTP_PORT, cmd, &rec_string);
        connect(http_client, SIGNAL(emit_receive()), this, SLOT(change_sqlite_status()));
        qDebug() << "wait the http respond~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~1";

        loop->exec();

        qDebug() << "respond is ok and will go ahead~~~~~~~~~~~~~~~~~~~~~~~~5";

    } else {
        qDebug() << StatisDate << "has uploaded !!!!";
        if (now_day - compare_day >= STATIS_CLEAR_DAYS) {


            delete_from_statis();
        }


    }


}

void ftpput::delete_from_statis()
{
    QSqlQuery query;
    char buf[BUF_SIZE];
    bool ret;
    QString command;


    query = QSqlQuery(cartvu_db);

    // delete from Statis where statisdate='20131107';
    bzero(buf, BUF_SIZE);
    snprintf(buf, BUF_SIZE, "delete from %s where StatisDate = %s", CARTVU_STATIS, StatisDate.toLatin1().data());
    command = QString(QLatin1String(buf));

    ret = query.exec(command);
    qDebug() << buf;
    if (ret == false) {
        recordLog(2, 34, strcat(buf, " execute fail(check_statis)"));
        qDebug("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!fail!!!!!!!!!!\n");
    } else {
        qDebug("\n!!!!!!!!!delete the statis is !!!!!!!!ok!!!!!!!!!!!!!!\n");
    }

}


void ftpput::change_sqlite_status()
{

    QSqlQuery query;
    QString tmp;
    int start_pos;
    //static int try_soft_count = 0;
    char buf[BUF_SIZE];
    bool ret;
    QString command;


    disconnect(http_client, SIGNAL(emit_receive()), this, SLOT(change_sqlite_status()));

    qDebug() << "in the receive..............~~~~~~~~~~~~~~~~~~~2";

    if (http_client->error_timeout == true) {
        qDebug() << "time out and connection is fail!!! please check!!!";
        /*
        try_soft_count++;
        if (try_soft_count < TEST_TIME_COUNT) {
            qDebug() << "try another times and sleep 3 secs";
            qDebug() << "\n******************************************\n";
            sleep(3);
            check_is_uploaded();

        } else {

            qDebug() << "connect to host error, http request error!please check the network!";
            sleep(1);
            qDebug() << "try sofware update fail 5 times and will show here!";

        }
*/
    } else {

        start_pos = rec_string.indexOf("Connection: close");
        tmp = rec_string.right(rec_string.length() - start_pos - 17).trimmed().toLower();

        qDebug() << "\n!!!!!!!!!!!!!!!the receive string is !!!!!!!!!!";
        qDebug() << tmp;
        start_pos = tmp.indexOf("ok");
        if (start_pos > 0) {
            qDebug() << "update to local server is ok!";
            query = QSqlQuery(cartvu_db);
            bzero(buf, BUF_SIZE);
            snprintf(buf, BUF_SIZE, "update %s set UploadFlag = 1 where StatisDate = %s", CARTVU_STATIS, StatisDate.toLatin1().data());
            command = QString(QLatin1String(buf));

            ret = query.exec(command);
            qDebug() << buf;
            if (ret == false) {
                recordLog(2, 34, strcat(buf, " execute fail(check_statis)"));
                qDebug("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!fail!!!!!!!!!!\n");
            } else {
                qDebug("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ok!!!!!!!!!!!!!!\n");
            }
        } else {
            qDebug() << "update to local server is fail!";
        }
        //while(1);
    }
    qDebug() << "before quit~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~3";
    loop->quit();
    qDebug() << "after quit~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~4";
}



void ftpput::write_to_struct()
{

    global_statis_lock.lock();
    bzero(cartvu_statis.statis_date, DATE_SIZE);
    snprintf(cartvu_statis.statis_date, DATE_SIZE, "%s", StatisDate.toLatin1().data());
    //strncpy(cartvu_statis.statis_date, StatisDate.toLatin1().data(), DATE_SIZE);
    qDebug("%s is today and will record", cartvu_statis.statis_date);


    cartvu_statis.cart_num = CartNum;
    cartvu_statis.alert_num = AlertNum;
    cartvu_statis.confirm_num = ConfirmNum;
    cartvu_statis.upload_flag = UploadFlag;
    global_statis_lock.unlock();
    qDebug() << "the information is below!!";
    qDebug("%s\t%d\t%d\t%d\t%d", cartvu_statis.statis_date, cartvu_statis.cart_num, cartvu_statis.alert_num, cartvu_statis.confirm_num, cartvu_statis.upload_flag);

}
/******************
 *******************
 ***do   3 things in this function********
 1:unloaded to make into queue
 2:delete the file if not mach
 3:delete the file if the data if bigger than 30 days and not updated
 **********************
 */
void ftpput::check_alarm_image()
{
    qDebug() << "check alarm image";
    char       buf[BUF_SIZE];
    QSqlQuery query;
    QString command;
    QString tmp_time;
    QString tmp_name;

    bool ret;
    struct dirent *dir_p;
    DIR *dir;
    bool file_has_flag = false;

    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        cartvu_db = QSqlDatabase::addDatabase("QSQLITE");
        qDebug() << "add QSQLITE here !four here";
        recordLog(2, 17, (char*)"add QSQLITE here !four here(check_alarm_image)");
    }

    cartvu_db.setDatabaseName(CARTVU_DB);


    if (!cartvu_db.open())
    {
        //QMessageBox::critical(0, "Cannot open database", "Unabel to establise a database connection", QMessageBox::Cancel);
        perror("open cartvu.db fail!!!!!!!!!");
        recordLog(2, 17, (char*)"open cartvu.db fail!!!!!!!!!(check_alarm_image)");
        return  ;
    } else {
        qDebug() << "open cartvu.db database ok!";
    }

    //create table AlertImage(id int primary key, FileName text, AlertTime text, Confirmed int, Cashier txt, BarCode text, Flag int);
    //insert into AlertImage values(5, 'picAlarm5', '2013-09-06 14:08', 1, '8888', '12345678910', 1);


    if((dir = opendir(SAVE_VIDEO_DIR)) == NULL)
    {
        perror("open dir fail ");
        recordLog(2, 17, (char*)"open dir fail");
        return;
    }
    while ((dir_p = readdir(dir)) != NULL) {

        file_has_flag = false;

        qDebug("now the name is %s",dir_p->d_name);
        if ((strcmp(dir_p->d_name, ".") == 0) || (strcmp(dir_p->d_name, "..") == 0)) {
            qDebug() << "not go ahead to compare";
            continue;
        }
        tmp_name = QString(dir_p->d_name);
        //tmp_name = tmp_name.mid(5, 14 + 4);
        qDebug() << "the select name is " << tmp_name;


        query = QSqlQuery(cartvu_db);
        bzero(buf, BUF_SIZE);
        sprintf(buf, "select *from  %s where FileName='%s'", CARTVU_ALERT_IMAGE, dir_p->d_name);
        command = QString(QLatin1String(buf));

        ret = query.exec(command);
        if (ret == false) {
            qDebug("%s is fail", buf);
            recordLog(2, 34, strcat(buf, " is fail"));
            cartvu_db.close();
            return;
        } else {
            qDebug("%s is ok", buf);
        }
        /////////////////////////////////////
        //return to the first before
        //query.first();
        //query.previous();
        while(query.next()) {

            bzero(&cartvu_alert_image, sizeof(cartvu_alert_image));
            sqlite_file_name = query.value(0).toString();
            strcpy(cartvu_alert_image.file_name, sqlite_file_name.toLatin1().data());
            //sqlite_file_name = sqlite_file_name.mid(5, 14 + 4);
            strcpy(cartvu_alert_image.alert_time, query.value(1).toString().toLatin1().data());
            cartvu_alert_image.confirmed = query.value(2).toInt();
            strcpy(cartvu_alert_image.cashier, query.value(3).toString().toLatin1().data());
            strcpy(cartvu_alert_image.barcode, query.value(4).toString().toLatin1().data());
            cartvu_alert_image.flag = query.value(5).toInt();
            qDebug("%s\t%s\t%d\t%s\t%s\t%d",
                   cartvu_alert_image.file_name,
                   cartvu_alert_image.alert_time,
                   cartvu_alert_image.confirmed,
                   cartvu_alert_image.cashier,
                   cartvu_alert_image.barcode,
                   cartvu_alert_image.flag
                   );
            if (tmp_name.compare(sqlite_file_name) == 0) {
                file_has_flag = true;
                qDebug() << "find the same name in the sqlite";
                //check if the file has uploaded
                check_information_uploaded();
                break;

            }
        }
        ///////////////////////////////////////
        //当前 /cartvu/alarm_images/文件夹下的图片未能在数据库中找到时，删除图片
        if (file_has_flag == false) {
            qDebug() << "not found the pic name in the sqlite";

            bzero(buf, BUF_SIZE);
            snprintf(buf, BUF_SIZE, "/bin/rm %s%s", SAVE_VIDEO_DIR, dir_p->d_name);
            my_system(buf);
            qDebug() << "delete the file " << dir_p->d_name;
        }

    }
    qDebug() << "close the database";
    cartvu_db.close();
    //显示上传告警队列
    show_ftpput();
}

void ftpput::show_ftpput()
{
    struct alert_image_more   *tmp;

    qDebug() << "!!!!!!!!!!!!!!the ftpput queue is below!!!!!!!!!!!!";
    tmp = alert_image_head->next;
    while (tmp != alert_image_head) {
        qDebug("%s\t%s\t%d\t%s\t%s\t%d",
               tmp->alert_image.file_name,
               tmp->alert_image.alert_time,
               tmp->alert_image.confirmed,
               tmp->alert_image.cashier,
               tmp->alert_image.barcode,
               tmp->alert_image.flag
               );
        tmp = tmp->next;
    }

    qDebug("end here");


}


void ftpput::check_information_uploaded()
{
    struct alert_image_more *alert_image_tmp;
    int tmp_day;
    char buf[BUF_SIZE];
    QSqlQuery query;
    QString command;
    bool ret = false;


    if (cartvu_alert_image.flag != UPLOADED_OK) {
        qDebug() << "make into queue!!!!!";
        alert_image_tmp = (struct alert_image_more *)malloc(sizeof(struct alert_image_more));
        if (alert_image_tmp == NULL) {
            perror("malloc for alert image head fail");
            exit(1);
        }

        global_ftpput_lock.lock();
        alert_image_tmp->next = alert_image_head->next;
        alert_image_tmp->front = alert_image_head;

        alert_image_head->next->front = alert_image_tmp;
        alert_image_head->next = alert_image_tmp;

        memcpy(&(alert_image_tmp->alert_image), &cartvu_alert_image, sizeof(cartvu_alert_image));
        global_ftpput_lock.unlock();

    } else {
        sqlite_file_name = sqlite_file_name.mid(5, 14);
        qDebug() << sqlite_file_name;
        tmp_day = qstring_to_day_time(sqlite_file_name);
        if (now_day - tmp_day >= CLEAR_DAYS) {
            bzero(buf, BUF_SIZE);
            snprintf(buf, BUF_SIZE, "/bin/rm %s%s", SAVE_VIDEO_DIR, cartvu_alert_image.file_name);
            my_system(buf);
            qDebug() << "delete the file and clear the sqlite data " << cartvu_alert_image.file_name;


            query = QSqlQuery(cartvu_db);
            bzero(buf, BUF_SIZE);
            sprintf(buf, "delete from %s where FileName='%s'", CARTVU_ALERT_IMAGE, cartvu_alert_image.file_name);
            command = QString(QLatin1String(buf));
            ret = query.exec(command);
            if (ret == false) {
                qDebug("%s is fail", buf);
                recordLog(2, 34, strcat(buf, " fail!!(check_information_uploaded)"));
                return;
            } else {
                qDebug("%s is ok", buf);
            }
        } else {
            qDebug() << "not delete the file until bigger than 30days";
        }


    }

}

void ftpput::update_alarm_image()
{
    struct alert_image_more   *tmp;
    struct alert_image_more   *fre_tmp;
    char local_path[BUF_SIZE] = {0};
    char remote_path[BUF_SIZE] = {0};
    global_config c_sys;
    int ret;
    //char buf[400];

    global_ftpput_lock.lock();

    tmp = alert_image_head->next;
    //qDebug() << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
   // qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    qDebug() << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!start ftpput the alert image to local server!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    //当定时时间到时，会上传告警队列的信息，一直上传直到成功
    while (tmp != alert_image_head) {
        qDebug("%s\t%s\t%d\t%s\t%s\t%d",
               tmp->alert_image.file_name,
               tmp->alert_image.alert_time,
               tmp->alert_image.confirmed,
               tmp->alert_image.cashier,
               tmp->alert_image.barcode,
               tmp->alert_image.flag
               );

        bzero(local_path, BUF_SIZE);
        snprintf(local_path, BUF_SIZE, "%s%s", SAVE_VIDEO_DIR, tmp->alert_image.file_name);

        bzero(remote_path, BUF_SIZE);
        snprintf(remote_path, BUF_SIZE, "%s%s", ADNODE_ALERT_DIR, tmp->alert_image.file_name);


        // 1  将图片先上传到localserver然后写入标志到数据库
        c_sys.ftpput_to_server(global_rsys->ftp_user, global_rsys->ftp_passwd, global_rsys->local_server, local_path, remote_path, ERROR_DOWNLOAD);
        if (c_sys.down_load_ok == true) {
            qDebug("ftpput the %s to %s is ok", local_path, remote_path);
            //sprintf(buf, "ftpput the %s to %s is ok", local_path, remote_path);

            //recordLog(2, 33, buf);


            /////////////////////////// need to update the sqlite and transmit the http request
            //#define MAKING_INFORMATION          0
            ///#define INFORMATION_NOT_UPLOADED    1
            //#define IMAGE_UPLOADED              2
            //#define UPLOADED_OK                 3

            tmp->alert_image.flag = IMAGE_UPLOADED;
            ret = update_sqlite_alert_image(&(tmp->alert_image), false);

       // 2 上传图片成功后发起http请求将信息发给localserver 并将标志写进数据库
            if (ret == true) {
                transmit_http_request(&(tmp->alert_image));
            } else {
                qDebug() << "write to sqlite is error";
            }



            fre_tmp = tmp;
            tmp = tmp->next;

            // when the server has transmit ok  here will free the struct alert image
            if (receive_status == true) {
                tmp->front = fre_tmp->front;
                fre_tmp->front->next = tmp;
                free(fre_tmp);
                qDebug() << "delete the uploaded link ok";
            } else {
                qDebug() << "will not delete the error link";
            }
        } else {
            tmp->alert_image.flag = INFORMATION_NOT_UPLOADED;
            tmp = tmp->next;

            qDebug("ftpput the %s is fail please check the network or other error", local_path);
            //relogin the localserver maybe the passwd is error
            global_mac_log_ok_flag = false;
            //recordLog(2, 2, (char*)"ftpput the alertimage is fail will relogin the server");
        }




    }

    qDebug() << "\n~~~~~~~~~~~~~~~~~~~~update alarm image ok!~~~~~~~~~~~\n";
    global_ftpput_lock.unlock();
}


void ftpput::transmit_http_request(struct alert_image *tmp_alert_image)
{
    QString cmd;
    char buf[BUF_SIZE] = {0};
    char tmp[BUF_SIZE] = {0};
    int length;

    bzero(tmp, BUF_SIZE);
    snprintf(tmp, BUF_SIZE, "filename=%s&alarmtime=%s&confirm=%d&cashier=%s&barcode=%s&",
             tmp_alert_image->file_name, tmp_alert_image->alert_time, tmp_alert_image->confirmed, tmp_alert_image->cashier, tmp_alert_image->barcode);
    length = strlen(tmp);

    //http://~/image.cgi?filename=xxx&alarmtime=YYYYMMDDhhmmss&confirm=0/1&cashier=xxxx&barcode=xxxxxxxxxxxx
    bzero(buf, BUF_SIZE);
    snprintf(buf, BUF_SIZE, "POST /cgi-bin/image.cgi HTTP/1.1\r\nContent-Length:%d\n\n%s\r\n\r\n", length, tmp);
    cmd = QString(buf);
    qDebug() << cmd;

    record_tmp = tmp_alert_image;
    alert_http_client->transmit_info(global_rsys->local_server, HTTP_PORT, cmd, &rec_string);
    connect(alert_http_client, SIGNAL(emit_receive()), this, SLOT(change_sqlite_alert_image()));
    qDebug() << "wait the alert image http respond";
    image_loop->exec();
    qDebug() << "go ahead to alert image transmit";
}

void ftpput::change_sqlite_alert_image()
{
    int start_pos;
    QString tmp;
    int ret;
    char buf[1024];


    disconnect(alert_http_client, SIGNAL(emit_receive()), this, SLOT(change_sqlite_alert_image()));
    receive_status = false;


    if (alert_http_client->error_timeout == true) {
        qDebug() << "transmit alert image to localserver is fail!  time out and connection is fail!!! please check!!!";
    } else {

        start_pos = rec_string.indexOf("Connection: close");
        tmp = rec_string.right(rec_string.length() - start_pos - 17).trimmed();

        qDebug() << "\n!!!!!!!!!!!!!!!the receive string is !!!!!!!!!!";
        qDebug() << tmp;
        tmp = tmp.toLower();
        strcpy(buf, tmp.toLatin1().data());
        if (tmp.contains("ok")) {
            // update sqlite flag to 3
            record_tmp->flag = UPLOADED_OK;
            // 上传信息成功后，将标志写进数据库
            ret = update_sqlite_alert_image(record_tmp, false);
            if (ret == true) {
                receive_status = true;
            }
        } else {
            recordLog(2, 34, strcat(buf, " is fail(update_sqlite_alert_image)"));
            qDebug() << "receive from local server fail send alert informatin fail";
        }
    }
    image_loop->quit();
    qDebug() << "alert image loop quit ok";
}

bool ftpput::update_sqlite_alert_image(struct alert_image *tmp_alert_image, bool flag)
{
    char       buf[BUF_SIZE];
    QSqlQuery query;
    QString command;
    bool ret;


    global_database_lock.lock();
    qDebug() << "change alertimage locked the global database";


   sleep(1);


    /*
    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        cartvu_db = QSqlDatabase::addDatabase("QSQLITE");
        qDebug() << "add QSQLITE here !four here";
    }

    cartvu_db.setDatabaseName(CARTVU_DB);


    if (!cartvu_db.open())
    {
        //QMessageBox::critical(0, "Cannot open database", "Unabel to establise a database connection", QMessageBox::Cancel);
        perror("open cartvu.db fail!!!!!!!!!");
        return  false;
    } else {
        qDebug() << "open cartvu.db database ok!";
    }
    */


    query = QSqlQuery(cartvu_db);

    bzero(buf, BUF_SIZE);

    if (flag == INSERT_FLAG) {
        snprintf(buf, BUF_SIZE, "insert into %s values('%s','%s',%d,'%s','%s',%d)",CARTVU_ALERT_IMAGE,
                 tmp_alert_image->file_name, tmp_alert_image->alert_time, tmp_alert_image->confirmed, tmp_alert_image->cashier, tmp_alert_image->barcode, tmp_alert_image->flag);
    } else {
        snprintf(buf, BUF_SIZE, "update %s set FileName='%s',AlertTime='%s',Confirmed=%d,Cashier='%s',BarCode='%s',Flag=%d where Filename='%s'",CARTVU_ALERT_IMAGE,
                 tmp_alert_image->file_name, tmp_alert_image->alert_time, tmp_alert_image->confirmed, tmp_alert_image->cashier, tmp_alert_image->barcode, tmp_alert_image->flag, tmp_alert_image->file_name);
    }



    command = QString(QLatin1String(buf));
    ret = query.exec(command);
    if (ret == false) {
        qDebug("%s is fail", buf);
        recordLog(2, 34, strcat(buf, "is fail(update_sqlite_alert_image)"));
    } else {
        qDebug("%s is ok", buf);
    }




    //cartvu_db.close();


    global_database_lock.unlock();
    qDebug() << "change alertimage unlocked the global database";

    return ret;

}

void ftpput::making_alert_image()
{
    QString now_time;
    QString file_tmp;
    QDateTime tmp;
    int s_pos;
    bool ret = false;


    now_time = tmp.currentDateTime().toString("yyyyMMddhhmmss");


    file_tmp = QString(global_image_filename);
    do {
        s_pos = file_tmp.indexOf("/");
        file_tmp = file_tmp.right(file_tmp.length() - s_pos -1);
    } while(s_pos >=0);
    qDebug() << file_tmp;
    //file name
    bzero(cartvu_alert_image.file_name, FILE_SIZE);
    strncpy(cartvu_alert_image.file_name, file_tmp.toLatin1().data(), FILE_SIZE);

    //alert time
    bzero(cartvu_alert_image.alert_time, FILE_SIZE);
    strncpy(cartvu_alert_image.alert_time, now_time.toLatin1().data(), FILE_SIZE);

    //confirmed
    cartvu_alert_image.confirmed = 0;

    //cashier number
    bzero(cartvu_alert_image.cashier, FILE_SIZE);
    strncpy(cartvu_alert_image.cashier, global_cashier_nu, FILE_SIZE);

    //barcode
    strncpy(cartvu_alert_image.barcode, "0", FILE_SIZE);


    qDebug() << "FileName:" << cartvu_alert_image.file_name;
    qDebug() << "AlertTime :" << cartvu_alert_image.alert_time;
    qDebug("Confirmed :%d" , cartvu_alert_image.confirmed);
    qDebug() << "Cashier:" << cartvu_alert_image.cashier;
    qDebug() << "BarCode:" << cartvu_alert_image.barcode;

    cartvu_alert_image.flag = MAKING_INFORMATION;
    // new the item
    ret = update_sqlite_alert_image(&cartvu_alert_image, true);
    if (ret == true) {
        qDebug() << "write to  sqlite is ok!!";

    } else {
        qDebug() << "write to sqlite is error";
    }


}




void ftpput::malloc_size_for_alert()
{
    bool ret = false;
    struct alert_image_more *alert_image_tmp;

    // meant that the information is ok
    cartvu_alert_image.flag = 1;
    ret = update_sqlite_alert_image(&cartvu_alert_image, false);
    if (ret == true) {
        qDebug() << "write to sqlite3 is ok  flag = 1 is ok";
    } else {
        qDebug() << "write to sqlite3 is error";
    }

    alert_image_tmp = (struct alert_image_more *)malloc(sizeof(struct alert_image_more));
    if (alert_image_tmp == NULL) {
        perror("malloc for alert image head fail");
        recordLog(2, 8, (char*)"malloc fail(malloc_size_for_alert)");
        exit(1);
    }

    qDebug() << "global_ftpput locked here";
    global_ftpput_lock.lock();
    alert_image_tmp->next = alert_image_head->next;
    alert_image_tmp->front = alert_image_head;

    alert_image_head->next->front = alert_image_tmp;
    alert_image_head->next = alert_image_tmp;

    memcpy(&(alert_image_tmp->alert_image), &cartvu_alert_image, sizeof(cartvu_alert_image));
    global_ftpput_lock.unlock();
    qDebug() << "\n\n!!!!!!!!!!!!!!!!malloc size is ok!!!!!!!!!!!!!!!!\n";
    update_alarm_image_flag = true;
    //update_alarm_image();
    qDebug() << "\n!!!!!!!!!!!!update to local server flag is ok!!!!!!!!!!!!!\n";
}



void ftpput::first_open_db()
{


    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        cartvu_db = QSqlDatabase::addDatabase("QSQLITE");
        qDebug() << "add QSQLITE here !four here";
        recordLog(2, 17, (char*)"add QSQLITE here !four here(first_open_db)");
    }

    cartvu_db.setDatabaseName(CARTVU_DB);



    if (!cartvu_db.open())
    {
        //QMessageBox::critical(0, "Cannot open database", "Unabel to establise a database connection", QMessageBox::Cancel);
        perror("open cartvu.db fail!!!!!!!!!");
        recordLog(2, 17, (char*)"open cartvu.db fail!!!!(first_open_db)");
        return  ;
    } else {
        qDebug() << "open cartvu.db database ok!";
    }


}


void ftpput::run()
{
    int i = 0;
    int five_sec = 0;

    http_client = new client();
    loop = new QEventLoop();
    qDebug() << "global_database_lock is locked here";
    global_database_lock.lock();
    //2 开机检查statis表  和告警表
    check_statis();
    check_alarm_image();
    global_database_lock.unlock();
    qDebug() << "global_database_lock unlocked is ok";


    alert_http_client = new client();
    image_loop = new QEventLoop();


    connect(global_sensor, SIGNAL(start_alarm()), this, SLOT(making_alert_image()));
    // in order to avoid  the information below
    /*   QObject: Cannot create children for a parent that is in a different thread.
    (Parent is QTcpSocket(0x322380), parent's thread is ftpput(0x29a538), current thread is QThread(0x1d6810)
*/
    connect(global_serialMode, SIGNAL(record_ok()), this, SLOT(malloc_size_for_alert()));
    qDebug() << "ftpput put start!!!!!!!!";


    first_open_db();

    while(1) {
        sleep(1);
        if (update_alarm_image_flag == true) {
            update_alarm_image_flag = false;
            if (network_flag == true) {
                update_alarm_image();
            }
        }

        i++;
        if (i >= WRITE_TIME) {
            i = 0;


            //qDebug() << "global_database_lock is locked in run fun";
            global_database_lock.lock();
            write_statis();
            global_database_lock.unlock();
            //qDebug() << "global_database_lock unlocked is in run fun";

            if (network_flag == true) {
                five_sec++;
                if (five_sec >= FTPPUT_COUNT) {
                    global_passwd_lock.lock();
                    strncpy(ftp_passwd, global_rsys->ftp_passwd, FTP_SIZE);
                    global_passwd_lock.unlock();
                    update_alarm_image();

                    five_sec = 0;

                }
            }


        }


    }

}



void ftpput::write_statis()
{
    char       buf[BUF_SIZE];
    QSqlQuery query;
    QString command;
    bool ret;


    /*

    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        cartvu_db = QSqlDatabase::addDatabase("QSQLITE");
        qDebug() << "add QSQLITE here !four here";
    }

    cartvu_db.setDatabaseName(CARTVU_DB);



    if (!cartvu_db.open())
    {
        //QMessageBox::critical(0, "Cannot open database", "Unabel to establise a database connection", QMessageBox::Cancel);
        perror("open cartvu.db fail!!!!!!!!!");
        return  ;
    } else {
        qDebug() << "open cartvu.db database ok!";
    }
*/
    query = QSqlQuery(cartvu_db);

    // update Statis set StatisDate='20131101',CartNum=3,AlertNum=4,ConfirmNum=5,UploadFlag=0 where StatisDate='20131101';
    // delete from Statis where StatisDate='20131101';
    // insert into Statis values('20131101',1,1,1,1);
    bzero(buf, BUF_SIZE);
    //snprintf(buf, BUF_SIZE, "update Statis set StatisDate='20131101',CartNum=3,AlertNum=4,ConfirmNum=5,UploadFlag=0 where StatisDate='20131101'");
    //printf("cartvu_statis.upload_flag is %d\n", cartvu_statis.upload_flag);
    //qDebug("cartvu_statis.upload_flag is %d", cartvu_statis.upload_flag);
    //cartvu_statis.upload_flag = 0;
    snprintf(buf, BUF_SIZE, "update %s set StatisDate='%s',CartNum=%d,AlertNum=%d,ConfirmNum=%d,UploadFlag=%d where StatisDate='%s'",CARTVU_STATIS,
             cartvu_statis.statis_date, cartvu_statis.cart_num, cartvu_statis.alert_num, cartvu_statis.confirm_num, cartvu_statis.upload_flag, cartvu_statis.statis_date);

    command = QString(QLatin1String(buf));

    ret = query.exec(command);
    if (ret == false) {
        qDebug("%s \n!!!!!!!!!!!!!~~~~~~~~~~~~~~~~~~~~~~~~~fail!!!!!!!!!!!!!!!!!!!", buf);
        recordLog(2, 34, strcat(buf, " is fail"));
    } else {
        qDebug("%s is ok", buf);
    }


    qDebug() << "update statis every 5 sec is ok";

    //cartvu_db.close();
    //while(1);
}


ftpput::~ftpput()
{
    qDebug() << "delete the ftpput";
}
