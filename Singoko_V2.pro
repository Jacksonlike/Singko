#-------------------------------------------------
#
# Project created by QtCreator 2017-08-01T19:25:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += network

TARGET = Singoko_V2
TEMPLATE = app


SOURCES += src/chatface/chatwindow.cpp \
    src/chatface/expression.cpp \
    src/contactlist/friend_pushbutton.cpp \
    src/contactlist/toolbox.cpp \
    src/maininterface/widget.cpp \
    src/message/Message.cpp \
    src/message/ownMessage.cpp \
    src/message/udpmessage.cpp \
    src/message/userMessage.cpp \
    src/socket/mysocket.cpp \
    src/main.cpp \
    src/maininterface/lineedit.cpp

HEADERS  += inc/chatface/chatwindow.h \
    inc/chatface/expression.h \
    inc/contactslist/friend_pushbutton.h \
    inc/contactslist/toolbox.h \
    inc/maininterface/widget.h \
    inc/message/Message.h \
    inc/message/ownMessage.h \
    inc/message/userMessage.h \
    inc/socket/mysocket.h \
    inc/socket/udpmessage.h \
    inc/contactslist/groupwidget.h \
    inc/maininterface/lineedit.h

INCLUDEPATH += inc/chatface \
    inc/contactslist \
    inc/maininterface \
    inc/message \
    inc/socket


FORMS += \
    ui/chatwindow.ui \
    ui/expression.ui \
    ui/maininterface.ui

RESOURCES += \
    resource/iamage.qrc
