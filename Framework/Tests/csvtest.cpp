#include "Tests/csvtest.h"

void CSVTest::runTests() {
    std::cout << "Démarrage des tests pour la classe CSVHandler...\n";
    testCSVExtraction();
    std::cout << "Tous les tests pour la classe CSVHandler ont réussi avec succès !\n";
}

/*void CSVTest::testCSVExtraction() {
    // Conteneurs pour stocker les données extraites
    std::vector<std::shared_ptr<Etudiant>> etudiants;
    std::vector<std::shared_ptr<Stage>> stages;
    std::vector<std::shared_ptr<Enseignant>> enseignants;
    std::vector<std::shared_ptr<EnseignantStage>> enseignantStages;

    // Chemin vers le fichier CSV
    const std::string cheminFichier = "/Users/tomroyer/Downloads/stage_s7.csv";

    // Création de l'instance de CSVHandler
    CSVHandler csvHandler(cheminFichier);

    // Extraction des informations
    csvHandler.extraireInformations(etudiants, stages, enseignants, enseignantStages);

    // Vérification des données extraites
    assert(!etudiants.empty());
    assert(!stages.empty());
    assert(!enseignants.empty());
    assert(!enseignantStages.empty());

    // Affichage des données extraites pour validation visuelle
    std::cout << "Données extraites :\n";

    for (const auto& etudiant : etudiants) {
        std::cout << "Etudiant : " << etudiant->getNom() << " " << etudiant->getPrenom() << "\n";
        if (auto stage = etudiant->getStage()) {
            std::cout << "  Stage : " << stage->getTitre() << " chez " << stage->getEntreprise() << "\n";
            if (auto tuteur = stage->getTuteur()) {
                std::cout << "  Tuteur ESEO : " << tuteur->getNom() << "\n";
            }
        }
    }

    for (const auto& enseignant : enseignants) {
        std::cout << "Enseignant : " << enseignant->getNom() << "\n";
    }

    for (const auto& stage : stages) {
        std::cout << "Stage : " << stage->getTitre() << " chez " << stage->getEntreprise() << "\n";
    }

    /*for (const auto& enseignantStage : enseignantStages) {
        std::cout << "Enseignant lié au stage : "
                  << enseignantStage->getEnseignant()->getNom() << " - "
                  << enseignantStage->getStage()->getTitre() << "\n";
    }*/

    //std::cout << "Test CSV Extraction : OK\n";
//}

void CSVTest::testCSVExtraction() {
    std::vector<std::shared_ptr<Etudiant>> etudiants;
    std::vector<std::shared_ptr<Stage>> stages;
    std::vector<std::shared_ptr<Enseignant>> enseignants;

    const std::string cheminFichier = "/Users/corentinjozwiak/Downloads/stage_s7.csv";

    CSVHandler csvHandler(cheminFichier);
    csvHandler.extraireInformations(etudiants, stages, enseignants);

    // Vérification des données extraites
    assert(!etudiants.empty());
    assert(!stages.empty());
    assert(!enseignants.empty());

    // Affichage des données extraites pour validation visuelle
    std::cout << "Données extraites :\n";

    for (const auto& etudiant : etudiants) {
        std::cout << "Etudiant : " << etudiant->getNom() << " " << etudiant->getPrenom() << "\n";
        if (auto stage = etudiant->getStage()) {
            std::cout << "  Stage : " << stage->getTitre() << " chez " << stage->getEntreprise() << "\n";
            if (auto tuteur = stage->getTuteur()) {
                std::cout << "  Tuteur : " << tuteur->getNom() << "\n";
            }
        }
    }

    for (const auto& enseignant : enseignants) {
        std::cout << "Enseignant : " << enseignant->getNom() << "\n";
    }

    for (const auto& stage : stages) {
        std::cout << "Stage : " << stage->getTitre() << " chez " << stage->getEntreprise() << "\n";
    }

    std::cout << "Test CSV Extraction : OK\n";
}

