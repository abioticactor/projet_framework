#include "testjury.h"

TestJury::TestJury() {}

void TestJury::runTests(){
    std::cout << "\nDEBUT des tests pour la Classe JURY\n " << std::endl;
    testConstructeur();
    testSetters();
    testVerifDispo();
    std::cout << "\nFIN des tests pour la Classe JURY\n " << std::endl;
}

void TestJury::testConstructeur(){
    Enseignant prez=Enseignant("SCHLINQUER","Thomas");
    Enseignant coj=Enseignant("TRENCHANT","Vincent");
    Enseignant* p_prez=(Enseignant*) &prez;
    Enseignant* p_coj=(Enseignant*) &coj;
    Jury jury=Jury(p_prez,p_coj);
    int score=0;
    if (jury.getPresident()==prez){
        score+=1;
    }
    if (jury.getCojury()==coj){
        score+=1;
    }
    std::cout << "Test Constructeur: " << score << "/2" << std::endl;
}

void TestJury::testSetters(){
    Enseignant thomas=Enseignant("SCHLINQUER","Thomas");
    Enseignant vincent=Enseignant("TRENCHANT","Vincent");
    Enseignant* p_prez=(Enseignant*) &thomas;
    Enseignant* p_coj=(Enseignant*) &vincent;
    Jury jury=Jury(p_prez,p_coj);
    jury.setCojury(&thomas);
    jury.setPresident(&vincent);
    int score=0;
    if (jury.getPresident()==vincent){
        score+=1;
    }
    if (jury.getCojury()==thomas){
        score+=1;
    }
    std::cout << "Test Setters: " << score << "/2" << std::endl;
}

void TestJury::testVerifDispo(){
    Enseignant thomas=Enseignant("SCHLINQUER","Thomas");
    Enseignant vincent=Enseignant("TRENCHANT","Vincent");
    Enseignant* p_prez=(Enseignant*) &thomas;
    Enseignant* p_coj=(Enseignant*) &vincent;
    Jury jury=Jury(p_prez,p_coj);
    Creneau c1=Creneau("12/01/25","10:00");
    Creneau c2=Creneau("13/01/25","10:00");
    Creneau c3=Creneau("12/01/25","13:00");
    Creneau c4=Creneau("14/01/25","13:00");
    thomas.ajouterDisponibilite(&c1);
    thomas.ajouterDisponibilite(&c2);
    thomas.ajouterDisponibilite(&c3);
    vincent.ajouterDisponibilite(&c1);
    vincent.ajouterDisponibilite(&c4);
    int score=0;
    if (jury.verifDispo()){
        score+=1;
    }
    vincent.retirerDisponibilite(&c1);
    if (!jury.verifDispo()){
        score+=1;
    }
    std::cout << "Test VerifDispo: " << score << "/2" << std::endl;
}
