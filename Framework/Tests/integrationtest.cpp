#include "Tests/integrationtest.h"

void IntegrationTest::runTests() {
    std::cout << "Démarrage des tests d'intégration...\n";
    testLinkingEntities();
    std::cout << "Tous les tests d'intégration ont réussi avec succès !\n";
}

void IntegrationTest::testLinkingEntities() {
    // Création d'un enseignant
    auto enseignant = std::make_shared<Enseignant>("Dupont", "Marie", std::vector<std::string>{"Mathématiques", "Physique"});

    // Création d'un tuteur (Personne)
    auto tuteur = std::make_shared<Personne>("Martin", "Jean");

    // Création d'un stage
    auto stage = std::make_shared<Stage>("Google", "Développeur", tuteur);

    // Liaison entre l'enseignant et le stage via EnseignantStage
    EnseignantStage enseignantStage(enseignant, stage);
    assert(enseignantStage.getEnseignant()->getNom() == "Dupont");
    assert(enseignantStage.getStage()->getTitre() == "Développeur");

    // Création d'un étudiant
    Etudiant etudiant("Schmitt", "Paul", "3A", {"Informatique", "Mathématiques"});

    // Assigner le stage à l'étudiant
    etudiant.assignerStage(stage);
    assert(etudiant.getStage()->getEntreprise() == "Google");
    assert(etudiant.getStage()->getTuteur()->getNom() == "Martin");

    // Vérification finale des relations
    std::cout << "Étudiant : " << etudiant.getNom() << " " << etudiant.getPrenom() << "\n";
    std::cout << "Classe : " << etudiant.getClasse() << "\n";
    std::cout << "Options : ";
    for (const auto& option : etudiant.getOptions()) {
        std::cout << option << " ";
    }
    std::cout << "\nStage : " << etudiant.getStage()->getTitre() << "\n";
    std::cout << "Entreprise : " << etudiant.getStage()->getEntreprise() << "\n";
    std::cout << "Tuteur : " << etudiant.getStage()->getTuteur()->getNom() << " " << etudiant.getStage()->getTuteur()->getPrenom() << "\n";
    std::cout << "Enseignant lié : " << enseignantStage.getEnseignant()->getNom() << " " << enseignantStage.getEnseignant()->getPrenom() << "\n";

    std::cout << "Test linkingEntities : OK\n";
}
