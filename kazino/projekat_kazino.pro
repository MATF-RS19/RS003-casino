#-------------------------------------------------
#
# Project created by QtCreator 2019-01-02T15:12:02
#
#-------------------------------------------------

QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projekat_kazino
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    igrac.cpp \
    igrac_slot.cpp \
    slot.cpp \
    manja_veca.cpp \
    igrac_bj.cpp \
    racunar_bj.cpp \
    black_jack.cpp

HEADERS += \
        mainwindow.h \
    igrac.h \
    igrac_slot.h \
    slot.h \
    manja_veca.h \
    igrac_bj.h \
    racunar_bj.h \
    black_jack.h

FORMS += \
        mainwindow.ui \
    slot.ui \
    manja_veca.ui \
    black_jack.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=
