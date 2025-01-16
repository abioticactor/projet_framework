#include "csvtest.h"

void TestCSV::testLireFichier() {
    QString cheminFichier = "test_lire.csv";
    QFile file(cheminFichier);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Nom,Prenom,Classe\n";
        out << "Dupont,Jean,3A\n";
        out << "Martin,Claire,4B\n";
        file.close();
    }

    CSV csvHandler(cheminFichier);
    auto data = csvHandler.lireFichier();

    assert(data.size() == 3); // 3 lignes attendues
    assert(data[0].size() == 3); // 3 colonnes attendues
    assert(data[1][0] == "Dupont");
    assert(data[2][2] == "4B");

    file.remove();
    qDebug() << "testLireFichier passé avec succès !";
}

void TestCSV::testEcrireFichier() {
    QString cheminFichier = "test_ecrire.csv";
    std::vector<std::vector<QString>> donnees = {
        {"Nom", "Prenom", "Classe"},
        {"Dupont", "Jean", "3A"},
        {"Martin", "Claire", "4B"}
    };

    CSV csvHandler(cheminFichier);
    assert(csvHandler.ecrireFichier(donnees));

    QFile file(cheminFichier);
    assert(file.open(QIODevice::ReadOnly | QIODevice::Text));

    QTextStream in(&file);
    QString line1 = in.readLine();
    QString line2 = in.readLine();
    QString line3 = in.readLine();

    assert(line1 == "Nom,Prenom,Classe");
    assert(line2 == "Dupont,Jean,3A");
    assert(line3 == "Martin,Claire,4B");

    file.close();
    file.remove();
    qDebug() << "testEcrireFichier passé avec succès !";
}

void TestCSV::testImporterEnseignants() {
    QString cheminFichier = "test_enseignants.csv";
    QFile file(cheminFichier);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "ID,Nom,Prenom\n";
        out << "1,Dupont,Jean\n";
        out << "2,Martin,Claire\n";
        file.close();
    }

    CSV csvHandler(cheminFichier);
    auto enseignants = csvHandler.importerEnseignants();

    assert(enseignants.size() == 2);
    assert(enseignants[0]->getNom() == "Dupont");
    assert(enseignants[0]->getPrenom() == "Jean");
    assert(enseignants[1]->getNom() == "Martin");

    file.remove();
    qDebug() << "testImporterEnseignants passé avec succès !";
}

void TestCSV::testImporterEtudiants() {
    QString cheminFichier = "test_etudiants.csv";
    QFile file(cheminFichier);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "ID,Nom,Prenom,Classe,Option1,Option2\n";
        out << "1,Dupont,Jean,3A,Maths,Physique\n";
        out << "2,Martin,Claire,4B,Chimie,Biologie\n";
        file.close();
    }

    CSV csvHandler(cheminFichier);
    auto etudiants = csvHandler.importerEtudiants();

    assert(etudiants.size() == 2);
    assert(etudiants[0]->getNom() == "Dupont");
    assert(etudiants[0]->getClasse() == "3A");
    assert(etudiants[1]->getNom() == "Martin");

    file.remove();
    qDebug() << "testImporterEtudiants passé avec succès !";
}

void TestCSV::runAllTests() {
    testLireFichier();
    testEcrireFichier();
    testImporterEnseignants();
    testImporterEtudiants();
    qDebug() << "Tous les tests sont passés avec succès !";
}
