#ifndef SOUTENANCETEST_H
#define SOUTENANCETEST_H

#include "Model/soutenance.h"
#include <cassert>
#include <iostream>

class SoutenanceTest {
public:
    // Méthode principale pour exécuter tous les tests
    static void runTests();

private:
    // Tests individuels
    static void testAjouterEtudiant();
    static void testAjouterJury();
    static void testVerifierDisponibilites();
    static void testAffecterJury();
};

#endif // SOUTENANCETEST_H
