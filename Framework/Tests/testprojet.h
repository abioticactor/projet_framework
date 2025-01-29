#ifndef TESTPROJET_H
#define TESTPROJET_H

#include <string>
#include <vector>
#include <memory>
#include "Controller/CSVHandler.h"
#include "Model/etudiant.h"
#include "Model/enseignant.h"
#include "Model/stage.h"
#include "Model/creneau.h"
#include "Model/jury.h"
#include "Model/soutenance.h"
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>





class TestProjet {
public:
    // Données extraites du CSV
    std::vector<std::shared_ptr<Etudiant>>   m_etudiants;
    std::vector<std::shared_ptr<Stage>>      m_stages;
    std::vector<std::shared_ptr<Enseignant>> m_enseignants;

    // Tous les créneaux créés (pour simplifier)
    std::vector<std::shared_ptr<Creneau>> m_creneaux;

    // Soutenance gère la liste finale (étudiants, jurys, etc.)
    Soutenance m_soutenance;

public:
    // 1. Extraction des données via CSVHandler
    void extraireDonnees(const std::string& cheminCsv);

    // 2. Création de créneaux et association aux étudiants/enseignants
    void creerEtAssignerCreneaux();

    // 3. Création des jurys (président/co-jury) + vérification, en respectant la règle
    //    "le même créneau peut être utilisé 2 fois max et pas par un enseignant déjà présent sur ce créneau".
    void creerJurysEtAffecterEtudiants();

    // 4. Affichage final de toutes les soutenances
    void afficherToutesLesSoutenances() const;

    const Soutenance& getSoutenance() const { return m_soutenance; }

    const std::vector<std::shared_ptr<Etudiant>>& getEtudiants() const {
        return m_etudiants;
    }

    // Accès en lecture seule (const) à la liste d’enseignants
    const std::vector<std::shared_ptr<Enseignant>>& getEnseignants() const {
        return m_enseignants;
    }

    std::vector<std::shared_ptr<Creneau>>& getCreneaux() {
        return m_creneaux;
    }
    const std::vector<std::shared_ptr<Creneau>>& getCreneaux() const {
        return m_creneaux;
    }
    void sauvegarderDonnees(const QString &fichier) const;
    void restaurerDonnees(const QString &fichier);
    bool aDejaUneSoutenance(const std::shared_ptr<Etudiant>& etudiant) const;
    int nombreSoutenancesPourCreneau(const std::shared_ptr<Creneau>& creneau) const;


};

#endif // TESTPROJET_H
