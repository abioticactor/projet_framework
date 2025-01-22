#include "Tests/stagetest.h"

void StageTest::runTests() {
    std::cout << "Démarrage des tests pour la classe Stage...\n";
    testConstructeur();
    testGetSetEntreprise();
    testGetSetTitre();
    testGetSetTuteur();
    std::cout << "Tous les tests de la classe Stage ont réussi avec succès !\n";
}

void StageTest::testConstructeur() {
    auto tuteur = std::make_shared<Enseignant>("Dupont", "Jean");
    Stage stage("Google", "Développeur", tuteur);

    assert(stage.getEntreprise() == "Google");
    assert(stage.getTitre() == "Développeur");
    assert(stage.getTuteur()->getNom() == "Dupont");
    std::cout << "Test constructeur : OK\n";
}

void StageTest::testGetSetEntreprise() {
    auto tuteur = std::make_shared<Enseignant>("Dupont", "Jean");
    Stage stage("Google", "Développeur", tuteur);

    stage.setEntreprise("Amazon");
    assert(stage.getEntreprise() == "Amazon");
    std::cout << "Test get/set Entreprise : OK\n";
}

void StageTest::testGetSetTitre() {
    auto tuteur = std::make_shared<Enseignant>("Dupont", "Jean");
    Stage stage("Google", "Développeur", tuteur);

    stage.setTitre("Data Scientist");
    assert(stage.getTitre() == "Data Scientist");
    std::cout << "Test get/set Titre : OK\n";
}

void StageTest::testGetSetTuteur() {
    auto tuteur1 = std::make_shared<Enseignant>("Dupont", "Jean");
    auto tuteur2 = std::make_shared<Enseignant>("Martin", "Paul");
    Stage stage("Google", "Développeur", tuteur1);

    stage.setTuteur(tuteur2);
    assert(stage.getTuteur()->getNom() == "Martin");
    std::cout << "Test get/set Tuteur : OK\n";
}
