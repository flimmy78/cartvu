#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>//It's the case you have to pay attention
#include    <QDebug>
#include <QSignalMapper>
#include <QFile>
#include <QMouseEvent>
#include <QPointer>

#include "MyInputPanel.h"
#include "MyInputPannelContext.h"
MyInputPanel::MyInputPanel(MyInputPannelContext *ipc,QWidget *parent)
    :QWidget(parent, Qt::Tool|Qt::FramelessWindowHint),
    //: QWidget(parent, Qt::Tool | Qt::WindowStaysOnTopHint),
    lastFocusedWidget(0)
{
    inputform=new Ui::MyInputPanelForm;
    inputform->setupUi(this);



    btns=findChildren<QPushButton *>();
    btns_sz=btns.size();


    qDebug() << "btn size is " << btns_sz;
    xml_accu=0;
    //状态xml信息 包含字母按键等信息 写入键值对
    loadDoc();
    //从键值对中读取信息 做出设置属性
    num_caps();

    //设置当前键盘的字符， 有三种显示选择
    setKBcharacter();
    //焦点变化时  响应槽函数
    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)),
            this, SLOT(saveFocusWidget(QWidget*,QWidget*)));
    myMapping();
    //connect(this,SIGNAL(sendChar(QChar)),ipc,SLOT(charSlot(QChar)));
    //connect(this,SIGNAL(sendInt(int)),ipc,SLOT(intSlot(int)));

    connect(this,SIGNAL(sendChar(QChar)),this,SLOT(this_charSlot(QChar)));
    connect(this,SIGNAL(sendInt(int)),this,SLOT(this_intSlot(int)));

    should_move=false;

}

void MyInputPanel::this_charSlot(QChar character)
{
    QPointer<QWidget> w = focusWidget();

    if (!w)
        return;

    QKeyEvent keyPress(QEvent::KeyPress, character.unicode(), Qt::NoModifier, QString(character));
    QApplication::sendEvent(w, &keyPress);

    if (!w)
        return;

    QKeyEvent keyRelease(QEvent::KeyPress, character.unicode(), Qt::NoModifier, QString());
    QApplication::sendEvent(w, &keyRelease);

}

void MyInputPanel::intKey(int Key)
{
    QPointer<QWidget> w = focusWidget();

    if (!w)
        return;

    if (Key == Qt::Key_Enter) {

        emit send_info(QString(this->inputform->lineEdit_info->text()));
        qDebug() << "try to send info"<< this->inputform->lineEdit_info->text();
        this->close();
        return;
    }
    QKeyEvent keyPress(QEvent::KeyPress, Key, Qt::NoModifier, QString());
    QApplication::sendEvent(w, &keyPress);
}

void MyInputPanel::this_intSlot(int key)
{
   // QPointer<QWidget> w = focusWidget();

   // if (!w)
  //      return;
    switch(key)
    {
        //case 35:
        //   break;
    case 36:
        this->hide();
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
        capsPro();//"caps" key
        break;
    case 57:
        numPro();//"num" key
        break;

        /**/
    case 58:
        this_charSlot(' ');//"space" key
        break;
    default:
        return;
    }
}

void MyInputPanel::loadDoc()
{
    doc=new QDomDocument("keydoc");
    QFile file(":/keyboard.xml");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"xml file does not exist";
        return;
    } else {
        //qDebug() << "xml file is in :/keyboard.xml";
    }

    bool namespaceProcessing=false;
    QString *errorMsg = new QString();

    int errorLine=0;
    int errorColumn=0;

    QTextStream stream(&file);
    if(!doc->setContent(stream.readAll(),namespaceProcessing,errorMsg,&errorLine,&errorColumn))
    {
        qDebug()<<"can not set content";
        qDebug()<<"namespaceProcessing"<<namespaceProcessing;
        qDebug()<<"errormsg"<<errorMsg->toAscii();
        qDebug()<<"errorLine"<<errorLine;
        qDebug()<<"errorColomn"<<errorColumn;
        return;
    }
}

//--------------get num and caps keys' state--------------
void MyInputPanel::num_caps()
{
    bool OK;
    int caps_tmp = 0;
    int num_tmp = 0;

    //---------------get keys' nr in XML----------------------------
    for(QDomNode n=doc->documentElement().firstChild();(!n.isNull());n=n.nextSibling())
    {
        xml_accu+=1;
        //键值对  的text中是否有"CAPS"
        if(n.toElement().attribute("text").contains("CAPS"))
        {
            caps_tmp=n.toElement().attribute("nr").toInt(&OK);
            //qDebug() << xml_accu;
            //qDebug() << n.toElement().attribute("nr").toInt(&OK);
            continue;
        } else {
            //qDebug() << "good" << xml_accu;
            //qDebug() << "good" <<n.toElement().attribute("text");
        }

        if(n.toElement().attribute("text").contains("NUM"))
        {
            num_tmp=n.toElement().attribute("nr").toInt(&OK);
            continue;
        }

    }


    for(int i=0;i<btns_sz;i++)
    {
        //找到 caps按键来设置按键的效果
        if(btns[i]->objectName().remove("pushButton_").toInt(&OK)==caps_tmp)
        {
            //设置按钮按下时有变色效果
            btns[i]->setCheckable(true);
            //设置弹起效果
            //btns[i]->setChecked(false);
            //设置按下效果
            btns[i]->setChecked(true);
            
            caps=i;
            continue;

        }

        if(btns[i]->objectName().remove("pushButton_").toInt(&OK)==num_tmp)
        {
            btns[i]->setCheckable(true);
            btns[i]->setChecked(false);
            num=i;
            continue;
        }

    }

}

QString MyInputPanel::getKeyBoardAttr()
{
    QString str;
    if(btns[caps]->isChecked())
    {
        str="caps";
    }
    else if(btns[num]->isChecked())
    {
        str="num";
    }
    else
    {
        str="text";
    }
    return str;

}


void MyInputPanel::setKBcharacter()
{
    QDomElement root;
    bool OK;
    //设置字体大小
    QFont font("",20);
    //font.setPointSize(20);
    //找到当前的caps num 和text状态之一，  三种状态之一
    QString str=getKeyBoardAttr();
    //qDebug()<<"getKeyBoardAttr:"<<getKeyBoardAttr().toAscii();//test
    root=doc->documentElement();
    //for(int i=0;i<btns_sz;i++)
    //  45 个buttons
    for(int i=0;i<btns_sz;i++)
    {
        for(QDomNode n=root.firstChild();(!n.isNull());n=n.nextSibling())
        {
            int button=btns[i]->objectName().remove("pushButton_").toInt(&OK);
            int xml=n.toElement().attribute("nr").toInt(&OK);
            if(button==xml)
            {
                if(button==19)//'&'key display
                {
                    if(str=="num")
                    {
                        btns[i]->setIconSize(btns[i]->size()*0.8);//--------------adjust
                        btns[i]->setIcon(QIcon(":/image/&.png"));
                        btns[i]->setText(n.toElement().attribute(str));
                        break;
                    }
                    else
                    {
                        btns[i]->setIcon(QIcon(""));
                        btns[i]->setText(n.toElement().attribute(str));
                        break;
                    }
                }
                //除了 & 之外的处理
                else if(button<50)
                {
                    btns[i]->setText(n.toElement().attribute(str));
                    //qDebug()<<"btns[i]->text()"<<btns[i]->text().toAscii();
                    //root.removeChild(n);
                    break;
                }
                else
                {
                    switch(button)
                    {
                    case 50:
                        btns[i]->setIconSize(btns[i]->size());
                        //btns[i]->setIcon(QIcon(":/image/up.ico"));
                        btns[i]->setIcon(QIcon(":/img/up.png"));
                        btns[i]->setText("");
                        break;
                    case 51:
                        btns[i]->setIconSize(btns[i]->size());
                        //btns[i]->setIcon(QIcon(":/image/left.ico"));
                        btns[i]->setIcon(QIcon(":/img/left.png"));
                        btns[i]->setText("");
                        break;
                    case 52:
                        btns[i]->setIconSize(btns[i]->size());
                        //btns[i]->setIcon(QIcon(":/image/right.ico"));
                        btns[i]->setIcon(QIcon(":/img/right.png"));
                        btns[i]->setText("");
                        break;
                    case 53:
                        btns[i]->setIconSize(btns[i]->size());
                        //btns[i]->setIcon(QIcon(":/image/down.ico"));
                        btns[i]->setIcon(QIcon(":/img/down.png"));
                        btns[i]->setText("");
                        break;
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                        //QFont font("",5);
                        btns[i]->setFont(font);
                        btns[i]->setText(n.toElement().attribute("text"));
                        //btns[i]->setText("aasdfadf");
                        //qDebug() << n.toElement().attribute("text");
                        break;
                    default:
                        btns[i]->setText("test");

                    }

                }

            }
        }
    }
}


void MyInputPanel::saveFocusWidget(QWidget *oldFocus, QWidget *newFocus)
{
    if (newFocus != 0 && !this->isAncestorOf(newFocus)) {
        lastFocusedWidget = newFocus;
       // qDebug() << "new fouce is not zero and newfouce is not parent";
        qDebug()<<"lastFocusedWidget->objectName()"<<lastFocusedWidget->objectName();
        //qDebug() << oldFocus->objectName();
        qDebug() << newFocus->objectName();
        //this->inputform->lineEdit_info->setCursor(Qt::IBeamCursor);
    } else {
        //qDebug() << "first?";
    }


}

bool MyInputPanel::event(QEvent *e)
{

    switch (e->type()) {
    case QEvent::WindowActivate:

        if (lastFocusedWidget) {
            //lastFocusedWidget->activateWindow();
            //this->inputform->lineEdit_info->activateWindow();
        }
        qDebug() << "active window";
        break;
    case QEvent::MouseButtonPress:
        mousePressEvent(e);
        break;
    case QEvent::MouseButtonRelease:
        mouseReleaseEvent(e);
        break;
        //case QEvent::MouseMove:
        //  mouseMoveEvent(e);
        //  break;
    default:
        break;
    }
    //qDebug() << "in panel event";
    /**/
    return QWidget::event(e);
}


void MyInputPanel::myMapping()
{
    QSignalMapper *myMapper=new QSignalMapper(this);
    for(int i=0;i<btns.size();i++)
    {
        myMapper->setMapping(btns[i],btns[i]);
        connect(btns[i],SIGNAL(clicked()),myMapper,SLOT(map()));
    }
    connect(myMapper,SIGNAL(mapped(QWidget*)),this,SLOT(btnClicked(QWidget*)));
    //相当于当有按键发生时 由my Mapper mapping成功进而进入btnclicked槽函数


}

void MyInputPanel::btnClicked(QWidget *w)
{
    QPushButton *btnp=static_cast<QPushButton *>(w);
    int btn;
    bool OK;
    //QString now;
    btn=btnp->objectName().remove("pushButton_").toInt(&OK);
    if(btn<36)
    {
        //取第一个字符
        QChar ch=btnp->text().at(0);
        //qDebug()<<"ch"<<ch;
        //发送给前一个textedit保存起来，并模拟按下和弹起事件
        //now = inputform->lineEdit_info->text();
        //inputform->lineEdit_info->setText(now + QString(ch));
        emit sendChar(ch);
    }
    //除了 close up left down back enter caps num 空格之外
    else
    {
        emit sendInt(btn);
    }
}

void MyInputPanel::capsPro()
{
    if(btns[caps]->isChecked())
    {
        btns[num]->setChecked(false);
    }
    setKBcharacter();
    update();
}




void MyInputPanel::numPro()
{
    if(btns[num]->isChecked())
    {
        btns[caps]->setChecked(false);
    }
    setKBcharacter();
    update();
}




void MyInputPanel::mousePressEvent (QEvent *e)
{
    QMouseEvent *event=static_cast<QMouseEvent *>(e);
    if (event->button()!=Qt::LeftButton) return;
    this->should_move = true;
    this->widget_pos = this->pos();
    this->mouse_pos = event->globalPos();

}
void MyInputPanel::mouseReleaseEvent(QEvent *e)
{
    QMouseEvent *event=static_cast<QMouseEvent *>(e);
    if (event->button()!=Qt::LeftButton) return;
    this->should_move = false;

}
/*
void MyInputPanel::mouseMoveEvent ( QEvent *e)
{
    QMouseEvent *event=static_cast<QMouseEvent *>(e);
    if (this->should_move)
    {
        QPoint pos = event->globalPos();
        int x = pos.x()-this->mouse_pos.x();
        int y = pos.y()-this->mouse_pos.y();
        QWidget::move(this->widget_pos.x()+x,this->widget_pos.y()+y);
    }

}

*/

