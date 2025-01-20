#include "mainwindow.h"
#include "Tests/personnetest.h"
#include "Tests/enseignanttest.h"
#include "Tests/testcreneau.h"
#include "Tests/testcalendrier.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/

    //Test classe Personne
    PersonneTest::runTests();

    //Test classe Enseignant
    EnseignantTest::runTests();

    //Test classe Créneau
    TestCreneau::runTests();

    //Test classe Calendrier
    TestCalendrier::runTests();

    return 0;
}
