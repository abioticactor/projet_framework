#include "jury.h"

Jury::Jury() {}

Jury::Jury(Enseignant* president, Enseignant* cojury) {
    this->president=president;
    this->cojury=cojury;
}

Enseignant Jury::getCojury(){
    return *cojury;
}

Enseignant Jury::getPresident(){
    return *president;
}

void Jury::setCojury(Enseignant* cojury){
    this->cojury=cojury;
}

void Jury::setPresident(Enseignant* president){
    this->president=president;
}

bool Jury::verifDispo(){
    bool etat=false;
    for (int i=0;i<this->getPresident().getDisponibilites().getTaille();i++){
        for (int j=0;j<this->getCojury().getDisponibilites().getTaille();j++){
            if (this->getPresident().getDisponibilites().getCalendrier()[i]==this->getCojury().getDisponibilites().getCalendrier()[j]){
                etat=true;
            }
        }
    }
    return etat;
}
