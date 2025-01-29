QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/csvhandler.cpp \
    Model/calendrier.cpp \
    Model/creneau.cpp \
    Model/enseignant.cpp \
    Model/etudiant.cpp \
    Model/jury.cpp \
    Model/personne.cpp \
    Model/soutenance.cpp \
    Model/stage.cpp \
    Tests/csvtest.cpp \
    Tests/enseignanttest.cpp \
    Tests/etudianttest.cpp \
    Tests/personnetest.cpp \
    Tests/soutenancetest.cpp \
    Tests/stagetest.cpp \
    Tests/testcalendrier.cpp \
    Tests/testcreneau.cpp \
    Tests/testjury.cpp \
    Tests/testprojet.cpp \
    View/creneauxdialog.cpp \
    View/mainwindow.cpp \
    View/planningdialog.cpp \
    main.cpp

HEADERS += \
    Controller/csvhandler.h \
    Model/calendrier.h \
    Model/creneau.h \
    Model/enseignant.h \
    Model/etudiant.h \
    Model/jury.h \
    Model/personne.h \
    Model/soutenance.h \
    Model/stage.h \
    Tests/csvtest.h \
    Tests/enseignanttest.h \
    Tests/etudianttest.h \
    Tests/personnetest.h \
    Tests/soutenancetest.h \
    Tests/stagetest.h \
    Tests/testcalendrier.h \
    Tests/testcreneau.h \
    Tests/testjury.h \
    Tests/testprojet.h \
    View/creneauxdialog.h \
    View/mainwindow.h \
    View/planningdialog.h

FORMS += \
    PlanningDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../../../../../Downloads/stage_s7.csv
