#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <QThread>
#include <QTimer>
#include <QDebug>

#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/watchdog.h>






#define WATCH_DOG_PATH   "/dev/watchdog"
//��ʱ�޸�count���Ա���FEED_DOG_TIMER����ʱι��
#define MAIN_FEED_TIMER  29
//��ʱ30�����ι������
#define FEED_DOG_TIMER   30

//���ÿ��Ź���ʱ��
#define SET_WATCHDOG_TIME_OUT   32


#define MIN         3

//���Ź����ʱ��
#define WATDOG_CYCLE   (MIN*60/FEED_DOG_TIMER)


class watchdog : public QThread
{
    Q_OBJECT
public:
    watchdog();
    ~watchdog();
    void run();
    //���ÿ��Ź�ʱ��
    void set_watdog_time();
public:
    QTimer *watchdog_timer;
    int count;

private slots:
    //ι������
    void feed_dog();
    //�޸�count
    void feed_dog_count();

};

#endif // WATCHDOG_H
