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
//定时修改count，以便在FEED_DOG_TIMER到来时喂狗
#define MAIN_FEED_TIMER  29
//定时30秒进入喂狗函数
#define FEED_DOG_TIMER   30

//设置看门狗的时间
#define SET_WATCHDOG_TIME_OUT   32


#define MIN         3

//看门狗最大时间
#define WATDOG_CYCLE   (MIN*60/FEED_DOG_TIMER)


class watchdog : public QThread
{
    Q_OBJECT
public:
    watchdog();
    ~watchdog();
    void run();
    //设置看门狗时间
    void set_watdog_time();
public:
    QTimer *watchdog_timer;
    int count;

private slots:
    //喂狗函数
    void feed_dog();
    //修改count
    void feed_dog_count();

};

#endif // WATCHDOG_H
