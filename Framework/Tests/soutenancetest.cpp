#include "Tests/soutenancetest.h"

void SoutenanceTest::runTests() {
    std::cout << "\nDEBUT des tests pour la Classe SOUTENANCE\n" << std::endl;
    testAjouterEtudiant();
    testAjouterJury();
    testVerifierDisponibilites();
    testAffecterJury();
    std::cout << "\nFIN des tests pour la Classe SOUTENANCE\n" << std::endl;
}

void SoutenanceTest::testAjouterEtudiant() {
    Soutenance soutenance;
    auto etudiant = std::make_shared<Etudiant>("Royer", "Tom", "E4", std::vector<std::string>{"Informatique"});

    soutenance.ajouterEtudiant(etudiant);
    const auto& etudiants = soutenance.getEtudiants();
    int score=0;

    if (etudiants.size() == 1){
        //std::cout << "Test AjoutEtudiantTaille: OK " << std::endl;
        score+=1;
    }
    if (etudiants[0]->getNom() == "Royer"){
        //std::cout << "Test AjoutEtudiantNom: OK " << std::endl;
        score+=1;
    }
    if (etudiants[0]->getPrenom() == "Tom"){
        //std::cout << "Test AjoutEtudiantPrenom: OK " << std::endl;
        score+=1;
    }

    std::cout << "Test AjouterEtudiant: " << score << "/3" << std::endl;
}

void SoutenanceTest::testAjouterJury() {
    Soutenance soutenance;
    auto president = std::make_shared<Enseignant>("Dupont", "Marie", std::vector<std::string>{"Mathématiques"});
    auto cojury = std::make_shared<Enseignant>("Martin", "Paul", std::vector<std::string>{"Physique"});

    auto jury = std::make_shared<Jury>(president, cojury);
    soutenance.ajouterJury(jury);
    const auto& jurys = soutenance.getJurys();
    int score=0;

    if (jurys.size() == 1){
        //std::cout << "Test AjoutJuryTaille: OK " << std::endl;
        score+=1;
    }
    if (jurys[0]->getPresident()->getNom() == "Dupont"){
        //std::cout << "Test AjoutJuryNom: OK " << std::endl;
        score+=1;
    }
    if (jurys[0]->getCojury()->getNom() == "Martin"){
        //std::cout << "Test AjoutJuryPrenom: OK " << std::endl;
        score+=1;
    }

    std::cout << "Test AjouterJury: " << score << "/3" << std::endl;
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
    int score=0;

    if (dispo){
        //std::cout << "Test VerifDispo: OK " << std::endl;
        score+=1;
    }

    std::cout << "Test VerifierDisponibilites: " << score << "/1" << std::endl;
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
    int score=0;

    if (affectation){
        //std::cout << "Test Affectation: OK " << std::endl;
        score+=1;
    }

    const auto& jurys = soutenance.getJurys();
    if (jurys.size() == 1){
        //std::cout << "Test AffectationTaille: OK " << std::endl;
        score+=1;
    }
    if (jurys[0]->getPresident()->getNom() == "Dupont"){
        //std::cout << "Test AffectationPresident: OK " << std::endl;
        score+=1;
    }
    if (jurys[0]->getCojury()->getNom() == "Martin"){
        //std::cout << "Test AffectationCojury: OK " << std::endl;
        score+=1;
    }

    std::cout << "Test AffecterJury: " << score << "/4" << std::endl;;
}
