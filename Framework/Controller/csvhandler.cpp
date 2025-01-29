#include "Controller/csvhandler.h"

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

// Fonction locale pour enlever les espaces de début et de fin
static std::string trim(const std::string& s)
{
    // Trouver le premier caractère non ' ' et le dernier
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
        start++;
    }

    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) {
        end--;
    }

    return s.substr(start, end - start);
}

static std::string normaliserClef(const std::string& texte)
{
    // 1) enlever les espaces de début/fin
    std::string resultat = trim(texte);

    // 2) mettre en minuscules
    std::transform(resultat.begin(), resultat.end(), resultat.begin(),
                   [](unsigned char c){ return static_cast<unsigned char>(std::tolower(c)); });

    return resultat;
}



// Vérifie si une chaîne est vide
bool CSVHandler::estVide(const std::string& chaine) {
    return chaine.empty() || chaine.find_first_not_of(" \t\n\r") == std::string::npos;
}

// Méthode principale pour lire le fichier CSV
void CSVHandler::extraireInformations(std::vector<std::shared_ptr<Etudiant>>& etudiants,
                                      std::vector<std::shared_ptr<Stage>>& stages,
                                      std::vector<std::shared_ptr<Enseignant>>& enseignants) {
    std::ifstream fichier(cheminFichier);
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
        ligne = corrigerEncodage(ligne);
        auto champs = decouperLigne(ligne, ';');

        if (champs.size() < 6) {
            std::cerr << "Ligne ignorée (format incorrect) : " << ligne << "\n";
            continue;
        }

        std::string nom = corrigerEncodage(champs[0]);
        std::string prenom = corrigerEncodage(champs[1]);
        std::string option = corrigerEncodage(champs[2]);
        std::string entreprise = corrigerEncodage(champs[3]);
        std::string sujet = corrigerEncodage(champs[4]);
        std::string tuteurESEO = corrigerEncodage(champs[5]);

        // Création ou récupération de l'enseignant
        /*if (mapEnseignants.find(tuteurESEO) == mapEnseignants.end()) {
            auto enseignant = std::make_shared<Enseignant>(tuteurESEO, "", std::vector<std::string>{});
            mapEnseignants[tuteurESEO] = enseignant;
            enseignants.push_back(enseignant);
        }
        auto enseignantAssocie = mapEnseignants[tuteurESEO];*/

        // On modifie pour normaliser la clef
        std::string clefTuteur = normaliserClef(tuteurESEO);

        if (mapEnseignants.find(clefTuteur) == mapEnseignants.end()) {
            // Créer un Enseignant (dont 'nom' = clef normalisée,
            // ou, si vous préférez, le champ "nom" = l'original tuteurESEO, c'est un choix)
            auto enseignant = std::make_shared<Enseignant>(clefTuteur, "", std::vector<std::string>{});

            mapEnseignants[clefTuteur] = enseignant;
            enseignants.push_back(enseignant);
        }

        auto enseignantAssocie = mapEnseignants[clefTuteur];

        // Création ou récupération du stage
        std::string stageKey = entreprise + "-" + sujet;
        if (mapStages.find(stageKey) == mapStages.end()) {
            auto stage = std::make_shared<Stage>(entreprise, sujet, enseignantAssocie); // Associer directement le tuteur
            mapStages[stageKey] = stage;
            stages.push_back(stage);
        }
        auto stageAssocie = mapStages[stageKey];

        // Création de l'étudiant
        auto etudiant = std::make_shared<Etudiant>(nom, prenom, "Classe par défaut", std::vector<std::string>{option});
        etudiant->assignerStage(stageAssocie);
        etudiants.push_back(etudiant);
    }

    fichier.close();
}


std::string CSVHandler::corrigerEncodage(const std::string& texte) {
    std::string resultat;
    resultat.reserve(texte.size());

    for (size_t i = 0; i < texte.size(); ++i) {
        unsigned char c = texte[i];

        switch (c) {
        case 0xC8: resultat += "É"; break; // È devient É
        case 0xE8: resultat += "è"; break; // è reste è
        case 0xF9: resultat += "ù"; break; // ù reste ù
        case 0xE9: resultat += "é"; break; // é reste é
        case 0xC7: resultat += "Ç"; break; // Ç reste Ç
        case 0x92: // Apostrophe typographique (’)
        case 0x27: // Apostrophe ASCII (')
        case 0xB4: // Accent aigu utilisé comme apostrophe (´)
            resultat += "'"; break; // Remplace toutes par l'apostrophe ASCII
        default: resultat += c; break; // Autres caractères inchangés
        }
    }

    return resultat;
}
