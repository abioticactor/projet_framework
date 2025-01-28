#ifndef ETUDIANTTEST_H
#define ETUDIANTTEST_H

#include "Model/etudiant.h"
#include <cassert> // Pour les assertions
#include <iostream> // Pour les affichages dans les tests

class EtudiantTest {
public:
    // Méthode pour exécuter tous les tests
    static void runTests();

private:
    // Tests individuels
    static void testConstructeur();
    static void testSetters();
    static void testAjouterRetirerDispo();
};

#endif // ETUDIANTTEST_H
