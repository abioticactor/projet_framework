#ifndef TEST_CSV_H
#define TEST_CSV_H

#include "../Controller/csv.h"
#include <cassert>
#include <QDebug>
#include <memory>

// Classe pour organiser les tests de la classe CSV
class TestCSV {
public:
    // Tests unitaires pour chaque méthode
    static void testLireFichier();
    static void testEcrireFichier();
    static void testImporterEnseignants();
    static void testImporterEtudiants();

    // Méthode pour exécuter tous les tests
    static void runAllTests();
};

#endif // TEST_CSV_H
