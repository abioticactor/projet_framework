#include "Tests/soutenancetest.h"

void SoutenanceTest::runTests() {
    std::cout << "Démarrage des tests pour la classe Soutenance...\n";

    testAjouterEtudiant();
    testAjouterJury();
    testVerifierDisponibilites();
    testAffecterJury();

    std::cout << "Tous les tests pour la classe Soutenance ont réussi avec succès !\n";
}

void SoutenanceTest::testAjouterEtudiant() {
    Soutenance soutenance;
    auto etudiant = std::make_shared<Etudiant>("Royer", "Tom", "E4", std::vector<std::string>{"Informatique"});

    soutenance.ajouterEtudiant(etudiant);
    const auto& etudiants = soutenance.getEtudiants();

    assert(etudiants.size() == 1);
    assert(etudiants[0]->getNom() == "Royer");
    assert(etudiants[0]->getPrenom() == "Tom");

    std::cout << "Test ajouterEtudiant : OK\n";
}

void SoutenanceTest::testAjouterJury() {
    Soutenance soutenance;
    auto president = std::make_shared<Enseignant>("Dupont", "Marie", std::vector<std::string>{"Mathématiques"});
    auto cojury = std::make_shared<Enseignant>("Martin", "Paul", std::vector<std::string>{"Physique"});

    auto jury = std::make_shared<Jury>(president, cojury);
    soutenance.ajouterJury(jury);
    const auto& jurys = soutenance.getJurys();

    assert(jurys.size() == 1);
    assert(jurys[0]->getPresident()->getNom() == "Dupont");
    assert(jurys[0]->getCojury()->getNom() == "Martin");

    std::cout << "Test ajouterJury : OK\n";
}

void SoutenanceTest::testVerifierDisponibilites() {
    Soutenance soutenance;
    auto creneau = std::make_shared<Creneau>("2025-01-01", "10:00");

    auto president = std::make_shared<Enseignant>("Dupont", "Marie", std::vector<std::string>{"Mathématiques"});
    auto cojury = std::make_shared<Enseignant>("Martin", "Paul", std::vector<std::string>{"Physique"});

    president->ajouterDisponibilite(creneau);
    cojury->ajouterDisponibilite(creneau);

    auto jury = std::make_shared<Jury>(president, cojury);

    auto etudiant = std::make_shared<Etudiant>("Royer", "Tom", "E4", std::vector<std::string>{"Informatique"});
    etudiant->ajouterDisponibiliteEtudiant(creneau);

    bool dispo = soutenance.verifierDisponibilites(*etudiant, *jury);
    assert(dispo);

    std::cout << "Test verifierDisponibilites : OK\n";
}

void SoutenanceTest::testAffecterJury() {
    Soutenance soutenance;
    auto creneau = std::make_shared<Creneau>("2025-01-01", "10:00");

    // Création d'un tuteur pour le stage
    auto tuteur = std::make_shared<Enseignant>("Dupont", "Marie", std::vector<std::string>{"Mathématiques"});
    tuteur->ajouterDisponibilite(creneau);

    // Création d'un co-jury
    auto cojury = std::make_shared<Enseignant>("Martin", "Paul", std::vector<std::string>{"Physique"});
    cojury->ajouterDisponibilite(creneau);

    // Création de l'étudiant et de son stage
    auto etudiant = std::make_shared<Etudiant>("Royer", "Tom", "E4", std::vector<std::string>{"Informatique"});
    auto stage = std::make_shared<Stage>("Google", "Développement IA", tuteur);
    etudiant->assignerStage(stage);
    etudiant->ajouterDisponibiliteEtudiant(creneau);

    // Liste des enseignants disponibles
    std::vector<std::shared_ptr<Enseignant>> enseignants = {tuteur, cojury};

    // Test d'affectation
    bool affectation = soutenance.affecterJury(*etudiant, enseignants);
    assert(affectation);

    const auto& jurys = soutenance.getJurys();
    assert(jurys.size() == 1);
    assert(jurys[0]->getPresident()->getNom() == "Dupont");
    assert(jurys[0]->getCojury()->getNom() == "Martin");

    std::cout << "Test affecterJury : OK\n";
}
