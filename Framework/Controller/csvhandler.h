#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include "Model/etudiant.h"
#include "Model/stage.h"
#include "Model/enseignantstage.h"
#include <string>
#include <vector>
#include <memory>

class CSVHandler {
private:
    std::string cheminFichier; // Chemin du fichier CSV

public:
    // Constructeur
    explicit CSVHandler(const std::string& cheminFichier);

    // Méthode principale pour lire le fichier et organiser les données
    void extraireInformations(std::vector<std::shared_ptr<Etudiant>>& etudiants,
                              std::vector<std::shared_ptr<Stage>>& stages,
                              std::vector<std::shared_ptr<Enseignant>>& enseignants,
                              std::vector<std::shared_ptr<EnseignantStage>>& enseignantStages);

private:
    // Méthode pour découper une ligne CSV en plusieurs champs
    std::vector<std::string> decouperLigne(const std::string& ligne, char separateur = ',');

    // Vérifie si une chaîne est vide ou non
    bool estVide(const std::string& chaine);
};

#endif // CSVHANDLER_H
