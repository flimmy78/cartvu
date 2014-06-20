#include "cartvu.h"
#include "ui_cartvu.h"
#include "camThread.h"
#include "login.h"


extern login *global_log;

cartvu::cartvu(camThread *cam, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cartvu)
{
    ui->setupUi(this);
    //remove the menu
    this->setWindowFlags(Qt::FramelessWindowHint);

    //initial for other before  log in
    cartvu_init();
    //
    camera = cam;
    setup_slot_init();
}

cartvu::~cartvu()
{
    delete ui;
}



void cartvu::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void cartvu::cartvu_init(void)
{


    static int i = 1;
    qDebug("now is %d\n", i++);
//    camera = new camThread();
//    camera->start(QThread::LowPriority);

}
void cartvu::setup_slot_init(void)
{



}



void cartvu::on_log_button_clicked()
{
    //login *a = new login(camera);
    //a->show();

    global_log->show();
    this->close();
    //wait for thread to exit   if not do this it will cause problem
    //camera->wait();
    //delete camera;
    //system("killall -9 madplay");
    delete this;
}

void cartvu::on_exit_button_clicked()
{
    my_system("killall -9 ./car_test");




    this->close();
}
