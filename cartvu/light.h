#ifndef LIGHT_H
#define LIGHT_H

#include <QObject>
#include <QDebug>

#include <stdio.h>
#include <linux/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <errno.h>


//lcd �ı����豸·��
#define PWM_BACK_LIGHT   "/dev/pwm_back_light"
#define PWM_IOCTL_SET_FREQ 1
#define PWM_IOCTL_STOP    0

//�������������豸·��
#define LIGHT_PATH   "/dev/i2c-1"

#define I2C_SLAVE	0x0703	/* Use this slave address */
#define I2C_SLAVE_FORCE	0x0706	/* Use this slave address, even if it*/

#define I2C_RETRIES     0x0701
#define I2C_TIMEOUT     0x0702
#define I2C_RDWR             0x0707



//#define LIGHT_ADDR  0x5d   //
//������������ַ
#define LIGHT_ADDR  0x48   //

#define MAX_START   3

#define I2C_M_TEN 0x0010
#define I2C_M_RD 0x0001

//#define LIGHT_SIZE   3


struct i2c_msg_light
{
    unsigned short addr;
    unsigned short flags;

    unsigned short len;
    unsigned char *buf;
};

struct i2c_rdwr_ioctl_data
{
    struct i2c_msg_light *msgs;
    int nmsgs;
    /* nmsgs1*/
};



class light : public QObject
{
Q_OBJECT
public:
    explicit light(int light_strong, QObject *parent = 0);
    //��ȡ������ֵ
    int data_start(void);
    //i2c��ȡ����ֵ
    int light_get_light(struct i2c_rdwr_ioctl_data *light_data_tmp, int light_fd);
    
    void stop();
    //���������ǿ��
    void adjust_back_light(unsigned int duty);
    //���ö�ȡ�������ļ��ı���ǿ��
    void global_set_bak_light(int ligh_str);
public:
    int light_fd;
    struct i2c_rdwr_ioctl_data light_data;

    //char light_buf[LIGHT_SIZE];
    int global_light_strong;

    bool closing_light_flag;
signals:

public slots:
    //��ʱ��ȡ����ֵ��������
    void light_adjust();

};

#endif // LIGHT_H
