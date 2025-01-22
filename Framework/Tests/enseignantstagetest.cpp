/*#include "Tests/enseignantstagetest.h"

void EnseignantStageTest::runTests() {
    std::cout << "Démarrage des tests pour la classe EnseignantStage...\n";
    testConstructeur();
    testGetSetEnseignant();
    testGetSetStage();
    std::cout << "Tous les tests de la classe EnseignantStage ont réussi avec succès !\n";
}

void EnseignantStageTest::testConstructeur() {
    auto tuteur = std::make_shared<Personne>("Dupont", "Jean");
    auto enseignant = std::make_shared<Enseignant>("Martin", "Paul", std::vector<std::string>{"Mathématiques"});
    auto stage = std::make_shared<Stage>("Google", "Développeur", tuteur);

    EnseignantStage enseignantStage(enseignant, stage);
    assert(enseignantStage.getEnseignant()->getNom() == "Martin");
    assert(enseignantStage.getStage()->getEntreprise() == "Google");
    std::cout << "Test constructeur : OK\n";
}

void EnseignantStageTest::testGetSetEnseignant() {
    auto tuteur = std::make_shared<Personne>("Dupont", "Jean");
    auto enseignant1 = std::make_shared<Enseignant>("Martin", "Paul", std::vector<std::string>{"Physique"});
    auto enseignant2 = std::make_shared<Enseignant>("Dupont", "Marie", std::vector<std::string>{"Informatique"});
    auto stage = std::make_shared<Stage>("Google", "Développeur", tuteur);

    EnseignantStage enseignantStage(enseignant1, stage);
    enseignantStage.setEnseignant(enseignant2);
    assert(enseignantStage.getEnseignant()->getNom() == "Dupont");
    std::cout << "Test get/set Enseignant : OK\n";
}

void EnseignantStageTest::testGetSetStage() {
    auto tuteur = std::make_shared<Personne>("Dupont", "Jean");
    auto enseignant = std::make_shared<Enseignant>("Martin", "Paul", std::vector<std::string>{"Mathématiques"});
    auto stage1 = std::make_shared<Stage>("Google", "Développeur", tuteur);
    auto stage2 = std::make_shared<Stage>("Amazon", "Cloud Engineer", tuteur);

    EnseignantStage enseignantStage(enseignant, stage1);
    enseignantStage.setStage(stage2);
    assert(enseignantStage.getStage()->getEntreprise() == "Amazon");
    std::cout << "Test get/set Stage : OK\n";
}*/
