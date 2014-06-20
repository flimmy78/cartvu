#ifndef CARTVU_H
#define CARTVU_H
#include <QDebug>
#include <QMainWindow>



#include "camThread.h"
namespace Ui {
    class cartvu;
}

class cartvu : public QMainWindow {
    Q_OBJECT
public:
    explicit cartvu(camThread *cam, QWidget *parent = 0);
    ~cartvu();
    void cartvu_init(void);
    void setup_slot_init(void);





protected:
    void changeEvent(QEvent *e);

private:
    Ui::cartvu *ui;
    camThread  *camera;
private slots:
    void on_exit_button_clicked();
    void on_log_button_clicked();

};

#endif // CARTVU_H
