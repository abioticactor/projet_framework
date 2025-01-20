#include "testcalendrier.h"

TestCalendrier::TestCalendrier() {}

void TestCalendrier::runTests(){
    std::cout << "\nDEBUT des tests pour la Classe CALENDRIER\n " << std::endl;
    testAjouteRetireCreneau();
    testDispo();
    testTri();
    std::cout << "\nFIN des tests pour la Classe CALENDRIER\n " << std::endl;
}

void TestCalendrier::testAjouteRetireCreneau(){
    Creneau creneau1=Creneau("14/10/24","10:45");
    Creneau creneau2=Creneau("15/10/24","12:45");
    Calendrier c=Calendrier();
    c.ajouteCreneau(&creneau1);
    c.ajouteCreneau(&creneau2);
    int score=0;
    if (c.getCalendrier()[0]==&creneau1){
        //std::cout << "Test getCalendrierAjouter: OK" << std::endl;
        score+=1;
    }
    if (c.getTaille()==2){
        //std::cout << "Test getTailleAjouter: OK" << std::endl;
        score+=1;
    }

    c.retireCreneau(&creneau1);

    if (c.getCalendrier()[0]==&creneau2){
        //std::cout << "Test getCalendrierRetirer: OK" << std::endl;
        score+=1;
    }
    if (c.getTaille()==1){
        //std::cout << "Test getTailleRetirer: OK" << std::endl;
        score+=1;
    }
    std::cout << "Test AjouteRetireCreneau: " << score << "/4" << std::endl;
}

void TestCalendrier::testDispo(){
    Creneau creneau1=Creneau("14/10/24","10:45");
    Creneau creneau2=Creneau("15/10/24","12:45");
    Creneau creneau3=Creneau("14/10/24","10:45");
    Calendrier c=Calendrier();
    c.ajouteCreneau(&creneau1);
    int score=0;
    if (c.estDispo(&creneau2)){
        //std::cout << "Test estDipoV: OK" << std::endl;
        score+=1;
    }
    if (!c.estDispo(&creneau3)){
        //std::cout << "Test estDipoF: OK" << std::endl;
        score+=1;
    }
    std::cout <<"Test Dispo: " << score << "/2" << std::endl;
}

void TestCalendrier::testTri(){
    int score=0;
    Creneau creneau1=Creneau("14/10/24","10:45");
    Creneau creneau2=Creneau("14/10/24","11:45");
    Creneau creneau3=Creneau("15/10/24","12:45");
    Creneau creneau4=Creneau("16/10/24","09:45");
    Calendrier c_ordo=Calendrier();
    Calendrier c_desordo=Calendrier();
    c_ordo.ajouteCreneau(&creneau1);
    c_ordo.ajouteCreneau(&creneau2);
    c_ordo.ajouteCreneau(&creneau3);
    c_ordo.ajouteCreneau(&creneau4);
    c_desordo.ajouteCreneau(&creneau1);
    c_desordo.ajouteCreneau(&creneau3);
    c_desordo.ajouteCreneau(&creneau4);
    c_desordo.ajouteCreneau(&creneau2);
    c_desordo.triCreneau();
    for (int i=0;i<c_ordo.getTaille();i++){
        if (c_ordo.getCalendrier()[i]==c_desordo.getCalendrier()[i]){
            score+=1;
        }
    }
    std::cout << "Test Tri: " << score << "/4" << std::endl;
}

