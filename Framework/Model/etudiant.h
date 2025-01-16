#ifndef ETUDIANT_H
#define ETUDIANT_H

#include "Model/personne.h"
#include "Model/calendrier.h"
#include <vector>
#include <memory>
#include <string>

class Etudiant : public Personne {
private:
    std::string classe;                     // Classe de l'étudiant
    std::vector<std::string> options;       // Liste des options choisies
    Calendrier calendrier;            // Gestion des créneaux via un calendrier

public:
    // Constructeur
    Etudiant(const std::string& nom, const std::string& prenom, const std::string& classe, const std::vector<std::string>& options);

    // Gestion des créneaux via le calendrier
    void ajouterDisponibiliteEtudiant(Creneau* creneau);
    void retirerDisponibiliteEtudiant(Creneau* creneau);
    std::vector<Creneau*> getDisponibilitesEtudiant() const;

    // Gestion des options
    std::vector<std::string> getOptions() const;
    void setOptions(const std::vector<std::string>& options);

    // Gestion de la classe
    std::string getClasse() const;
    void setClasse(const std::string& classe);
};

#endif // ETUDIANT_H
