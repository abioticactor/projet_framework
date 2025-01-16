#include "calendrier.h"

Calendrier::Calendrier() {}

void Calendrier::ajouteCreneau(Creneau* c){
    this->creneaux.push_back(c);
    this->taille=taille+1;
}

/*void Calendrier::retireCreneau(Creneau* c){
    int index=-1;
    Creneau* p_c;
    for (int i=0;i<this->taille;i++){
        p_c=this->creneaux[i];
        if (&p_c==&c){
            index=i;
        }
    }
    if (index!=-1){
        this->creneaux.erase(creneaux.begin()+index-1);
        this->taille=taille-1;
    }
}*/

void Calendrier::retireCreneau(Creneau* c) {
    for (auto it = creneaux.begin(); it != creneaux.end(); ++it) {
        if (**it == *c) {  // Comparaison des valeurs des créneaux
            creneaux.erase(it); // Supprime le créneau trouvé
            taille -= 1;        // Met à jour la taille
            return;             // Fin de la méthode après suppression
        }
    }
}


std::vector<Creneau*> Calendrier::getCalendrier() const{
    return this->creneaux;
}

int Calendrier::getTaille(){
    return this->taille;
}

/*bool Calendrier::estDispo(Creneau* c){
    bool result=true;
    for (int i=0;i<this->taille;i++){
        Creneau* p_c=this->creneaux[i];
        if (&p_c==&c){
            result=false;
        }
    }
    return result;
}*/

bool Calendrier::estDispo(Creneau* c) {
    for (int i = 0; i < this->taille; i++) {
        if (*this->creneaux[i] == *c) {  // Utilisation de l'opérateur == de Creneau
            return false;
        }
    }
    return true;
}


void Calendrier::triCreneau(){
    int t=this->getTaille();
    Calendrier calend;
    while (calend.getTaille()<t){
        Creneau* p_min=this->creneaux[0];
        Creneau min=*p_min;
        for (int i=0;i<this->taille;i++){
            Creneau* p_cren=this->creneaux[i];
            Creneau cren=*p_cren;
            if (cren<min){
                min=cren;
            }
        }
        calend.ajouteCreneau(p_min);
        this->retireCreneau(p_min);
    }
    this->creneaux=calend.getCalendrier();
}
