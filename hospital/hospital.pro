#-------------------------------------------------
#
# Project created by QtCreator 2014-05-31T15:42:58
#
#-------------------------------------------------

QT       += core gui
QT       +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hospital
TEMPLATE = app


SOURCES += main.cpp\
        hos_main.cpp \
    sick_bed.cpp \
    patient_manager.cpp \
    personnel_manager.cpp \
    salary.cpp \
    transfer.cpp \
    dept_manager.cpp \
    job_manager.cpp \
    login.cpp \
    chgpwd.cpp

HEADERS  += hos_main.h \
    sick_bed.h \
    patient_manager.h \
    personnel_manager.h \
    salary.h \
    transfer.h \
    dept_manager.h \
    job_manager.h \
    login.h \
    chgpwd.h

FORMS    += hos_main.ui \
    sick_bed.ui \
    patient_manager.ui \
    personnel_manager.ui \
    salary.ui \
    transfer.ui \
    dept_manager.ui \
    job_manager.ui \
    login.ui \
    chgpwd.ui
