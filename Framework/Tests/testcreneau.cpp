#include "testcreneau.h"

TestCreneau::TestCreneau() {}

void TestCreneau::runTests(){
    std::cout << "\nDEBUT des tests pour la Classe CRENEAU\n " << std::endl;
    testConstructeur();
    testSetters();
    testOperateurs();
    std::cout << "\nFIN des tests pour la Classe CRENEAU\n " << std::endl;
}

void TestCreneau::testConstructeur(){
    Creneau creneau=Creneau("14/10/24","10:45");
    int score=0;
    if (creneau.getDate()=="14/10/24"){
        //std::cout << "Test getDate: OK" << std::endl;
        score+=1;
    }
    if (creneau.getHeure()=="10:45"){
        //std::cout << "Test getHeure: OK" << std::endl;
        score+=1;
    }
    std::cout << "Test Constructeur: " << score << "/2" << std::endl;
}

void TestCreneau::testSetters(){
    Creneau creneau=Creneau("14/10/24","10:45");
    creneau.setDate("16/12/24");
    creneau.setHeure("11:00");
    int score=0;
    if (creneau.getDate()=="16/12/24"){
        //std::cout << "Test setDate: OK" << std::endl;
        score+=1;
    }
    if (creneau.getHeure()=="11:00"){
        //std::cout << "Test setHeure: OK" << std::endl;
        score+=1;
    }
    std::cout << "Test Setters: " << score << "/2" << std::endl;
}

void TestCreneau::testOperateurs(){
    Creneau c1=Creneau("14/10/24","10:45");
    Creneau c2=Creneau("14/10/24","10:45");

    Creneau c3=Creneau("14/10/24","11:00");
    Creneau c4=Creneau("15/10/24","09:00");

    Creneau c5=Creneau("14/10/24","09:00");
    Creneau c6=Creneau("13/10/24","15:45");

    int score=0;
    if (c1==c2){
        //std::cout << "Test egal: OK" << std::endl;
        score+=1;
    }
    if (c1<c3){
        //std::cout << "Test infH: OK" << std::endl;
        score+=1;
    }
    if (c1<c4){
        //std::cout << "Test infD: OK" << std::endl;
        score+=1;
    }
    if (c1>c5){
        //std::cout << "Test supH: OK" << std::endl;
        score+=1;
    }
    if (c1>c6){
        //std::cout << "Test supD: OK" << std::endl;
        score+=1;
    }
    std::cout << "Test Operateurs: " << score << "/5" << std::endl;
}
