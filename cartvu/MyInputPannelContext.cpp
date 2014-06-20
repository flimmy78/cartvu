#include <QPointer>


#include "MyInputPannelContext.h"
#include    "MyInputPanel.h"

MyInputPannelContext::MyInputPannelContext(QObject *parent) :
        QInputContext(parent)
{
    //inputpanel=new MyInputPanel(this);
    //connect(inputpanel, SIGNAL(send_info(QString)), this, SLOT(update_line(QString)));
    qDebug() << "new here";

}
void MyInputPannelContext::update_line(QString info)
{
        QLineEdit *b;
        b = (QLineEdit*)this->widget;
        b->setText(info);
        qDebug() << "signal happen";
}

QString MyInputPannelContext::identifierName()
{
    qDebug() << "identifierName";
    return "MyInputPannelContext";
}

void MyInputPannelContext::reset()
{
    qDebug() << "MyInputPannelContext::reset";
}

bool MyInputPannelContext::isComposing() const
{
    qDebug() << "isComposing";
    return false;
}

QString MyInputPannelContext::language()
{
    qDebug() << "language";
    return "en_US";
}



bool MyInputPannelContext::filterEvent(const QEvent* event)
{
    if (event->type() == QEvent::RequestSoftwareInputPanel) {

        //event->
        //inputpanel->inputform->lineEdit_info->setText("hello");
        updatePosition();
        //inputpanel->show();
        qDebug() << "show request software";
        return true;
    } else if (event->type() == QEvent::CloseSoftwareInputPanel) {
       // inputpanel->hide();
        qDebug() << "close software input";
        return true;
    }

    //qDebug() << "filterEvent";
    return false;
}



void MyInputPannelContext::updatePosition()
{
    //QTextEdit *a;
    //QLineEdit *b;
    QString name;
    widget = focusWidget();
    if (!widget)
        return;

   // QRect widgetRect = widget->rect();


    name = widget->objectName();
    qDebug()  << name;
    /*
    b = (QLineEdit*)widget;
    //b->setText("you are right");
    qDebug() << b->text();
*/

    /*
    //更新键盘里面的lineEdit内容
    inputpanel->inputform->lineEdit_info->setText(b->text());
    // in order to set the focus to lineEdit so the keyboard is valid
    inputpanel->inputform->lineEdit_info->setFocus();
    inputpanel->inputform->lineEdit_info->setCursor(Qt::IBeamCursor);
    inputpanel->inputform->label_info->setText(name.remove("lineEdit_"));
    */
            //qDebug() << widget->objectName().;
            //QPoint panelPos = QPoint(widgetRect.left(), widgetRect.bottom() + 2);
     /*QPoint panelPos = QPoint(0, 0);
    panelPos = widget->mapToGlobal(panelPos);
    inputpanel->move(panelPos);
   */
    //inputpanel->show();

}


void MyInputPannelContext::charSlot(QChar character)
{
    //QPointer<QWidget> w = focusWidget();
    QPointer<QWidget> w = widget;

    if (!w)
        return;

    QKeyEvent keyPress(QEvent::KeyPress, character.unicode(), Qt::NoModifier, QString(character));
    QApplication::sendEvent(w, &keyPress);

    if (!w)
        return;

    QKeyEvent keyRelease(QEvent::KeyPress, character.unicode(), Qt::NoModifier, QString());
    QApplication::sendEvent(w, &keyRelease);

}

void MyInputPannelContext::intKey(int Key)
{
    //QPointer<QWidget> w = focusWidget();
    QPointer<QWidget> w = widget;

    if (!w)
        return;

    if (Key == Qt::Key_Enter) {
        //inputpanel->close();
        return;
    }
    QKeyEvent keyPress(QEvent::KeyPress, Key, Qt::NoModifier, QString());
    QApplication::sendEvent(w, &keyPress);


}

void MyInputPannelContext::intSlot(int key)
{
    // QPointer<QWidget> w = focusWidget();

    // if (!w)
    //      return;
    switch(key)
    {
        //case 35:
        //   break;
    case 36:
        //inputpanel->hide();
        break;
    case 50:
        intKey(Qt::Key_Up);
        break;
    case 51:
        intKey(Qt::Key_Left);
        break;
    case 52:
        intKey(Qt::Key_Right);
        break;
    case 53:
        intKey(Qt::Key_Down);
        break;
    case 54:
        intKey(Qt::Key_Backspace);
        break;
    case 55:
        intKey(Qt::Key_Enter);
        break;
    case 56:
       // inputpanel->capsPro();//"caps" key
        break;
    case 57:
       // inputpanel->numPro();//"num" key
        break;
    case 58:
        charSlot(' ');//"space" key
        break;
    default:
        return;
    }
}






MyInputPannelContext::~MyInputPannelContext()
{
    //delete inputpanel;
}




