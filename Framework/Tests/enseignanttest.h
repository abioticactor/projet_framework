#ifndef ENSEIGNANTTEST_H
#define ENSEIGNANTTEST_H

#include "Model/enseignant.h"
#include <cassert> // Pour les assertions
#include <iostream> // Pour les affichages dans les tests

class EnseignantTest {
public:
    // Méthode pour exécuter tous les tests
    static void runTests();

private:
    // Tests individuels
    static void testConstructeur();
    static void testAjouterCompetence();
    static void testGetCompetences();
    static void testPossedeCompetence();
};

#endif // ENSEIGNANTTEST_H
