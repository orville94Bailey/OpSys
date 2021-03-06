#-------------------------------------------------
#
# Project created by QtCreator 2014-08-29T22:21:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = op_sys_part1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    quitwindow.cpp \
    datewindow.cpp \
    directorywindow.cpp \
    helpwindow.cpp \
    pcb.cpp \
    pcblist.cpp \
    pcbwindow.cpp \
    pcbshower.cpp \
    processschedulers.cpp \
    qpcbcontroller.cpp \
    quantumdefinewindow.cpp \
    ticketdefine.cpp

HEADERS  += mainwindow.h \
    quitwindow.h \
    datewindow.h \
    directorywindow.h \
    helpwindow.h \
    pcb.h \
    enums.h \
    pcblist.h \
    pcbwindow.h \
    pcbshower.h \
    processschedulers.h \
    qpcbcontroller.h \
    quantumdefinewindow.h \
    ticketdefine.h

FORMS    += mainwindow.ui \
    quitwindow.ui \
    datewindow.ui \
    directorywindow.ui \
    helpwindow.ui \
    pcbwindow.ui \
    pcbshower.ui \
    processschedulers.ui \
    qpcbcontroller.ui \
    quantumdefinewindow.ui \
    ticketdefine.ui
