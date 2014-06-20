#ifndef CAMTHREAD_H
#define CAMTHREAD_H
#include <QThread>
#include <QProcess>
#include <QTimer>




#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <linux/types.h>
#include <linux/fb.h>
#include <linux/videodev2.h>
#include <sys/poll.h>
#include <signal.h>
#include <sys/shm.h>
#include <QMutex>
#include <QDateTime>
#include <errno.h>




#include "config_sys.h"
#include   "jpeglib.h"
#include "videodev2_samsung.h"

#define FILE_SIZE    100
#define BUF_SIZE            400

//#define SHARE_APP    "/setting_qt"


#define SAVE_VIDEO_DIR  "/cartvu/alarm_images/"
#define SAVE_VIDEO_PIC  "/video_pic.jpg"




#define CAMERA_DEV_NAME         "/dev/video0"      // device name of camera
#define FRAMEBUFFER_DEV_NAME0   "/dev/fb0"         // device name of frame buffer
#define FRAMEBUFFER_DEV_NAME1   "/dev/fb1"         // device name of frame buffer
#define CAPTURE_BUFFER_NUMBER   4                  // the number of capture buffer



#define CAMERA_DEV__OLD_NAME         "/dev/video14"      // device name of camera
#define OFFSET_CAMERA_HEIGHT             2

#if 0

#define CAMERA_WIDTH            640
#define CAMERA_HEIGHT           480
#else

#if 0

#define CAMERA_WIDTH            784
#define CAMERA_HEIGHT           580
#else
#define CAMERA_WIDTH            720
#define CAMERA_HEIGHT           586
#endif


#endif


#define CAM_LINELEN  4
#define CAMERA_BPP              32
#define CAMERA_FRAMEPIXEL       CAMERA_WIDTH * CAMERA_HEIGHT
#define CAMERA_LINELEN          CAMERA_WIDTH * CAMERA_BPP / 8
#define CAMERA_SIZE             CAMERA_LINELEN * CAMERA_HEIGHT
#define CAMERA_YUVLEN           CAMERA_FRAMEPIXEL + CAMERA_FRAMEPIXEL / 2


// skip the top pix or left pix
#define TOP_SKIP                  0   // 24
#define LEFT_SKIP                 0   // 2

#define PAL_TYPE   0
#define NTSC_TYPE  1


//pal type
// skip every extra line
#define EXTRA_LINE_PAL                1000   //15


//ntsc  type
// skip every extra line
#define EXTRA_LINE_NTSC                1000  //4



//#define QUALITY_PER         30
//#define QUALITY_PER         60
#define QUALITY_PER         80



#define SHOW_VIDEO_DELAY    200




extern void func(int signo);




class camThread : public QThread
{

Q_OBJECT

public:
    camThread(unsigned char*);
    ~camThread();
    void run();

    int openCamera();
    int getCapability();
    int selectInput();
    int setFormat();
    int requestCameraBuffer();

    int initCameraBuffer();
    //int openFramebuffer();
    int startStream();
    //yuv装换为rgb
    void decodeYUV420SP(unsigned int* rgbBuf, unsigned char* yuv420sp);
    //从摄像头获取图像
    int fetchPicture();
    //停止摄像头
    int stopStream();
    //注册信号
    void signal_init();
    void qt_shmget();
    //保存摄像头图片
    int savePic(const char *filename);
    //将rgb保存为jpeg格式
    int write_jpeg(const char *filename,unsigned char *buf,int quality,int width, int height, int gray);

    bool judge_driver(const char *path);
signals:
        //发送在界面显示摄像头图片
    void play(void);
private slots:
    //保存摄像头图片
    void take_pic(void);
    //启动定时器让qt显示摄像头图像
    void emit_pic(void);
    // 当告警产生时，将以前保存的buffer恢复到界面来显示
    void show_last_pic();
public:
    unsigned char *fbAddr0, *fbAddr1;
    bool lock_flag;
    bool take_pic_flag;
    QMutex mutex_video;
    QMutex fetch_video;
    QTimer *cam_timer;
    int now_image_quality;

    bool old_driver_flag;
    int height_offset;

    bool fetch_flag;
private:
    QProcess *process;


    int camFd;                                         // camera file handler
    int fbFd0, fbFd1;                                  // frame buffer file handler
    int inputDevice;                                   // index of input device
    struct pollfd  m_events_c;                         // use for poll()
    unsigned fbBPP0, fbBpp1;                           // color depth of framebuffer
                    // buffer address of framebuffer
    int fbWidth0, fbHeight0, fbLineLen0, fbSize0;      // width, height, line length, size per frame of frame buffer
    int fbWidth1, fbHeight1, fbLineLen1, fbSize1;      // width, height, line length, size per frame of frame buffer
    unsigned int fbIndex;

    unsigned camBPP;                                   // color depth of camera
    int camWidth, camHeight, camLineLen, camSize;      // width, height, line length, size per frame of frame buffer
    unsigned char camAddr[CAMERA_SIZE];                // buffer address of camera
    struct v4l2_buffer c;

    unsigned char *shm_buffer;
    struct {
      void * data;
      int len;
    } captureBuffer[CAPTURE_BUFFER_NUMBER];
};



#endif // CAMTHREAD_H
