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
    //���numʱ�л�������ʾ
    void numPro();
    //���capsʱ�л�������ʾ
    void capsPro();
    //���ͼ�����������¼�
    void intKey(int Key);
public:
    Ui::MyInputPanelForm *inputform;
signals:
    //�����ַ�
    void sendChar(QChar ch);
    //���ͷ��ַ�ʱ
    void sendInt(int key);
    //���enterʱ�����ⷢ���ź�
    void send_info(QString);

protected:
    // ��갴���¼�
    bool event(QEvent *e);
    
private slots:
    //��һ������Ľ��㣬�뵱ǰ�Ľ���
    void saveFocusWidget(QWidget *oldFocus, QWidget *newFocus);
    //�������ϵİ�ť����ʱ
    void btnClicked(QWidget *w);
    //���µ�ǰ�����ַ�
    void this_charSlot(QChar character);
    //���µ�ǰ����������Ϣ
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
    //װ��xml���̲����ļ�
    void loadDoc();
    //num��caps�ĵ�ǰ״̬ʶ��
    void num_caps();
    //��ȡ��ǰnum caps text״̬
    QString getKeyBoardAttr();
    //���¼��̵��ַ���ʾ
    void setKBcharacter();
    //���м��̰�ť���ź���۵�map
    void myMapping();
    //��갴��
    void mousePressEvent(QEvent *e);
    //��굯��
    void mouseReleaseEvent(QEvent *e);
     /*void mouseMoveEvent(QEvent *e);
    */
    
};

#endif // MYINPUTPANEL_H
