#include "Model/enseignant.h"

// Constructeur
Enseignant::Enseignant(const std::string& nom, const std::string& prenom, const std::vector<std::string>& competences)
    : Personne(nom, prenom), competences(competences) {}

// Ajouter une compétence
void Enseignant::ajouterCompetence(const std::string& competence) {
    // Vérifie si la compétence est déjà présente
    if (std::find(competences.begin(), competences.end(), competence) == competences.end()) {
        competences.push_back(competence);
    }
}

// Récupérer les compétences
std::vector<std::string> Enseignant::getCompetences() const {
    return competences;
}

// Vérifier si une compétence est possédée
bool Enseignant::possedeCompetence(const std::string& competence) const {
    return std::find(competences.begin(), competences.end(), competence) != competences.end();
}
