#include "synchTime.h"






extern global_config *global_conf_sys;

extern int my_system();
extern bool network_flag;

extern void recordLog(int type, int code, char *info);

synchTime::synchTime()
{
    synch_init();

}

void  synchTime::synch_init()
{
    
    
    strncpy(local_server, global_conf_sys->sys_network.local_server, TMP_SIZE);
    
    timeZone = global_conf_sys->sys_global.time_zone;
    //0-none  1-USA  2-EUROPE
    savingTimeExistFlag = global_conf_sys->sys_global.saveing_time;
    
    //sleep(4);
    qDebug("the saving time is %d\n",savingTimeExistFlag);
    //sleep(4);
    //now year
    now_year = global_conf_sys->sys_mod_date.year;
    qDebug("now the year is %d", now_year);
    
    
    try_count = 0;
}




void  synchTime::timeSynchronization()
{
    sender = new QUdpSocket(this);
    connect(&syn_timer, SIGNAL(timeout()), this, SLOT(syn_state()));

    if (network_flag == false) {
        try_count = 5;
        syn_timer.start(1000);
        recordLog(5, 2, (char*)"network is error no sys the time");
    } else {

        iGMT = 0;

        sender->bind(BIND_PORT);
        sntpHeaderSender.LiVnMode = LIVN_MODE;
        serverAddress = QHostAddress(local_server);

        send_time();

        connect(sender, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
        qDebug() << "connect ok!";
        syn_timer.start(SYN_TIMEOUT*1000);
    }


}




void synchTime::send_time()
{
    OriTimeInt = time(0) + SNTPEPOCH - 3600U * iGMT;
    sender->writeDatagram((char *)&sntpHeaderSender, sizeof(struct SntpHeader), serverAddress, BIND_PORT);
    qDebug()<<"writeDatagram length:"<<sizeof(struct SntpHeader)<<"\n";
}



void  synchTime::syn_state()
{

    qDebug() << "the server has not send the time!!!please check the network and try another time";
    if (try_count++ < SYN_CONNT) {
        qDebug("try anoter %d times", try_count);
        send_time();
    } else {
        syn_timer.stop();
        disconnect(sender, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
        disconnect(&syn_timer, SIGNAL(timeout()), this, SLOT(syn_state()));
        qDebug() << "syn time error~!~!~!~!~!~!~!~!~!~!";
        judge_savingtime();
    }

}


// first step
void  synchTime::getTimeInformation()
{
    int      pos = 0;
    //char     buf[TMP_SIZE];
    char savingtime_path[FILE_LENGTH];
    QString  line, cmd,  value;

    bzero(savingtime_path, FILE_LENGTH);

            //    /cartvu/proc/savingtime/2013.EU
    if (savingTimeExistFlag == 2) {
        snprintf(savingtime_path, FILE_LENGTH, "%s%d.EU", SAVING_TIME_PATH, now_year);
    } else if (savingTimeExistFlag == 1) {//          /cartvu/proc/savingtime/2013.USA
        snprintf(savingtime_path, FILE_LENGTH, "%s%d.USA", SAVING_TIME_PATH, now_year);
    }  else {
        qDebug() << "no daylight saving time";
        return;
    }

    qDebug("savingtime  file is %s", savingtime_path);

    QFile savingtime_file(savingtime_path);
    if (savingtime_file.exists()) {
        if (savingtime_file.open(QIODevice::ReadWrite)) {
            QTextStream   stream(&savingtime_file);
            do {
                line = stream.readLine().toLower();
                pos = line.indexOf('=');
                cmd = line.left(pos).trimmed();
                value = line.right(line.length() - pos - 1).trimmed();
                if (cmd.compare("stbegin") == 0) {
                    start_day = value.toLong();
                    qDebug("start_day:%d\n", start_day);
                } else if (cmd.compare("stend") == 0) {
                    end_day   = value.toLong();
                    qDebug("savingTimeEnd:%d\n", end_day);
                }
            } while (!line.isNull());
            geting_stamp();
        } else {
            qDebug("%s file open fail!!!", savingtime_path);
            recordLog(5, 17, (char*)"saving file open fail!");
        }
    } else {
        qDebug("the %s file is not exist", savingtime_path);
        recordLog(5, 17, (char*)"saving file is not exist");
    }
}


void synchTime::geting_stamp()
{
    struct tm tm;
    char buf[TMP_SIZE] = {0};



    // setting the time zone
    bzero(buf, TMP_SIZE);
    snprintf(buf, TMP_SIZE, "GMT%+d", -timeZone);
    qDebug("%s", buf);
    my_system("date -R");
    qDebug("!!!!!!!!!!after setting the timezone!!!!!!!!!");
    setenv("TZ", buf, 1);
    my_system("date -R");




    tm.tm_year = now_year - 1900;//
    tm.tm_mon = START_MONTH - 1;
    tm.tm_mday = start_day;
    tm.tm_hour = START_HOUR;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    savingTimeStart = mktime(&tm);
    printf("%d-%d-%d %d:00:00 is %ld\n", now_year, START_MONTH, start_day, START_HOUR, savingTimeStart);

    tm.tm_year = now_year - 1900;//
    tm.tm_mon = END_MONTH - 1;
    tm.tm_mday = end_day;
    tm.tm_hour = END_HOUR;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    savingTimeEnd = mktime(&tm);
    printf("%d-%d-%d %d:00:00 is %ld\n", now_year, END_MONTH, end_day, END_HOUR, savingTimeEnd);

}

void  synchTime::readPendingDatagrams()
{
    int     count = 0;
    int     retValue = 0;
    char    *pBuf = NULL;
    unsigned  char  tempChar;
    QByteArray   datagram;

    //long int tmp1,tmp2;




    // stop the timer
    syn_timer.stop();
    disconnect(&syn_timer, SIGNAL(timeout()), this, SLOT(syn_state()));
    disconnect(sender, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));



    pBuf = (char *)&sntpHeaderTransfer;
    sntpHeaderReceive = (struct SntpHeader *)pBuf;
    memset(sntpHeaderReceive, 0, sizeof(struct SntpHeader));


    while (sender->hasPendingDatagrams())
    {
        datagram.resize(sender->pendingDatagramSize());
        sender->readDatagram(pBuf, datagram.size());
    }

    qDebug()<<"the receive data is ok!\n";
    for (count = 4; count < 12; count++)
    {
        tempChar = *(pBuf + count * 4);
        *(pBuf + count * 4) = *(pBuf + count * 4 + 3);
        *(pBuf + count * 4 + 3) = tempChar;
        tempChar = *(pBuf + count * 4 + 1);
        *(pBuf + count * 4  + 1) = *(pBuf + count * 4 + 2);
        *(pBuf + count * 4  + 2) = tempChar;
    }


    qDebug("\n time() is %lu\n", time((time_t *)NULL));
    qDebug("\n 4 max is %d\n", 0xffffffff);


    qDebug("\nRefTimeInt = %lu\n", sntpHeaderReceive->RefTimeInt);
    qDebug("\nOriTimeInt = %lu\n", sntpHeaderReceive->OriTimeInt);

    qDebug("\n t1 OriTimeInt = %lu\n", OriTimeInt);
    qDebug("\n t2 RecvTimeInt = %lu\n", sntpHeaderReceive->RecvTimeInt);
    qDebug("\n t3 TranTimeInt = %lu\n", sntpHeaderReceive->TranTimeInt);
    DestTimeInt = time((time_t *)NULL) + SNTPEPOCH - 3600U * iGMT;
    qDebug("\n t4 Local TimeStamp = %lu\n", DestTimeInt);


    //                      [  (t2 - t1)     +                  (t3 - t4)    ]/2
    difference  = (sntpHeaderReceive->RecvTimeInt - OriTimeInt)/2 + (sntpHeaderReceive->TranTimeInt - DestTimeInt)/2;
    //difference  = difference / 2;
    qDebug("now the difference is %lld\n", difference);
    qDebug() << difference;

    /*
    tmp1 = (sntpHeaderReceive->RecvTimeInt - OriTimeInt);
    tmp2 = (sntpHeaderReceive->TranTimeInt - DestTimeInt);
    difference = (tmp1 + tmp2)/2;
    qDebug("tmp1 is %lu\n", tmp1);
    qDebug("tmp2 is %lu\n", tmp2);
    qDebug("now the difference is %lu\n", difference);
    qDebug() << difference;
*/
    tz.tz_minuteswest = iGMT * 60;
    tz.tz_dsttime = 0;

    tv.tv_usec = 0;
    tv.tv_sec  = time(0) + difference;


    time(&timep);
    tp = gmtime(&timep);
    qDebug("\n!!!!!!!!!the  date before adjusting and utc is :%04d-%02d-%02d %02d:%02d:%02d\n", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);
    my_system("hwclock --show");
    my_system("date -R");


    retValue = settimeofday(&tv, &tz);
    if (retValue == 0) {
        qDebug()<<"\nSetting Time OK!\n";
        recordLog(5, 9, (char*)"Setting Time OK");
    } else {
        qDebug()<<"\nSetting Time Fail!\n";
        recordLog(5, 9, (char*)"Setting Time Fail");
    }


    time(&timep);
    tp = gmtime(&timep);
    qDebug("\n!!!!!!!!!!!!the  date after adjusting and utc is :%04d-%02d-%02d %02d:%02d:%02d\n", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);
    setenv("TZ", "GMT+0", 1);

    modifyRTC(tp);


    my_system("hwclock --show");
    my_system("date -R");
    my_system("hwclock --hctosys");
    //my_system("hwclock -s");


    // setting the time zone
    bzero(buf, TMP_SIZE);
    snprintf(buf, TMP_SIZE, "GMT%+d", -timeZone);
    qDebug("%s", buf);
    my_system("date -R");
    setenv("TZ", buf, 1);
    my_system("date -R");





    time(&timep);
    tp = localtime(&timep);
    qDebug("\n!!!!!!!the  date after setting the TIME ZONE is :%04d-%02d-%02d %02d:%02d:%02d\n", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);
    my_system("hwclock --show");

    
    judge_savingtime();


}
void synchTime::judge_savingtime()
{

    if (0 != savingTimeExistFlag)
    {
         timep = time(0);
         qDebug("time(0) is %ld", timep);
         if ((timep > savingTimeStart) && (timep < savingTimeEnd)) {
             snprintf(buf, TMP_SIZE, "GMT%+02d", -(timeZone+1));
             printf("set TZ=%s\n", buf);
             setenv("TZ", buf, 1);
             printf("iiiiiiiiiiiiii in the daylight saving time iiiiiiiiiiiiii\n");
         } else {
             snprintf(buf, TMP_SIZE, "GMT%+02d", -timeZone);
             printf("set TZ=%s\n", buf);
             setenv("TZ", buf, 1);
             printf("ooooooooooooo outside the daylight saving time oooooooooooooo\n");
         }
     } else {
         snprintf(buf, TMP_SIZE, "GMT%+02d", -timeZone);
         printf("set TZ=%s\n", buf);
         setenv("TZ", buf, 1);
        qDebug() << "it has no daylight savingtime here! and set the tz is ok";
     }
    qDebug() << "the time is set ok and end here";


    qDebug() << "before delete the sendoer ";
    //delete sender;
    qDebug() << "delete the sendoer ok?";
    emit syn_time_ok();
}

bool synchTime::modifyRTC(struct  tm  *tp)
{
    int   ret = -1;
    int   fd  = -1;
    char buf[TMP_SIZE] = {0};

    qDebug()<<"RTC before adjusting:\n";
    bzero(buf, TMP_SIZE);
    snprintf(buf, TMP_SIZE, "hwclock --show -f %s", RTC_DEVICE);
    my_system(buf);

    fd = open(RTC_DEVICE, O_RDONLY);
    qDebug()<<"fd:"<<fd<<"\n";
    if (fd < 0) {
        qDebug()<<"open rtc fail!\n";
        recordLog(5, 17, (char*)"open rtc fail!");
        return  false;
    } else {
        qDebug()<<"open rtc success\n";
    }

    rtcTm.tm_year = tp->tm_year;
    rtcTm.tm_mon  = tp->tm_mon;
    rtcTm.tm_mday = tp->tm_mday;
    rtcTm.tm_hour = tp->tm_hour;
    rtcTm.tm_min  = tp->tm_min;
    rtcTm.tm_sec  = tp->tm_sec;

    ret = ioctl(fd, RTC_SET_TIME, &rtcTm);
    if (ret < 0)
    {
        qDebug()<<"RTC_SET_TIME:ERROR"<<"\n";
        recordLog(5, 35, (char*)"RTC_SET_TIME:ERROR");
        return   false;
    }

    ret = ioctl(fd, RTC_RD_TIME, &rtcTm);
    if (ret < 0)
    {
        qDebug()<<"RTC_RD_TIME:ERROR"<<"\n";
        recordLog(5, 35, (char*)"RTC_RD_TIME:ERROR");
        return   false;
    }

    close(fd);

    qDebug()<<"RTC after adjusting:\n";

    bzero(buf, TMP_SIZE);
    snprintf(buf, TMP_SIZE, "hwclock -f %s", RTC_DEVICE);
    my_system(buf);
    return  true;
}
