/********************************************************************************
** Form generated from reading UI file 'config_setting.ui'
**
** Created: Fri Jun 13 18:09:23 2014
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIG_SETTING_H
#define UI_CONFIG_SETTING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_config_setting
{
public:
    QLineEdit *lineEdit_local_server;
    QLineEdit *lineEdit_store_name;
    QLineEdit *lineEdit_time_zone;
    QLineEdit *lineEdit_openning_time;
    QLineEdit *lineEdit_closing_time;
    QLineEdit *lineEdit_image_time;
    QLineEdit *lineEdit_e2_timeout;
    QLineEdit *lineEdit_alarm_interval;
    QLabel *label_localserver;
    QLabel *label_store_name;
    QLabel *label_closing_time;
    QLabel *label_openning_time;
    QLabel *label_working_mode;
    QLabel *label_saving_time;
    QLabel *label_camera_type;
    QLabel *label_time_zone;
    QLabel *label_image_time;
    QLabel *label_is_number;
    QLabel *label_alarm_interval;
    QLabel *label_e2_timeout;
    QPushButton *button_modify_settings;
    QPushButton *button_return;
    QPushButton *button_read_default_settings;
    QComboBox *cb_savingtime;
    QComboBox *cb_working_mode;
    QComboBox *cb_camera_type;
    QComboBox *cb_is_number;
    QComboBox *cb_alarm_mode;
    QComboBox *cb_alarm_id;
    QComboBox *cb_alarm_volume;
    QComboBox *cb_standby_mode;
    QComboBox *cb_image_quality;
    QComboBox *cb_extra_item_info;
    QComboBox *cb_brightness;
    QLabel *sec_cashier_timeout;
    QLabel *sec_e2_timeout;
    QLabel *sec_alarm_interval;
    QLabel *sec_image_time;
    QLabel *label_alarm_mode;
    QLabel *label_alarm_id;
    QLabel *label_alarm_volume;
    QLabel *label_standby_mode;
    QLabel *label_revolve_range;
    QLabel *label_revolve_period;
    QLabel *label_extra_item_info;
    QLabel *label_image_quality;
    QLabel *label_reset_time;
    QLabel *label_brightness;
    QLabel *label_cashier_timeout;
    QLineEdit *lineEdit_revolve_range;
    QLineEdit *lineEdit_revolve_period;
    QLineEdit *lineEdit_reset_time;
    QLineEdit *lineEdit_cashier_timeout;
    QLabel *label_settings;
    QComboBox *cb_settings;
    QLabel *sec_revolve_period;
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
    QPushButton *pushButton_minus;
    QPushButton *pushButton_colon;

    void setupUi(QDialog *config_setting)
    {
        if (config_setting->objectName().isEmpty())
            config_setting->setObjectName(QString::fromUtf8("config_setting"));
        config_setting->resize(1280, 800);
        config_setting->setCursor(QCursor(Qt::BlankCursor));
        config_setting->setStyleSheet(QString::fromUtf8(""));
        lineEdit_local_server = new QLineEdit(config_setting);
        lineEdit_local_server->setObjectName(QString::fromUtf8("lineEdit_local_server"));
        lineEdit_local_server->setEnabled(false);
        lineEdit_local_server->setGeometry(QRect(230, 10, 250, 50));
        QFont font;
        font.setPointSize(15);
        lineEdit_local_server->setFont(font);
        lineEdit_store_name = new QLineEdit(config_setting);
        lineEdit_store_name->setObjectName(QString::fromUtf8("lineEdit_store_name"));
        lineEdit_store_name->setEnabled(false);
        lineEdit_store_name->setGeometry(QRect(230, 75, 300, 50));
        QFont font1;
        font1.setPointSize(12);
        lineEdit_store_name->setFont(font1);
        lineEdit_time_zone = new QLineEdit(config_setting);
        lineEdit_time_zone->setObjectName(QString::fromUtf8("lineEdit_time_zone"));
        lineEdit_time_zone->setGeometry(QRect(230, 270, 100, 50));
        lineEdit_time_zone->setFont(font);
        lineEdit_openning_time = new QLineEdit(config_setting);
        lineEdit_openning_time->setObjectName(QString::fromUtf8("lineEdit_openning_time"));
        lineEdit_openning_time->setGeometry(QRect(230, 140, 150, 50));
        lineEdit_openning_time->setFont(font);
        lineEdit_closing_time = new QLineEdit(config_setting);
        lineEdit_closing_time->setObjectName(QString::fromUtf8("lineEdit_closing_time"));
        lineEdit_closing_time->setGeometry(QRect(230, 200, 150, 50));
        lineEdit_closing_time->setFont(font);
        lineEdit_image_time = new QLineEdit(config_setting);
        lineEdit_image_time->setObjectName(QString::fromUtf8("lineEdit_image_time"));
        lineEdit_image_time->setGeometry(QRect(230, 725, 100, 50));
        lineEdit_image_time->setFont(font);
        lineEdit_e2_timeout = new QLineEdit(config_setting);
        lineEdit_e2_timeout->setObjectName(QString::fromUtf8("lineEdit_e2_timeout"));
        lineEdit_e2_timeout->setGeometry(QRect(230, 595, 100, 50));
        lineEdit_e2_timeout->setFont(font);
        lineEdit_alarm_interval = new QLineEdit(config_setting);
        lineEdit_alarm_interval->setObjectName(QString::fromUtf8("lineEdit_alarm_interval"));
        lineEdit_alarm_interval->setGeometry(QRect(230, 660, 100, 50));
        lineEdit_alarm_interval->setFont(font);
        label_localserver = new QLabel(config_setting);
        label_localserver->setObjectName(QString::fromUtf8("label_localserver"));
        label_localserver->setGeometry(QRect(10, 10, 210, 50));
        label_localserver->setFont(font1);
        label_localserver->setLayoutDirection(Qt::RightToLeft);
        label_localserver->setAutoFillBackground(false);
        label_store_name = new QLabel(config_setting);
        label_store_name->setObjectName(QString::fromUtf8("label_store_name"));
        label_store_name->setGeometry(QRect(10, 75, 210, 50));
        label_store_name->setFont(font1);
        label_store_name->setLayoutDirection(Qt::RightToLeft);
        label_store_name->setAutoFillBackground(false);
        label_closing_time = new QLabel(config_setting);
        label_closing_time->setObjectName(QString::fromUtf8("label_closing_time"));
        label_closing_time->setGeometry(QRect(10, 205, 210, 50));
        label_closing_time->setFont(font1);
        label_closing_time->setLayoutDirection(Qt::RightToLeft);
        label_closing_time->setAutoFillBackground(false);
        label_openning_time = new QLabel(config_setting);
        label_openning_time->setObjectName(QString::fromUtf8("label_openning_time"));
        label_openning_time->setGeometry(QRect(10, 140, 210, 50));
        label_openning_time->setFont(font1);
        label_openning_time->setLayoutDirection(Qt::RightToLeft);
        label_openning_time->setAutoFillBackground(false);
        label_working_mode = new QLabel(config_setting);
        label_working_mode->setObjectName(QString::fromUtf8("label_working_mode"));
        label_working_mode->setGeometry(QRect(10, 400, 210, 50));
        label_working_mode->setFont(font1);
        label_working_mode->setLayoutDirection(Qt::RightToLeft);
        label_working_mode->setAutoFillBackground(false);
        label_saving_time = new QLabel(config_setting);
        label_saving_time->setObjectName(QString::fromUtf8("label_saving_time"));
        label_saving_time->setGeometry(QRect(10, 335, 210, 50));
        label_saving_time->setFont(font1);
        label_saving_time->setLayoutDirection(Qt::RightToLeft);
        label_saving_time->setAutoFillBackground(false);
        label_camera_type = new QLabel(config_setting);
        label_camera_type->setObjectName(QString::fromUtf8("label_camera_type"));
        label_camera_type->setGeometry(QRect(10, 465, 210, 50));
        label_camera_type->setFont(font1);
        label_camera_type->setLayoutDirection(Qt::RightToLeft);
        label_camera_type->setAutoFillBackground(false);
        label_time_zone = new QLabel(config_setting);
        label_time_zone->setObjectName(QString::fromUtf8("label_time_zone"));
        label_time_zone->setGeometry(QRect(10, 270, 210, 50));
        label_time_zone->setFont(font1);
        label_time_zone->setLayoutDirection(Qt::RightToLeft);
        label_time_zone->setAutoFillBackground(false);
        label_image_time = new QLabel(config_setting);
        label_image_time->setObjectName(QString::fromUtf8("label_image_time"));
        label_image_time->setGeometry(QRect(10, 725, 210, 50));
        label_image_time->setFont(font1);
        label_image_time->setLayoutDirection(Qt::RightToLeft);
        label_image_time->setAutoFillBackground(false);
        label_is_number = new QLabel(config_setting);
        label_is_number->setObjectName(QString::fromUtf8("label_is_number"));
        label_is_number->setGeometry(QRect(10, 530, 210, 50));
        label_is_number->setFont(font1);
        label_is_number->setLayoutDirection(Qt::RightToLeft);
        label_is_number->setAutoFillBackground(false);
        label_alarm_interval = new QLabel(config_setting);
        label_alarm_interval->setObjectName(QString::fromUtf8("label_alarm_interval"));
        label_alarm_interval->setGeometry(QRect(10, 660, 210, 50));
        label_alarm_interval->setFont(font1);
        label_alarm_interval->setLayoutDirection(Qt::RightToLeft);
        label_alarm_interval->setAutoFillBackground(false);
        label_e2_timeout = new QLabel(config_setting);
        label_e2_timeout->setObjectName(QString::fromUtf8("label_e2_timeout"));
        label_e2_timeout->setGeometry(QRect(10, 595, 210, 50));
        label_e2_timeout->setFont(font1);
        label_e2_timeout->setLayoutDirection(Qt::RightToLeft);
        label_e2_timeout->setAutoFillBackground(false);
        button_modify_settings = new QPushButton(config_setting);
        button_modify_settings->setObjectName(QString::fromUtf8("button_modify_settings"));
        button_modify_settings->setGeometry(QRect(540, 0, 391, 50));
        button_modify_settings->setFont(font);
        button_return = new QPushButton(config_setting);
        button_return->setObjectName(QString::fromUtf8("button_return"));
        button_return->setGeometry(QRect(560, 210, 321, 50));
        button_return->setFont(font);
        button_read_default_settings = new QPushButton(config_setting);
        button_read_default_settings->setObjectName(QString::fromUtf8("button_read_default_settings"));
        button_read_default_settings->setGeometry(QRect(550, 100, 401, 50));
        button_read_default_settings->setFont(font);
        cb_savingtime = new QComboBox(config_setting);
        cb_savingtime->setObjectName(QString::fromUtf8("cb_savingtime"));
        cb_savingtime->setGeometry(QRect(230, 335, 150, 41));
        cb_savingtime->setFont(font);
        cb_savingtime->setContextMenuPolicy(Qt::DefaultContextMenu);
        cb_working_mode = new QComboBox(config_setting);
        cb_working_mode->setObjectName(QString::fromUtf8("cb_working_mode"));
        cb_working_mode->setGeometry(QRect(230, 400, 150, 41));
        cb_working_mode->setFont(font);
        cb_camera_type = new QComboBox(config_setting);
        cb_camera_type->setObjectName(QString::fromUtf8("cb_camera_type"));
        cb_camera_type->setGeometry(QRect(230, 465, 150, 41));
        cb_camera_type->setFont(font);
        cb_is_number = new QComboBox(config_setting);
        cb_is_number->setObjectName(QString::fromUtf8("cb_is_number"));
        cb_is_number->setGeometry(QRect(230, 530, 150, 41));
        cb_is_number->setFont(font);
        cb_alarm_mode = new QComboBox(config_setting);
        cb_alarm_mode->setObjectName(QString::fromUtf8("cb_alarm_mode"));
        cb_alarm_mode->setGeometry(QRect(1120, 10, 150, 50));
        cb_alarm_mode->setFont(font);
        cb_alarm_id = new QComboBox(config_setting);
        cb_alarm_id->setObjectName(QString::fromUtf8("cb_alarm_id"));
        cb_alarm_id->setGeometry(QRect(1120, 75, 150, 50));
        cb_alarm_id->setFont(font);
        cb_alarm_volume = new QComboBox(config_setting);
        cb_alarm_volume->setObjectName(QString::fromUtf8("cb_alarm_volume"));
        cb_alarm_volume->setGeometry(QRect(1120, 140, 150, 50));
        cb_alarm_volume->setFont(font);
        cb_standby_mode = new QComboBox(config_setting);
        cb_standby_mode->setObjectName(QString::fromUtf8("cb_standby_mode"));
        cb_standby_mode->setGeometry(QRect(1120, 205, 150, 50));
        cb_standby_mode->setFont(font);
        cb_image_quality = new QComboBox(config_setting);
        cb_image_quality->setObjectName(QString::fromUtf8("cb_image_quality"));
        cb_image_quality->setGeometry(QRect(1120, 400, 150, 50));
        cb_image_quality->setFont(font);
        cb_extra_item_info = new QComboBox(config_setting);
        cb_extra_item_info->setObjectName(QString::fromUtf8("cb_extra_item_info"));
        cb_extra_item_info->setGeometry(QRect(1120, 465, 150, 50));
        cb_extra_item_info->setFont(font);
        cb_brightness = new QComboBox(config_setting);
        cb_brightness->setObjectName(QString::fromUtf8("cb_brightness"));
        cb_brightness->setGeometry(QRect(1120, 595, 150, 50));
        cb_brightness->setFont(font);
        sec_cashier_timeout = new QLabel(config_setting);
        sec_cashier_timeout->setObjectName(QString::fromUtf8("sec_cashier_timeout"));
        sec_cashier_timeout->setGeometry(QRect(1220, 660, 50, 50));
        sec_cashier_timeout->setFont(font);
        sec_e2_timeout = new QLabel(config_setting);
        sec_e2_timeout->setObjectName(QString::fromUtf8("sec_e2_timeout"));
        sec_e2_timeout->setGeometry(QRect(330, 595, 50, 50));
        sec_e2_timeout->setFont(font);
        sec_alarm_interval = new QLabel(config_setting);
        sec_alarm_interval->setObjectName(QString::fromUtf8("sec_alarm_interval"));
        sec_alarm_interval->setGeometry(QRect(330, 660, 50, 50));
        sec_alarm_interval->setFont(font);
        sec_image_time = new QLabel(config_setting);
        sec_image_time->setObjectName(QString::fromUtf8("sec_image_time"));
        sec_image_time->setGeometry(QRect(330, 725, 50, 50));
        sec_image_time->setFont(font);
        label_alarm_mode = new QLabel(config_setting);
        label_alarm_mode->setObjectName(QString::fromUtf8("label_alarm_mode"));
        label_alarm_mode->setGeometry(QRect(900, 10, 210, 50));
        label_alarm_mode->setFont(font1);
        label_alarm_mode->setLayoutDirection(Qt::RightToLeft);
        label_alarm_mode->setAutoFillBackground(false);
        label_alarm_id = new QLabel(config_setting);
        label_alarm_id->setObjectName(QString::fromUtf8("label_alarm_id"));
        label_alarm_id->setGeometry(QRect(900, 75, 210, 50));
        label_alarm_id->setFont(font1);
        label_alarm_id->setLayoutDirection(Qt::RightToLeft);
        label_alarm_id->setAutoFillBackground(false);
        label_alarm_volume = new QLabel(config_setting);
        label_alarm_volume->setObjectName(QString::fromUtf8("label_alarm_volume"));
        label_alarm_volume->setGeometry(QRect(900, 140, 210, 50));
        label_alarm_volume->setFont(font1);
        label_alarm_volume->setLayoutDirection(Qt::RightToLeft);
        label_alarm_volume->setAutoFillBackground(false);
        label_standby_mode = new QLabel(config_setting);
        label_standby_mode->setObjectName(QString::fromUtf8("label_standby_mode"));
        label_standby_mode->setGeometry(QRect(900, 205, 210, 50));
        label_standby_mode->setFont(font1);
        label_standby_mode->setLayoutDirection(Qt::RightToLeft);
        label_standby_mode->setAutoFillBackground(false);
        label_revolve_range = new QLabel(config_setting);
        label_revolve_range->setObjectName(QString::fromUtf8("label_revolve_range"));
        label_revolve_range->setGeometry(QRect(900, 270, 210, 50));
        label_revolve_range->setFont(font1);
        label_revolve_range->setLayoutDirection(Qt::RightToLeft);
        label_revolve_range->setAutoFillBackground(false);
        label_revolve_period = new QLabel(config_setting);
        label_revolve_period->setObjectName(QString::fromUtf8("label_revolve_period"));
        label_revolve_period->setGeometry(QRect(900, 335, 210, 50));
        label_revolve_period->setFont(font1);
        label_revolve_period->setLayoutDirection(Qt::RightToLeft);
        label_revolve_period->setAutoFillBackground(false);
        label_extra_item_info = new QLabel(config_setting);
        label_extra_item_info->setObjectName(QString::fromUtf8("label_extra_item_info"));
        label_extra_item_info->setGeometry(QRect(900, 465, 210, 50));
        label_extra_item_info->setFont(font1);
        label_extra_item_info->setLayoutDirection(Qt::RightToLeft);
        label_extra_item_info->setAutoFillBackground(false);
        label_image_quality = new QLabel(config_setting);
        label_image_quality->setObjectName(QString::fromUtf8("label_image_quality"));
        label_image_quality->setGeometry(QRect(900, 400, 210, 50));
        label_image_quality->setFont(font1);
        label_image_quality->setLayoutDirection(Qt::RightToLeft);
        label_image_quality->setAutoFillBackground(false);
        label_reset_time = new QLabel(config_setting);
        label_reset_time->setObjectName(QString::fromUtf8("label_reset_time"));
        label_reset_time->setGeometry(QRect(900, 530, 210, 50));
        label_reset_time->setFont(font1);
        label_reset_time->setLayoutDirection(Qt::RightToLeft);
        label_reset_time->setAutoFillBackground(false);
        label_brightness = new QLabel(config_setting);
        label_brightness->setObjectName(QString::fromUtf8("label_brightness"));
        label_brightness->setGeometry(QRect(900, 595, 210, 50));
        label_brightness->setFont(font1);
        label_brightness->setLayoutDirection(Qt::RightToLeft);
        label_brightness->setAutoFillBackground(false);
        label_cashier_timeout = new QLabel(config_setting);
        label_cashier_timeout->setObjectName(QString::fromUtf8("label_cashier_timeout"));
        label_cashier_timeout->setGeometry(QRect(900, 660, 210, 50));
        label_cashier_timeout->setFont(font1);
        label_cashier_timeout->setLayoutDirection(Qt::RightToLeft);
        label_cashier_timeout->setAutoFillBackground(false);
        lineEdit_revolve_range = new QLineEdit(config_setting);
        lineEdit_revolve_range->setObjectName(QString::fromUtf8("lineEdit_revolve_range"));
        lineEdit_revolve_range->setGeometry(QRect(1120, 270, 150, 50));
        lineEdit_revolve_range->setFont(font);
        lineEdit_revolve_period = new QLineEdit(config_setting);
        lineEdit_revolve_period->setObjectName(QString::fromUtf8("lineEdit_revolve_period"));
        lineEdit_revolve_period->setGeometry(QRect(1120, 335, 100, 50));
        lineEdit_revolve_period->setFont(font);
        lineEdit_reset_time = new QLineEdit(config_setting);
        lineEdit_reset_time->setObjectName(QString::fromUtf8("lineEdit_reset_time"));
        lineEdit_reset_time->setGeometry(QRect(1120, 530, 150, 50));
        lineEdit_reset_time->setFont(font);
        lineEdit_cashier_timeout = new QLineEdit(config_setting);
        lineEdit_cashier_timeout->setObjectName(QString::fromUtf8("lineEdit_cashier_timeout"));
        lineEdit_cashier_timeout->setGeometry(QRect(1120, 660, 100, 50));
        lineEdit_cashier_timeout->setFont(font);
        label_settings = new QLabel(config_setting);
        label_settings->setObjectName(QString::fromUtf8("label_settings"));
        label_settings->setGeometry(QRect(900, 735, 210, 50));
        label_settings->setFont(font1);
        label_settings->setLayoutDirection(Qt::RightToLeft);
        label_settings->setAutoFillBackground(false);
        cb_settings = new QComboBox(config_setting);
        cb_settings->setObjectName(QString::fromUtf8("cb_settings"));
        cb_settings->setGeometry(QRect(1120, 735, 150, 50));
        cb_settings->setFont(font);
        sec_revolve_period = new QLabel(config_setting);
        sec_revolve_period->setObjectName(QString::fromUtf8("sec_revolve_period"));
        sec_revolve_period->setGeometry(QRect(1220, 335, 50, 50));
        sec_revolve_period->setFont(font);
        gridLayoutWidget = new QWidget(config_setting);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(420, 360, 412, 421));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gridLayoutWidget->sizePolicy().hasHeightForWidth());
        gridLayoutWidget->setSizePolicy(sizePolicy);
        gridLayoutWidget->setMinimumSize(QSize(150, 0));
        QFont font2;
        font2.setPointSize(40);
        gridLayoutWidget->setFont(font2);
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
        pushButton_2->setFont(font2);
        pushButton_2->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt2_up.png);"));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(gridLayoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setMinimumSize(QSize(95, 95));
        pushButton_3->setMaximumSize(QSize(95, 95));
        pushButton_3->setFont(font2);
        pushButton_3->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt3_up.png);"));

        gridLayout->addWidget(pushButton_3, 0, 2, 1, 1);

        pushButton_4 = new QPushButton(gridLayoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
        pushButton_4->setMinimumSize(QSize(95, 95));
        pushButton_4->setMaximumSize(QSize(95, 95));
        pushButton_4->setFont(font2);
        pushButton_4->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt4_up.png);"));

        gridLayout->addWidget(pushButton_4, 1, 0, 1, 1);

        pushButton_5 = new QPushButton(gridLayoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        sizePolicy.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy);
        pushButton_5->setMinimumSize(QSize(95, 95));
        pushButton_5->setMaximumSize(QSize(95, 95));
        pushButton_5->setFont(font2);
        pushButton_5->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt5_up.png);"));

        gridLayout->addWidget(pushButton_5, 1, 1, 1, 1);

        pushButton_6 = new QPushButton(gridLayoutWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        sizePolicy.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy);
        pushButton_6->setMinimumSize(QSize(95, 95));
        pushButton_6->setMaximumSize(QSize(95, 95));
        pushButton_6->setFont(font2);
        pushButton_6->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt6_up.png);"));

        gridLayout->addWidget(pushButton_6, 1, 2, 1, 1);

        pushButton_7 = new QPushButton(gridLayoutWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        sizePolicy.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy);
        pushButton_7->setMinimumSize(QSize(95, 95));
        pushButton_7->setMaximumSize(QSize(95, 95));
        pushButton_7->setFont(font2);
        pushButton_7->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt7_up.png);"));

        gridLayout->addWidget(pushButton_7, 2, 0, 1, 1);

        pushButton_8 = new QPushButton(gridLayoutWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        sizePolicy.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy);
        pushButton_8->setMinimumSize(QSize(95, 95));
        pushButton_8->setMaximumSize(QSize(95, 95));
        pushButton_8->setFont(font2);
        pushButton_8->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt8_up.png);"));

        gridLayout->addWidget(pushButton_8, 2, 1, 1, 1);

        pushButton_9 = new QPushButton(gridLayoutWidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        sizePolicy.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy);
        pushButton_9->setMinimumSize(QSize(95, 95));
        pushButton_9->setMaximumSize(QSize(95, 95));
        pushButton_9->setFont(font2);
        pushButton_9->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt9_up.png);"));

        gridLayout->addWidget(pushButton_9, 2, 2, 1, 1);

        pushButton_1 = new QPushButton(gridLayoutWidget);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setEnabled(true);
        sizePolicy.setHeightForWidth(pushButton_1->sizePolicy().hasHeightForWidth());
        pushButton_1->setSizePolicy(sizePolicy);
        pushButton_1->setMinimumSize(QSize(95, 95));
        pushButton_1->setMaximumSize(QSize(95, 95));
        pushButton_1->setFont(font2);
        pushButton_1->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt1_up.png);"));

        gridLayout->addWidget(pushButton_1, 0, 0, 1, 1);

        pushButton_ac = new QPushButton(gridLayoutWidget);
        pushButton_ac->setObjectName(QString::fromUtf8("pushButton_ac"));
        sizePolicy.setHeightForWidth(pushButton_ac->sizePolicy().hasHeightForWidth());
        pushButton_ac->setSizePolicy(sizePolicy);
        pushButton_ac->setMinimumSize(QSize(95, 95));
        pushButton_ac->setMaximumSize(QSize(95, 95));
        pushButton_ac->setFont(font2);
        pushButton_ac->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/btac_up.png);"));

        gridLayout->addWidget(pushButton_ac, 3, 0, 1, 1);

        pushButton_0 = new QPushButton(gridLayoutWidget);
        pushButton_0->setObjectName(QString::fromUtf8("pushButton_0"));
        sizePolicy.setHeightForWidth(pushButton_0->sizePolicy().hasHeightForWidth());
        pushButton_0->setSizePolicy(sizePolicy);
        pushButton_0->setMinimumSize(QSize(95, 95));
        pushButton_0->setMaximumSize(QSize(95, 95));
        pushButton_0->setFont(font2);
        pushButton_0->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/bt0_up.png);"));

        gridLayout->addWidget(pushButton_0, 3, 1, 1, 1);

        pushButton_del = new QPushButton(gridLayoutWidget);
        pushButton_del->setObjectName(QString::fromUtf8("pushButton_del"));
        sizePolicy.setHeightForWidth(pushButton_del->sizePolicy().hasHeightForWidth());
        pushButton_del->setSizePolicy(sizePolicy);
        pushButton_del->setMinimumSize(QSize(95, 95));
        pushButton_del->setMaximumSize(QSize(95, 95));
        pushButton_del->setFont(font2);
        pushButton_del->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/btdel_up.png);"));

        gridLayout->addWidget(pushButton_del, 3, 2, 1, 1);

        pushButton_minus = new QPushButton(gridLayoutWidget);
        pushButton_minus->setObjectName(QString::fromUtf8("pushButton_minus"));
        pushButton_minus->setMinimumSize(QSize(95, 95));
        pushButton_minus->setMaximumSize(QSize(95, 95));
        pushButton_minus->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/minus_up.png);"));

        gridLayout->addWidget(pushButton_minus, 3, 3, 1, 1);

        pushButton_colon = new QPushButton(gridLayoutWidget);
        pushButton_colon->setObjectName(QString::fromUtf8("pushButton_colon"));
        pushButton_colon->setMinimumSize(QSize(95, 95));
        pushButton_colon->setMaximumSize(QSize(95, 95));
        pushButton_colon->setStyleSheet(QString::fromUtf8("border-image: url(:/pic/colon_down.png);"));

        gridLayout->addWidget(pushButton_colon, 2, 3, 1, 1);


        retranslateUi(config_setting);

        cb_savingtime->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(config_setting);
    } // setupUi

    void retranslateUi(QDialog *config_setting)
    {
        config_setting->setWindowTitle(QApplication::translate("config_setting", "Dialog", 0, QApplication::UnicodeUTF8));
        lineEdit_local_server->setText(QString());
        lineEdit_store_name->setText(QString());
        lineEdit_time_zone->setText(QString());
        lineEdit_openning_time->setText(QString());
        lineEdit_closing_time->setText(QString());
        lineEdit_image_time->setText(QString());
        lineEdit_e2_timeout->setText(QString());
        lineEdit_alarm_interval->setText(QString());
        label_localserver->setText(QApplication::translate("config_setting", "Local Server:", 0, QApplication::UnicodeUTF8));
        label_store_name->setText(QApplication::translate("config_setting", "Store Name:", 0, QApplication::UnicodeUTF8));
        label_closing_time->setText(QApplication::translate("config_setting", "Closing Time:", 0, QApplication::UnicodeUTF8));
        label_openning_time->setText(QApplication::translate("config_setting", "Openning Time:", 0, QApplication::UnicodeUTF8));
        label_working_mode->setText(QApplication::translate("config_setting", "Working Mode:", 0, QApplication::UnicodeUTF8));
        label_saving_time->setText(QApplication::translate("config_setting", "Saving Time:", 0, QApplication::UnicodeUTF8));
        label_camera_type->setText(QApplication::translate("config_setting", "Camera Type:", 0, QApplication::UnicodeUTF8));
        label_time_zone->setText(QApplication::translate("config_setting", "Time Zone:", 0, QApplication::UnicodeUTF8));
        label_image_time->setText(QApplication::translate("config_setting", "Image Time:", 0, QApplication::UnicodeUTF8));
        label_is_number->setText(QApplication::translate("config_setting", "IS Number:", 0, QApplication::UnicodeUTF8));
        label_alarm_interval->setText(QApplication::translate("config_setting", "Alarm Interval:", 0, QApplication::UnicodeUTF8));
        label_e2_timeout->setText(QApplication::translate("config_setting", "E2 Timeout:", 0, QApplication::UnicodeUTF8));
        button_modify_settings->setText(QApplication::translate("config_setting", "Modify Settings", 0, QApplication::UnicodeUTF8));
        button_return->setText(QApplication::translate("config_setting", "Return", 0, QApplication::UnicodeUTF8));
        button_read_default_settings->setText(QApplication::translate("config_setting", "Read Default Settings", 0, QApplication::UnicodeUTF8));
        cb_savingtime->clear();
        cb_savingtime->insertItems(0, QStringList()
         << QApplication::translate("config_setting", "NONE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "USA", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "EUROPE", 0, QApplication::UnicodeUTF8)
        );
        cb_working_mode->clear();
        cb_working_mode->insertItems(0, QStringList()
         << QApplication::translate("config_setting", "Single", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "Cartvu", 0, QApplication::UnicodeUTF8)
        );
        cb_camera_type->clear();
        cb_camera_type->insertItems(0, QStringList()
         << QApplication::translate("config_setting", "PAL", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "NTSC", 0, QApplication::UnicodeUTF8)
        );
        cb_is_number->clear();
        cb_is_number->insertItems(0, QStringList()
         << QApplication::translate("config_setting", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "3", 0, QApplication::UnicodeUTF8)
        );
        cb_alarm_mode->clear();
        cb_alarm_mode->insertItems(0, QStringList()
         << QApplication::translate("config_setting", "Single", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "Cycle", 0, QApplication::UnicodeUTF8)
        );
        cb_alarm_id->clear();
        cb_alarm_id->insertItems(0, QStringList()
         << QApplication::translate("config_setting", "0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "5", 0, QApplication::UnicodeUTF8)
        );
        cb_alarm_volume->clear();
        cb_alarm_volume->insertItems(0, QStringList()
         << QApplication::translate("config_setting", "0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "9", 0, QApplication::UnicodeUTF8)
        );
        cb_standby_mode->clear();
        cb_standby_mode->insertItems(0, QStringList()
         << QApplication::translate("config_setting", "CARTVU", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "CONTINUOUS PICTURE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "REVOLVE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "USER DEFINE", 0, QApplication::UnicodeUTF8)
        );
        cb_image_quality->clear();
        cb_image_quality->insertItems(0, QStringList()
         << QApplication::translate("config_setting", "High", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "Medium", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "Poor", 0, QApplication::UnicodeUTF8)
        );
        cb_extra_item_info->clear();
        cb_extra_item_info->insertItems(0, QStringList()
         << QApplication::translate("config_setting", "No", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "Yes", 0, QApplication::UnicodeUTF8)
        );
        cb_brightness->clear();
        cb_brightness->insertItems(0, QStringList()
         << QApplication::translate("config_setting", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "9", 0, QApplication::UnicodeUTF8)
        );
        sec_cashier_timeout->setText(QApplication::translate("config_setting", "Sec", 0, QApplication::UnicodeUTF8));
        sec_e2_timeout->setText(QApplication::translate("config_setting", "Sec", 0, QApplication::UnicodeUTF8));
        sec_alarm_interval->setText(QApplication::translate("config_setting", "Sec", 0, QApplication::UnicodeUTF8));
        sec_image_time->setText(QApplication::translate("config_setting", "Sec", 0, QApplication::UnicodeUTF8));
        label_alarm_mode->setText(QApplication::translate("config_setting", "Alarm Mode:", 0, QApplication::UnicodeUTF8));
        label_alarm_id->setText(QApplication::translate("config_setting", "Alarm ID:", 0, QApplication::UnicodeUTF8));
        label_alarm_volume->setText(QApplication::translate("config_setting", "Alarm Volume:", 0, QApplication::UnicodeUTF8));
        label_standby_mode->setText(QApplication::translate("config_setting", "Standby Mode:", 0, QApplication::UnicodeUTF8));
        label_revolve_range->setText(QApplication::translate("config_setting", "Revolve Range:", 0, QApplication::UnicodeUTF8));
        label_revolve_period->setText(QApplication::translate("config_setting", "Revolve Period:", 0, QApplication::UnicodeUTF8));
        label_extra_item_info->setText(QApplication::translate("config_setting", "Extra Item Info:", 0, QApplication::UnicodeUTF8));
        label_image_quality->setText(QApplication::translate("config_setting", "Image Quality:", 0, QApplication::UnicodeUTF8));
        label_reset_time->setText(QApplication::translate("config_setting", "Reset Time:", 0, QApplication::UnicodeUTF8));
        label_brightness->setText(QApplication::translate("config_setting", "Brightness:", 0, QApplication::UnicodeUTF8));
        label_cashier_timeout->setText(QApplication::translate("config_setting", "Cashier Timeout:", 0, QApplication::UnicodeUTF8));
        lineEdit_revolve_range->setText(QString());
        lineEdit_revolve_period->setText(QString());
        lineEdit_reset_time->setText(QString());
        lineEdit_cashier_timeout->setText(QString());
        label_settings->setText(QApplication::translate("config_setting", "Settings:", 0, QApplication::UnicodeUTF8));
        cb_settings->clear();
        cb_settings->insertItems(0, QStringList()
         << QApplication::translate("config_setting", "0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("config_setting", "1", 0, QApplication::UnicodeUTF8)
        );
        sec_revolve_period->setText(QApplication::translate("config_setting", "Sec", 0, QApplication::UnicodeUTF8));
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
        pushButton_minus->setText(QString());
        pushButton_colon->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class config_setting: public Ui_config_setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIG_SETTING_H
