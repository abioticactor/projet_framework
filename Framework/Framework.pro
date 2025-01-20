QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/matrice.cpp \
    Model/calendrier.cpp \
    Model/creneau.cpp \
    Model/enseignant.cpp \
    Model/enseignantstage.cpp \
    Model/etudiant.cpp \
    Model/personne.cpp \
    Model/stage.cpp \
    Tests/enseignantstagetest.cpp \
    Tests/enseignanttest.cpp \
    Tests/etudianttest.cpp \
    Tests/integrationtest.cpp \
    Tests/personnetest.cpp \
    Tests/stagetest.cpp \
    Tests/testcalendrier.cpp \
    Tests/testcreneau.cpp \
    View/personneview.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Controller/matrice.h \
    Model/calendrier.h \
    Model/creneau.h \
    Model/enseignant.h \
    Model/enseignantstage.h \
    Model/etudiant.h \
    Model/personne.h \
    Model/stage.h \
    Tests/enseignantstagetest.h \
    Tests/enseignanttest.h \
    Tests/etudianttest.h \
    Tests/integrationtest.h \
    Tests/personnetest.h \
    Tests/stagetest.h \
    Tests/testcalendrier.h \
    Tests/testcreneau.h \
    View/personneview.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
