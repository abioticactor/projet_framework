#include "Tests/enseignanttest.h"

void EnseignantTest::runTests() {
    std::cout << "\nDEBUT des tests pour la Classe ENSEIGNANT\n" << std::endl;
    testConstructeur();
    testAjouterCompetence();
    testPossedeCompetence();
    testAjouterRetirerDispo();
    std::cout << "\nDEBUT des tests pour la Classe ENSEIGNANT\n" << std::endl;
}

void EnseignantTest::testConstructeur() {
    Enseignant enseignant("Morlet", "Lucas", {"Mathématiques", "Physique"});
    int score=0;
    if (enseignant.getNom() == "Morlet"){
        //std::cout << "Test getNom: OK " << std::endl;
        score+=1;
    }
    if (enseignant.getPrenom() == "Lucas"){
        //std::cout << "Test getPrenom: OK " << std::endl;
        score+=1;
    }
    if (enseignant.getCompetences().size() == 2){
        //std::cout << "Test getNbCompetences: OK " << std::endl;
        score+=1;
    }
    if (enseignant.getCompetences()[0] == "Mathématiques"){
        //std::cout << "Test getCompetence1: OK " << std::endl;
        score+=1;
    }
    if (enseignant.getCompetences()[1] == "Physique"){
        //std::cout << "Test getCompetence2: OK " << std::endl;
        score+=1;
    }
    std::cout << "Test Constructeur: " << score << "/5" << std::endl;
}

void EnseignantTest::testAjouterCompetence() {
    Enseignant enseignant("Trenchant", "Vincent");
    enseignant.ajouterCompetence("Informatique");
    enseignant.ajouterCompetence("Mathématiques");
    enseignant.ajouterCompetence("Informatique"); // Doublon, ne doit pas être ajouté
    int score=0;
    if (enseignant.getCompetences().size() == 2){
        //std::cout << "Test getNbCompetence: OK " << std::endl;
        score+=1;
    }
    if (enseignant.getCompetences()[0] == "Informatique"){
        //std::cout << "Test getCompetence1: OK " << std::endl;
        score+=1;
    }
    if (enseignant.getCompetences()[1] == "Mathématiques"){
        //std::cout << "Test getCompetence2: OK " << std::endl;
        score+=1;
    }
    std::cout << "Test AjouterCompetence: " << score << "/3" << std::endl;
}

void EnseignantTest::testPossedeCompetence() {
    Enseignant enseignant("Boubaker", "Bader", {"Physique", "Informatique"});
    int score=0;
    if (enseignant.possedeCompetence("Informatique")){
        //std::cout << "Test PossedeCompetenceV: OK " << std::endl;
        score+=1;
    }
    if (!enseignant.possedeCompetence("Mathématiques")){
        //std::cout << "Test PossedeCompetenceF: OK " << std::endl;
        score+=1;
    }
    std::cout << "Test PossedeCompetence: " << score << "/2" << std::endl;
}

void EnseignantTest::testAjouterRetirerDispo() {
    Enseignant enseignant("Renut", "Damien");
    auto creneau1 = std::make_shared<Creneau>("2025-01-01", "10:00");
    auto creneau2 = std::make_shared<Creneau>("2025-01-01", "10:00"); // Même créneau
    auto creneau3 = std::make_shared<Creneau>("2025-01-04", "14:00");

    enseignant.ajouterDisponibilite(creneau1);
    enseignant.ajouterDisponibilite(creneau2); // Ne doit pas être ajouté
    enseignant.ajouterDisponibilite(creneau3);

    auto disponibilites = enseignant.getDisponibilites().getCalendrier();
    int score=0;

    if (disponibilites.size() == 2){
        //std::cout << "Test AjouterCompetencesTaille: OK " << std::endl;
        score+=1;
    }
    if (disponibilites[0]->getDate() == "2025-01-01"){
        //std::cout << "Test AjouterCompetencesDate1: OK " << std::endl;
        score+=1;
    }
    if (disponibilites[0]->getHeure() == "10:00"){
        //std::cout << "Test AjouterCompetencesHeure1: OK " << std::endl;
        score+=1;
    }

    enseignant.retirerDisponibilite(creneau1);
    auto disponibilites2 = enseignant.getDisponibilites().getCalendrier();

    if (disponibilites2.size() == 1){
        //std::cout << "Test RetirerCompetencesTaille: OK " << std::endl;
        score+=1;
    }
    if (disponibilites2[0]->getDate() == "2025-01-04"){
        //std::cout << "Test RetirerCompetencesDate1: OK " << std::endl;
        score+=1;
    }
    if (disponibilites2[0]->getHeure() == "14:00"){
        //std::cout << "Test RetirerCompetencesHeure1: OK " << std::endl;
        score+=1;
    }

    std::cout << "Test AjouterRetirerDispo: " << score << "/6" << std::endl;
}

