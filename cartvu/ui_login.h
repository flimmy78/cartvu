/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created: Fri Jun 13 18:09:23 2014
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QLineEdit *lineEdit;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_1;
    QPushButton *pushButton_ac;
    QPushButton *pushButton_0;
    QPushButton *pushButton_del;
    QPushButton *login_button;
    QLabel *label_kings;
    QPushButton *big_button;
    QLabel *version_label;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QString::fromUtf8("login"));
        login->resize(1280, 800);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(login->sizePolicy().hasHeightForWidth());
        login->setSizePolicy(sizePolicy);
        login->setMinimumSize(QSize(0, 0));
        login->setMaximumSize(QSize(1280, 800));
        QFont font;
        font.setPointSize(25);
        login->setFont(font);
        login->setCursor(QCursor(Qt::BlankCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/pic/favicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        login->setWindowIcon(icon);
        login->setStyleSheet(QString::fromUtf8("#login {\n"
"border-image: url(:/pic/log_bk.png);\n"
"}"));
        lineEdit = new QLineEdit(login);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(500, 190, 321, 101));
        lineEdit->setFont(font);
        lineEdit->setCursor(QCursor(Qt::BlankCursor));
        lineEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 153, 51);"));
        gridLayoutWidget = new QWidget(login);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(210, 320, 321, 412));
        sizePolicy.setHeightForWidth(gridLayoutWidget->sizePolicy().hasHeightForWidth());
        gridLayoutWidget->setSizePolicy(sizePolicy);
        gridLayoutWidget->setMinimumSize(QSize(150, 0));
        QFont font1;
        font1.setPointSize(40);
        gridLayoutWidget->setFont(font1);
        gridLayoutWidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(10);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMinimumSize(QSize(95, 95));
        pushButton_2->setMaximumSize(QSize(95, 95));
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt2_up.png);"));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(gridLayoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setMinimumSize(QSize(95, 95));
        pushButton_3->setMaximumSize(QSize(95, 95));
        pushButton_3->setFont(font1);
        pushButton_3->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt3_up.png);"));

        gridLayout->addWidget(pushButton_3, 0, 2, 1, 1);

        pushButton_4 = new QPushButton(gridLayoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
        pushButton_4->setMinimumSize(QSize(95, 95));
        pushButton_4->setMaximumSize(QSize(95, 95));
        pushButton_4->setFont(font1);
        pushButton_4->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt4_up.png);"));

        gridLayout->addWidget(pushButton_4, 1, 0, 1, 1);

        pushButton_5 = new QPushButton(gridLayoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        sizePolicy.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy);
        pushButton_5->setMinimumSize(QSize(95, 95));
        pushButton_5->setMaximumSize(QSize(95, 95));
        pushButton_5->setFont(font1);
        pushButton_5->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt5_up.png);"));

        gridLayout->addWidget(pushButton_5, 1, 1, 1, 1);

        pushButton_6 = new QPushButton(gridLayoutWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        sizePolicy.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy);
        pushButton_6->setMinimumSize(QSize(95, 95));
        pushButton_6->setMaximumSize(QSize(95, 95));
        pushButton_6->setFont(font1);
        pushButton_6->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt6_up.png);"));

        gridLayout->addWidget(pushButton_6, 1, 2, 1, 1);

        pushButton_7 = new QPushButton(gridLayoutWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        sizePolicy.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy);
        pushButton_7->setMinimumSize(QSize(95, 95));
        pushButton_7->setMaximumSize(QSize(95, 95));
        pushButton_7->setFont(font1);
        pushButton_7->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt7_up.png);"));

        gridLayout->addWidget(pushButton_7, 2, 0, 1, 1);

        pushButton_8 = new QPushButton(gridLayoutWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        sizePolicy.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy);
        pushButton_8->setMinimumSize(QSize(95, 95));
        pushButton_8->setMaximumSize(QSize(95, 95));
        pushButton_8->setFont(font1);
        pushButton_8->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt8_up.png);"));

        gridLayout->addWidget(pushButton_8, 2, 1, 1, 1);

        pushButton_9 = new QPushButton(gridLayoutWidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        sizePolicy.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy);
        pushButton_9->setMinimumSize(QSize(95, 95));
        pushButton_9->setMaximumSize(QSize(95, 95));
        pushButton_9->setFont(font1);
        pushButton_9->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt9_up.png);"));

        gridLayout->addWidget(pushButton_9, 2, 2, 1, 1);

        pushButton_1 = new QPushButton(gridLayoutWidget);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setEnabled(true);
        sizePolicy.setHeightForWidth(pushButton_1->sizePolicy().hasHeightForWidth());
        pushButton_1->setSizePolicy(sizePolicy);
        pushButton_1->setMinimumSize(QSize(95, 95));
        pushButton_1->setMaximumSize(QSize(95, 95));
        pushButton_1->setFont(font1);
        pushButton_1->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt1_up.png);"));

        gridLayout->addWidget(pushButton_1, 0, 0, 1, 1);

        pushButton_ac = new QPushButton(gridLayoutWidget);
        pushButton_ac->setObjectName(QString::fromUtf8("pushButton_ac"));
        sizePolicy.setHeightForWidth(pushButton_ac->sizePolicy().hasHeightForWidth());
        pushButton_ac->setSizePolicy(sizePolicy);
        pushButton_ac->setMinimumSize(QSize(95, 95));
        pushButton_ac->setMaximumSize(QSize(95, 95));
        pushButton_ac->setFont(font1);
        pushButton_ac->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/btac_up.png);"));

        gridLayout->addWidget(pushButton_ac, 3, 0, 1, 1);

        pushButton_0 = new QPushButton(gridLayoutWidget);
        pushButton_0->setObjectName(QString::fromUtf8("pushButton_0"));
        sizePolicy.setHeightForWidth(pushButton_0->sizePolicy().hasHeightForWidth());
        pushButton_0->setSizePolicy(sizePolicy);
        pushButton_0->setMinimumSize(QSize(95, 95));
        pushButton_0->setMaximumSize(QSize(95, 95));
        pushButton_0->setFont(font1);
        pushButton_0->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt0_up.png);"));

        gridLayout->addWidget(pushButton_0, 3, 1, 1, 1);

        pushButton_del = new QPushButton(gridLayoutWidget);
        pushButton_del->setObjectName(QString::fromUtf8("pushButton_del"));
        sizePolicy.setHeightForWidth(pushButton_del->sizePolicy().hasHeightForWidth());
        pushButton_del->setSizePolicy(sizePolicy);
        pushButton_del->setMinimumSize(QSize(95, 95));
        pushButton_del->setMaximumSize(QSize(95, 95));
        pushButton_del->setFont(font1);
        pushButton_del->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/btdel_up.png);"));

        gridLayout->addWidget(pushButton_del, 3, 2, 1, 1);

        login_button = new QPushButton(login);
        login_button->setObjectName(QString::fromUtf8("login_button"));
        login_button->setGeometry(QRect(900, 180, 250, 100));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(login_button->sizePolicy().hasHeightForWidth());
        login_button->setSizePolicy(sizePolicy1);
        login_button->setMinimumSize(QSize(0, 100));
        login_button->setFont(font);
        login_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/log_up.png);"));
        label_kings = new QLabel(login);
        label_kings->setObjectName(QString::fromUtf8("label_kings"));
        label_kings->setGeometry(QRect(300, 50, 800, 60));
        label_kings->setFont(font);
        label_kings->setStyleSheet(QString::fromUtf8("color: rgb(255, 153, 51);"));
        big_button = new QPushButton(login);
        big_button->setObjectName(QString::fromUtf8("big_button"));
        big_button->setGeometry(QRect(0, 0, 1280, 800));
        big_button->setCursor(QCursor(Qt::BlankCursor));
        big_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/zero.png);"));
        version_label = new QLabel(login);
        version_label->setObjectName(QString::fromUtf8("version_label"));
        version_label->setGeometry(QRect(1010, 20, 240, 40));
        QFont font2;
        font2.setPointSize(15);
        version_label->setFont(font2);
        version_label->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/zero.png);\n"
"color: rgb(255, 153, 51);"));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QApplication::translate("login", "Dialog", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_8->setText(QString());
        pushButton_9->setText(QString());
        pushButton_1->setText(QString());
        pushButton_ac->setText(QString());
        pushButton_0->setText(QString());
        pushButton_del->setText(QString());
        login_button->setText(QString());
        label_kings->setText(QApplication::translate("login", "Kings #66 Lane 5", 0, QApplication::UnicodeUTF8));
        big_button->setText(QApplication::translate("login", "now will shutdown the screen!", 0, QApplication::UnicodeUTF8));
        version_label->setText(QApplication::translate("login", "Version", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
