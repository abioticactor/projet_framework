#include "mainwindow.h"
#include "Tests/personnetest.h"
#include "Tests/enseignanttest.h"
#include "Tests/testcreneau.h"
#include "Tests/testcalendrier.h"
#include "Tests/etudianttest.h"
#include "Tests/stagetest.h"
#include "Tests/enseignantstagetest.h"
#include "Tests/csvtest.h"
#include "Tests/testjury.h"
#include "Tests/soutenancetest.h"
#include "Tests/testprojet.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();

    //Test classe Personne
    PersonneTest::runTests();

    //Test classe Enseignant
    EnseignantTest::runTests();

    //Test classe Créneau
    TestCreneau::runTests();

    //Test classe Calendrier
    TestCalendrier::runTests();

    //Test classe Jury
    TestJury::runTests();

    //Test classe Etudiant
    EtudiantTest::runTests();

    //Test classe Stage
    StageTest::runTests();

    //Test classe EnseignantStage
    //EnseignantStageTest::runTests();

    //Test CSV
    CSVTest::runTests();

    //Test Soutenance
    SoutenanceTest::runTests();

    //Test liens
    TestProjet test;
    test.extraireDonnees("/Users/tomroyer/Downloads/stage_s7.csv");
    test.creerEtAssignerCreneaux();
    test.creerJurysEtAffecterEtudiants();
    test.afficherToutesLesSoutenances();

    return 0;
}
