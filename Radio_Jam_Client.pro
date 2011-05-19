#-------------------------------------------------
#
# Project created by QtCreator 2011-04-28T15:19:26
#
#-------------------------------------------------

QT       += core gui network phonon

TARGET = Radio_Jam_Client
TEMPLATE = app


SOURCES += main.cpp\
        radio_jam_client.cpp \
    thread_lien_serveur.cpp \
    thread_reception.cpp

HEADERS  += radio_jam_client.h \
    thread_lien_serveur.h \
    thread_reception.h

FORMS    += radio_jam_client.ui
