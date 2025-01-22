#include "stage.h"

// Constructeur
Stage::Stage(const std::string& entreprise, const std::string& titre, const std::shared_ptr<Enseignant>& tuteur)
    : entreprise(entreprise), titre(titre), tuteur(tuteur) {}

// Gestion de l'entreprise
std::string Stage::getEntreprise() const {
    return entreprise;
}

void Stage::setEntreprise(const std::string& entreprise) {
    this->entreprise = entreprise;
}

// Gestion du titre
std::string Stage::getTitre() const {
    return titre;
}

void Stage::setTitre(const std::string& titre) {
    this->titre = titre;
}

// Gestion du tuteur
std::shared_ptr<Enseignant> Stage::getTuteur() const {
    return tuteur;
}

void Stage::setTuteur(const std::shared_ptr<Enseignant>& tuteur) {
    this->tuteur = tuteur;
}


