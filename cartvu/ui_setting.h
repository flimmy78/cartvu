/********************************************************************************
** Form generated from reading UI file 'setting.ui'
**
** Created: Fri Jun 13 18:09:23 2014
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_setting
{
public:
    QPushButton *factory_button;
    QPushButton *telnet_button;
    QPushButton *sensor_show_button;
    QPushButton *return_button;
    QPushButton *reset_button;
    QTextEdit *show_text;
    QTextEdit *show_label;
    QPushButton *bt_config_setttings;
    QPushButton *setting_hide_button;

    void setupUi(QDialog *setting)
    {
        if (setting->objectName().isEmpty())
            setting->setObjectName(QString::fromUtf8("setting"));
        setting->resize(1280, 800);
        setting->setCursor(QCursor(Qt::BlankCursor));
        setting->setStyleSheet(QString::fromUtf8("#setting {\n"
"border-image: url(:/pic/log_frame.jpg);\n"
"}\n"
"\n"
""));
        factory_button = new QPushButton(setting);
        factory_button->setObjectName(QString::fromUtf8("factory_button"));
        factory_button->setGeometry(QRect(70, 170, 450, 100));
        QFont font;
        font.setPointSize(20);
        factory_button->setFont(font);
        telnet_button = new QPushButton(setting);
        telnet_button->setObjectName(QString::fromUtf8("telnet_button"));
        telnet_button->setGeometry(QRect(80, 380, 300, 100));
        telnet_button->setFont(font);
        sensor_show_button = new QPushButton(setting);
        sensor_show_button->setObjectName(QString::fromUtf8("sensor_show_button"));
        sensor_show_button->setGeometry(QRect(80, 650, 300, 100));
        sensor_show_button->setFont(font);
        return_button = new QPushButton(setting);
        return_button->setObjectName(QString::fromUtf8("return_button"));
        return_button->setGeometry(QRect(1020, 700, 250, 100));
        return_button->setFont(font);
        reset_button = new QPushButton(setting);
        reset_button->setObjectName(QString::fromUtf8("reset_button"));
        reset_button->setGeometry(QRect(690, 240, 300, 100));
        reset_button->setFont(font);
        show_text = new QTextEdit(setting);
        show_text->setObjectName(QString::fromUtf8("show_text"));
        show_text->setGeometry(QRect(80, 520, 331, 71));
        show_text->setFont(font);
        show_text->viewport()->setProperty("cursor", QVariant(QCursor(Qt::BlankCursor)));
        show_text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        show_label = new QTextEdit(setting);
        show_label->setObjectName(QString::fromUtf8("show_label"));
        show_label->setGeometry(QRect(460, 420, 511, 351));
        QFont font1;
        font1.setPointSize(10);
        show_label->setFont(font1);
        show_label->viewport()->setProperty("cursor", QVariant(QCursor(Qt::BlankCursor)));
        bt_config_setttings = new QPushButton(setting);
        bt_config_setttings->setObjectName(QString::fromUtf8("bt_config_setttings"));
        bt_config_setttings->setGeometry(QRect(750, 90, 450, 100));
        bt_config_setttings->setFont(font);
        setting_hide_button = new QPushButton(setting);
        setting_hide_button->setObjectName(QString::fromUtf8("setting_hide_button"));
        setting_hide_button->setGeometry(QRect(0, 0, 1280, 800));
        setting_hide_button->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/zero.png);"));

        retranslateUi(setting);

        QMetaObject::connectSlotsByName(setting);
    } // setupUi

    void retranslateUi(QDialog *setting)
    {
        setting->setWindowTitle(QApplication::translate("setting", "Dialog", 0, QApplication::UnicodeUTF8));
        factory_button->setText(QApplication::translate("setting", "Factory Settings", 0, QApplication::UnicodeUTF8));
        telnet_button->setText(QApplication::translate("setting", "Enable Telnet", 0, QApplication::UnicodeUTF8));
        sensor_show_button->setText(QApplication::translate("setting", "Show Sensors", 0, QApplication::UnicodeUTF8));
        return_button->setText(QApplication::translate("setting", "Return", 0, QApplication::UnicodeUTF8));
        reset_button->setText(QApplication::translate("setting", "Reset System", 0, QApplication::UnicodeUTF8));
        show_text->setHtml(QApplication::translate("setting", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:20pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; "
                        "margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        show_label->setHtml(QApplication::translate("setting", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; "
                        "margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        bt_config_setttings->setText(QApplication::translate("setting", "Config.sys Settings", 0, QApplication::UnicodeUTF8));
        setting_hide_button->setText(QApplication::translate("setting", "will shutdown the light!", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class setting: public Ui_setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
