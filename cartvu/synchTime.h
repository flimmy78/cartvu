#ifndef SYNCHTIME_H
#define SYNCHTIME_H

#include <QObject>
#include <QtNetwork>
#include <QString>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QUdpSocket>
#include  <QDebug>


#include "config_sys.h"











#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/rtc.h>
#include <arpa/inet.h>

#include <string.h>
#include <strings.h>
#include <time.h>
#include <sys/time.h>







#define RTC_DEVICE  "/dev/rtc0"

#define SAVING_TIME_PATH          "/cartvu/savingtime/"

#define FILE_LENGTH          50


#define TMP_SIZE   200


#define RE_FID_SIZE  4

#define BIND_PORT   123

#define LIVN_MODE  0x1b

//70��ʱ���
#define SNTPEPOCH           86400U  * (365U * 70U + 17U)

//��ʱ����ʼ�������·�
#define START_MONTH    3
#define END_MONTH      11

//��ʱ����ʼ�ڽ���Сʱ
#define START_HOUR      2
#define END_HOUR       2

// syn time out sec
#define SYN_TIMEOUT      5

#define SYN_CONNT        5



//sntpЭ��
struct  SntpHeader
{
    unsigned  char  LiVnMode;
    unsigned  char  Stratum;
    unsigned  char  Poll;
    unsigned  char  Precision;
    long      int   RootDelay;
    long      int   RootDispersion;
    char      RefID[RE_FID_SIZE];
    long      int   RefTimeInt;
    long      int   RefTimeFraction;
    long      int   OriTimeInt;
    long      int   OriTimeFraction;
    long      int   RecvTimeInt;
    long      int   RecvTimeFraction;
    long      int   TranTimeInt;
    long      int   TranTimeFraction;
};


class synchTime : public QObject
{
    Q_OBJECT
public:
    synchTime();
    void synch_init();
  //����ͨ�벻ͨ�����ִ������
    void timeSynchronization();
    //��ȡ��ʱ���ļ�
    void getTimeInformation();
    //��ȡ��ʱ���ļ���¼���ڵ�����ʱ���
    void geting_stamp();
    //�ж��Ƿ�����ʱ���ڣ�������ϵͳʱ��
    void judge_savingtime();
    //�޸�rtcʵʱʱ��
    bool modifyRTC(struct tm *tp);
    //�������ݸ�localserver����ȡʱ��ͬ����Ϣ
    void send_time();
public:
    char local_server[TMP_SIZE];
    QUdpSocket *sender;
    QHostAddress  serverAddress;

    struct timezone    tz;
    struct timeval     tv;
    struct tm          *tp;


    struct SntpHeader  sntpHeaderSender;
    struct SntpHeader  sntpHeaderTransfer;
    struct SntpHeader  *sntpHeaderReceive;

    long  int  OriTimeInt;
    long  int  DestTimeInt;
    long  long int  difference;
//long int  difference;

    int   iGMT;


    struct  rtc_time  rtcTm;

    int timeZone;
    char buf[TMP_SIZE];

    time_t  timep;

    char   savingTimeExistFlag;

    int start_day;
    int end_day;
    long  int  savingTimeStart;
    long  int  savingTimeEnd;
    int now_year;
    QTimer syn_timer;
    int try_count;
private slots:
    //�յ�localserver���͵���Ϣʱ���޸�ʱ��
    void readPendingDatagrams();
    //��localserverʱ��ͬ����ʱ������
    void  syn_state();

signals:
    //ʱ��ͬ����ɣ������Ƿ� ������
    void syn_time_ok();

};

#endif // SYNCHTIME_H
