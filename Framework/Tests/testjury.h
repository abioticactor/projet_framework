#ifndef TESTJURY_H
#define TESTJURY_H

#include "Model/jury.h"

class TestJury
{
public:
    TestJury();
    static void runTests();
    static void testConstructeur();
    static void testSetters();
    static void testVerifDispo();
};

#endif // TESTJURY_H
