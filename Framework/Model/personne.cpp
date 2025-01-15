#include "Personne.h"

// Initialisation de la variable statique
int Personne::identifiant = 0;


// Constructeur
Personne::Personne(std::string nom, std::string prenom) {
    this->nom = nom;
    this->prenom = prenom;
    this->id = ++identifiant;// Génération automatique d'un identifiant unique
}

// Getters
std::string Personne::getNom() const {
    return nom;
}

void Personne::setNom(std::string nom) {
    this->nom = nom;
}

std::string Personne::getPrenom() const {
    return prenom;
}

// Setters
void Personne::setPrenom(std::string prenom) {
    this->prenom = prenom;
}

int Personne::getId() const {
    return id;
}
