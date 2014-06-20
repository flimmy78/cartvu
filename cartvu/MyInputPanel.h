#ifndef MYINPUTPANEL_H
#define MYINPUTPANEL_H

#include <QWidget>
#include <QList>
#include <QChar>
#include <QString>
#include <QPoint>
#include <QPushButton>
#include "ui_MyInputPanelForm.h"

class MyInputPannelContext;
class QDomDocument;
namespace Ui {
    class MyInputPanelForm;
}

class MyInputPanel : public QWidget
{
    Q_OBJECT
public:
    explicit MyInputPanel(MyInputPannelContext *ipc,QWidget *parent=0 );
    //点击num时切换键盘显示
    void numPro();
    //点击caps时切换键盘显示
    void capsPro();
    //发送键盘输入键的事件
    void intKey(int Key);
public:
    Ui::MyInputPanelForm *inputform;
signals:
    //发送字符
    void sendChar(QChar ch);
    //发送非字符时
    void sendInt(int key);
    //点击enter时，往外发送信号
    void send_info(QString);

protected:
    // 鼠标按键事件
    bool event(QEvent *e);
    
private slots:
    //上一个窗体的焦点，与当前的焦点
    void saveFocusWidget(QWidget *oldFocus, QWidget *newFocus);
    //当键盘上的按钮按下时
    void btnClicked(QWidget *w);
    //更新当前键盘字符
    void this_charSlot(QChar character);
    //更新当前其他按键信息
    void this_intSlot(int key);
private:

    QList<QPushButton *> btns;
    int btns_sz;
    QDomDocument *doc;
    int caps;
    int num;
    int xml_accu;
    QWidget *lastFocusedWidget;

    bool should_move;
    QPoint  mouse_pos;
    QPoint  widget_pos;
    //装载xml键盘布局文件
    void loadDoc();
    //num与caps的当前状态识别
    void num_caps();
    //读取当前num caps text状态
    QString getKeyBoardAttr();
    //更新键盘的字符显示
    void setKBcharacter();
    //所有键盘按钮的信号与槽的map
    void myMapping();
    //鼠标按下
    void mousePressEvent(QEvent *e);
    //鼠标弹起
    void mouseReleaseEvent(QEvent *e);
     /*void mouseMoveEvent(QEvent *e);
    */
    
};

#endif // MYINPUTPANEL_H
