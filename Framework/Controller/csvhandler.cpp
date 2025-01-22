#include "Controller/csvhandler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

// Constructeur
CSVHandler::CSVHandler(const std::string& cheminFichier) : cheminFichier(cheminFichier) {}


// Découpe une ligne CSV en plusieurs champs
std::vector<std::string> CSVHandler::decouperLigne(const std::string& ligne, char separateur) {
    std::vector<std::string> champs;
    std::stringstream ss(ligne);
    std::string champ;

    while (std::getline(ss, champ, separateur)) {
        champs.push_back(champ);
    }

    return champs;
}


// Vérifie si une chaîne est vide
bool CSVHandler::estVide(const std::string& chaine) {
    return chaine.empty() || chaine.find_first_not_of(" \t\n\r") == std::string::npos;
}

// Méthode principale pour lire le fichier CSV
void CSVHandler::extraireInformations(std::vector<std::shared_ptr<Etudiant>>& etudiants,
                                      std::vector<std::shared_ptr<Stage>>& stages,
                                      std::vector<std::shared_ptr<Enseignant>>& enseignants,
                                      std::vector<std::shared_ptr<EnseignantStage>>& enseignantStages) {
    std::ifstream fichier(cheminFichier, std::ios::binary);
    if (!fichier.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << cheminFichier << std::endl;
        return;
    }
    std::cout << "Fichier ouvert avec succès : " << cheminFichier << std::endl;
    if (!fichier.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << cheminFichier << std::endl;
        return;
    }

    std::unordered_map<std::string, std::shared_ptr<Stage>> mapStages; // Pour éviter les doublons
    std::unordered_map<std::string, std::shared_ptr<Enseignant>> mapEnseignants; // Pour éviter les doublons
    std::string ligne;

    // Lire la première ligne pour ignorer les en-têtes
    std::getline(fichier, ligne);

    while (std::getline(fichier, ligne)) {
        //std::cout << "Ligne lue : " << ligne << std::endl;
        auto champs = decouperLigne(ligne, ';');

        if (champs.size() < 6){
            std::cerr << "Ligne ignorée (mauvais format) : " << ligne << std::endl;
            continue; // Vérification du format (Nom, Prénom, Option, Entreprise, Sujet, Tuteur)
        }

        std::string nom = champs[0];
        std::string prenom = champs[1];
        std::string option = champs[2];
        std::string entreprise = champs[3];
        std::string sujet = champs[4];
        std::string tuteurESEO = champs[5];

        // Affiche les champs découpés
        /*std::cout << "Nom : " << nom << ", Prenom : " << prenom << ", Option : " << option
                  << ", Entreprise : " << entreprise << ", Sujet : " << sujet
                  << ", Tuteur : " << tuteurESEO << std::endl;*/

        // Création ou récupération du stage
        std::string stageKey = entreprise + "-" + sujet;
        if (mapStages.find(stageKey) == mapStages.end()) {
            auto stage = std::make_shared<Stage>(entreprise, sujet, nullptr); // Tuteur ajouté plus tard
            mapStages[stageKey] = stage;
            stages.push_back(stage);
        }
        auto stageAssocie = mapStages[stageKey];

        // Création ou récupération de l'enseignant
        if (mapEnseignants.find(tuteurESEO) == mapEnseignants.end()) {
            auto enseignant = std::make_shared<Enseignant>(tuteurESEO, "", std::vector<std::string>{}); // Pas de prénom ou compétences pour le moment
            mapEnseignants[tuteurESEO] = enseignant;
            enseignants.push_back(enseignant);
        }
        auto enseignantAssocie = mapEnseignants[tuteurESEO];

        // Liaison EnseignantStage
        auto enseignantStage = std::make_shared<EnseignantStage>(enseignantAssocie, stageAssocie);
        enseignantStages.push_back(enseignantStage);

        // Assigner le tuteur au stage
        stageAssocie->setTuteur(enseignantAssocie);

        // Création de l'étudiant
        auto etudiant = std::make_shared<Etudiant>(nom, prenom, "Classe par défaut", std::vector<std::string>{option});
        etudiant->assignerStage(stageAssocie);
        etudiants.push_back(etudiant);
    }

    fichier.close();
}
