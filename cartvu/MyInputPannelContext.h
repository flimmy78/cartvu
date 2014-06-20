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
    //当双击lineEdit等可输入时触发的函数
    bool filterEvent(const QEvent* event);
public:
    QWidget *widget;
signals:
    void now_line_string(QString info);
    
public slots:
    //更新键盘的字符显示
    void charSlot(QChar character);
    void intSlot(int key);
    //将当前触发lineEdit的内容更新
    void update_line(QString info);
private:
        //MyInputPanel *inputpanel;
        //读取当前的lineEdit的内容更新到键盘的lineEdit
        void updatePosition();
        //void leftKey();
        void intKey(int Key);

};

#endif // MYINPUTPANNELCONTEXT_H
