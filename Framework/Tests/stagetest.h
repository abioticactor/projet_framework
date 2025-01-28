#ifndef STAGETEST_H
#define STAGETEST_H

#include "Model/stage.h"
#include <cassert>
#include <iostream>

class StageTest {
public:
    // Méthode pour exécuter tous les tests
    static void runTests();

private:
    // Tests individuels
    static void testConstructeur();
    static void testSetters();
};

#endif // STAGETEST_H
