#include "jury.h"

Jury::Jury() {}

Jury::Jury(std::shared_ptr<Enseignant> president, std::shared_ptr<Enseignant> cojury) {
    this->president = president;
    this->cojury = cojury;
}

std::shared_ptr<Enseignant> Jury::getCojury() const {
    return cojury;
}

std::shared_ptr<Enseignant> Jury::getPresident() const {
    return president;
}

void Jury::setCojury(std::shared_ptr<Enseignant> cojury) {
    this->cojury = cojury;
}

void Jury::setPresident(std::shared_ptr<Enseignant> president) {
    this->president = president;
}

bool Jury::verifDispo() {
    bool etat = false;
    for (int i = 0; i < this->getPresident()->getDisponibilites().getTaille(); i++) {
        for (int j = 0; j < this->getCojury()->getDisponibilites().getTaille(); j++) {
            if (this->getPresident()->getDisponibilites().getCalendrier()[i] ==
                this->getCojury()->getDisponibilites().getCalendrier()[j]) {
                etat = true;
            }
        }
    }
    return etat;
}

// Setter/Getter pour le créneau
void Jury::setCreneauAttribue(std::shared_ptr<Creneau> c) {
    m_creneauAttribue = c;
}
std::shared_ptr<Creneau> Jury::getCreneauAttribue() const {
    return m_creneauAttribue;
}
