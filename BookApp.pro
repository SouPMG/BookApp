#-------------------------------------------------
#
# Project created by QtCreator 2016-06-07T21:25:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BookApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    libraryitem.cpp \
    book.cpp \
    ebook.cpp \
    library.cpp

HEADERS  += mainwindow.h \
    libraryitem.h \
    book.h \
    ebook.h \
    library.h

FORMS    += mainwindow.ui

RESOURCES += \
    library.qrc
