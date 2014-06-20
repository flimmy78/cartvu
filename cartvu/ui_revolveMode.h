/********************************************************************************
** Form generated from reading UI file 'revolveMode.ui'
**
** Created: Fri Jun 13 18:09:23 2014
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REVOLVEMODE_H
#define UI_REVOLVEMODE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_revolveMode
{
public:
    QLabel *revolve_label;
    QPushButton *return_button;
    QPushButton *log_in_out_button;

    void setupUi(QDialog *revolveMode)
    {
        if (revolveMode->objectName().isEmpty())
            revolveMode->setObjectName(QString::fromUtf8("revolveMode"));
        revolveMode->resize(1280, 800);
        revolveMode->setCursor(QCursor(Qt::BlankCursor));
        revolveMode->setStyleSheet(QString::fromUtf8(""));
        revolve_label = new QLabel(revolveMode);
        revolve_label->setObjectName(QString::fromUtf8("revolve_label"));
        revolve_label->setGeometry(QRect(0, 0, 1280, 800));
        revolve_label->setMaximumSize(QSize(1280, 800));
        revolve_label->setCursor(QCursor(Qt::BlankCursor));
        return_button = new QPushButton(revolveMode);
        return_button->setObjectName(QString::fromUtf8("return_button"));
        return_button->setGeometry(QRect(0, 0, 1280, 800));
        return_button->setCursor(QCursor(Qt::BlankCursor));
        return_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/zero.png);"));
        log_in_out_button = new QPushButton(revolveMode);
        log_in_out_button->setObjectName(QString::fromUtf8("log_in_out_button"));
        log_in_out_button->setGeometry(QRect(1000, 680, 250, 100));
        QFont font;
        font.setPointSize(20);
        log_in_out_button->setFont(font);
        log_in_out_button->setCursor(QCursor(Qt::BlankCursor));

        retranslateUi(revolveMode);

        QMetaObject::connectSlotsByName(revolveMode);
    } // setupUi

    void retranslateUi(QDialog *revolveMode)
    {
        revolveMode->setWindowTitle(QApplication::translate("revolveMode", "Dialog", 0, QApplication::UnicodeUTF8));
        revolve_label->setText(QString());
        return_button->setText(QString());
        log_in_out_button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class revolveMode: public Ui_revolveMode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REVOLVEMODE_H
