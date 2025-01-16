#include "Tests/enseignanttest.h"

void EnseignantTest::runTests() {
    std::cout << "Démarrage des tests pour la classe Enseignant...\n";
    testConstructeur();
    testAjouterCompetence();
    testGetCompetences();
    testPossedeCompetence();
    std::cout << "Tous les tests de la classe Enseignant ont réussi avec succès !\n";
}

void EnseignantTest::testConstructeur() {
    Enseignant enseignant("Dupont", "Marie", {"Mathématiques", "Physique"});
    assert(enseignant.getNom() == "Dupont");
    assert(enseignant.getPrenom() == "Marie");
    assert(enseignant.getCompetences().size() == 2);
    assert(enseignant.getCompetences()[0] == "Mathématiques");
    assert(enseignant.getCompetences()[1] == "Physique");
    assert(enseignant.getId()==8);
    std::cout << "Test constructeur : OK\n";
}

void EnseignantTest::testAjouterCompetence() {
    Enseignant enseignant("Smith", "John");
    enseignant.ajouterCompetence("Informatique");
    enseignant.ajouterCompetence("Mathématiques");
    enseignant.ajouterCompetence("Informatique"); // Doublon, ne doit pas être ajouté

    assert(enseignant.getCompetences().size() == 2);
    assert(enseignant.getCompetences()[0] == "Informatique");
    assert(enseignant.getCompetences()[1] == "Mathématiques");
    std::cout << "Test ajouterCompetence : OK\n";
}

void EnseignantTest::testGetCompetences() {
    Enseignant enseignant("Doe", "Jane", {"Chimie", "Biologie"});
    std::vector<std::string> competences = enseignant.getCompetences();

    assert(competences.size() == 2);
    assert(competences[0] == "Chimie");
    assert(competences[1] == "Biologie");
    std::cout << "Test getCompetences : OK\n";
}

void EnseignantTest::testPossedeCompetence() {
    Enseignant enseignant("Brown", "Emily", {"Physique", "Informatique"});

    assert(enseignant.possedeCompetence("Physique") == true);
    assert(enseignant.possedeCompetence("Mathématiques") == false);
    std::cout << "Test possedeCompetence : OK\n";
}
