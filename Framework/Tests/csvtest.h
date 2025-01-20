#ifndef CSVTEST_H
#define CSVTEST_H

#include "Controller/csvhandler.h"
#include <cassert>
#include <iostream>

class CSVTest {
public:
    // Méthode pour exécuter tous les tests
    static void runTests();

private:
    // Test individuel
    static void testCSVExtraction();
};

#endif // CSVTEST_H
