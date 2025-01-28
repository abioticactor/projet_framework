#include "Tests/personnetest.h"

void PersonneTest::runTests() {
    std::cout << "\nDEBUT des tests pour la Classe PERSONNE\n" << std::endl;
    testConstructeur();
    testSetters();
    std::cout << "\nFIN des tests pour la Classe PERSONNE\n" << std::endl;
}

void PersonneTest::testConstructeur() {
    Personne personne("Royer", "Tom");
    Personne personne2("Theuil", "Martin");
    int score=0;
    if (personne.getNom() == "Royer"){
        //std::cout << "Test getNom: OK " << std::endl;
        score+=1;
    }
    if (personne.getPrenom() == "Tom"){
        //std::cout << "Test getPrenom: OK " << std::endl;
        score+=1;
    }
    if (personne.getId() == 1){
        //std::cout << "Test getId: OK " << std::endl;
        score+=1;
    }
    if (personne2.getId() == 2){
        //std::cout << "Test getId2 : OK " << std::endl;
        score+=1;
    }
    std::cout << "Test Constructeur: " << score << "/4" << std::endl;
}

void PersonneTest::testSetters() {
    Personne personne4("Alice", "Smith");
    personne4.setNom("Bob");
    personne4.setPrenom("Brown");
    int score=0;
    if (personne4.getNom()=="Bob"){
        //std::cout << "Test setNom: OK " << std::endl;
        score+=1;
    }
    if (personne4.getPrenom()=="Brown"){
        //std::cout << "Test setPrenom: OK " << std::endl;
        score+=1;
    }
    std::cout << "Test Setters: " << score << "/2" << std::endl;
}


