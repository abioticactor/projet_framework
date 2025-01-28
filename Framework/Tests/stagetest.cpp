#include "Tests/stagetest.h"

void StageTest::runTests() {
    std::cout << "\nDEBUT des tests pour la Classe STAGE\n" << std::endl;
    testConstructeur();
    testSetters();
    std::cout << "\nFIN des tests pour la Classe STAGE\n" << std::endl;
}

void StageTest::testConstructeur() {
    auto tuteur = std::make_shared<Enseignant>("Dupont", "Jean");
    Stage stage("Google", "Développeur", tuteur);
    int score=0;
    if (stage.getEntreprise() == "Google"){
        //std::cout << "Test getEntreprise: OK " << std::endl;
        score+=1;
    }
    if (stage.getTitre() == "Développeur"){
        //std::cout << "Test getTitre: OK " << std::endl;
        score+=1;
    }
    if (stage.getTuteur()->getNom() == "Dupont"){
        //std::cout << "Test getNom: OK " << std::endl;
        score+=1;
    }
    std::cout << "Test Constructeur: " << score << "/3" << std::endl;
}

void StageTest::testSetters() {
    auto tuteur = std::make_shared<Enseignant>("Dupont", "Jean");
    auto tuteur2 = std::make_shared<Enseignant>("Martin", "Paul");
    Stage stage("Google", "Développeur", tuteur);

    stage.setEntreprise("Amazon");
    stage.setTitre("Data Scientist");
    stage.setTuteur(tuteur2);

    int score=0;
    if (stage.getEntreprise() == "Amazon"){
        //std::cout << "Test setEntreprise: OK " << std::endl;
        score+=1;
    }
    if (stage.getTitre() == "Data Scientist"){
        //std::cout << "Test setTitre: OK " << std::endl;
        score+=1;
    }
    if (stage.getTuteur()->getNom() == "Martin"){
        //std::cout << "Test setTuteur: OK " << std::endl;
        score+=1;
    }
    std::cout << "Test Setters: " << score << "/3" << std::endl;
}


