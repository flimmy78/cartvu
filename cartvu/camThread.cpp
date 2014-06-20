#include <QDebug>
#include "camThread.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "sensor.h"

extern int global_camfd;
//extern global_config *global_conf_sys;
extern QString global_lane_no;

extern global_config *global_conf_sys;

int global_extra_line;
extern void funk(int signo);
unsigned char *shm_save_buff;


char global_image_filename[FILE_SIZE] = {0};

extern void recordLog(int type, int code, char *info);


extern struct sensor_all_att all_sensor;

camThread::camThread(unsigned char* buf)
{
    shm_save_buff = (unsigned char *)malloc(CAMERA_WIDTH * CAMERA_HEIGHT * CAM_LINELEN);   // allocate memory for camera
    if (!shm_save_buff) {
        recordLog(9, 8, (char*)"malloc shm_save_buff fail");
        perror("shm_save_buff fail");
        //exit(1);
    }

    qDebug("camThread is construct ok\n");
    shm_buffer = buf;
    lock_flag = true;
    take_pic_flag = false;
    cam_timer = new QTimer();
    now_image_quality = IMAGE_QUALITY_H_PER;
    //default camera type;
    global_extra_line = EXTRA_LINE_NTSC;

    old_driver_flag = judge_driver(CAMERA_DEV__OLD_NAME);
}

bool camThread::judge_driver(const char *path)
{
    int fd;
    fd = open(path, O_RDWR);
    if (fd > 0) {
        close(fd);
        printf("old camera driver here\n");
        height_offset = OFFSET_CAMERA_HEIGHT;

        return true;
    } else {
        printf("new camera driver here\n");
        height_offset = 0;
        return false;
    }
}


void camThread::signal_init()
{
    signal(SIGHUP,func);
    signal(SIGINT,func);
    signal(SIGQUIT,func);
    signal(SIGILL,func);
    signal(SIGABRT,func);
    signal(SIGFPE,func);
    signal(SIGKILL,func);
    signal(SIGSEGV,funk);
    qDebug() << "register signal in camera thread";

    signal(SIGPIPE,func);
    //signal(SIGALRM,func);
    signal(SIGTERM,func);
#if 0
    signal(SIGUSER1,func);
    signal(SIGUSER2,func);
#endif
    //signal(SIGCHLD,func);
    signal(SIGCONT,func);
    signal(SIGSTOP,func);
    signal(SIGTSTP,func);
    signal(SIGTTIN,func);
    signal(SIGTTOU,func);


}


void camThread::qt_shmget()
{
    //    int shm_id = 0;
    //    shm_id = shmget (ftok(SHARE_APP, 'b'), CAMERA_WIDTH*CAMERA_HEIGHT*CAMERA_LINELEN, 0666 | IPC_CREAT);
    //
    //    if (shm_id < 0) {
    //        perror("shmget fail");
    //        exit(1);
    //    }
    //    shm_buffer = (unsigned char *)shmat (shm_id, (void *) 0, 0);
    //    if (!shm_buffer) {
    //        perror("shmat shm_buffer fail");
    //        exit(1);
    //    }

    //shm_buffer = new unsigned char(CAMERA_WIDTH*CAMERA_HEIGHT*CAM_LINELEN);

    //    shm_buffer = (unsigned char *)malloc(CAMERA_WIDTH*CAMERA_HEIGHT*CAM_LINELEN);
    //    if (!shm_buffer) {
    //        perror("shmat shm_buffer fail");
    //        exit(1);
    //    }
    //  global_buffer = shm_buffer;


}


void camThread::run()
{
    if (global_conf_sys->sys_working_mode.camera_type == PAL_TYPE) {
        global_extra_line = EXTRA_LINE_PAL;
    } else {
        global_extra_line = EXTRA_LINE_NTSC;
    }

    //process = new QProcess();
    //process->execute("/etc/sound_start.sh");
    //system("/etc/sound_start.sh");
    // while(1) {
    qDebug("you are in camThread()\n");

    //sleep(3);
    // }

    clock_t t;
    signal_init();

    fbIndex = 0;

    //qt_shmget();

    // ****1st step: open cameradevice
    if (openCamera() != 0) {
        recordLog(9, 17, (char*)"openCamera fail");
        qDebug("1. Openning camera device failed!\n");
        //system("/bin/ps");
        //system("/bin/ps  > /record");
        return;
    }  // end of if
    qDebug("1. Openning camera device OK!\n");

    // ****2nd step: check capability
    if (getCapability() != 0) {
        recordLog(9, 17, (char*)"Getting capability failed");
        qDebug("2. Getting capability failed or some capabilities is wrong!\n");
        return;
    }  // end of if
    qDebug("2. Getting capability OK!\n");

    // ****3rd step: check and select input device
    if ((inputDevice = selectInput()) == -1) {
        recordLog(9, 17, (char*)"Selecting input device failed");
        qDebug("3. Selecting input device failed!\n");
        return;
    }  // end of if
    qDebug("3. Selecting input device OK! Index of input is %d.\n", inputDevice);

    // ****4th step: set camera format
    if (setFormat() == -1) {
        recordLog(9, 17, (char*)"Setting camera format failed");
        qDebug("4. Setting camera format failed!\n");
        return;
    }  // end of if
    qDebug("4. Setting camera format OK!\n");

    // ****5th step: request the camera buffer
    if (requestCameraBuffer() == -1) {
        recordLog(9, 17, (char*)"Requesting Camera buffer failed!");
        qDebug("5. Requesting Camera buffer failed!\n");
        return;
    }  // end of if
    qDebug("5. Requesting camera buffer OK!\n");

    // ****6th step: initial the camera buffer
    if (initCameraBuffer() == -1) {
        recordLog(9, 17, (char*)"Initial camera buffer failed");
        qDebug("6. Initial camera buffer failed!\n");
        return;
    }  // end of if
    qDebug("6. Initial camera buffer OK!\n");



    //return 0;
    // ****9th step: Start stream
    if (startStream() != 0) {
        recordLog(9, 17, (char*)"Starting video stream failed");
        qDebug("9. Starting video stream failed!\n");
        return;
    }  // end of if
    qDebug("9. Starting video stream OK!\n");

    // ****10th step: setting params for poll()
    memset(&m_events_c, 0, sizeof(m_events_c));    // clear
    m_events_c.fd = camFd;                         // sockets wait for events in poll()
    m_events_c.events = POLLIN | POLLERR;          // events wait in poll(). READ and ERROR.others are POLLOUT POLLRDNORM POLLWRNORM
    qDebug("10. Setting params of poll() OK!\n");


    t = clock();
    //while ((poll(&m_events_c, 1, 1000) > 0) && ((clock() - t) < (CLOCKS_PER_SEC * 30))) {
    //while (poll(&m_events_c, 1, 1000) > 0) {
    connect(cam_timer, SIGNAL(timeout()), this, SLOT(emit_pic()));
    //cam_timer->start(SHOW_VIDEO_DELAY);
    //mutex_video.lock();
    //fetch_video.lock();
    fetch_flag = false;
    while (1) {
        // ***11th step: Fetch a capture picture
        if (lock_flag == false) {

            //qDebug() << "fetch lock";
            fetch_video.lock();
            fetch_flag = true;
            fetchPicture();
            //qDebug() << "unlock fetch";
            emit play();
            fetch_flag = false;
            //msleep(200);
        } else if (lock_flag == true){
            qDebug() << "you lock here!";
            mutex_video.lock();
            qDebug() << "you unlock!";
        }
    } // end of while

}

void camThread::emit_pic(void)
{


    fetch_video.unlock();
    //qDebug() << "unlock and emit!!!!!!!!!!!";
    
    //cam_timer->start(SHOW_VIDEO_DELAY);
    
    //emit play();
}



void camThread::take_pic(void)
{
    QString a;
    QDateTime tmp;
    char buf[BUF_SIZE] = {0};
    a = tmp.currentDateTime().toString("yyyyMMddhhmmss");
    //a = "" + global_lane_no + "-" + a;
    qDebug() << "now the take pic dir is ";

    snprintf(buf, BUF_SIZE, "%sI-%02d-%s.jpg", SAVE_VIDEO_DIR, global_lane_no.toInt(), a.toLatin1().data());
    qDebug() << buf;

    bzero(global_image_filename, FILE_SIZE);
    strncpy(global_image_filename, buf, FILE_SIZE);

    cam_timer->stop();
    take_pic_flag = true;
    qDebug() << "save!!!!!!!!!!!" ;
    //lock_flag = true;
    unlink(buf);
    //qDebug() << tmp.currentDateTime().toString("yyyyMMddhhmmss");
    //while(fetch_flag == true) {
    //    qDebug() << "wait here~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
   // }
    //qDebug() << tmp.currentDateTime().toString("yyyyMMddhhmmss");
    savePic(buf);
    qDebug() << "save ok!!!!!!!!!!!" ;

    //cam_timer->start(SHOW_VIDEO_DELAY);
}

void camThread::show_last_pic()
{
    int ret = 0;

    if (global_conf_sys->sys_standby.standby_mode == SERIAL_MODE) {
        this->cam_timer->stop();
    }

    ret = write_jpeg(global_image_filename,shm_save_buff,now_image_quality,CAMERA_WIDTH,CAMERA_HEIGHT,0);
    //ret = write_jpeg(SAVE_VIDEO_PIC,(unsigned char*)captureBuffer[c.index].data,75,CAMERA_WIDTH,CAMERA_HEIGHT,0);
    if (ret < 0) {
        perror("write to jpeg fail");
        recordLog(9, 28, (char*)"write to jpeg fail");
    } else {
        qDebug("write to jpeg ok! %s", __func__);
    }

    decodeYUV420SP((unsigned int*)shm_buffer, shm_save_buff);

    //memcpy(shm_buffer, shm_save_buff, CAMERA_WIDTH * CAMERA_HEIGHT * CAM_LINELEN);
    qDebug() << "copy to shm_buffer is ok";
    // show the alarm pic in the screen

    // let the image timer start to correct time here
    take_pic_flag = true;

    emit play();
}



/****************************************************
  1st step: Open camera device

return: 0 -- success
-1 - Failed
 *****************************************************/
int camThread::openCamera() {
    // Open camera Device
    const char *device = CAMERA_DEV_NAME;
    //camFd = open(device, O_RDWR|O_NONBLOCK);        // Non Block, Read and Write
    camFd = open(device, O_RDONLY|O_NONBLOCK);        // Non Block, Read Only

    if (camFd < 0) {
        recordLog(9, 17, (char*)"Cannot open camera device");
        //fprintf(stderr, "   Cannot open camera device %s\n", device);
        qDebug() << "Cannot open camera device";
        return -1;
    } // end
    global_camfd = camFd;
    camWidth   = CAMERA_WIDTH;                // pixels per row
    camHeight  = CAMERA_HEIGHT;               // pixels per col
    camBPP     = CAMERA_BPP;                  // Bits Per Pixel
    camLineLen = CAMERA_LINELEN;              // bytes per line
    camSize    = CAMERA_SIZE;                 // bytes per frame

    return 0;
} // end of openCamera()

/****************************************************
  2nd step: Getting capability

return: 0 -- success
-1 - Failed
 *****************************************************/
int camThread::getCapability() {
    int valid = 0;
    struct v4l2_capability cap;

    // ioctl: query capability
    if (ioctl(camFd, VIDIOC_QUERYCAP, &cap) < 0) {
        qDebug("   Cannot query capability\n");
        recordLog(9, 17, (char*)"Cannot query capability");
        return -1;
    } // end of if

    qDebug("   The driver name: %s v%d\n", cap.driver, cap.version);
    qDebug("   The divice name: %s\n", cap.card);
    qDebug("   Bus information: %s\n", cap.bus_info);

    // check capability of video capture
    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
        recordLog(9, 17, (char*)"It does not support the Video Capture interface");
        valid = -1;
        qDebug("   It does not support the Video Capture interface.\n");
    } else {
        qDebug("   It supports the Video Capture interface.\n");
    } // end of if

    // check capability of video output
    if (!(cap.capabilities & V4L2_CAP_VIDEO_OUTPUT)) {
        recordLog(9, 17, (char*)"It does not support the Video Capture interface");
        valid = -1;
        qDebug("   It does not support the Video Output interface.\n");
    } else {
        qDebug("   It supports the Video Output interface.\n");
    } // end of if

    // check capability of video overlay
    if (!(cap.capabilities & V4L2_CAP_VIDEO_OVERLAY)) {
        recordLog(9, 17, (char*)"It does not supports the Video Overlay interface");
        valid = -1;
        qDebug("   It does not supports the Video Overlay interface.\n");
    } else {
        qDebug("   It supports the Video Overlay interface.\n");
    } // end of if

    // check capability of video stream
    if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
        recordLog(9, 17, (char*)"It does not support streaming i/o");
        valid = -1;
        qDebug("   It does not support streaming i/o\n");
    } else {
        qDebug("   It supports video streaming i/o\n");
    } // end of if

    return valid;
} // end of getCapability()

/****************************************************
  3rd step: check and select input device

return: -1 -- failed
>=0 - index of input device
 *****************************************************/
int camThread::selectInput() {
    // check input device
    int valid = -1;
    static struct v4l2_input input;
    input.index = 0;

    if (ioctl(camFd, VIDIOC_ENUMINPUT, &input) != 0) {
        recordLog(9, 17, (char*)"VIDIOC_ENUMINPUT:No matching index found");
        qDebug("   No matching index found\n");
        return valid;
    } // end of if

    if (!input.name) {
        recordLog(9, 17, (char*)"No matching index found");
        qDebug("   No matching index found\n");
        return valid;
    }  // end
    qDebug("   Input device name: %s\n", input.name);

    // select input
    if (ioctl(camFd, VIDIOC_S_INPUT, &input) < 0) {
        recordLog(9, 17, (char*)"VIDIOC_S_INPUT failed");
        qDebug("   VIDIOC_S_INPUT failed\n");
        return valid;
    } // end
    return input.index;
} // end of selectInput()

/****************************************************
  4th step: Set camera format

return: 0 -- success
-1 - Failed
 *****************************************************/
int camThread::setFormat() {
    // Setting format
    struct v4l2_format fmt;
    memset(&fmt, 0, sizeof(fmt));

    //**** it dos not suport VIDIOC_S_FMT ioctl ****

    fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;                         // type of stream is CAPTURE_STREAM, cannot be OVERLAY
    fmt.fmt.pix.width       = camWidth;                                            // pixels per row
    fmt.fmt.pix.height      = camHeight;                                           // pixels per col
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_NV21;                                   // format of camera stream is NV21

    fmt.fmt.pix.sizeimage   = (fmt.fmt.pix.width * fmt.fmt.pix.height * 6) / 4;    // bytes per frame
    fmt.fmt.pix.field       = V4L2_FIELD_NONE;                                     // successive format, not interlace

    if (ioctl(camFd, VIDIOC_S_FMT, &fmt) < 0) {    // setting format ioctl
        recordLog(9, 17, (char*)"VIDIOC_S_FMT failed");
        qDebug("   VIDIOC_S_FMT failed\n");
        return -1;
    } // end
    return 0;
} // end of setFormat()

/****************************************************
  5th step: request the capture buffer in camera device

return: 0 -- success
-1 - Failed
 *****************************************************/
int camThread::requestCameraBuffer() {
    // request the capture buffer
    struct v4l2_requestbuffers req;
    memset(&req, 0, sizeof(req));                                 // clear the structure

    req.count  = CAPTURE_BUFFER_NUMBER;                          // buffer count to request
    req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;                    // type of buffer
    req.memory = V4L2_MEMORY_MMAP;                               // must be V4L2_MEMORY_MMAP or V4L2_MEMORY_USERPTR

    if (ioctl(camFd, VIDIOC_REQBUFS, &req) < 0) {                // Initiate Memory Mapping
        recordLog(9, 17, (char*)"Request camera buffer failed");
        qDebug("   Request camera buffer failed\n");
        return -1;
    } //end of if

    if (req.count != CAPTURE_BUFFER_NUMBER) {
        recordLog(9, 17, (char*)"Capture buffer number is wrong. number");
        // buffer count requested is not the same that wanted
        qDebug("   Capture buffer number is wrong. number = %d\n", req.count);
        return -1;
    } // end
    return 0;
} // end of mapCameraBuffer()

/***************************************************************
  6th step: initial camera buffers

return: 0 -- success
-1 - Failed
 ****************************************************************/
int camThread::initCameraBuffer() {
    // initial camera buffer
    int i;
    struct v4l2_buffer b;

    for (i = 0; i < CAPTURE_BUFFER_NUMBER; i++) {
        memset(&b, 0, sizeof(b));
        b.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        b.memory = V4L2_MEMORY_MMAP;
        b.index  = i;

        if (ioctl(camFd, VIDIOC_QUERYBUF, &b) < 0) {     // Query the status of a buffer
            recordLog(9, 17, (char*)"Query capture buffer failed");
            qDebug("   Query capture buffer failed\n");
            return -1;
        } // end of if
        /*s
         *i void *mmap(void *start,size_t length,int prot,int flags,int fd,off_t offsize);
         *i start   -  NULL
         *i length  -
         *i prot    - : PROT_EXEC /PROT_READ
         *i           PROT_WRITE /PROT_NONE
         *i flags   - mmap()MAP_SHARED MAP_PRIVATE
         *i fd      -
         *i offset  - 0
         *i
         e*/
        //captureBuffer[i].data = mmap(0, b.length, PROT_READ|PROT_WRITE, MAP_SHARED, fd, b.m.offset);
        captureBuffer[i].data = mmap(0, b.length, PROT_READ, MAP_SHARED, camFd, b.m.offset);
        // e                    PROT_READ:PROT_WRITE:  MAP_SHARED:
        captureBuffer[i].len = b.length;

        if (captureBuffer[i].data == MAP_FAILED) {
            recordLog(9, 17, (char*)"Unable to map capture buffer. index");
            qDebug("   Unable to map capture buffer. index = %d\n", i);
            return -1;
        } // end

        qDebug("   ImageSize[%d] = %d\n", i, b.length);
    } // end of for

    return 0;
} // end of mapAppBuffer()


/****************************************************
  9th step: start video stream

return: 0 -- success
-1 - Failed
 *****************************************************/
int camThread::startStream() {
    int i;
    struct v4l2_buffer b;                           // in videodev2.h
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    qDebug() << "try to start the stream";
    for (i = 0; i < CAPTURE_BUFFER_NUMBER; i++) {
        memset(&b, 0, sizeof(b));                      // clear
        b.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;       // buffer type
        b.memory = V4L2_MEMORY_MMAP;
        b.index  = i;

        if (ioctl(camFd, VIDIOC_QBUF, &b) < 0) {        // Exchange a buffer with the driver
            recordLog(9, 17, (char*)"Queue capture failed");
            qDebug("   Queue capture failed\n");
            return -1;
        }  // end of if
    }  // end of for

    if (ioctl (camFd, VIDIOC_STREAMON, &type) < 0) {
        recordLog(9, 17, (char*)"Cannot start stream");
        qDebug("   Cannot start stream\n");
        return -1;
    }  // end

    return 0;
} // end of startStream()



void camThread::decodeYUV420SP(unsigned int* rgbBuf,
                               unsigned char* yuv420sp) {
    //int frameSize = camWidth * camHeight;

    int k, m, n;
    int j, yp;
    int i = 0, y = 0;
    int uvp = 0, u = 0, v = 0;
    int y1192 = 0, r = 0, g = 0, b = 0;
    unsigned int xrgb8888;


    //int xrgb8888Index = 0;

    k = 0;
    for (j = 0; j < (CAMERA_HEIGHT + TOP_SKIP); j++) {         // row

        if ((j + 1) % global_extra_line == 0) k++;
        m = j - k;               // line number in camera buffer
        n = j;                   // line number in framebuffer

        if (old_driver_flag == true) {
            if (j >= CAMERA_HEIGHT - OFFSET_CAMERA_HEIGHT) {
                m = CAMERA_HEIGHT - OFFSET_CAMERA_HEIGHT - 1;
            }
        }
        yp = m * CAMERA_WIDTH;
        uvp = CAMERA_FRAMEPIXEL + (m >> 1) * CAMERA_WIDTH;
        u = 0;
        v = 0;
        // xrgb8888Index = n * fbWidth0;
        for (i = 0; i < CAMERA_WIDTH; i++, yp++) {          // col
            y = (0xff & ((int) yuv420sp[yp])) - 16;           // Y
            if (y < 0) y = 0;
            if ((i & 1) == 0) {                               // i is even
                v = (0xff & yuv420sp[uvp++]) - 128;             // V
                u = (0xff & yuv420sp[uvp++]) - 128;             // U
            }  // end

            y1192 = 1192 * y;
            r = (y1192 + 1634 * v);
            g = (y1192 - 833 * v - 400 * u);
            b = (y1192 + 2066 * u);

            if (r < 0) r = 0; else if (r > 262143) r = 262143;
            if (g < 0) g = 0; else if (g > 262143) g = 262143;
            if (b < 0) b = 0; else if (b > 262143) b = 262143;

            r = (unsigned char)(r >> 10);
            g = (unsigned char)(g >> 10);
            b = (unsigned char)(b >> 10);

            xrgb8888 = (unsigned int)((r << 16) | (g << 8) | b);
            //if (rgbBuf[xrgb8888Index] != xrgb8888) rgbBuf[xrgb8888Index] = xrgb8888;
            //xrgb8888Index++;
            if (n >= TOP_SKIP && n < CAMERA_HEIGHT + TOP_SKIP) {
                if (i < LEFT_SKIP) {
                    *rgbBuf = 0;
                } else {
                    *rgbBuf= xrgb8888;
                }
                rgbBuf++;
            }

        }  // end of for
    }  //end of for
} // end

/****************************************************
  11th step: fetch a capture picture

return: 0 -- success
-1 - Failed
 *****************************************************/
//struct v4l2_buffer c;
//unsigned char *data;
//int index = 0;
/*************************************/
int camThread::fetchPicture() {
    unsigned char *data_;
    // int i, j;
    memset(&c, 0, sizeof(c));
    c.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    c.memory = V4L2_MEMORY_MMAP;

    if (ioctl(camFd, VIDIOC_DQBUF, &c) < 0) {     // get buffer that filled data from camera device
        recordLog(8, 17, (char*)"Cannot fetch picture(VIDIOC_DQBUF failed memory");
        qDebug("   Cannot fetch picture(VIDIOC_DQBUF failed memory)\n");
        return -1;
    }

    //void *data_ = captureBuffer[b.index].data;
    //unsigned char* data = (unsigned char*) data_;
    //unsigned int len = b.bytesused;
    //unsigned int index = b.index;
     data_ = (unsigned char*)captureBuffer[c.index].data;             // captureBuffer
    if (old_driver_flag == true) {
        //c.index = 1;
        if (c.index == 0) {
            ;
        } else if (c.index == 1) {
            data_ +=656 + CAMERA_WIDTH*OFFSET_CAMERA_HEIGHT;
        } else if (c.index == 2) {
            data_ += 96;
        } else if (c.index == 3) {
            data_ +=752 + CAMERA_WIDTH*OFFSET_CAMERA_HEIGHT;
        }
        memcpy(camAddr, data_, CAMERA_YUVLEN- CAMERA_WIDTH*OFFSET_CAMERA_HEIGHT*1/2);
        //memcpy(camAddr, data_, CAMERA_YUVLEN);
    } else {
        memcpy(camAddr, data_, CAMERA_YUVLEN);
    }









    //memset(fbAddr0, 0, fbSize0);
    //data = (unsigned char *)captureBuffer[c.index].data;
    decodeYUV420SP((unsigned int*)shm_buffer, camAddr);

    if (ioctl(camFd, VIDIOC_QBUF, &c) < 0) {
        recordLog(8, 17, (char*)"Cannot fetch picture(VIDIOC_QBUF failed VIDIOC_QBUF");
        qDebug("   Cannot fetch picture(VIDIOC_QBUF failed)\n");
        return -1;
    } // end
    return 0;
} // end of fetchPicture()




int camThread::savePic(const char *filename)
{

    int ret;
    unsigned char *data_;
    char buf_echo[1024];

    memset(&c, 0, sizeof(c));
    c.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    c.memory = V4L2_MEMORY_MMAP;

    if (ioctl(camFd, VIDIOC_DQBUF, &c) < 0) {     // get buffer that filled data from camera device
        sprintf(buf_echo, "Cannot fetch picture(VIDIOC_DQBUF failed) camfd %s", filename);
        recordLog(8, 17, buf_echo);
        qDebug("%s", buf_echo);
        bzero(shm_save_buff, CAMERA_WIDTH * CAMERA_HEIGHT * CAM_LINELEN);
        return -1;
    }


    data_ = (unsigned char*)captureBuffer[c.index].data;             // captureBuffer
   if (old_driver_flag == true) {

       if (c.index == 0) {
           ;
       } else if (c.index == 1) {
           data_ +=656 + CAMERA_WIDTH*OFFSET_CAMERA_HEIGHT;
       } else if (c.index == 2) {
           data_ += 96;
       } else if (c.index == 3) {
           data_ +=752 + CAMERA_WIDTH*OFFSET_CAMERA_HEIGHT;
       }
       memcpy(camAddr, data_, CAMERA_YUVLEN- CAMERA_WIDTH*OFFSET_CAMERA_HEIGHT*1/2);
       //memcpy(camAddr, data_, CAMERA_YUVLEN);
   } else {
       memcpy(camAddr, data_, CAMERA_YUVLEN);
   }


    if (ioctl(camFd, VIDIOC_QBUF, &c) < 0) {
        recordLog(8, 17, (char*)"Cannot fetch picture(VIDIOC_QBUF failed)");
        qDebug("   Cannot fetch picture(VIDIOC_QBUF failed)\n");
        return -1;
    }


    //#define SINGLA_MODE     0
    if ((global_conf_sys->sys_working_mode.working_mode == SINGLE_MODE) || ((all_sensor.sensor[EXT_POSITION].has_signal) == SENSOR_SIGNAL_Y)) {
        ret = write_jpeg(filename,camAddr,now_image_quality,CAMERA_WIDTH,CAMERA_HEIGHT,0);
        //ret = write_jpeg(SAVE_VIDEO_PIC,(unsigned char*)captureBuffer[c.index].data,75,CAMERA_WIDTH,CAMERA_HEIGHT,0);
        if (ret < 0) {
            recordLog(8, 17, (char*)"write to jpeg fail single mode");
            perror("write to jpeg fail");
        } else {

            if ((all_sensor.sensor[EXT_POSITION].has_signal) == SENSOR_SIGNAL_Y) {
                qDebug() << "write to jpeg ok in extra sensor mode";
                recordLog(8, 17, (char*)"write to jpeg ok in extra sensor mode");
            } else {
                qDebug() << "write to jpeg ok in single mode";
                recordLog(8, 17, (char*)"write to jpeg ok in single mode");
            }
        }



        // in order to show in the screen
        decodeYUV420SP((unsigned int*)shm_buffer, camAddr);
        emit play();
    } else {
        //will emit when the alarm happen
        //decodeYUV420SP((unsigned int*)shm_save_buff, camAddr);
        
        memcpy(shm_save_buff, camAddr, CAMERA_YUVLEN);

        if (global_conf_sys->sys_standby.standby_mode == SERIAL_MODE) {
            cam_timer->start(SHOW_VIDEO_DELAY);
            //emit_pic();
        }
    }


    /**/

    return 0;
}


//write_jpeg(filename,address,75,WIDTH,HEIGHT,0)
int camThread::write_jpeg(const char *filename,unsigned char *buf,int quality,int width, int height, int gray)
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *fp;
    JSAMPROW row_pointer[1];
    unsigned char *line_buffer;
    line_buffer = (unsigned char*)calloc(width * 3, 1);
    unsigned char *ptr = line_buffer;

    int k, m, n;
    int j, yp;
    int i = 0, y = 0;
    int uvp = 0, u = 0, v = 0;
    int y1192 = 0, r = 0, g = 0, b = 0;
    k = 0;

    //qDebug() << "calloc buffer";
    if ((fp = fopen(filename,"w+")) == NULL )
    {
        fprintf(stderr,"grab: can't open %s: %s\n",filename,strerror(errno));
        recordLog(8, 17, (char*)"grab: can't open");
        return -1;
    }
    //qDebug() << "fopen buffer";
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, fp);
    cinfo.image_width  = width;
    cinfo.image_height = height;
    cinfo.input_components = gray ? 1: 3;
    cinfo.in_color_space = gray ? JCS_GRAYSCALE: JCS_RGB;
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);


    // qDebug() << "fset buffer";
    for (j = 0; j < (CAMERA_HEIGHT + TOP_SKIP); j++) {         // row
        //for (j = (CAMERA_HEIGHT + TOP_SKIP - 1); j >= 0 ; j--) {         // row
        if ((j + 1) % global_extra_line == 0) k++;
        m = j - k;               // line number in camera buffer
        n = j;                   // line number in framebuffer

        if (old_driver_flag == true) {
            if (j >= CAMERA_HEIGHT - OFFSET_CAMERA_HEIGHT) {
                m = CAMERA_HEIGHT - OFFSET_CAMERA_HEIGHT - 1;
            }
        }

        yp = m * CAMERA_WIDTH;
        uvp = CAMERA_FRAMEPIXEL + (m >> 1) * CAMERA_WIDTH;
        u = 0;
        v = 0;
        ptr = line_buffer;
        for (i = 0; i < CAMERA_WIDTH; i++, yp++) {          // col
            //for (i = CAMERA_WIDTH - 1; i >= 0; i--, yp++) {          // col
            y = (0xff & ((int) buf[yp])) - 16;           // Y
            if (y < 0) y = 0;
            if ((i & 1) == 0) {                               // i is even
                v = (0xff & buf[uvp++]) - 128;             // V
                u = (0xff & buf[uvp++]) - 128;             // U
            }  // end

            y1192 = 1192 * y;
            r = (y1192 + 1634 * v);
            g = (y1192 - 833 * v - 400 * u);
            b = (y1192 + 2066 * u);

            if (r < 0) r = 0; else if (r > 262143) r = 262143;
            if (g < 0) g = 0; else if (g > 262143) g = 262143;
            if (b < 0) b = 0; else if (b > 262143) b = 262143;


            if (n >= TOP_SKIP && n < CAMERA_HEIGHT + TOP_SKIP) {

                if (i < LEFT_SKIP) {
                    *(ptr++) = 0;
                    *(ptr++) = 0;
                    *(ptr++) = 0;
                } else {
                    *(ptr++) = r = (unsigned char)(r >> 10);
                    *(ptr++) = g = (unsigned char)(g >> 10);
                    *(ptr++) = b = (unsigned char)(b >> 10);
                }
            }
        }  // end of for
        if (n >= TOP_SKIP && n < CAMERA_HEIGHT + TOP_SKIP) {
            row_pointer[0] = line_buffer;
            jpeg_write_scanlines(&cinfo, row_pointer, 1);
        }
    }
    jpeg_finish_compress(&(cinfo));
    jpeg_destroy_compress(&(cinfo));
    free (line_buffer);
    fflush(fp);
    fclose(fp);

    return 0;
}




/****************************************************
  12th step: stop video stream

return: 0 -- success
-1 - Failed
 *****************************************************/
int camThread::stopStream() {
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    qDebug() << "try to stop the stream";
    if (ioctl (camFd, VIDIOC_STREAMOFF, &type) < 0) {
        recordLog(8, 17, (char*)"Cannot stop stream");
        qDebug("   Cannot stop stream\n");
        return -1;
    }  // end
    return 0;
} // end of stopStream()

/******************************************************


 *******************************************************/





camThread::~camThread()
{
    qDebug("################################\n");


}
