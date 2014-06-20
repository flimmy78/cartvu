/********************************************************************************
** Form generated from reading UI file 'selfMode.ui'
**
** Created: Tue Oct 8 10:44:06 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELFMODE_H
#define UI_SELFMODE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_selfMode
{
public:
    QLabel *self_label;

    void setupUi(QDialog *selfMode)
    {
        if (selfMode->objectName().isEmpty())
            selfMode->setObjectName(QString::fromUtf8("selfMode"));
        selfMode->resize(1280, 800);
        selfMode->setMaximumSize(QSize(1280, 800));
        selfMode->setStyleSheet(QString::fromUtf8("#selfMode {\n"
"border-image: url(:/pic/logo_cartvu.jpg);\n"
"}"));
        self_label = new QLabel(selfMode);
        self_label->setObjectName(QString::fromUtf8("self_label"));
        self_label->setGeometry(QRect(0, 0, 1280, 800));

        retranslateUi(selfMode);

        QMetaObject::connectSlotsByName(selfMode);
    } // setupUi

    void retranslateUi(QDialog *selfMode)
    {
        selfMode->setWindowTitle(QApplication::translate("selfMode", "Dialog", 0, QApplication::UnicodeUTF8));
        self_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class selfMode: public Ui_selfMode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELFMODE_H
