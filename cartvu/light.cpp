#include "light.h"



/*********struct i2c_rdwr_ioctl_datastruct
 *  * i2c_msg_light*******/





extern  void recordLog(int type, int code, char *info);






light::light(int light_strong,QObject *parent) :
        QObject(parent)
{
    closing_light_flag = false;



    int ret = -1;


    light_fd = open(LIGHT_PATH, O_RDWR);
    if (light_fd < 0) {
        perror("open light fail");
        recordLog(6, 17, (char*)"open light fail");
        return;
    }

    light_data.nmsgs = 2;


    light_data.msgs = (struct i2c_msg_light*)malloc(light_data.nmsgs*sizeof(struct i2c_msg_light));
    if(!light_data.msgs)
    {
        perror("malloc error");
        recordLog(6, 8, (char*)"malloc error");
        //exit(1);
    }

    ret = ioctl(light_fd, I2C_TIMEOUT,1);/**/
    if(ret < 0)
    {
        perror("set timeout error");
        recordLog(6, 35, (char*)"set timeout error");
    }

    ret = ioctl(light_fd, I2C_RETRIES,2);/**/
    if(ret < 0)
    {
        perror("set retries error");
        recordLog(6, 35, (char*)"set retries error");
    }



    global_set_bak_light(light_strong);

}


int light::data_start()
{
    int light_size;
    //qDebug() << "adjust the light and back light";
    light_size = light_get_light(&light_data, light_fd);
    return light_size;
}

int light::light_get_light(struct i2c_rdwr_ioctl_data *light_data_tmp, int light_fd)
{
    int t;

    int high;
    int low;
    int ret;
    char buf1_temp[2] = {0};
    char buf2_temp[4] = {0};
    static int error_count = 0;


    //qDebug("read start is ???");

    light_data_tmp->nmsgs = 2;
    (light_data_tmp->msgs[0]).len = 1;                                 //e2prom
    (light_data_tmp->msgs[0]).addr = LIGHT_ADDR;                         //e2prom
    (light_data_tmp->msgs[0]).flags = 0;                            //write
    (light_data_tmp->msgs[0]).buf = (unsigned char*)buf1_temp;
    (light_data_tmp->msgs[0]).buf[0] = 0x01;                        //e2prom


    (light_data_tmp->msgs[1]).len = 3;                                //
    (light_data_tmp->msgs[1]).addr = LIGHT_ADDR;                        // e2prom
    (light_data_tmp->msgs[1]).flags = I2C_M_RD;                //read
    (light_data_tmp->msgs[1]).buf = (unsigned char*)buf2_temp;//
    (light_data_tmp->msgs[1]).buf[0] = 0;                //
    (light_data_tmp->msgs[1]).buf[1] = 0;                //
    (light_data_tmp->msgs[1]).buf[2] = 0;                //

    ret = ioctl(light_fd, I2C_RDWR, (unsigned long)light_data_tmp);
    if (ret < 0)
    {
        error_count++;
        perror("ioctl error2 in get light fun");
        if (error_count == 1) {
            recordLog(6, 35, (char*)"ioctl error2 in get light fun");
        }
        if (error_count >= 10000) {
            error_count = 0;
        }
        return -1;
    }

    high = (light_data_tmp->msgs[1]).buf[1];
    low = (light_data_tmp->msgs[1]).buf[2];
    t = (high << 1) | (low >> 7);

    //printf("buf0   %x       %d \n", (light_data.msgs[1]).buf[0], (light_data.msgs[1]).buf[0]);
    //printf("buf1   %x\n", (light_data.msgs[1]).buf[1]);
    //printf("buf2   %x\n", (light_data.msgs[1]).buf[2]);

    //qDebug("result is %d\n",t);
    //  t =(light_data.msgs[1]).buf[0];
    //   t <<=8;
    //  t +=(light_data.msgs[1]).buf[1];
    // t >>=5;
    return t;
}


void light::stop()
{
    qDebug() << "stop the light and back light";
    close(light_fd);
}


void light::global_set_bak_light(int ligh_str)
{


    //global_light_strong = global_conf_sys->sys_global.brightness;
    global_light_strong = ligh_str;
    if (global_light_strong < 0) {
        global_light_strong = 0;
    } else if (global_light_strong > 9) {
        global_light_strong = 9;
    }
    qDebug() << "the light strong is " << global_light_strong;
    global_light_strong = global_light_strong*100000;
    adjust_back_light(global_light_strong);

}


void light::adjust_back_light(unsigned int duty)
{
    int fd = -1;
    int ret = -1;
    unsigned int fre;

    fd = open(PWM_BACK_LIGHT, O_RDWR);
    if(fd < 0) {
        perror("open back light fail:/dev/pwm_back_light");
        recordLog(6, 17, (char*)"open back light fail:/dev/pwm_back_light");
        return;
        //exit(1);
    }

    fre = duty;
    if (fre == 0) {
        ret = ioctl(fd, PWM_IOCTL_STOP, fre);
    } else {
        ret = ioctl(fd, PWM_IOCTL_SET_FREQ, fre);
    }

    if(ret < 0) {
        perror("ioctl fail:in set the fre fail");
        recordLog(6, 35, (char*)"ioctl fail:in set the fre fail");
        //exit(1);
    }
    close(fd);
}

void light::light_adjust()
{
    int light_strong;
    int back_light_strong;
    //qDebug() << "~~~light read test~~~";
    if (closing_light_flag == false) {

        light_strong = data_start();
        if (light_strong < 0) {
            printf("ioctl fail~~~~\n");
            return;
        }
        //qDebug() << light_strong;
        //back_light_strong = 1000000 - ((light_strong - 111)/4)*10000;//x:(510-111)=y:100wan
        //system("echo 'hello'");

        if (light_strong > 471) {
            light_strong = 471;
        }
#if 0
        if (light_strong < 111) {
            light_strong = 111;
        }
        back_light_strong = 1000000 - (light_strong - 111)*2500;//110wan - (x-111/40 + 1 )*10wan
#else
        if (light_strong < 181) {
            light_strong = 181;
        }
        back_light_strong =((light_strong - 181)/32 + 1) * 100000;
        //back_light_strong = 1100000 - ((light_strong - 181)/32 + 1) * 100000;
#endif
        if (back_light_strong > global_light_strong) {
            back_light_strong = global_light_strong;
        }



        adjust_back_light(back_light_strong);
    } else {
        //adjust_back_light(100000);
        adjust_back_light(0);
    }

}



