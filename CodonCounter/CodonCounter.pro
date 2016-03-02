#-------------------------------------------------
#
# Project created by QtCreator 2016-02-25T08:00:50
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = CodonCounter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        Sequence.cpp \
        qcustomplot.cpp

HEADERS  += mainwindow.h \
         Sequence.h \
         qcustomplot.h

FORMS    += mainwindow.ui
