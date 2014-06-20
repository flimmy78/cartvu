#include "watchdog.h"

extern void recordLog(int type, int code, char *info);
extern int ftpflag;
extern int my_system(const char* cmd);

watchdog::watchdog()
{

    count = 0;

    watchdog_timer = new QTimer();
    connect(watchdog_timer, SIGNAL(timeout()), this, SLOT(feed_dog_count()));
    //watchdog_timer->start(MAIN_FEED_TIMER*1000);

}

void watchdog::feed_dog_count()
{
    count = 0;
    qDebug() << "feed the dog count = 0 ok!";

}



watchdog::~watchdog()
{
    qDebug() << "delete watchdog";
}


void watchdog::run()
{

    watchdog_timer->start(MAIN_FEED_TIMER*1000);
    set_watdog_time();
   // exec();
    while (1) {
        sleep(1);
        feed_dog();
        //qDebug() << "sleep";

    }
}

void watchdog::set_watdog_time()
{
    int fd;
    int ret;
    int time_out;
    static int last_fd;

    fd = open(WATCH_DOG_PATH, O_RDWR);
    if (fd < 0)
    {
        perror("~~~~~~~~~~~~~~~open watchdog fail~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        qDebug("last watdog fd is %d", last_fd);
        recordLog(3, 17, (char*)"~~open watchdog fail~~~~~~");
        return;
        //exit(1);
    }

    time_out = SET_WATCHDOG_TIME_OUT;
    ret = ioctl(fd, WDIOC_SETTIMEOUT, &time_out);
    if (ret < 0)
    {
        perror("~~~~~~~~~~~~~~~~~~~~~~~~~read watchdog time out error~~~~~~~~~~~~~~~~~~~~");
        recordLog(3, 35, (char*)"read watchdog time out error~~~~~~~~");
        //exit(1);
    }
    qDebug("\n\nnow watchdog time out is %d second            \n", time_out);

    last_fd = fd;

    if (close(fd) < 0) {
        perror("~~~~~close watdog fd fail~~~~~~~");
        recordLog(3, 17, (char*)"close watdog fd fail~~~~~");
        qDebug() << "\n!!!!!!!!!!!!!!!!close watdog fd fail!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

    } else {
        qDebug("now the watdog fd is %d", fd);
    }


    qDebug() << "\nset watchdog is ok!!!!!!!!!!!!!!!!!!!!!!!\n";
}

void watchdog::feed_dog()
{
    static int time_count = 0;
    int fd;
    int ret;
    static int last_fd;

    //qDebug() << "feed!@@@@@@@@@@@";
    ++time_count;
    //qDebug("sleep %d sec", time_count);
    if (time_count < FEED_DOG_TIMER) {
        ;
    } else {
        time_count = 0;
        count++;
        qDebug("now the watchdog count is %d", count);
        if (count < WATDOG_CYCLE) {
            fd = open(WATCH_DOG_PATH, O_RDWR);
            if (fd < 0)
            {
                perror("~~~~~~~~~~~~~~~open watchdog fail~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                qDebug("last watdog fd is %d", last_fd);
                recordLog(3, 17, (char*)"~open watchdog fail(feed dog)");
                return;
                //exit(1);
            }
            ret = ioctl(fd, WDIOC_KEEPALIVE, NULL);
            if (ret < 0)
            {
                perror("~~~~~~~~~~~~~~~~~~~~ioctl watchdog fail~~~~~~~~~~~~~~~~~~");
                recordLog(3, 35, (char*)"ioctl watchdog fail~~~(feed dog)");
                //exit(1);
            }

            last_fd = fd;
            if (close(fd) < 0) {
                perror("~~~~~close watdog fd fail~~~~~~~");
                qDebug() << "\n!!!!!!!!!!!!!!!!close watdog fd fail!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
                recordLog(3, 35, (char*)"close watdog fd fail~~~(feed dog)");

            } else {
                qDebug("now the watdog fd is %d", fd);
            }
            //qDebug() << "feed the dog ok";

        } else {
            qDebug() << "not receive the count change!!! and will reboot";

        }
        if ((count > WATDOG_CYCLE - 2) && (ftpflag == 1)) {
            recordLog(3, 32, (char*)"the network maybe block kill ftpput and ftpget here");
            my_system("/usr/bin/killall ftpput");
            my_system("/usr/bin/killall ftpget");
            count = 0;
        }


    }
}
