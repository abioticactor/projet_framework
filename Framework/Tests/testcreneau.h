#ifndef TESTCRENEAU_H
#define TESTCRENEAU_H

#include "Model/creneau.h"
#include <iostream>

class TestCreneau
{
public:
    TestCreneau();
    static void runTests();
    static void testConstructeur();
    static void testSetters();
    static void testOperateurs();
};

#endif // TESTCRENEAU_H
