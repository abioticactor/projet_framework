#include "testjury.h"

TestJury::TestJury() {}

void TestJury::runTests(){
    std::cout << "\nDEBUT des tests pour la Classe JURY\n " << std::endl;
    testConstructeur();
    testSetters();
    testVerifDispo();
    std::cout << "\nFIN des tests pour la Classe JURY\n " << std::endl;
}

void TestJury::testConstructeur() {
    auto prez = std::make_shared<Enseignant>("SCHLINQUER", "Thomas");
    auto coj = std::make_shared<Enseignant>("TRENCHANT", "Vincent");
    Jury jury(prez, coj);
    int score = 0;
    if (*jury.getPresident() == *prez) {
        score += 1;
    }
    if (*jury.getCojury() == *coj) {
        score += 1;
    }
    std::cout << "Test Constructeur: " << score << "/2" << std::endl;
}

void TestJury::testSetters() {
    auto thomas = std::make_shared<Enseignant>("SCHLINQUER", "Thomas");
    auto vincent = std::make_shared<Enseignant>("TRENCHANT", "Vincent");
    Jury jury(thomas, vincent);
    jury.setCojury(thomas);
    jury.setPresident(vincent);
    int score = 0;
    if (*jury.getPresident() == *vincent) {
        score += 1;
    }
    if (*jury.getCojury() == *thomas) {
        score += 1;
    }
    std::cout << "Test Setters: " << score << "/2" << std::endl;
}

void TestJury::testVerifDispo() {
    auto thomas = std::make_shared<Enseignant>("SCHLINQUER", "Thomas");
    auto vincent = std::make_shared<Enseignant>("TRENCHANT", "Vincent");
    Jury jury(thomas, vincent);
    auto c1 = std::make_shared<Creneau>("12/01/25", "10:00");
    auto c2 = std::make_shared<Creneau>("13/01/25", "10:00");
    auto c3 = std::make_shared<Creneau>("12/01/25", "13:00");
    auto c4 = std::make_shared<Creneau>("14/01/25", "13:00");

    thomas->ajouterDisponibilite(c1);
    thomas->ajouterDisponibilite(c2);
    thomas->ajouterDisponibilite(c3);
    vincent->ajouterDisponibilite(c1);
    vincent->ajouterDisponibilite(c4);

    int score = 0;
    if (jury.verifDispo()) {
        score += 1;
    }
    vincent->retirerDisponibilite(c1);
    if (!jury.verifDispo()) {
        score += 1;
    }
    std::cout << "Test VerifDispo: " << score << "/2" << std::endl;
}
