#-------------------------------------------------
#
# Project created by QtCreator 2020-02-26T16:13:37
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Contractor
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
    graficcontainers/graficcontainerlistoffers.cpp \
    dialogs/dlgnewoffer.cpp \
    dto/offerbasedto.cpp \
    dto/agentbasedto.cpp \
    processor/agentprocessor.cpp \
    processor/offerprocessor.cpp \
    config/configuration.cpp \
    config/configbasefunctionality.cpp \
    dbsupport/dbconnection.cpp \
    dbsupport/dbconnectionmanager.cpp \
    dbsupport/dbacccesssafe.cpp \
    processor/agencyprocessor.cpp \
    dto/agencydto.cpp \
    processor/countryprocessor.cpp \
    dto/countrydto.cpp \
    dto/towndto.cpp \
    processor/townprocessor.cpp \
    dto/skilldto.cpp \
    processor/skillprocessor.cpp \
    dto/offerskilldto.cpp \
    processor/offerskillprocesor.cpp \
    dto/statusdto.cpp \
    processor/statusprocessor.cpp \
    graficcontainers/offerstable.cpp \
    operations/offerscaner.cpp \
    menucontainers/mainwindowmenu.cpp \
    menucontainers/offerstablemenu.cpp \
    graficcontainers/graficcontainerlistagent.cpp \
    graficcontainers/agentstable.cpp

HEADERS += \
        mainwindow.h \
    graficcontainers/graficcontainerlistoffers.h \
    dialogs/dlgnewoffer.h \
    dto/offerbasedto.h \
    dto/agentbasedto.h \
    commondef.h \
    processor/agentprocessor.h \
    processor/offerprocessor.h \
    config/configuration.h \
    config/configbasefunctionality.h \
    config/configdef.h \
    dbsupport/dbconnection.h \
    dbsupport/dbconnectionmanager.h \
    dbsupport/dbacccesssafe.h \
    processor/agencyprocessor.h \
    dto/agencydto.h \
    processor/countryprocessor.h \
    dto/countrydto.h \
    dto/towndto.h \
    processor/townprocessor.h \
    dto/skilldto.h \
    processor/skillprocessor.h \
    dto/offerskilldto.h \
    processor/offerskillprocesor.h \
    dto/attractivity.h \
    dto/statusdto.h \
    processor/statusprocessor.h \
    graficcontainers/offerstable.h \
    operations/offerscaner.h \
    menucontainers/mainwindowmenu.h \
    menucontainers/offerstablemenu.h \
    graficcontainers/graficcontainerlistagent.h \
    graficcontainers/agentstable.h \
    dto/agentrank.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    contractor.cfg \
    scripts/create_database_and_tables.sql
