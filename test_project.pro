QT -= gui
QT += core
QT += mqtt

INCLUDEPATH += /home/toicuteee/qtmqtt/build/src/mqtt


CONFIG += c++17 console
CONFIG -= app_bundle
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        mqqt.cpp \      
        pipeline_new.cpp
CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
        mqqt.h \
        pipeline_new.h

