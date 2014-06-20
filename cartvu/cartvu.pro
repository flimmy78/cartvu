# #####################################################################
# Automatically generated by qmake (2.01a) Tue Nov 26 15:12:54 2013
# #####################################################################
TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += camThread.h \
    cartvu.h \
    client.h \
    config_setting.h \
    config_sys.h \
    ftpput.h \
    jpeglib.h \
    light.h \
    login.h \
    MyInputPanel.h \
    MyInputPannelContext.h \
    read_sys.h \
    revolveMode.h \
    sensor.h \
    serialMode.h \
    setting.h \
    synchTime.h \
    ui_cartvuMode.h \
    ui_selfMode.h \
    videodev2_samsung.h \
    watchdog.h \
    recordLog.h \
    strseparate.h
FORMS += cartvu.ui \
    config_setting.ui \
    login.ui \
    MyInputPanelForm.ui \
    revolveMode.ui \
    serialMode.ui \
    setting.ui
SOURCES += camThread.cpp \
    cartvu.cpp \
    client.cpp \
    config_setting.cpp \
    config_sys.cpp \
    ftpput.cpp \
    light.cpp \
    login.cpp \
    main.cpp \
    MyInputPanel.cpp \
    MyInputPannelContext.cpp \
    read_sys.cpp \
    revolveMode.cpp \
    sensor.cpp \
    serialMode.cpp \
    setting.cpp \
    synchTime.cpp \
    watchdog.cpp
RESOURCES += photo.qrc
QT += xml
QT += network
QT += sql
LIBS += -ljpeg \
    -L/work_place/jpeg-8b/tmp/lib \
    -lcrypt
OTHER_FILES += recordLog.inc
