#include "Tests/enseignanttest.h"

void EnseignantTest::runTests() {
    std::cout << "Démarrage des tests pour la classe Enseignant...\n";
    testConstructeur();
    testAjouterCompetence();
    testGetCompetences();
    testPossedeCompetence();
    testAjouterDisponibilite();
    testRetirerDisponibilite();
    std::cout << "Tous les tests de la classe Enseignant ont réussi avec succès !\n";
}

void EnseignantTest::testConstructeur() {
    Enseignant enseignant("Morlet", "Lucas", {"Mathématiques", "Physique"});
    assert(enseignant.getNom() == "Morlet");
    assert(enseignant.getPrenom() == "Lucas");
    assert(enseignant.getCompetences().size() == 2);
    assert(enseignant.getCompetences()[0] == "Mathématiques");
    assert(enseignant.getCompetences()[1] == "Physique");
    std::cout << "Test constructeur : OK\n";
}

void EnseignantTest::testAjouterCompetence() {
    Enseignant enseignant("Trenchant", "Vincent");
    enseignant.ajouterCompetence("Informatique");
    enseignant.ajouterCompetence("Mathématiques");
    enseignant.ajouterCompetence("Informatique"); // Doublon, ne doit pas être ajouté

    assert(enseignant.getCompetences().size() == 2);
    assert(enseignant.getCompetences()[0] == "Informatique");
    assert(enseignant.getCompetences()[1] == "Mathématiques");
    std::cout << "Test ajouterCompetence : OK\n";
}

void EnseignantTest::testGetCompetences() {
    Enseignant enseignant("Schlinquer", "Thomas", {"Chimie", "Biologie"});
    std::vector<std::string> competences = enseignant.getCompetences();

    assert(competences.size() == 2);
    assert(competences[0] == "Chimie");
    assert(competences[1] == "Biologie");
    std::cout << "Test getCompetences : OK\n";
}

void EnseignantTest::testPossedeCompetence() {
    Enseignant enseignant("Boubaker", "Bader", {"Physique", "Informatique"});

    assert(enseignant.possedeCompetence("Physique") == true);
    assert(enseignant.possedeCompetence("Mathématiques") == false);
    std::cout << "Test possedeCompetence : OK\n";
}

void EnseignantTest::testAjouterDisponibilite() {
    Enseignant enseignant("Mignot", "Romain");
    Creneau* creneau1 = new Creneau("2025-01-01", "10:00");
    Creneau* creneau2 = new Creneau("2025-01-01", "10:00"); // Même créneau

    enseignant.ajouterDisponibilite(creneau1);
    enseignant.ajouterDisponibilite(creneau2); // Ne doit pas être ajouté

    auto disponibilites = enseignant.getDisponibilites();
    assert(disponibilites.size() == 1);
    assert(disponibilites[0]->getDate() == "2025-01-01");
    assert(disponibilites[0]->getHeure() == "10:00");

    delete creneau1;
    delete creneau2;

    std::cout << "Test ajouterDisponibilite : OK\n";
}

void EnseignantTest::testRetirerDisponibilite() {
    Enseignant enseignant("Renut", "Damien");
    Creneau* creneau1 = new Creneau("2025-01-03", "10:00");
    Creneau* creneau2 = new Creneau("2025-01-04", "14:00");

    enseignant.ajouterDisponibilite(creneau1);
    enseignant.ajouterDisponibilite(creneau2);
    enseignant.retirerDisponibilite(creneau1);

    auto disponibilites = enseignant.getDisponibilites();
    assert(disponibilites.size() == 1);
    assert(disponibilites[0]->getDate() == "2025-01-04");

    delete creneau1;
    delete creneau2;

    std::cout << "Test retirerDisponibilite : OK\n";
}


