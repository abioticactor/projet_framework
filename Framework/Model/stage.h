#ifndef STAGE_H
#define STAGE_H

#include "Model/personne.h"
#include "Model/enseignant.h"

#include <memory>
#include <vector>
#include <string>

class Stage {
private:
    std::string entreprise;                     // Nom de l'entreprise
    std::string titre;                          // Titre du stage
    std::shared_ptr<Enseignant> tuteur;           // Tuteur du stage

public:
    // Constructeur
    Stage(const std::string& entreprise, const std::string& titre, const std::shared_ptr<Enseignant>& tuteur);

    // Gestion de l'entreprise
    std::string getEntreprise() const;
    void setEntreprise(const std::string& entreprise);

    // Gestion du titre
    std::string getTitre() const;
    void setTitre(const std::string& titre);

    /*// Gestion du tuteur
    std::shared_ptr<Personne> getTuteur() const;
    void setTuteur(const std::shared_ptr<Personne>& tuteur);*/

    // Gestion du tuteur
    std::shared_ptr<Enseignant> getTuteur() const;
    void setTuteur(const std::shared_ptr<Enseignant>& tuteur);


};

#endif // STAGE_H
