#ifndef PERSONNETEST_H
#define PERSONNETEST_H

#include "Model/personne.h"
#include <cassert> // Pour les assertions
#include <iostream> // Pour les affichages dans les tests

class PersonneTest {
public:
    // Méthode pour exécuter tous les tests
    static void runTests();

private:
    // Tests individuels
    static void testConstructeur();
    static void testGetNom();
    static void testSetNom();
    static void testGetPrenom();
    static void testSetPrenom();
    static void testGetId();
};

#endif // PERSONNETEST_H
