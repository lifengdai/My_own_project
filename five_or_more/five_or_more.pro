#-------------------------------------------------
#
# Project created by QtCreator 2017-04-26T09:46:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = five_or_more
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    board.cpp \
    cell.cpp \
    gameEngine.cpp \
    cell_tuple.cpp

HEADERS  += mainwindow.h \
    board.h \
    public.h \
    cell.h \
    gameEngine.h \
    cell_tuple.h

FORMS    += mainwindow.ui
