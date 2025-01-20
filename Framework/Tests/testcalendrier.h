#ifndef TESTCALENDRIER_H
#define TESTCALENDRIER_H

#include "Model/calendrier.h"
#include <iostream>

class TestCalendrier
{
public:
    TestCalendrier();
    static void runTests();
    static void testAjouteRetireCreneau();
    static void testDispo();
    static void testTri();
};

#endif // TESTCALENDRIER_H
