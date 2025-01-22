#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H

#include "Model/personne.h"
#include "Model/calendrier.h"
#include <vector>
#include <string>
#include <algorithm> // Pour std::find


class Enseignant : public Personne {
private:
    Calendrier calendrier;            // Gestion des créneaux via un calendrier
    std::vector<std::string> competences; // Liste des compétences de l'enseignant

public:
    // Constructeur
    Enseignant(const std::string& nom, const std::string& prenom, const std::vector<std::string>& competences = {});

    // Gestion des créneaux
    void ajouterDisponibilite(Creneau* creneau);
    void retirerDisponibilite(Creneau* creneau);
    Calendrier getDisponibilites() const;

    // Gestion des compétences
    void ajouterCompetence(const std::string& competence);
    std::vector<std::string> getCompetences() const;
    bool possedeCompetence(const std::string& competence) const;
};

#endif // ENSEIGNANT_H
