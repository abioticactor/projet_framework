#include "mainwindow.h"
#include "Tests/personnetest.h"
#include "Tests/enseignanttest.h"
#include "Tests/etudianttest.h"


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

    //Test classe Etudiant
    EtudiantTest::runTests();

    return 0;
}
