/********************************************************************************
** Form generated from reading UI file 'cartvu.ui'
**
** Created: Fri Jun 13 18:09:23 2014
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARTVU_H
#define UI_CARTVU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cartvu
{
public:
    QWidget *centralWidget;
    QPushButton *log_button;
    QPushButton *exit_button;

    void setupUi(QMainWindow *cartvu)
    {
        if (cartvu->objectName().isEmpty())
            cartvu->setObjectName(QString::fromUtf8("cartvu"));
        cartvu->setEnabled(true);
        cartvu->resize(1280, 800);
        cartvu->setMaximumSize(QSize(1600, 900));
        cartvu->setCursor(QCursor(Qt::BlankCursor));
        cartvu->setAutoFillBackground(true);
        cartvu->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(cartvu);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMaximumSize(QSize(1280, 800));
        centralWidget->setCursor(QCursor(Qt::ArrowCursor));
        centralWidget->setAutoFillBackground(false);
        centralWidget->setStyleSheet(QString::fromUtf8("#centralWidget {\n"
"border-image: url(:/pic/logo_cartvu.jpg);\n"
"}"));
        log_button = new QPushButton(centralWidget);
        log_button->setObjectName(QString::fromUtf8("log_button"));
        log_button->setGeometry(QRect(840, 630, 434, 168));
        QFont font;
        font.setPointSize(50);
        font.setBold(true);
        font.setItalic(true);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        font.setKerning(true);
        log_button->setFont(font);
        log_button->setCursor(QCursor(Qt::ArrowCursor));
        log_button->setAutoFillBackground(false);
        log_button->setStyleSheet(QString::fromUtf8("border-image:url(:/pic/login_button.jpg);\n"
"\n"
"\n"
""));
        log_button->setFlat(false);
        exit_button = new QPushButton(centralWidget);
        exit_button->setObjectName(QString::fromUtf8("exit_button"));
        exit_button->setGeometry(QRect(1150, 20, 61, 51));
        exit_button->setCursor(QCursor(Qt::ArrowCursor));
        cartvu->setCentralWidget(centralWidget);

        retranslateUi(cartvu);

        QMetaObject::connectSlotsByName(cartvu);
    } // setupUi

    void retranslateUi(QMainWindow *cartvu)
    {
        cartvu->setWindowTitle(QApplication::translate("cartvu", "cartvu", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cartvu->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        log_button->setText(QApplication::translate("cartvu", "LOG   IN", 0, QApplication::UnicodeUTF8));
        exit_button->setText(QApplication::translate("cartvu", "exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class cartvu: public Ui_cartvu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARTVU_H
