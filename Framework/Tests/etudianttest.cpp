#include "Tests/etudianttest.h"

void EtudiantTest::runTests() {
    std::cout << "\nDEBUT des tests pour la Classe ETUDIANT\n" << std::endl;
    testConstructeur();
    testSetters();
    testAjouterRetirerDispo();
    std::cout << "\nFIN des tests pour la Classe ETUDIANT\n" << std::endl;
}

void EtudiantTest::testConstructeur() {
    Etudiant etudiant("Schmitt", "Jordan", "E4", {"E-sante"});
    int score=0;
    if (etudiant.getNom() == "Schmitt"){
        //std::cout << "Test getNom: OK " << std::endl;
        score+=1;
    }
    if (etudiant.getPrenom() == "Jordan"){
        //std::cout << "Test getPrenom: OK " << std::endl;
        score+=1;
    }
    if (etudiant.getClasse() == "E4"){
        //std::cout << "Test getClasse: OK " << std::endl;
        score+=1;
    }
    if (etudiant.getOptions().size() == 1){
        //std::cout << "Test getOptionsTaille: OK " << std::endl;
        score+=1;
    }
    if (etudiant.getOptions()[0] == "E-sante"){
        //std::cout << "Test getOptions1: OK " << std::endl;
        score+=1;
    }
    std::cout << "Test Constructeur: " << score << "/5" << std::endl;
}

void EtudiantTest::testSetters() {
    Etudiant etudiant("Ramelet", "Nathan", "E4", {});
    auto tuteur = std::make_shared<Enseignant>("Dupont", "Marie");
    auto stage1 = std::make_shared<Stage>("Microsoft", "Data Scientist", tuteur);
    etudiant.setClasse("E3");
    etudiant.setOptions({"Indus 4.0"});
    etudiant.setStage(stage1);
    int score=0;
    if (etudiant.getClasse()=="E3"){
        //std::cout << "Test setClasse: OK " << std::endl;
        score+=1;
    }
    if (etudiant.getOptions().size()==1){
        //std::cout << "Test setOptionsTaille: OK " << std::endl;
        score+=1;
    }
    if (etudiant.getOptions()[0]=="Indus 4.0"){
        //std::cout << "Test setOptions1: OK " << std::endl;
        score+=1;
    }
    if (etudiant.getStage()->getTitre()=="Data Scientist"){
        //std::cout << "Test setStageTitre: OK " << std::endl;
        score+=1;
    }
    if (etudiant.getStage()->getEntreprise() == "Microsoft"){
        //std::cout << "Test setStageEntreprise: OK " << std::endl;
        score+=1;
    }
    if (etudiant.getStage()->getTuteur()->getNom() == "Dupont"){
        //std::cout << "Test setStageTuteur: OK " << std::endl;
        score+=1;
    }
    std::cout << "Test Setters: " << score << "/6" << std::endl;
}


void EtudiantTest::testAjouterRetirerDispo() {
    Etudiant etudiant("Ramelet", "Nathan", "E4", {});
    auto creneau1 = std::make_shared<Creneau>("2025-01-01", "10:00");
    auto creneau2 = std::make_shared<Creneau>("2025-01-01", "10:00"); // Même créneau
    auto creneau3 = std::make_shared<Creneau>("2025-01-04", "14:00");

    etudiant.ajouterDisponibiliteEtudiant(creneau1);
    etudiant.ajouterDisponibiliteEtudiant(creneau2); // Ne doit pas être ajouté
    etudiant.ajouterDisponibiliteEtudiant(creneau3);

    auto disponibilites = etudiant.getDisponibilitesEtudiant();
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

    etudiant.retirerDisponibiliteEtudiant(creneau1);
    auto disponibilites2 = etudiant.getDisponibilitesEtudiant();

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


