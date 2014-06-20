#include "sensor.h"


//struct sensor_att sensor[SENSOR_NUM] = {
//    {.name = "E1_SENSOR", .pin = E1_PIN, .state = 0, .error_num = 0, .allow_error_num = E1_ERROR_MAX},
//    {.name = " S_SENSOR", .pin = S_PIN,  .state = 0, .error_num = 0, .allow_error_num = S_ERROR_MAX},
//    {.name = "I1_SENSOR", .pin = I1_PIN, .state = 0, .error_num = 0, .allow_error_num = I1_ERROR_MAX},
//    {.name = "I2_SENSOR", .pin = I2_PIN, .state = 0, .error_num = 0, .allow_error_num = I2_ERROR_MAX},
//    {.name = "I3_SENSOR", .pin = I3_PIN, .state = 0, .error_num = 0, .allow_error_num = I3_ERROR_MAX},
//    {.name = "E2_SENSOR", .pin = E2_PIN, .state = 0, .error_num = 0, .allow_error_num = E2_ERROR_MAX},
//};

//extern camThread *global_camera;                                  // camera class(reference to camThread.cpp)
int global_buttons_fd;                                            // handler of buttons device

extern global_config *global_conf_sys;                            // class for processing config.sys(reference to config_sys.cpp)

extern char status[STATUS_SIZE];

extern struct statis  cartvu_statis;
extern QMutex global_statis_lock;

extern void initial_machine();
extern void funm(int signo);

extern camThread *global_camera;


struct alalyse_signal {
    int flag;
    char timestamp[30];

};

struct alalyse_signal judge_has_e2_signal = {
    0,
    "start"
};



struct sensor_all_att all_sensor = {
    {
        {"E1_SENSOR", E1_PIN, 0, 0, 0, E1_ERROR_MAX, E1_CHAR, SENSOR_GOOD},
        {" S_SENSOR",  S_PIN, 0, 0, 0,  S_ERROR_MAX,  S_CHAR, SENSOR_GOOD},
        {"I1_SENSOR", I1_PIN, 0, 0, 0, I1_ERROR_MAX, I1_CHAR, SENSOR_GOOD},
        {"I2_SENSOR", I2_PIN, 0, 0, 0, I2_ERROR_MAX, I2_CHAR, SENSOR_GOOD},
        {"I3_SENSOR", I3_PIN, 0, 0, 0, I3_ERROR_MAX, I3_CHAR, SENSOR_GOOD},
        {"E2_SENSOR", E2_PIN, 0, 0, 0, E2_ERROR_MAX, E2_CHAR, SENSOR_GOOD},
        {"EXT_SENSOR", EXT_PIN, 0, 0, 0, EXT_ERROR_MAX, EXT_CHAR, SENSOR_GOOD},
    },
E2_STATE,
'X',
};
//struct sensor_att sensor[SENSOR_NUM] = {
//    {"E1_SENSOR", E1_PIN, 0, 0, E1_ERROR_MAX},
//    {" S_SENSOR",  S_PIN, 0, 0,  S_ERROR_MAX},
//    {"I1_SENSOR", I1_PIN, 0, 0, I1_ERROR_MAX},
//    {"I2_SENSOR", I2_PIN, 0, 0, I2_ERROR_MAX},
//    {"I3_SENSOR", I3_PIN, 0, 0, I3_ERROR_MAX},
//    {"E2_SENSOR", E2_PIN, 0, 0, E2_ERROR_MAX},
//};


u8 del_flag = 0;

// not use accu and i judge of e1,s,e2
#define USE_ACCU_I     0


#if USE_ACCU_I
#define OTHER_SENSOR   4


char   all_sensor_record[OTHER_SENSOR] = {E1_CHAR, S_CHAR, I_CHAR, E2_CHAR};
int sen_sum = (int)E1_CHAR + (int)S_CHAR + (int)I_CHAR + (int)E2_CHAR;
int sen_pos = 4;

#else
#define OTHER_SENSOR   3
char   all_sensor_record[OTHER_SENSOR] = {E1_CHAR, S_CHAR, E2_CHAR};
int sen_sum = (int)E1_CHAR + (int)S_CHAR + (int)E2_CHAR;
int sen_pos = 3;

#endif





char   i_sensor_record[I_SENSOR_NUM] = {I1_CHAR, I2_CHAR, I3_CHAR};
int i_sum = (int)I1_CHAR + (int)I2_CHAR + (int)I3_CHAR;
int i_pos = 3;




char  sensor_judge[JUDGE_SIZE] = {0};
int  judge_pos = 0;




/****************************************************************************
  Function: sensor_c()
  Description: Constructor function

  Entry: None
  Return: None
*****************************************************************************/
sensor_c::sensor_c()
{
    qDebug() << "constructor sensor";
    now_position_state = E2_STATE;                                        // initial state
    now_key_state = 0;

    alarm_interval_ok = true;

    connect(&E2_timeout, SIGNAL(timeout()), this, SLOT(switch_to_E2()));
}

sensor_c::~sensor_c()
{
    qDebug() << "delete sensor";
}
/***************************************************************************

****************************************************************************/
void sensor_c::run()
{

    have_alarm_flag = false;
    qDebug() << "\n~~~~~first sensor thread start!!!!~~~~\n";
    signal(SIGSEGV,funm);
    qDebug() << "register the funm ok";

    /*button_test*/
    //camera = global_camera;

    now_conf_sys = global_conf_sys;

    //you shall connect here but not  in the construct fun
    //connect(this, SIGNAL(take_alarm_pic()), camera, SLOT(take_pic()));
    //buttons_fd = open_button();
    qDebug() << "before led_show";
    led_show();
    qDebug() << "led_show ok";
    fisrt_read_button();


    global_buttons_fd = open_button();
    qDebug() << "second ~~~sensor thread start";
    while (1) {

        now_key_state = button_test();

        if (now_key_state < 0) {
            perror("error open or read button");

            return;
        }
        //show_sensor_state();
        // no need to judge error
        if ((now_conf_sys->sys_working_mode.working_mode == SINGLE_MODE) || (all_sensor.sensor[EXT_POSITION].has_signal == SENSOR_SIGNAL_Y)) {
            now_position_state = E1_STATE;
            position_switch(&now_position_state);
            qDebug() << "no need to judge sensor error";
        } else {//
            position_switch(&now_position_state);
            sensor_error_judge();//
        }


        // add extra sensor signal here
        // if (all_sensor.sensor[EXT_POSITION].has_signal == SENSOR_SIGNAL_Y) {

        //  }


        //qDebug("5cartvu_statis.upload_flag is %d", cartvu_statis.upload_flag);
        emit show_led(&all_sensor);
    }
}

void sensor_c::fisrt_read_button()
{
    int buttons_fd = -1;
    int ret = -1;
    key_type key_info;

    buttons_fd = open(BUTTON_DEVICE, O_RDWR | O_NONBLOCK);
    if (buttons_fd < 0) {
        perror("open buttons_fd fail");
        recordLog(7, 17, (char*)"open buttons fd fail");
        return;
    }
    global_buttons_fd = buttons_fd;
    ret = read(buttons_fd, &key_info, sizeof(key_info));
    if (ret < 0) {
        perror("read error");
        recordLog(7, 35, (char*)"read error fail");
    }

    sensor_set_pin(key_info);
    position_switch(&now_position_state);
    emit show_led(&all_sensor);

    ret = close(buttons_fd);
    if (ret < 0) {
        perror("close first buttons_fd error");
    }
}



int sensor_c::open_button(void) {
    int ret = -1;
    qDebug() << "who call me!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    //while(1);
    int fd = open(BUTTON_DEVICE, BUTTON_FLAG);

    if (fd < 0) {
        perror("first open buttons fail and will terminate the thread!");
        recordLog(7, 17, (char*)"first open buttons fail and will terminate the thread!");
        //exit(1);
        //this->terminate();
        perror("after terminate!");
        qDebug() << "global_buttons_fd is " << global_buttons_fd;
        if (ret < 0) {
            perror("now fd error!");
        }
        //while(1);
        return -1;
    } else {
        global_buttons_fd = fd;
    }

    return fd;
}
int sensor_c::open_button_noblock(void) {

    int fd = open(BUTTON_DEVICE, O_RDWR | O_NONBLOCK);

    if (fd < 0) {

        perror("open buttons with noblock fail");
        recordLog(7, 17, (char*)"open buttons with noblock fail");
        //while(1);
        //this->terminate();
        exit(1);
    }

    return fd;
}


void sensor_c::sensor_set_pin(key_type key_info) {
    int i = 0;
    for (i = 0; i < ALL_SENSOR_NUM; i++) {
        all_sensor.sensor[i].state = (key_info.key_state >> all_sensor.sensor[i].pin) & 0x1;
        all_sensor.sensor[i].has_signal = (key_info.signal_key_state >> all_sensor.sensor[i].pin) & 0x1;
        if (all_sensor.sensor[i].has_signal) {
            all_sensor.now_signal = all_sensor.sensor[i].signal_style;
            //clear the error signal
            status[STATUS_SENSOR_SIZE - 1 - i] = '0';
            all_sensor.sensor[i].error_num = 0;
            all_sensor.sensor[4].error_flag = SENSOR_GOOD;
        }
    }
}

void sensor_c::show_sensor_state() {
    int i;
    for (i = 0; i < ALL_SENSOR_NUM; i++)
        printf("%s is %d\n", all_sensor.sensor[i].name, all_sensor.sensor[i].state);

}


int sensor_c::button_test() {
    int ret = -1;
    key_type key_info;
    int buttons_fd = -1;

    //buttons_fd = open_button();
    buttons_fd = global_buttons_fd;
    if (buttons_fd < 0) {
        recordLog(7, 17, (char*)"buttons fd is below zero");
        perror("buttons fd is below zero");
        return -1;
    }
    //  while (1) {
    ret = read(buttons_fd, &key_info, sizeof(key_info));
    if (ret < 0) {
        recordLog(7, 35, (char*)"first read buttons fail");
        perror("first read buttons fail");
        //while(1);
        //this->terminate();
    }
    //qDebug("1cartvu_statis.upload_flag is %d", cartvu_statis.upload_flag);

    buttons_fd = judge_reboot(key_info, buttons_fd);
    //qDebug("2cartvu_statis.upload_flag is %d", cartvu_statis.upload_flag);
    //printf("key_state is %x\n", key_info.key_state);
    //printf("signal_key_state is %x\n", key_info.signal_key_state);
    sensor_set_pin(key_info);
    //qDebug("3cartvu_statis.upload_flag is %d", cartvu_statis.upload_flag);


    /*
#ifdef DEBUG
    printf("%x\n", key_info.key_state);
#endif
#if BUTTON_NO_BLOCK
    sleep(1);
#endif
    */
    /*
    if (buttons_fd > 0) {
        //ret = close(buttons_fd);
        if (ret < 0) {
            perror("close now buttons_fd error");
        } else {
            //qDebug() << "close the buttons_fd ok! " << buttons_fd;
        }
    }
    */

    return (int)key_info.key_state;
}




int sensor_c::judge_reboot(key_type key_info, int buttons_fd) {
    int ret = 0;
    //char buf[BUF_SIZE] = {0};
    int fd;
    if (del_flag == 0) {
        if ((key_info.key_state&0x100) == 0x100) {
            qDebug() << "try to reboot the system";
            //emit take_alarm_pic();
            ret = close(buttons_fd);
            if (ret < 0) {
                perror("close buttrons_fd error");
                //while(1);
            }

            printf("you want to reset the machine? hold the button for 3 sec!\n");
            sleep(3);
            fd = open(BUTTON_DEVICE, O_RDWR | O_NONBLOCK);
            if (fd < 0) {
                perror("open buttons_fd fail not to reboot");
                recordLog(7, 17, (char*)"open buttons_fd fail not to reboot");
                return -1;
            }
            buttons_fd = fd;
            global_buttons_fd = fd;
            ret = read(buttons_fd, &key_info, sizeof(key_info));
            if (ret < 0) {
                perror("read error");
                recordLog(7, 35, (char*)"read buttons error");
                return buttons_fd;
            }

            if ((key_info.key_state&0x100) == 0x100) {
                del_flag = 1;
                /*
                bzero(buf, BUF_SIZE);
                snprintf(buf, BUF_SIZE, "echo \"===delete %s ===\" > /dev/tty0", "/etc/eth0-setting");
                printf("%s\n", buf);
                my_system(buf);

                bzero(buf, BUF_SIZE);
                snprintf(buf, BUF_SIZE, "/bin/rm %s", "/etc/eth0-setting");
                my_system(buf);
                */

                initial_machine();
                recordLog(1, 22, (char*)"initial machine due to the pcb board button click !");

                //my_system("/bin/date -R >> /var/log/eth0-setting.log");
                //my_system("echo 'delete eth0-setting due to the pcb board button click' >>/var/log/eth0-setting.log");

                my_system("/sbin/reboot");
                this->terminate();
            } else {


                printf("do nothing\n");
            }
            ret = close(buttons_fd);
            if (ret < 0) {
                perror("close now buttons_fd error");
            }
            //return -1;
            global_buttons_fd = open(BUTTON_DEVICE, O_RDWR);
            if(buttons_fd < 0) {
                perror("open fail");
                recordLog(1, 17, (char*)"open fail !");
                exit(1);
            }
            buttons_fd = global_buttons_fd;
        }
    }
    return buttons_fd;
}

int sensor_c::open_led() {
    int fd = open(LED_DEVICE, O_RDWR);
    if (fd < 0) {
        perror("open leds fail");
        recordLog(1, 17, (char*)"open leds fail !");
        exit(1);
    }
    return fd;
}


void sensor_c::led_show() {
    int ret = -1;
    int led_fd;
    int flag = 1;
    int i = 0;
    int j = 8;
    led_fd = open_led();
    while (j--) {
        /*led_fd:	fd
         *flag:		(0,1)
         *i:		(0 1 2 3)
         */
        ret = ioctl(led_fd, flag, i);
        i++;
        if(ret < 0) {
            perror("led control fail\n");
            exit(1);
        }
        if (i == 4) {
            i = 0;
            if (flag == 1) {
                flag = 0;
            } else {
                flag = 1;
            }
            //flag = !flag;
            //qDebug("flag is %d", flag);
        }
        //qDebug() << j;
        usleep(100*1000);//100ms
    }
    close(led_fd);
}

void sensor_c::set_alarm_interval_ture() {
    alarm_interval_timer.stop();
    disconnect(&alarm_interval_timer, SIGNAL(timeout()), this, SLOT(set_alarm_interval_ture()));
    alarm_interval_ok = true;
    qDebug() << "!!!!!!!!!!!!!!set the alarm_interval_ok true!!!!!!!!!!!!!!!!";
}

void sensor_c::send_take_alarm_pic() {
    if (global_camera != NULL) {
        global_camera->cam_timer->stop();
        while(global_camera->fetch_flag == true) {
            qDebug() << "wait~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
            usleep(10000);
        }
    }
    emit take_alarm_pic();
}


void sensor_c::camera_snapshot() {
    //printf("i have snapshot the camera\n");

    // qDebug("working mode is %d\n", now_conf_sys->sys_working_mode.working_mode);
    //qDebug() << "working mode is " << now_conf_sys->sys_working_mode.working_mode;
    if ((now_conf_sys->sys_working_mode.working_mode == SINGLE_MODE) || (all_sensor.sensor[EXT_POSITION].has_signal == SENSOR_SIGNAL_Y)) {
        send_alarm_and_take_pic();
    } else if (now_conf_sys->sys_working_mode.working_mode == CARTVU_FULL_MODE){
        send_take_alarm_pic();
        qDebug() << "working in cartvu mode";
    } else {
        send_take_alarm_pic();
        qDebug() << "the config.sys is sending the error mode to cartvu";
    }
}


void sensor_c::s_to_i_deal(u8 *now_position_state) {
    //qDebug("now the working I_number is %d", now_conf_sys->sys_working_mode.I_number);
    if (now_conf_sys->sys_working_mode.I_number == 1) {
        if (all_sensor.sensor[I1_POSITION].state == SENSOR_SIGNAL_Y) {
            *now_position_state = I_STATE;
            alarm_deal();
        }

    } else if (now_conf_sys->sys_working_mode.I_number == 2) {
        if (
                (!all_sensor.sensor[I1_POSITION].state) && (!all_sensor.sensor[I2_POSITION].state)
                ) {
            *now_position_state = I_STATE;
            alarm_deal();
        }
    } else {//3 sensor default
        if (
                (!all_sensor.sensor[I1_POSITION].state) && (!all_sensor.sensor[I2_POSITION].state) && (!all_sensor.sensor[I3_POSITION].state)
                ) {
            *now_position_state = I_STATE;
            alarm_deal();
        }
    }

}


void sensor_c::e1_deal(u8 *now_position_state) {
    //s
    if ((all_sensor.sensor[S_POSITION].has_signal == SENSOR_SIGNAL_Y) || (all_sensor.sensor[EXT_POSITION].has_signal == SENSOR_SIGNAL_Y)) {
        if ((all_sensor.sensor[EXT_POSITION].has_signal == SENSOR_SIGNAL_Y)) {
            recordLog(1, 17, (char*)"\nin extern mode and alarm here\n");
            *now_position_state = E1_STATE;
            qDebug() << "you are in extra sensor mode here";
        } else if (now_conf_sys->sys_working_mode.working_mode == SINGLE_MODE) {
            *now_position_state = E1_STATE;
            recordLog(1, 17, (char*)"\nin single mode and alarm here\n");
            qDebug() << "you are in single mode here!";
        }  else {
            *now_position_state = S_STATE;
        }
        camera_snapshot();//
        qDebug() << "locked the global statis in sensor thread";
        global_statis_lock.lock();
        //qDebug("the upload flag is %d", cartvu_statis.upload_flag);
        cartvu_statis.cart_num++;
        qDebug() << "\n!!!!!!!!cart num is add!!!!!!!!!!!\n";
        //qDebug("the upload flag is %d", cartvu_statis.upload_flag);
        global_statis_lock.unlock();

    }
    if (*now_position_state == S_STATE) {
        s_to_i_deal(now_position_state);
    }
}


void sensor_c::switch_to_E2() {
    E2_timeout.stop();
    //disconnect(&E2_timeout, SIGNAL(timeout()), this, SLOT(switch_to_E2()));
    now_position_state = E2_STATE;
    all_sensor.sensor_position_state = now_position_state;
    emit show_led(&all_sensor);
    qDebug() << "switch to E2_STATE";
}



void sensor_c::send_alarm_and_take_pic()
{
    if (alarm_interval_ok == true) {
        alarm_interval_ok = false;
        qDebug() << "send pic and alarm sound";
        //send save pic signal
        send_take_alarm_pic();
        emit start_alarm();

        connect(&alarm_interval_timer, SIGNAL(timeout()), this, SLOT(set_alarm_interval_ture()));
        alarm_interval_timer.start(now_conf_sys->sys_working_mode.alarm_interval*1000);

        if (now_conf_sys->sys_standby.standby_mode != SERIAL_MODE) {
            emit return_to_serial_mode();
        }


        qDebug() << "in single or extern mode locked the global statis in sensor thread:alarm_deal";
        global_statis_lock.lock();
        //qDebug("the upload flag is %d", cartvu_statis.upload_flag);
        cartvu_statis.alert_num++;
        qDebug() << "\n!!!!!!!!alert num is add!!!!!!!!!!!\n";
        //qDebug("the upload flag is %d", cartvu_statis.upload_flag);
        global_statis_lock.unlock();



    }

}


void sensor_c::alarm_deal() {
    QDateTime tmp;
    QString a;
    a = tmp.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");


    qDebug("I have deal alarm\n");
    //emit start_alarm();

    //if (alarm_interval_ok == true) {
    //  alarm_interval_ok = false;
    //send save pic signal
    emit last_alarm_pic();
    emit start_alarm();


    have_alarm_flag = true;
    qDebug() << "send last_alarm_pic and alarm sound";
    //connect(&alarm_interval_timer, SIGNAL(timeout()), this, SLOT(set_alarm_interval_ture()));
    //alarm_interval_timer.start(now_conf_sys->sys_working_mode.alarm_interval*1000);

    if (now_conf_sys->sys_standby.standby_mode != SERIAL_MODE) {
        emit return_to_serial_mode();
    }
    //}

    qDebug() << "locked the global statis in sensor thread:alarm_deal";
    global_statis_lock.lock();
    //qDebug("the upload flag is %d", cartvu_statis.upload_flag);
    cartvu_statis.alert_num++;

    judge_has_e2_signal.flag = 1;
    strcpy(judge_has_e2_signal.timestamp, a.toLatin1().data());
    qDebug() << "\n!!!!!!!!alert num is add!!!!!!!!!!!\n";
    //qDebug("the upload flag is %d", cartvu_statis.upload_flag);
    global_statis_lock.unlock();


}


void sensor_c::s_deal(u8 *now_position_state) {
    //qDebug("now the working I_number is %d", now_conf_sys->sys_working_mode.I_number);
    if (now_conf_sys->sys_working_mode.I_number == 1) {
        if (all_sensor.sensor[I1_POSITION].has_signal == SENSOR_SIGNAL_Y) {
            *now_position_state = I_STATE;
            alarm_deal();
        } else if (all_sensor.sensor[E2_POSITION].has_signal == SENSOR_SIGNAL_Y) {
            *now_position_state = E2_STATE;
        } else if (all_sensor.sensor[E1_POSITION].has_signal == SENSOR_SIGNAL_Y) {
            *now_position_state = E1_STATE;
        }

    } else if (now_conf_sys->sys_working_mode.I_number == 2) {
        if (
                (all_sensor.sensor[I1_POSITION].has_signal && (!all_sensor.sensor[I2_POSITION].state)) ||
                (all_sensor.sensor[I2_POSITION].has_signal && (!all_sensor.sensor[I1_POSITION].state))
                ) {
            *now_position_state = I_STATE;
            alarm_deal();
        } else if (all_sensor.sensor[E2_POSITION].has_signal == SENSOR_SIGNAL_Y) {
            *now_position_state = E2_STATE;
        } else if (all_sensor.sensor[E1_POSITION].has_signal == SENSOR_SIGNAL_Y) {
            *now_position_state = E1_STATE;
        }

        if (all_sensor.sensor[E2_POSITION].state) {
            *now_position_state = E2_STATE;
            qDebug("int s statue and E2 is hight level");
        }

        /*
        if (all_sensor.sensor[I2_POSITION].has_signal) {
            *now_position_state = E2_STATE;
            qDebug("I3 has signal and stop judge the obstal");
        }
        */

    } else {//3 sensor default
        if (
                (all_sensor.sensor[I1_POSITION].has_signal && (!all_sensor.sensor[I2_POSITION].state) && (!all_sensor.sensor[I3_POSITION].state)) ||
                (all_sensor.sensor[I2_POSITION].has_signal && (!all_sensor.sensor[I1_POSITION].state) && (!all_sensor.sensor[I3_POSITION].state)) ||
                (all_sensor.sensor[I3_POSITION].has_signal && (!all_sensor.sensor[I1_POSITION].state) && (!all_sensor.sensor[I2_POSITION].state))
                ) {
            *now_position_state = I_STATE;
            alarm_deal();
        } else if (all_sensor.sensor[E2_POSITION].has_signal == SENSOR_SIGNAL_Y) {
            *now_position_state = E2_STATE;
        } else if (all_sensor.sensor[E1_POSITION].has_signal == SENSOR_SIGNAL_Y) {
            *now_position_state = E1_STATE;
        }

        if (all_sensor.sensor[E2_POSITION].state) {
            *now_position_state = E2_STATE;
            qDebug("in s status and E2 is hight level");
        }

        /*
        else if (!all_sensor.sensor[E2_POSITION].state) {
            qDebug("the e2 sensor is in low level");
        }*/

        /*
        if (all_sensor.sensor[I3_POSITION].has_signal) {
            *now_position_state = E2_STATE;
            qDebug("I3 has signal and stop judge the obstacle");
        }
        */

    }

}

void sensor_c::i_deal(u8 *now_position_state) {
    if (all_sensor.sensor[E2_POSITION].has_signal == SENSOR_SIGNAL_Y) {
        *now_position_state = E2_STATE;


        if (judge_has_e2_signal.flag == 1) {
            QDateTime tmp;
            QString a;
            char buf[1024];
            a = tmp.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

            judge_has_e2_signal.flag = 0;
            sprintf(buf, "alarm time:%s~~~~~e2 time:%s", judge_has_e2_signal.timestamp, a.toLatin1().data());
            recordLog(1, 17, buf);
            qDebug() << buf;
        }

    }

    if (all_sensor.sensor[E1_POSITION].has_signal == SENSOR_SIGNAL_Y) {
        if (judge_has_e2_signal.flag == 1) {
            QDateTime tmp;
            QString a;
            char buf[1024];
            a = tmp.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

            judge_has_e2_signal.flag = 0;
            sprintf(buf, "alarm time:%s~~~~~e1 time:%s  no E2 time here error!!!", judge_has_e2_signal.timestamp, a.toLatin1().data());
            recordLog(1, 17, buf);
            qDebug() << buf;
        }
    }

}

void sensor_c::e2_deal(u8 *now_position_state) {
    //e1
    if (all_sensor.sensor[E1_POSITION].has_signal == SENSOR_SIGNAL_Y) {

        E2_timeout.start(now_conf_sys->sys_working_mode.E2_time_out*1000);
        //qDebug("4cartvu_statis.upload_flag is %d", cartvu_statis.upload_flag);
        *now_position_state = E1_STATE;

        if (have_alarm_flag == true) {
            have_alarm_flag = false;
            if (global_conf_sys->sys_alarm.image_time == 0) {
                emit  image_time_ok();
            }
        }
    }
}



void sensor_c::show_now_state(u8 now_position_state) {
    switch (now_position_state) {
    case E1_STATE:
        qDebug("=====E1_STATE=======\n");
        break;
    case S_STATE:
        qDebug("=====S_STATE=======\n");
        break;
    case I_STATE:
        qDebug("=====I_STATE=======\n");
        break;
    case E2_STATE:
        qDebug("=====E2_STATE=======\n");
        break;
    default:
        perror("no position state! maybe memory error");
        recordLog(1, 17, (char*)"no position state! maybe memory error!");
        //while(1);
        this->terminate();
    }
    state_show(now_position_state);
}

void sensor_c::position_switch(u8 *now_position_state) {

    if (all_sensor.sensor[E2_POSITION].has_signal == SENSOR_SIGNAL_Y) {
        *now_position_state = E2_STATE;


        if (judge_has_e2_signal.flag == 1) {
            QDateTime tmp;
            QString a;
            char buf[1024];
            a = tmp.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

            judge_has_e2_signal.flag = 0;
            sprintf(buf, "alarm time:%s~~~~~e2 time:%s", judge_has_e2_signal.timestamp, a.toLatin1().data());
            recordLog(1, 17, buf);
            qDebug() << buf;
        }

    }
    /*
    if (all_sensor.sensor[E2_POSITION].state) {
        *now_position_state = E2_STATE;
    }
    */


    //printf("hi %d\n", now_position_state);
    switch (*now_position_state) {
    case E1_STATE:
        e1_deal(now_position_state);
        break;
    case S_STATE:
        s_deal(now_position_state);
        break;
    case I_STATE:
        i_deal(now_position_state);
        break;
    case E2_STATE:
        e2_deal(now_position_state);
        break;
    default:
        perror("no position state\n");
        recordLog(1, 17, (char*)"no position state");
        //while(1);
        this->terminate();
    }
    all_sensor.sensor_position_state = *now_position_state;
    show_now_state(*now_position_state);
}








void sensor_c::i_sensor_error_judge(void) {
    static char last_i_signal = 'X';
    char now_sig = all_sensor.now_signal;
    //int tmp_pos;
    int i = 0;
    bool inside_array = false;


    int diff = 0;
    qDebug("~~~~~~~~~~~~~~~~%s~~~~~~~~~~~~~~~~~~E2:%d sen_pos is %d", all_sensor.sensor[now_sig -1].name, all_sensor.sensor[5].state, sen_pos);
    if (now_sig != last_i_signal) {
        //record as last signal
        last_i_signal = now_sig;

        for(i = 0; i < i_pos; i++) {
            if (now_sig == i_sensor_record[i]) {
                inside_array = true;
                break;
            }
        }

        //the signal is inside the array
        if (inside_array == true) {
            //qDebug() << "inside the array";

            if (i_pos == (2 + 1)) {
                // I1 I2 I3 clear error num
                /*
                all_sensor.sensor[2].error_num = 0;
                all_sensor.sensor[3].error_num = 0;
                all_sensor.sensor[4].error_num = 0;

                all_sensor.sensor[2].error_flag = SENSOR_GOOD;
                all_sensor.sensor[3].error_flag = SENSOR_GOOD;
                all_sensor.sensor[4].error_flag = SENSOR_GOOD;

                status[STATUS_SENSOR_SIZE - 1 - 2] = '0';
                status[STATUS_SENSOR_SIZE - 1 - 3] = '0';
                status[STATUS_SENSOR_SIZE - 1 - 4] = '0';
                */
                qDebug("clear error");
            } else {  //such as 'I1->I2->I1->I2'
                diff = i_sum - i_sensor_record[0] - i_sensor_record[1] - i_sensor_record[2];
                qDebug("now the diff is %d, %d", diff, all_sensor.sensor[diff - 1].error_num);
                if (++all_sensor.sensor[diff - 1].error_num >= all_sensor.sensor[diff - 1].allow_error_num) {
                    all_sensor.sensor[diff - 1].error_flag = SENSOR_ERROR;
                    qDebug("the i sensor error is  %s", all_sensor.sensor[diff - 1].name);
                    status[STATUS_SENSOR_SIZE - 1 - (diff - 1)] = '1';
                } else {
                    //all_sensor.sensor[diff - 1].error_flag = SENSOR_GOOD;
                    //status[STATUS_SENSOR_SIZE - 1 - (diff - 1)] = '0';
                }
            }
            bzero(i_sensor_record, I_SENSOR_NUM);
            i_pos = 0;
        } else { // the signal is not inside the array
            //qDebug() << "the signal is not inside the array";
        }
        if (i_pos >= I_SENSOR_NUM) {
            qDebug() << "unexpect  i signal obtain!";
            qDebug("error sig is %d", now_sig);
            i_pos = 0;
            //sleep(3);
        } else {
            i_sensor_record[i_pos] = now_sig;
            i_pos++;
        }
    } else {
        //qDebug() << "the same I  signal equal the last one and do nothing!";
    }


    qDebug("I:%d %d %d", i_sensor_record[0], i_sensor_record[1], i_sensor_record[2] );

}

void sensor_c::other_sensor_error_judge(void) {
    static char last_sen_signal = 'X';
    char now_sig = all_sensor.now_signal;
    int i = 0;
    bool inside_array = false;


    int diff = 0;
    qDebug("~~~~~~~~~~~~~~~~%s~~~~~~~~~~~~~~~~~~E1:%d  S:%d  E2:%d is %d", all_sensor.sensor[now_sig -1].name,
           all_sensor.sensor[0].state, all_sensor.sensor[1].state, all_sensor.sensor[5].state, sen_pos);
    //E1->S->I->E2    ->  E1->S->I->    S
    if (now_sig != last_sen_signal) {
        //record as last signal
        last_sen_signal = now_sig;

        for(i = 0; i < sen_pos; i++) {
            if (now_sig == all_sensor_record[i]) {
                inside_array = true;
                break;
            }
        }
        //if (sen_pos == 3)
        //the signal is inside the array
        if (inside_array == true) {
            qDebug() << "inside the array";

            if (sen_pos == OTHER_SENSOR) {
                // E1 S E2 clear error num
                /*
                all_sensor.sensor[0].error_num = 0;
                all_sensor.sensor[1].error_num = 0;
                all_sensor.sensor[5].error_num = 0;

                all_sensor.sensor[0].error_flag = SENSOR_GOOD;
                all_sensor.sensor[1].error_flag = SENSOR_GOOD;
                all_sensor.sensor[5].error_flag = SENSOR_GOOD;

                status[STATUS_SENSOR_SIZE - 1 - 0] = '0';
                status[STATUS_SENSOR_SIZE - 1 - 1] = '0';
                status[STATUS_SENSOR_SIZE - 1 - 5] = '0';
                */
                qDebug("clear other sensor error");
            } else if (sen_pos == (OTHER_SENSOR - 1)){  //such as 'E1 ->S->I->E1'
                diff = sen_sum;
                for(i = 0; i < OTHER_SENSOR; i++) {
                    diff -= all_sensor_record[i];
                }
                //diff = sen_sum - all_sensor_record[0] - all_sensor_record[1] - all_sensor_record[2] - all_sensor_record[3];

                if (diff != I_CHAR) {// I sensor is not included
                    qDebug("now sen diff is %d, %d", diff, all_sensor.sensor[diff - 1].error_num);
                    if (++all_sensor.sensor[diff - 1].error_num >= all_sensor.sensor[diff - 1].allow_error_num) {
                        all_sensor.sensor[diff - 1].error_flag = SENSOR_ERROR;
                        qDebug("the other error is  %s", all_sensor.sensor[diff - 1].name);
                        status[STATUS_SENSOR_SIZE - 1 - (diff - 1)] = '1';
                    } else {
                        //all_sensor.sensor[diff - 1].error_flag = SENSOR_GOOD;
                        //status[STATUS_SENSOR_SIZE - 1 - (diff - 1)] = '0';
                    }
                } else {
                    qDebug() << "!!!!!!!!!!!!!!!!!!!!!all i sensor is error please check!!!!!!!!!!!!!!!!";
                }


            }
            bzero(all_sensor_record, OTHER_SENSOR);
            sen_pos = 0;
        } else { // the signal is not inside the array
            qDebug() << "the signal is not inside the array";
        }
        if (sen_pos >= OTHER_SENSOR) {
            qDebug() << "unexpect other signal obtain!";
            //sleep(3);
            sen_pos = 0;
        } else {
            all_sensor_record[sen_pos] = now_sig;
            sen_pos++;
        }
    } else {
        // qDebug() << "the same signal equal the last one and do nothing!";
    }
    if (OTHER_SENSOR == 4) {
        qDebug("other:%d %d %d %d", all_sensor_record[0], all_sensor_record[1], all_sensor_record[2], all_sensor_record[3]);
    } else if (OTHER_SENSOR == 3) {
        qDebug("other:%d %d %d", all_sensor_record[0], all_sensor_record[1], all_sensor_record[2]);
    }

}



void sensor_c::accumulate_judge(void)
{
    int i = 0;
    int j = 0;
    bool sensor_good = false;
    static char last_signal = 'X';
    bool error_flag = false;

    if (last_signal != all_sensor.now_signal) {
        last_signal = sensor_judge[judge_pos++] = all_sensor.now_signal;
        if (judge_pos >= JUDGE_SIZE) {

            judge_pos = 0;
            for(i = 0; i < SENSOR_NUM; i++) {
                sensor_good = false;
                for(j = 0; j < JUDGE_SIZE; j++) {
                    if (all_sensor.sensor[i].signal_style == sensor_judge[j]) {
                        sensor_good = true;
                        break;
                    }
                }
                if (sensor_good == false) {
                    printf("now the error sensor is %s\n", all_sensor.sensor[i].name);
                    status[STATUS_SENSOR_SIZE - 1 - i] = '1';
                    error_flag = true;
                } else {
                    //status[STATUS_SENSOR_SIZE - 1 - i] = '0';
                }
            }
            if ((i == SENSOR_NUM) && (error_flag == false)) {
                printf("\n=====all the sensor is good\n======");
            }
            printf("================the record char is ======================\n");
            for(j = 0; j < JUDGE_SIZE; j++) {
                printf("%d\t", sensor_judge[j]);
            }
            printf("\n================the record char is ======================\n");
        }
    }
}



void sensor_c::sensor_error_judge() {

#if USE_ACCU_I
    accumulate_judge();
#endif
    if (all_sensor.now_signal == I1_CHAR
        || all_sensor.now_signal == I2_CHAR
        || all_sensor.now_signal == I3_CHAR
        ) {
        i_sensor_error_judge();
#if USE_ACCU_I
        all_sensor.now_signal = I_CHAR;
#endif
    }

    if (all_sensor.now_signal == E1_CHAR
        || all_sensor.now_signal == S_CHAR
        || all_sensor.now_signal == I_CHAR
        || all_sensor.now_signal == E2_CHAR
        ) {
        other_sensor_error_judge();
    }



}

void sensor_c::state_show(u8 now_position_state) {
    int ret = -1;
    int led_fd = -1;
    int i = 0;
    led_fd = open_led();
    for (i = 0; i < 4; i++)
        ioctl(led_fd, 0, i);
    switch (now_position_state) {
    case E1_STATE:
        ret = ioctl(led_fd, 1, 3);
        break;
    case S_STATE:
        ret = ioctl(led_fd, 1, 2);
        break;
    case I_STATE:
        ret = ioctl(led_fd, 1, 1);
        break;
    case E2_STATE:
        ret = ioctl(led_fd, 1, 0);
        break;
    default:
        printf("no position state\n");
        recordLog(1, 35, (char*)"no position state");
        exit(1);
    }


    // printf("now_position_state is %d\n", now_position_state);
    // sleep(1);
    if(ret < 0) {
        perror("led control fail\n");
        recordLog(1, 35, (char*)"led control fail");
        exit(1);
    }

    close(led_fd);
}
void sensor_c::sensor_adjust_state() {
    //    int ret = -1;
    //    u8 key_state;
    //    int button_fd = -1;
    //
    //    button_fd = open_button_noblock();
    //
    //    ret = read(button_fd, &key_state, sizeof(key_state));
    //    if (ret < 0) {
    //        perror("read buttons fail");
    //        exit(1);
    //    }
    //    sensor_set_pin(key_state);
    //    close(button_fd);
}


void sensor_c::sensor_mutex_init(pthread_mutex_t *mutex) {
    int ret = -1;
    ret = pthread_mutex_init(mutex, NULL);
    if (ret != 0) {
        perror("pthread_mutex_init fail");
        exit(1);
    }

}

void sensor_c::sensor_mutex_lock(pthread_mutex_t *mutex) {
    int ret = -1;
    ret = pthread_mutex_lock(mutex);
    if (ret != 0) {
        perror("pthread_mutex_lock fail");
        exit(1);
    }

}

void sensor_c::sensor_mutex_unlock(pthread_mutex_t *mutex) {
    int ret = -1;
    ret = pthread_mutex_unlock(mutex);
    if (ret != 0) {
        perror("pthread_mutex_unlock fail");
        exit(1);
    }

}
