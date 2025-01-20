#include "Tests/etudianttest.h"

void EtudiantTest::runTests() {
    std::cout << "Démarrage des tests pour la classe Etudiant...\n";
    testConstructeur();
    testGetSetClasse();
    testGetSetOptions();
    testAjouterDisponibiliteEtudiant();
    testRetirerDisponibiliteEtudiant();
    testGetDisponibilitesEtudiant();
    std::cout << "Tous les tests de la classe Etudiant ont réussi avec succès !\n";
}

void EtudiantTest::testConstructeur() {
    Etudiant etudiant("Schmitt", "Jordan", "E4", {"E-sante"});
    assert(etudiant.getNom() == "Schmitt");
    assert(etudiant.getPrenom() == "Jordan");
    assert(etudiant.getClasse() == "E4");
    assert(etudiant.getOptions().size() == 1);
    assert(etudiant.getOptions()[0] == "E-sante");
    std::cout << "Test constructeur : OK\n";
}

void EtudiantTest::testGetSetClasse() {
    Etudiant etudiant("Ramelet", "Nathan", "E4", {});
    assert(etudiant.getClasse() == "E4");
    etudiant.setClasse("E3");
    assert(etudiant.getClasse() == "E3");
    std::cout << "Test get/set Classe : OK\n";
}

void EtudiantTest::testGetSetOptions() {
    Etudiant etudiant("Vardanyan", "Ruben", "E4", {});
    assert(etudiant.getOptions().empty());
    etudiant.setOptions({"Indus 4.0"});
    assert(etudiant.getOptions().size() == 1);
    assert(etudiant.getOptions()[0] == "Indus 4.0");
    std::cout << "Test get/set Options : OK\n";
}

void EtudiantTest::testAjouterDisponibiliteEtudiant() {
    Etudiant etudiant("Barbe", "Clement", "E4", {});
    Creneau* creneau1 = new Creneau("2025-01-01", "10:00");
    Creneau* creneau2 = new Creneau("2025-01-01", "10:00"); // Même créneau

    etudiant.ajouterDisponibiliteEtudiant(creneau1);
    etudiant.ajouterDisponibiliteEtudiant(creneau2); // Ne doit pas être ajouté

    auto disponibilites = etudiant.getDisponibilitesEtudiant();
    assert(disponibilites.size() == 1);
    assert(disponibilites[0]->getDate() == "2025-01-01");
    assert(disponibilites[0]->getHeure() == "10:00");

    std::cout << "Test ajouterDisponibilite : OK\n";
}

void EtudiantTest::testRetirerDisponibiliteEtudiant() {
    Etudiant etudiant("Constant", "Pierre", "E4", {});
    Creneau* creneau1 = new Creneau("2025-01-03", "10:00");
    Creneau* creneau2 = new Creneau("2025-01-04", "14:00");

    etudiant.ajouterDisponibiliteEtudiant(creneau1);
    etudiant.ajouterDisponibiliteEtudiant(creneau2);
    etudiant.retirerDisponibiliteEtudiant(creneau1);

    auto disponibilites = etudiant.getDisponibilitesEtudiant();
    assert(disponibilites.size() == 1);
    assert(disponibilites[0]->getDate() == "2025-01-04");
    assert(disponibilites[0]->getHeure() == "14:00");

    std::cout << "Test retirerDisponibilite : OK\n";
}

void EtudiantTest::testGetDisponibilitesEtudiant() {
    Etudiant etudiant("Martin", "PE", "E4", {});
    Creneau* creneau1 = new Creneau("2025-01-03", "10:00");
    Creneau* creneau2 = new Creneau("2025-01-05", "14:00");

    etudiant.ajouterDisponibiliteEtudiant(creneau1);
    etudiant.ajouterDisponibiliteEtudiant(creneau2);

    auto disponibilites = etudiant.getDisponibilitesEtudiant();
    assert(disponibilites.size() == 2);
    assert(disponibilites[0]->getDate() == "2025-01-03");
    assert(disponibilites[0]->getHeure() == "10:00");
    assert(disponibilites[1]->getDate() == "2025-01-05");
    assert(disponibilites[1]->getHeure() == "14:00");

    std::cout << "Test getDisponibilites : OK\n";
}
