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
    static void testGetSetClasse();
    static void testGetSetOptions();
    static void testAjouterDisponibiliteEtudiant();
    static void testRetirerDisponibiliteEtudiant();
    static void testGetDisponibilitesEtudiant();
    static void testAssignationStage();
    static void testGetSetStage();
};

#endif // ETUDIANTTEST_H
