#include "testcalendrier.h"

TestCalendrier::TestCalendrier() {}

void TestCalendrier::runTests() {
    std::cout << "\nDEBUT des tests pour la Classe CALENDRIER\n " << std::endl;
    testAjouteRetireCreneau();
    testDispo();
    testTri();
    std::cout << "\nFIN des tests pour la Classe CALENDRIER\n " << std::endl;
}

void TestCalendrier::testAjouteRetireCreneau() {
    auto creneau1 = std::make_shared<Creneau>("2024-12-14", "10:45");
    auto creneau2 = std::make_shared<Creneau>("2024-12-15", "12:45");
    Calendrier c = Calendrier();
    c.ajouteCreneau(creneau1);
    c.ajouteCreneau(creneau2);
    int score = 0;
    if (c.getCalendrier()[0] == creneau1) {
        score += 1;
    }
    if (c.getTaille() == 2) {
        score += 1;
    }

    c.retireCreneau(creneau1);

    if (c.getCalendrier()[0] == creneau2) {
        score += 1;
    }
    if (c.getTaille() == 1) {
        score += 1;
    }
    std::cout << "Test AjouteRetireCreneau: " << score << "/4" << std::endl;
}

void TestCalendrier::testDispo() {
    auto creneau1 = std::make_shared<Creneau>("2024-12-14", "10:45");
    auto creneau2 = std::make_shared<Creneau>("2024-12-15", "12:45");
    auto creneau3 = std::make_shared<Creneau>("2024-12-14", "10:45");
    Calendrier c = Calendrier();
    c.ajouteCreneau(creneau1);
    int score = 0;
    if (c.estDispo(creneau2)) {
        score += 1;
    }
    if (!c.estDispo(creneau3)) {
        score += 1;
    }
    std::cout << "Test Dispo: " << score << "/2" << std::endl;
}

void TestCalendrier::testTri() {
    int score = 0;
    auto creneau1 = std::make_shared<Creneau>("2024-12-14", "10:45");
    auto creneau2 = std::make_shared<Creneau>("2024-12-14", "11:45");
    auto creneau3 = std::make_shared<Creneau>("2024-12-15", "12:45");
    auto creneau4 = std::make_shared<Creneau>("2024-12-16", "09:45");
    Calendrier c_ordo = Calendrier();
    Calendrier c_desordo = Calendrier();
    c_ordo.ajouteCreneau(creneau1);
    c_ordo.ajouteCreneau(creneau2);
    c_ordo.ajouteCreneau(creneau3);
    c_ordo.ajouteCreneau(creneau4);
    c_desordo.ajouteCreneau(creneau1);
    c_desordo.ajouteCreneau(creneau3);
    c_desordo.ajouteCreneau(creneau4);
    c_desordo.ajouteCreneau(creneau2);
    c_desordo.triCreneau();
    for (int i = 0; i < c_ordo.getTaille(); i++) {
        if (c_ordo.getCalendrier()[i] == c_desordo.getCalendrier()[i]) {
            score += 1;
        }
    }
    std::cout << "Test Tri: " << score << "/4" << std::endl;
}
