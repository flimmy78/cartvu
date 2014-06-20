#ifndef MYINPUTPANNELCONTEXT_H
#define MYINPUTPANNELCONTEXT_H

#include <QInputContext>
#include <QDebug>
#include <QTextEdit>
#include <QLineEdit>
class MyInputPanel;


class MyInputPannelContext : public QInputContext
{
    Q_OBJECT
public:
    explicit MyInputPannelContext(QObject *parent = 0);
    ~MyInputPannelContext();


    QString identifierName();
    QString language();

    bool isComposing() const;

    void reset();
    //��˫��lineEdit�ȿ�����ʱ�����ĺ���
    bool filterEvent(const QEvent* event);
public:
    QWidget *widget;
signals:
    void now_line_string(QString info);
    
public slots:
    //���¼��̵��ַ���ʾ
    void charSlot(QChar character);
    void intSlot(int key);
    //����ǰ����lineEdit�����ݸ���
    void update_line(QString info);
private:
        //MyInputPanel *inputpanel;
        //��ȡ��ǰ��lineEdit�����ݸ��µ����̵�lineEdit
        void updatePosition();
        //void leftKey();
        void intKey(int Key);

};

#endif // MYINPUTPANNELCONTEXT_H
