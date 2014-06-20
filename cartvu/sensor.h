#ifndef SENSOR_H
#define SENSOR_H

#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QMutex>








#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <strings.h>
#include <sys/ioctl.h>

//#include "camThread.h"
#include "config_sys.h"
#include "login.h"

#define BUTTON_DEVICE  "/dev/buttons"
#define LED_DEVICE  "/dev/leds"


//#define DEBUG			//



#define BUTTON_NO_BLOCK        0
#if  BUTTON_NO_BLOCK
#define  BUTTON_FLAG     O_RDWR | O_NONBLOCK
#else
#define  BUTTON_FLAG     O_RDWR
#endif






//#define I_SENSOR_2            //i,







#define I_SENSOR_NUM			3				//the number of I  sensor
#define EXT_SENDOR_NUM                  1
#define SENSOR_NUM              I_SENSOR_NUM+3

#define ALL_SENSOR_NUM          SENSOR_NUM+EXT_SENDOR_NUM

#define E2_TIMEOUT				10				//timeout    unit:minute

#define E1_STATE				0
#define S_STATE					1
#define I_STATE					2
#define E2_STATE				3

//gpio  0~7         8  9
//对应的sensor的gpio的管脚位置
#define EXT_PIN					0

#define E1_PIN					5
#define S_PIN					4

#define I1_PIN					1
#define I2_PIN					2
#define I3_PIN					3

#define E2_PIN					6


#define RESET_PIN               8

//当sensor的错误数多与以下值时，更改status上传给localserver
#define E1_ERROR_MAX            3*3
#define S_ERROR_MAX             3*3
#define I1_ERROR_MAX            4*3
#define I2_ERROR_MAX            4*3
#define I3_ERROR_MAX            4*3
#define E2_ERROR_MAX            3*3

#define EXT_ERROR_MAX            3*3


#define  MAX_NAME               20


//#define ETH0_SETTING   "/etc/eth0-setting"




#define E1_CHAR       1 //'B'  //begin
#define  S_CHAR       2 //'P'  //photograph
#define E2_CHAR       6 //'E'  // end

#define EXT_CHAR       0 //  // end


#define I1_CHAR       3 //'F'  //front
#define I2_CHAR       4 //'M'  //middle
#define I3_CHAR       5 //'L'  //last

#define I_CHAR       I1_CHAR + I2_CHAR + I3_CHAR //12

//保存18个sensor后来判断是否有传感器坏了
#define JUDGE_SIZE     18

typedef  unsigned char    u8;
typedef  unsigned int    u32;


//{"E1_SENSOR", E1_PIN, 0, 0, 0, E1_ERROR_MAX},
struct sensor_att {
    char name[MAX_NAME];//传感器名
    u8  pin;//哪一个引脚
    u8 state;//当前引脚高低电平状态
    u8 has_signal;//是否触发了此引脚
    u8 error_num;//当前sensor的错误次数
    u8 allow_error_num;//允许的错误次数
    char signal_style;//信号的字符类型，为判错准备
    char error_flag;//当前sensor错误的状态
};

typedef struct key_info {
    unsigned int key_state;//读取驱动的引脚状态
    unsigned int signal_key_state;//哪一个引脚有信号
}key_type;



struct sensor_all_att {
    struct sensor_att sensor[ALL_SENSOR_NUM];
    unsigned char sensor_position_state;
    char   now_signal;
};


#define E1_POSITION             0
#define S_POSITION              1
#define I1_POSITION             2
#define I2_POSITION             3
#define I3_POSITION             4
#define E2_POSITION             5

#define EXT_POSITION            6

#define SENSOR_SIGNAL_Y         1
#define SENSOR_SIGNAL_N         0



#define SENSOR_GOOD             0
#define SENSOR_ERROR            1






class sensor_c : public QThread
{
    Q_OBJECT
public:
    sensor_c();
    ~sensor_c();
    //sensro传感器线程
    void run();


    void sensor_mutex_init(pthread_mutex_t *);
    void sensor_mutex_lock(pthread_mutex_t *);
    void sensor_mutex_unlock(pthread_mutex_t *);

//传感器拍照
    void camera_snapshot();
//E1 S I E2等状态切换
    void sensor_adjust_state();
    int open_button(void);
    //将从驱动中读取的信息写进结构体
    void sensor_set_pin(key_type);
    //显示传感器的状态
    void show_sensor_state();
    int button_test();
    void sensor_printf(int);
    int open_led();
    //led显示
    void led_show();
    //收到信号时的处理
    void e1_deal(u8 *);
    void s_deal(u8 *);
    void i_deal(u8 *);
    void e2_deal(u8 *);
    void s_to_i_deal(u8 *now_position_state);
    //状态切换
    void position_switch(u8 *);
    //传感器错误判断  三种类型  总的判断，  I的判断  , E1 S I E2的判断
    void sensor_error_judge();
    
    void state_show(u8);
    //判断是否按下了恢复出厂设置的按钮
    int judge_reboot(key_type , int );
    int open_button_noblock(void);
    //告警处理
    void alarm_deal();
    void show_now_state(u8 );
    void fisrt_read_button();
    //I传感器错误判断
    void i_sensor_error_judge(void);
    //除了I传感器外的其他判断
    void other_sensor_error_judge(void);
    //所有的传感器一起判断
    void accumulate_judge();
    //告警并且显示图片
    void send_alarm_and_take_pic();

    void send_take_alarm_pic();
public:
    u8 now_position_state;
    int now_key_state;
    //camThread *camera;
    global_config *now_conf_sys;

    QTimer  E2_timeout;
    QTimer alarm_interval_timer;
    bool alarm_interval_ok;
    bool have_alarm_flag;
    //struct sensor_att sensor[SENSOR_NUM];
private:

private slots:
    void switch_to_E2();
    void set_alarm_interval_ture();

signals:
    void show_led(struct sensor_all_att *sensor);
    //发送告警信号
    void take_alarm_pic(void);
    //发送告警及恢复上一次拍照图片
    void last_alarm_pic();
    void start_alarm(void);
    //发送由待机模式转换到非待机模式的信号
    void return_to_serial_mode(void);
    //imagetime 超时时的信号
    void image_time_ok(void);

};

#endif // SENSOR_H
