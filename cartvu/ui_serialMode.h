/********************************************************************************
** Form generated from reading UI file 'serialMode.ui'
**
** Created: Fri Jun 13 18:09:23 2014
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALMODE_H
#define UI_SERIALMODE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_serialMode
{
public:
    QPushButton *check_button;
    QPushButton *logout_button;
    QPushButton *list_button;
    QLabel *time_label;
    QLabel *lane_label;
    QLabel *cashier_label;
    QPushButton *title_button;
    QLabel *label_E1;
    QLabel *label_S;
    QLabel *label_I1;
    QLabel *label_I2;
    QLabel *label_I3;
    QLabel *label_E2;
    QLabel *label_state;
    QPushButton *pushButton_hide;
    QLabel *label_error;
    QPushButton *time_button;
    QPushButton *lane_button;
    QLabel *cam_label;
    QPushButton *tick_button;
    QTextEdit *merchan_text;
    QLabel *label_EXT;
    QPushButton *recover_button;

    void setupUi(QDialog *serialMode)
    {
        if (serialMode->objectName().isEmpty())
            serialMode->setObjectName(QString::fromUtf8("serialMode"));
        serialMode->resize(1280, 800);
        QFont font;
        font.setPointSize(80);
        serialMode->setFont(font);
        serialMode->setCursor(QCursor(Qt::BlankCursor));
        serialMode->setStyleSheet(QString::fromUtf8("#serialMode {\n"
"border-image: url(:/pic/serial_bak.png);\n"
"}"));
        check_button = new QPushButton(serialMode);
        check_button->setObjectName(QString::fromUtf8("check_button"));
        check_button->setGeometry(QRect(1040, 40, 240, 600));
        QFont font1;
        font1.setPointSize(50);
        check_button->setFont(font1);
        check_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/check_green_up.png);"));
        logout_button = new QPushButton(serialMode);
        logout_button->setObjectName(QString::fromUtf8("logout_button"));
        logout_button->setGeometry(QRect(0, 40, 240, 280));
        QFont font2;
        font2.setPointSize(30);
        logout_button->setFont(font2);
        logout_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/logout_up.png);"));
        list_button = new QPushButton(serialMode);
        list_button->setObjectName(QString::fromUtf8("list_button"));
        list_button->setGeometry(QRect(0, 320, 240, 320));
        list_button->setFont(font2);
        list_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/list_up.png);"));
        time_label = new QLabel(serialMode);
        time_label->setObjectName(QString::fromUtf8("time_label"));
        time_label->setGeometry(QRect(0, 700, 420, 100));
        QFont font3;
        font3.setPointSize(19);
        time_label->setFont(font3);
        time_label->setStyleSheet(QString::fromUtf8("color: rgb(255, 153, 51);"));
        lane_label = new QLabel(serialMode);
        lane_label->setObjectName(QString::fromUtf8("lane_label"));
        lane_label->setGeometry(QRect(430, 700, 420, 100));
        QFont font4;
        font4.setPointSize(25);
        lane_label->setFont(font4);
        lane_label->setStyleSheet(QString::fromUtf8("color: rgb(255, 153, 51);"));
        cashier_label = new QLabel(serialMode);
        cashier_label->setObjectName(QString::fromUtf8("cashier_label"));
        cashier_label->setGeometry(QRect(860, 700, 420, 100));
        cashier_label->setFont(font4);
        cashier_label->setStyleSheet(QString::fromUtf8("color: rgb(255, 153, 51);"));
        title_button = new QPushButton(serialMode);
        title_button->setObjectName(QString::fromUtf8("title_button"));
        title_button->setGeometry(QRect(0, 0, 1280, 40));
        QFont font5;
        font5.setPointSize(20);
        title_button->setFont(font5);
        title_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/zero.png);\n"
"color: rgb(255, 153, 51);"));
        label_E1 = new QLabel(serialMode);
        label_E1->setObjectName(QString::fromUtf8("label_E1"));
        label_E1->setGeometry(QRect(260, 10, 35, 21));
        label_E1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_S = new QLabel(serialMode);
        label_S->setObjectName(QString::fromUtf8("label_S"));
        label_S->setGeometry(QRect(300, 10, 35, 21));
        label_S->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_I1 = new QLabel(serialMode);
        label_I1->setObjectName(QString::fromUtf8("label_I1"));
        label_I1->setGeometry(QRect(360, 10, 35, 21));
        label_I1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_I2 = new QLabel(serialMode);
        label_I2->setObjectName(QString::fromUtf8("label_I2"));
        label_I2->setGeometry(QRect(400, 10, 35, 21));
        label_I2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_I3 = new QLabel(serialMode);
        label_I3->setObjectName(QString::fromUtf8("label_I3"));
        label_I3->setGeometry(QRect(440, 10, 35, 21));
        label_I3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_E2 = new QLabel(serialMode);
        label_E2->setObjectName(QString::fromUtf8("label_E2"));
        label_E2->setGeometry(QRect(500, 10, 35, 21));
        label_E2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_state = new QLabel(serialMode);
        label_state->setObjectName(QString::fromUtf8("label_state"));
        label_state->setGeometry(QRect(730, 10, 130, 21));
        label_state->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_hide = new QPushButton(serialMode);
        pushButton_hide->setObjectName(QString::fromUtf8("pushButton_hide"));
        pushButton_hide->setGeometry(QRect(860, 640, 420, 160));
        pushButton_hide->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/zero.png);"));
        label_error = new QLabel(serialMode);
        label_error->setObjectName(QString::fromUtf8("label_error"));
        label_error->setGeometry(QRect(910, 10, 200, 21));
        label_error->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        time_button = new QPushButton(serialMode);
        time_button->setObjectName(QString::fromUtf8("time_button"));
        time_button->setGeometry(QRect(0, 640, 420, 160));
        time_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/zero.png);"));
        lane_button = new QPushButton(serialMode);
        lane_button->setObjectName(QString::fromUtf8("lane_button"));
        lane_button->setGeometry(QRect(430, 640, 420, 160));
        lane_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/zero.png);"));
        cam_label = new QLabel(serialMode);
        cam_label->setObjectName(QString::fromUtf8("cam_label"));
        cam_label->setGeometry(QRect(248, 50, 784, 580));
        cam_label->setFocusPolicy(Qt::StrongFocus);
        cam_label->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/standby.png);"));
        tick_button = new QPushButton(serialMode);
        tick_button->setObjectName(QString::fromUtf8("tick_button"));
        tick_button->setGeometry(QRect(290, 80, 237, 187));
        tick_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/tick.png);"));
        merchan_text = new QTextEdit(serialMode);
        merchan_text->setObjectName(QString::fromUtf8("merchan_text"));
        merchan_text->setGeometry(QRect(250, 50, 780, 580));
        merchan_text->viewport()->setProperty("cursor", QVariant(QCursor(Qt::BlankCursor)));
        merchan_text->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        label_EXT = new QLabel(serialMode);
        label_EXT->setObjectName(QString::fromUtf8("label_EXT"));
        label_EXT->setGeometry(QRect(200, 10, 35, 21));
        label_EXT->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        recover_button = new QPushButton(serialMode);
        recover_button->setObjectName(QString::fromUtf8("recover_button"));
        recover_button->setGeometry(QRect(0, 0, 1280, 800));
        recover_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/zero.png);"));

        retranslateUi(serialMode);

        QMetaObject::connectSlotsByName(serialMode);
    } // setupUi

    void retranslateUi(QDialog *serialMode)
    {
        serialMode->setWindowTitle(QApplication::translate("serialMode", "Dialog", 0, QApplication::UnicodeUTF8));
        check_button->setText(QString());
        logout_button->setText(QString());
        list_button->setText(QString());
        time_label->setText(QApplication::translate("serialMode", "2013-08-07 18:00:00", 0, QApplication::UnicodeUTF8));
        lane_label->setText(QApplication::translate("serialMode", "12345", 0, QApplication::UnicodeUTF8));
        cashier_label->setText(QApplication::translate("serialMode", "     123456", 0, QApplication::UnicodeUTF8));
        title_button->setText(QApplication::translate("serialMode", "title", 0, QApplication::UnicodeUTF8));
        label_E1->setText(QApplication::translate("serialMode", "E1", 0, QApplication::UnicodeUTF8));
        label_S->setText(QApplication::translate("serialMode", "S", 0, QApplication::UnicodeUTF8));
        label_I1->setText(QApplication::translate("serialMode", "I1", 0, QApplication::UnicodeUTF8));
        label_I2->setText(QApplication::translate("serialMode", "I2", 0, QApplication::UnicodeUTF8));
        label_I3->setText(QApplication::translate("serialMode", "I3", 0, QApplication::UnicodeUTF8));
        label_E2->setText(QApplication::translate("serialMode", "E2", 0, QApplication::UnicodeUTF8));
        label_state->setText(QApplication::translate("serialMode", "state", 0, QApplication::UnicodeUTF8));
        pushButton_hide->setText(QString());
        label_error->setText(QApplication::translate("serialMode", "state", 0, QApplication::UnicodeUTF8));
        time_button->setText(QString());
        lane_button->setText(QString());
        cam_label->setText(QApplication::translate("serialMode", "camera pic", 0, QApplication::UnicodeUTF8));
        tick_button->setText(QString());
        label_EXT->setText(QApplication::translate("serialMode", "EXT", 0, QApplication::UnicodeUTF8));
        recover_button->setText(QApplication::translate("serialMode", "!", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class serialMode: public Ui_serialMode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALMODE_H
