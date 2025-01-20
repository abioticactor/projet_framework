#ifndef INTEGRATIONTEST_H
#define INTEGRATIONTEST_H

#include "Model/etudiant.h"
#include "Model/enseignant.h"
#include "Model/stage.h"
#include "Model/enseignantstage.h"
#include <cassert>
#include <iostream>

class IntegrationTest {
public:
    static void runTests();

private:
    static void testLinkingEntities();
};

#endif // INTEGRATIONTEST_H
