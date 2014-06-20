/********************************************************************************
** Form generated from reading UI file 'cartvuMode.ui'
**
** Created: Tue Oct 8 10:44:06 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARTVUMODE_H
#define UI_CARTVUMODE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_cartvuMode
{
public:
    QLabel *cartvu_label;

    void setupUi(QDialog *cartvuMode)
    {
        if (cartvuMode->objectName().isEmpty())
            cartvuMode->setObjectName(QString::fromUtf8("cartvuMode"));
        cartvuMode->resize(1280, 800);
        cartvuMode->setMaximumSize(QSize(1280, 800));
        cartvuMode->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/logo_cartvu.jpg);"));
        cartvu_label = new QLabel(cartvuMode);
        cartvu_label->setObjectName(QString::fromUtf8("cartvu_label"));
        cartvu_label->setGeometry(QRect(0, 0, 1280, 800));
        cartvu_label->setMaximumSize(QSize(1280, 800));

        retranslateUi(cartvuMode);

        QMetaObject::connectSlotsByName(cartvuMode);
    } // setupUi

    void retranslateUi(QDialog *cartvuMode)
    {
        cartvuMode->setWindowTitle(QApplication::translate("cartvuMode", "Dialog", 0, QApplication::UnicodeUTF8));
        cartvu_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class cartvuMode: public Ui_cartvuMode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARTVUMODE_H
