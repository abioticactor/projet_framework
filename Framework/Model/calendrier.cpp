#include "calendrier.h"

Calendrier::Calendrier() {}

void Calendrier::ajouteCreneau(std::shared_ptr<Creneau> c) {
    this->creneaux.push_back(c);
    this->taille = taille + 1;
}

void Calendrier::retireCreneau(std::shared_ptr<Creneau> c) {
    for (auto it = creneaux.begin(); it != creneaux.end(); ++it) {
        if (**it == *c) { // Comparaison des valeurs des créneaux
            creneaux.erase(it); // Supprime le créneau trouvé
            taille -= 1;        // Met à jour la taille
            return;             // Fin de la méthode après suppression
        }
    }
}


std::vector<std::shared_ptr<Creneau>> Calendrier::getCalendrier() const {
    return this->creneaux;
}


int Calendrier::getTaille(){
    return this->taille;
}


bool Calendrier::estDispo(std::shared_ptr<Creneau> c) {
    for (int i = 0; i < this->taille; i++) {
        if (*this->creneaux[i] == *c) { // Utilisation de l'opérateur == de Creneau
            return false;
        }
    }
    return true;
}

void Calendrier::triCreneau() {
    std::sort(creneaux.begin(), creneaux.end(), [](std::shared_ptr<Creneau> a, std::shared_ptr<Creneau> b) {
        if (a->getDate() != b->getDate()) {
            return a->getDate() < b->getDate(); // Tri par date
        }
        return a->getHeure() < b->getHeure();   // Tri par heure si les dates sont identiques
    });
}
