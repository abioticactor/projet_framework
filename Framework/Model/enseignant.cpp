#include "Model/enseignant.h"

// Constructeur
Enseignant::Enseignant(const std::string& nom, const std::string& prenom, const std::vector<std::string>& competences)
    : Personne(nom, prenom), competences(competences) {}

// Gestion des créneaux
void Enseignant::ajouterDisponibilite(Creneau* creneau) {
    if (calendrier.estDispo(creneau)) {
        calendrier.ajouteCreneau(creneau);
    } else {
        std::cout << "Le créneau " << creneau->getDate() << " " << creneau->getHeure()
        << " existe déjà dans le calendrier." << std::endl;
    }
}


void Enseignant::retirerDisponibilite(Creneau* creneau) {
    calendrier.retireCreneau(creneau);
}

Calendrier Enseignant::getDisponibilites() const {
    return this->calendrier;
}

// Gestion des compétences
void Enseignant::ajouterCompetence(const std::string& competence) {
    if (std::find(competences.begin(), competences.end(), competence) == competences.end()) {
        competences.push_back(competence);
    }
}

std::vector<std::string> Enseignant::getCompetences() const {
    return competences;
}

bool Enseignant::possedeCompetence(const std::string& competence) const {
    return std::find(competences.begin(), competences.end(), competence) != competences.end();
}
