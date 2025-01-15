#include "Personne.h"

int Personne::identifiant = 0;

Personne::Personne(std::string nom, std::string prenom) {
    this->nom = nom;
    this->prenom = prenom;
    this->id = ++identifiant;
}

std::string Personne::getNom() const {
    return nom;
}

void Personne::setNom(std::string nom) {
    this->nom = nom;
}

std::string Personne::getPrenom() const {
    return prenom;
}

void Personne::setPrenom(std::string prenom) {
    this->prenom = prenom;
}

int Personne::getId() const {
    return id;
}
