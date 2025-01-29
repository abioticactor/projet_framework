#include "TestProjet.h"


// 1) Extraction des données depuis le CSV
void TestProjet::extraireDonnees(const std::string& cheminCsv)
{
    std::cout << "[TestProjet] Extraction des donnees depuis le CSV...\n";

    CSVHandler csvHandler(cheminCsv);
    csvHandler.extraireInformations(m_etudiants, m_stages, m_enseignants);

    std::cout << "[TestProjet] Extraction terminee !\n"
              << "  - Nb etudiants : " << m_etudiants.size() << "\n"
              << "  - Nb stages : "    << m_stages.size()    << "\n"
              << "  - Nb enseignants : " << m_enseignants.size() << "\n";
}

// 2) Creation et association des creneaux
void TestProjet::creerEtAssignerCreneaux()
{
    std::cout << "\n[TestProjet] Creation et association des creneaux...\n";

    // Exemple : 5 jours, de 9h a 17h par tranche de 2h
    for (int jour = 1; jour <= 5; ++jour) {
        for (int heure = 9; heure <= 17; heure += 2) {
            auto c = std::make_shared<Creneau>(
                "2025-01-" + std::to_string(jour),
                std::to_string(heure) + ":00"
                );
            m_creneaux.push_back(c);
        }
    }

    // Associer ces creneaux à chaque enseignant
    for (auto& enseignant : m_enseignants) {
        for (auto& creneau : m_creneaux) {
            enseignant->ajouterDisponibilite(creneau);
        }
    }

    // Associer ces creneaux à chaque etudiant
    for (auto& etudiant : m_etudiants) {
        for (auto& creneau : m_creneaux) {
            etudiant->ajouterDisponibiliteEtudiant(creneau);
        }
    }

    std::cout << "[TestProjet] Creneaux crees et assignes.\n";
}

// 3) Creation des jurys et affectation des etudiants
/*void TestProjet::creerJurysEtAffecterEtudiants()
{
    std::cout << "\n[TestProjet] Creation des jurys et affectation des etudiants...\n";

    // Pour chaque creneau, on stocke la liste des paires (president, co_jury) qui l'occupent deja.
    // On limite a 2 paires par creneau. De plus, aucun enseignant ne doit apparaitre 2 fois sur le meme creneau.
    // Cle = shared_ptr<Creneau>, Valeur = vecteur de paires { (president, co_jury) }
    std::unordered_map<std::shared_ptr<Creneau>,
                       std::vector<std::pair<std::shared_ptr<Enseignant>,
                                             std::shared_ptr<Enseignant>>>> creneauOccupations;

    for (auto& etudiant : m_etudiants) {
        auto stage = etudiant->getStage();
        if (!stage) {
            // Pas de stage => pas de jury possible
            continue;
        }

        auto president = stage->getTuteur();
        if (!president) {
            continue;
        }

        bool juryAssigne = false;

        // Chercher un co_jury different
        for (auto& co_jury : m_enseignants) {
            if (co_jury == president) {
                continue; // meme pointeur => skip
            }

            // Creer un Jury provisoire
            auto jury = std::make_shared<Jury>(president, co_jury);

            // Verifier qu'il y a un creneau commun president/co_jury
            if (!jury->verifDispo()) {
                // Pas de creneau commun => skip
                continue;
            }

            // Recuperer leurs calendriers
            auto calPres  = president->getDisponibilites().getCalendrier();
            auto calCo    = co_jury->getDisponibilites().getCalendrier();
            auto calEtud  = etudiant->getDisponibilitesEtudiant();

            // Parcours des creneaux du president
            for (auto& creneauPres : calPres) {

                // Verifier si co_jury possede aussi creneauPres
                auto itCo = std::find_if(calCo.begin(), calCo.end(),
                                         [&](auto& c){ return (*c == *creneauPres); });
                if (itCo == calCo.end()) {
                    continue; // co_jury ne l'a pas
                }

                // Verifier si etudiant possede aussi creneauPres
                auto itEt = std::find_if(calEtud.begin(), calEtud.end(),
                                         [&](auto& c){ return (*c == *creneauPres); });
                if (itEt == calEtud.end()) {
                    continue; // etudiant ne l'a pas
                }

                // => creneauPres est commun (president, co_jury, etudiant).
                // On verifie dans creneauOccupations[creneauPres] :
                //   1) s'il y a deja 2 paires => creneau plein
                //   2) s'il y a un enseignant en commun

                auto& listePaires = creneauOccupations[creneauPres];
                if (static_cast<int>(listePaires.size()) >= 2) {
                    // Deja 2 binomes => creneau sature
                    continue;
                }

                // Verifier l'absence de tout enseignant en commun
                // si l'un des 2 se trouve deja dans une paire (p1, p2), on skip
                bool overlap = false;
                for (auto& paire : listePaires) {
                    // paire.first = president deja occupant
                    // paire.second = co_jury deja occupant
                    if (paire.first == president || paire.first == co_jury ||
                        paire.second == president || paire.second == co_jury) {
                        overlap = true;
                        break;
                    }
                }
                if (overlap) {
                    // On ne peut pas re-utiliser ce creneau pour un des memes enseignants
                    continue;
                }

                // Verifier la compatibilite triple via Soutenance::verifierDisponibilites
                if (!m_soutenance.verifierDisponibilites(*etudiant, *jury)) {
                    continue;
                }

                // => Tout est OK, on affecte
                listePaires.emplace_back(president, co_jury);

                jury->setCreneauAttribue(creneauPres);
                // On stocke la triple liaison
                m_soutenance.assigner(etudiant, jury, creneauPres);


                std::cout << "Etudiant " << etudiant->getNom()
                          << " affecte a Jury : ("
                          << president->getNom() << " & "
                          << co_jury->getNom() << ") sur le creneau "
                          << creneauPres->getDate() << " "
                          << creneauPres->getHeure() << "\n";

                juryAssigne = true;
                break; // fin de recherche de creneau
            }

            if (juryAssigne) {
                // plus besoin de chercher d'autre co_jury
                break;
            }
        }

        if (!juryAssigne) {
            std::cerr << "Aucun jury possible pour l'etudiant : "
                      << etudiant->getNom() << "\n";
        }
    }

    std::cout << "[TestProjet] Fin de l'affectation des jurys.\n";
}*/

/*void TestProjet::creerJurysEtAffecterEtudiants() {
    std::cout << "\n[TestProjet] Creation de jurys (2 soutenances max par creneau)\n";

    // occupationEnseignants[creneau] : liste des enseignants déjà pris sur ce créneau
    std::unordered_map<std::shared_ptr<Creneau>, std::vector<std::shared_ptr<Enseignant>>> occupationEnseignants;

    // Ensemble des étudiants déjà affectés (chacun n'a qu'une soutenance)
    std::unordered_set<std::shared_ptr<Etudiant>> etudiantsAffectes;

    for (auto& creneau : m_creneaux) {
        int nbAffectations = 0; // combien d'étudiants ont été affectés sur ce creneau

        // On va parcourir TOUS les étudiants
        // et on affecte ceux qu’on peut, jusqu’à 2
        for (auto& etu : m_etudiants) {
            // Stop si le creneau est déjà plein
            if (nbAffectations >= 2) {
                break;
            }

            // Déjà affecté ? => skip
            if (etudiantsAffectes.find(etu) != etudiantsAffectes.end()) {
                continue;
            }

            auto stage = etu->getStage();
            if (!stage) continue;

            auto president = stage->getTuteur();
            if (!president) continue;

            // Vérifier si l'étudiant est dispo sur creneau
            auto calEtud = etu->getDisponibilitesEtudiant();
            bool etuOK = std::any_of(calEtud.begin(), calEtud.end(),
                                     [&](auto& c){ return (*c == *creneau); });
            if (!etuOK) continue;

            // Vérifier si le président est dispo
            auto calPres = president->getDisponibilites().getCalendrier();
            bool presOK = std::any_of(calPres.begin(), calPres.end(),
                                      [&](auto& c){ return (*c == *creneau); });
            if (!presOK) continue;

            // Vérifier si le président n'est pas déjà dans occupationEnseignants[creneau]
            auto& occEns = occupationEnseignants[creneau];
            if (std::find(occEns.begin(), occEns.end(), president) != occEns.end()) {
                continue; // Deja occupé
            }

            // On cherche un co_jury
            std::shared_ptr<Enseignant> co_jury = nullptr;
            for (auto& e : m_enseignants) {
                if (e == president) continue; // pas la meme
                // Vérifier e->dispo sur creneau
                auto calE = e->getDisponibilites().getCalendrier();
                bool eOk = std::any_of(calE.begin(), calE.end(),
                                       [&](auto& cc){ return (*cc == *creneau); });
                if (!eOk) continue;

                // Vérifier e pas déjà occupé
                if (std::find(occEns.begin(), occEns.end(), e) != occEns.end()) {
                    continue;
                }

                co_jury = e;
                break;
            }
            if (!co_jury) {
                continue; // pas trouvé de co-jury
            }

            // On a (president, co_jury, etu)
            auto jury = std::make_shared<Jury>(president, co_jury);

            // Vérifier triple compat via Soutenance
            if (!m_soutenance.verifierDisponibilites(*etu, *jury)) {
                continue;
            }

            // => on affecte
            jury->setCreneauAttribue(creneau);
            // Marquer president / co_jury comme occupés
            occEns.push_back(president);
            occEns.push_back(co_jury);

            // Ajouter la triple liaison
            m_soutenance.assigner(etu, jury, creneau);

            // Ajouter etu dans la set "déjà affecté"
            etudiantsAffectes.insert(etu);

            nbAffectations++;

            std::cout << "[" << nbAffectations << " assign] Etu " << etu->getNom()
                      << " => (" << president->getNom() << " & "
                      << co_jury->getNom() << ") sur "
                      << creneau->getDate() << " " << creneau->getHeure() << "\n";
        }
        // On passe au creneau suivant
    }
    std::cout << "[TestProjet] Fin de l'affectation.\n";
}*/

// 3) Creation des jurys et affectation des etudiants
void TestProjet::creerJurysEtAffecterEtudiants() {
    std::cout << "\n[TestProjet] Début de l'affectation des jurys...\n";
    std::cout << "[TestProjet] Nombre de créneaux disponibles : " << m_creneaux.size() << "\n";

    // occupationEnseignants[creneau] : liste des enseignants déjà pris sur ce créneau
    std::unordered_map<std::shared_ptr<Creneau>, std::unordered_set<std::shared_ptr<Enseignant>>> occupationEnseignants;

    // Ensemble des étudiants déjà affectés (chacun n'a qu'une soutenance)
    std::unordered_set<std::shared_ptr<Etudiant>> etudiantsAffectes;

    for (auto& creneau : m_creneaux) {
        if (nombreSoutenancesPourCreneau(creneau) >= 2) {
            std::cout << "[INFO] Créneau " << creneau->getDate() << " " << creneau->getHeure()
                      << " est déjà rempli avec 2 soutenances, ignoré.\n";
            continue;
        }
        std::cout << "  Parcourir le créneau : " << creneau->getDate() << " " << creneau->getHeure() << "\n";
        int nbAffectations = 0; // combien d'étudiants ont été affectés sur ce creneau

        // On va parcourir TOUS les étudiants
        // et on affecte ceux qu’on peut, jusqu’à 2
        for (auto& etu : m_etudiants) {
            if(aDejaUneSoutenance(etu)){
                std::cout << "    Etudiant à déjà une soutenance.\n";
                continue;
            }
            // Stop si le creneau est déjà plein
            if (nbAffectations >= 2) {
                std::cout << "    Créneau plein, passage au suivant.\n";
                break;
            }

            // Déjà affecté ? => skip
            if (etudiantsAffectes.find(etu) != etudiantsAffectes.end()) {
                continue;
            }

            auto stage = etu->getStage();
            if (!stage) {
                std::cout << "    Etudiant " << etu->getNom() << " n'a pas de stage.\n";
                continue;
            }

            auto president = stage->getTuteur();
            if (!president) {
                std::cout << "    Stage de l'étudiant " << etu->getNom() << " n'a pas de tuteur.\n";
                continue;
            }

            // Vérifier si l'étudiant est dispo sur creneau
            auto calEtud = etu->getDisponibilitesEtudiant();
            bool etuOK = std::any_of(calEtud.begin(), calEtud.end(),
                                     [&](auto& c){ return (*c == *creneau); });
            if (!etuOK) {
                std::cout << "    Etudiant " << etu->getNom() << " non disponible sur ce créneau.\n";
                continue;
            }

            // Vérifier si le président est dispo
            auto calPres = president->getDisponibilites().getCalendrier();
            bool presOK = std::any_of(calPres.begin(), calPres.end(),
                                      [&](auto& c){ return (*c == *creneau); });
            if (!presOK) {
                std::cout << "    Président " << president->getNom() << " non disponible sur ce créneau.\n";
                continue;
            }

            // Vérifier si le président n'est pas déjà dans occupationEnseignants[creneau]
            auto& occEns = occupationEnseignants[creneau];
            if (occEns.find(president) != occEns.end()) {
                std::cout << "    Président " << president->getNom() << " déjà occupé sur ce créneau.\n";
                continue; // Déjà occupé
            }

            // On cherche un co_jury
            std::shared_ptr<Enseignant> co_jury = nullptr;
            for (auto& e : m_enseignants) {
                if (e == president) continue; // pas le même

                // Vérifier e->dispo sur creneau
                auto calE = e->getDisponibilites().getCalendrier();
                bool eOk = std::any_of(calE.begin(), calE.end(),
                                       [&](auto& cc){ return (*cc == *creneau); });
                if (!eOk) {
                    std::cout << "    Co-jury " << e->getNom() << " non disponible sur ce créneau.\n";
                    continue;
                }

                // Vérifier e pas déjà occupé
                if (occEns.find(e) != occEns.end()) {
                    std::cout << "    Co-jury " << e->getNom() << " déjà occupé sur ce créneau.\n";
                    continue;
                }

                co_jury = e;
                std::cout << "    Co-jury trouvé : " << co_jury->getNom() << "\n";
                break;
            }
            if (!co_jury) {
                std::cout << "    Aucun co-jury disponible pour l'étudiant " << etu->getNom() << " sur ce créneau.\n";
                continue; // pas trouvé de co-jury
            }

            // Vérifier triple compat via Soutenance
            auto jury = std::make_shared<Jury>(president, co_jury);
            if (!m_soutenance.verifierDisponibilites(*etu, *jury)) {
                std::cout << "    Triple compatibilité échouée pour l'étudiant " << etu->getNom() << " avec le jury ("
                          << president->getNom() << " & " << co_jury->getNom() << ").\n";
                continue;
            }

            // => on affecte
            jury->setCreneauAttribue(creneau);
            // Marquer president / co_jury comme occupés
            occEns.insert(president);
            occEns.insert(co_jury);

            // Ajouter la triple liaison
            m_soutenance.assigner(etu, jury, creneau);

            // Ajouter etu dans la set "déjà affecté"
            etudiantsAffectes.insert(etu);

            nbAffectations++;

            std::cout << "[" << nbAffectations << " assign] Etu " << etu->getNom()
                      << " => (" << president->getNom() << " & "
                      << co_jury->getNom() << ") sur "
                      << creneau->getDate() << " " << creneau->getHeure() << "\n";
        }
        // On passe au creneau suivant
    }
    std::cout << "[TestProjet] Fin de l'affectation.\n";
}




void TestProjet::afficherToutesLesSoutenances() const
{
    std::cout << "\n=== Recapitulatif des soutenances ===\n";

    // Lire la liste d'affectations
    const auto& affectations = m_soutenance.getAffectations();

    for (auto& aff : affectations) {
        auto etu     = aff.etu;
        auto jury    = aff.jury;
        auto creneau = aff.creneau;

        if (!etu) {
            std::cout << "[ATTENTION] Affectation sans etudiant!\n";
            continue;
        }
        if (!jury) {
            std::cout << "Etudiant : " << etu->getNom()
            << " mais pas de jury!\n";
            continue;
        }

        std::cout << "Etudiant : "
                  << etu->getNom() << " "
                  << etu->getPrenom() << "\n";

        auto stage = etu->getStage();
        if (stage) {
            std::cout << "  Stage : " << stage->getTitre()
            << " (Entreprise: "
            << stage->getEntreprise() << ")\n";
            if (auto tut = stage->getTuteur()) {
                std::cout << "  Tuteur : " << tut->getNom() << "\n";
            }
        }

        // Jury
        auto pres  = jury->getPresident();
        auto cojur = jury->getCojury();
        std::string nomCo = cojur ? cojur->getNom() : "Inconnu";

        std::cout << "  Jury : President="
                  << (pres ? pres->getNom() : "Null")
                  << ", Co-jury="
                  << nomCo << "\n";

        // Creneau
        if (creneau) {
            std::cout << "  Creneau attribue : "
                      << creneau->getDate() << " "
                      << creneau->getHeure() << "\n";
        } else {
            std::cout << "  Pas de creneau stocke!\n";
        }

        std::cout << "----------------------------------------\n";
    }

    std::cout << "=== Fin du recapitulatif ===\n";
}

/*void TestProjet::sauvegarderDonnees(const QString &fichier) const
{
    if (m_creneaux.empty()) {
        std::cerr << "Aucune sauvegarde à effectuer : aucun créneau enregistré.\n";
        return;
    }

    QJsonObject sauvegarde;

    // Sauvegarde des créneaux
    QJsonArray creneauxArray;
    for (const auto &creneau : m_creneaux) {
        QJsonObject creneauObj;
        creneauObj["date"] = QString::fromStdString(creneau->getDate());
        creneauObj["heure"] = QString::fromStdString(creneau->getHeure());
        creneauxArray.append(creneauObj);
    }
    sauvegarde["creneaux"] = creneauxArray;

    // Sauvegarde des étudiants
    QJsonArray etudiantsArray;
    for (const auto &etu : m_etudiants) {
        QJsonObject etuObj;
        etuObj["nom"] = QString::fromStdString(etu->getNom());
        etuObj["prenom"] = QString::fromStdString(etu->getPrenom());
        etudiantsArray.append(etuObj);
    }
    sauvegarde["etudiants"] = etudiantsArray;

    // Sauvegarde des enseignants
    QJsonArray enseignantsArray;
    for (const auto &ens : m_enseignants) {
        QJsonObject ensObj;
        ensObj["nom"] = QString::fromStdString(ens->getNom());
        enseignantsArray.append(ensObj);
    }
    sauvegarde["enseignants"] = enseignantsArray;

    // Sauvegarde des stages
    QJsonArray stagesArray;
    for (const auto &stage : m_stages) {
        QJsonObject stageObj;
        stageObj["titre"] = QString::fromStdString(stage->getTitre());
        stageObj["entreprise"] = QString::fromStdString(stage->getEntreprise());
        stageObj["tuteur"] = QString::fromStdString(stage->getTuteur()->getNom());
        stagesArray.append(stageObj);
    }
    sauvegarde["stages"] = stagesArray;

    // Sauvegarde des affectations
    QJsonArray affectationsArray;
    for (const auto &aff : m_soutenance.getAffectations()) {
        QJsonObject affObj;
        affObj["etudiant"] = QString::fromStdString(aff.etu->getNom());
        affObj["jury_president"] = QString::fromStdString(aff.jury->getPresident()->getNom());
        affObj["jury_cojury"] = QString::fromStdString(aff.jury->getCojury()->getNom());
        affObj["creneau_date"] = QString::fromStdString(aff.creneau->getDate());
        affObj["creneau_heure"] = QString::fromStdString(aff.creneau->getHeure());
        affectationsArray.append(affObj);
    }
    sauvegarde["affectations"] = affectationsArray;

    // Écrire dans un fichier
    QFile file(fichier);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(sauvegarde).toJson());
        file.close();
        std::cout << "Sauvegarde effectuée dans " << fichier.toStdString() << "\n";
    }
}


void TestProjet::restaurerDonnees(const QString &fichier)
{
    QFile file(fichier);
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Impossible d'ouvrir le fichier de sauvegarde : " << fichier.toStdString() << "\n";
        return;
    }

    QByteArray saveData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(saveData);
    QJsonObject sauvegarde = document.object();

    // Restaurer les créneaux
    m_creneaux.clear();
    QJsonArray creneauxArray = sauvegarde["creneaux"].toArray();
    for (const auto &c : creneauxArray) {
        QJsonObject creneauObj = c.toObject();
        auto creneau = std::make_shared<Creneau>(creneauObj["date"].toString().toStdString(),
                                                 creneauObj["heure"].toString().toStdString());
        m_creneaux.push_back(creneau);
    }

    // Restaurer les étudiants
    m_etudiants.clear();
    QJsonArray etudiantsArray = sauvegarde["etudiants"].toArray();
    for (const auto &e : etudiantsArray) {
        QJsonObject etuObj = e.toObject();
        auto etu = std::make_shared<Etudiant>(etuObj["nom"].toString().toStdString(),
                                              etuObj["prenom"].toString().toStdString(),
                                              "", std::vector<std::string>());
        m_etudiants.push_back(etu);
    }

    // Restaurer les enseignants
    m_enseignants.clear();
    QJsonArray enseignantsArray = sauvegarde["enseignants"].toArray();
    for (const auto &e : enseignantsArray) {
        QJsonObject ensObj = e.toObject();
        auto ens = std::make_shared<Enseignant>(ensObj["nom"].toString().toStdString(),
                                                "", std::vector<std::string>());
        m_enseignants.push_back(ens);
    }

    // Restaurer les stages
    m_stages.clear();
    QJsonArray stagesArray = sauvegarde["stages"].toArray();
    for (const auto &s : stagesArray) {
        QJsonObject stageObj = s.toObject();
        auto tuteur = std::make_shared<Enseignant>(stageObj["tuteur"].toString().toStdString(),
                                                   "", std::vector<std::string>());
        auto stage = std::make_shared<Stage>(stageObj["entreprise"].toString().toStdString(),
                                             stageObj["titre"].toString().toStdString(), tuteur);
        m_stages.push_back(stage);
    }

    // Restaurer les affectations
    m_soutenance.clearAffectations(); // Nettoyer les affectations existantes
    QJsonArray affectationsArray = sauvegarde["affectations"].toArray();
    for (const auto &aff : affectationsArray) {
        QJsonObject affObj = aff.toObject();
        auto etu = std::find_if(m_etudiants.begin(), m_etudiants.end(),
                                [&](auto &e) { return e->getNom() == affObj["etudiant"].toString().toStdString(); });
        auto president = std::find_if(m_enseignants.begin(), m_enseignants.end(),
                                      [&](auto &e) { return e->getNom() == affObj["jury_president"].toString().toStdString(); });
        auto cojury = std::find_if(m_enseignants.begin(), m_enseignants.end(),
                                   [&](auto &e) { return e->getNom() == affObj["jury_cojury"].toString().toStdString(); });
        auto creneau = std::find_if(m_creneaux.begin(), m_creneaux.end(),
                                    [&](auto &c) { return c->getDate() == affObj["creneau_date"].toString().toStdString() &&
                                                          c->getHeure() == affObj["creneau_heure"].toString().toStdString(); });

        if (etu != m_etudiants.end() && president != m_enseignants.end() &&
            cojury != m_enseignants.end() && creneau != m_creneaux.end()) {
            auto jury = std::make_shared<Jury>(*president, *cojury);
            m_soutenance.assigner(*etu, jury, *creneau);
        }
    }
}*/

void TestProjet::sauvegarderDonnees(const QString &fichier) const
{
    if (m_creneaux.empty()) {
        std::cerr << "Aucune sauvegarde à effectuer : aucun créneau enregistré.\n";
        return;
    }

    QJsonObject sauvegarde;

    // Sauvegarde des créneaux
    QJsonArray creneauxArray;
    for (const auto &creneau : m_creneaux) {
        QJsonObject creneauObj;
        creneauObj["date"] = QString::fromStdString(creneau->getDate());
        creneauObj["heure"] = QString::fromStdString(creneau->getHeure());
        creneauxArray.append(creneauObj);
    }
    sauvegarde["creneaux"] = creneauxArray;

    // Sauvegarde des enseignants
    QJsonArray enseignantsArray;
    for (const auto &ens : m_enseignants) {
        QJsonObject ensObj;
        ensObj["nom"] = QString::fromStdString(ens->getNom());
        enseignantsArray.append(ensObj);
    }
    sauvegarde["enseignants"] = enseignantsArray;

    // Sauvegarde des stages
    QJsonArray stagesArray;
    for (const auto &stage : m_stages) {
        QJsonObject stageObj;
        stageObj["titre"] = QString::fromStdString(stage->getTitre());
        stageObj["entreprise"] = QString::fromStdString(stage->getEntreprise());
        stageObj["tuteur"] = QString::fromStdString(stage->getTuteur()->getNom());
        stagesArray.append(stageObj);
    }
    sauvegarde["stages"] = stagesArray;

    // Sauvegarde des étudiants avec leur stage
    QJsonArray etudiantsArray;
    for (const auto &etu : m_etudiants) {
        QJsonObject etuObj;
        etuObj["nom"] = QString::fromStdString(etu->getNom());
        etuObj["prenom"] = QString::fromStdString(etu->getPrenom());
        if (etu->getStage()) {
            etuObj["stage"] = QString::fromStdString(etu->getStage()->getTitre());  // Lien vers le stage
        } else {
            etuObj["stage"] = "";
        }
        etudiantsArray.append(etuObj);
    }
    sauvegarde["etudiants"] = etudiantsArray;

    // Sauvegarde des soutenances (affectations)
    QJsonArray affectationsArray;
    for (const auto &aff : m_soutenance.getAffectations()) {
        QJsonObject affObj;
        affObj["etudiant"] = QString::fromStdString(aff.etu->getNom());
        affObj["jury_president"] = QString::fromStdString(aff.jury->getPresident()->getNom());
        affObj["jury_cojury"] = QString::fromStdString(aff.jury->getCojury()->getNom());
        affObj["creneau_date"] = QString::fromStdString(aff.creneau->getDate());
        affObj["creneau_heure"] = QString::fromStdString(aff.creneau->getHeure());
        affectationsArray.append(affObj);
    }
    sauvegarde["affectations"] = affectationsArray;

    // Écrire dans un fichier
    QFile file(fichier);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(sauvegarde).toJson());
        file.close();
        std::cout << "Sauvegarde effectuée dans " << fichier.toStdString() << "\n";
    }
}

void TestProjet::restaurerDonnees(const QString &fichier)
{
    QFile file(fichier);
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Impossible d'ouvrir le fichier de sauvegarde : " << fichier.toStdString() << "\n";
        return;
    }

    QByteArray saveData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(saveData);
    QJsonObject sauvegarde = document.object();

    // === Restaurer les créneaux sans écraser les anciens ===
    QJsonArray creneauxArray = sauvegarde["creneaux"].toArray();
    for (const auto &c : creneauxArray) {
        QJsonObject creneauObj = c.toObject();
        auto creneau = std::make_shared<Creneau>(creneauObj["date"].toString().toStdString(),
                                                 creneauObj["heure"].toString().toStdString());

        // Vérifier si ce créneau existe déjà
        auto it = std::find_if(m_creneaux.begin(), m_creneaux.end(),
                               [&](auto &existingCreneau) { return *existingCreneau == *creneau; });

        if (it == m_creneaux.end()) {
            m_creneaux.push_back(creneau); // Ajouter uniquement s'il n'existe pas déjà
        }
    }

    // === Restaurer les enseignants sans doublon ===
    QJsonArray enseignantsArray = sauvegarde["enseignants"].toArray();
    for (const auto &e : enseignantsArray) {
        QJsonObject ensObj = e.toObject();
        auto nom = ensObj["nom"].toString().toStdString();

        auto it = std::find_if(m_enseignants.begin(), m_enseignants.end(),
                               [&](auto &existingEns) { return existingEns->getNom() == nom; });

        if (it == m_enseignants.end()) {
            auto ens = std::make_shared<Enseignant>(nom, "", std::vector<std::string>());
            m_enseignants.push_back(ens);
        }
    }

    // === Restaurer les stages en préservant les liens ===
    QJsonArray stagesArray = sauvegarde["stages"].toArray();
    for (const auto &s : stagesArray) {
        QJsonObject stageObj = s.toObject();
        auto titre = stageObj["titre"].toString().toStdString();
        auto entreprise = stageObj["entreprise"].toString().toStdString();
        auto tuteurNom = stageObj["tuteur"].toString().toStdString();

        auto tuteur = std::find_if(m_enseignants.begin(), m_enseignants.end(),
                                   [&](auto &e) { return e->getNom() == tuteurNom; });

        if (tuteur != m_enseignants.end()) {
            auto it = std::find_if(m_stages.begin(), m_stages.end(),
                                   [&](auto &existingStage) { return existingStage->getTitre() == titre; });

            if (it == m_stages.end()) {
                auto stage = std::make_shared<Stage>(entreprise, titre, *tuteur);
                m_stages.push_back(stage);
            }
        }
    }

    // === Restaurer les étudiants en préservant leurs stages ===
    QJsonArray etudiantsArray = sauvegarde["etudiants"].toArray();
    for (const auto &e : etudiantsArray) {
        QJsonObject etuObj = e.toObject();
        auto nom = etuObj["nom"].toString().toStdString();
        auto prenom = etuObj["prenom"].toString().toStdString();
        auto stageTitre = etuObj["stage"].toString().toStdString();

        auto it = std::find_if(m_etudiants.begin(), m_etudiants.end(),
                               [&](auto &existingEtu) { return existingEtu->getNom() == nom; });

        if (it == m_etudiants.end()) {
            auto etu = std::make_shared<Etudiant>(nom, prenom, "", std::vector<std::string>());

            auto stageAssocie = std::find_if(m_stages.begin(), m_stages.end(),
                                             [&](auto &s) { return s->getTitre() == stageTitre; });

            if (stageAssocie != m_stages.end()) {
                etu->setStage(*stageAssocie);
            }

            m_etudiants.push_back(etu);
        }
    }

    // === Restaurer les soutenances sans écraser les anciennes ===
    QJsonArray affectationsArray = sauvegarde["affectations"].toArray();
    for (const auto &aff : affectationsArray) {
        QJsonObject affObj = aff.toObject();
        auto etudiantNom = affObj["etudiant"].toString().toStdString();
        auto juryPresidentNom = affObj["jury_president"].toString().toStdString();
        auto juryCojuryNom = affObj["jury_cojury"].toString().toStdString();
        auto creneauDate = affObj["creneau_date"].toString().toStdString();
        auto creneauHeure = affObj["creneau_heure"].toString().toStdString();

        auto etu = std::find_if(m_etudiants.begin(), m_etudiants.end(),
                                [&](auto &e) { return e->getNom() == etudiantNom; });

        auto president = std::find_if(m_enseignants.begin(), m_enseignants.end(),
                                      [&](auto &e) { return e->getNom() == juryPresidentNom; });

        auto cojury = std::find_if(m_enseignants.begin(), m_enseignants.end(),
                                   [&](auto &e) { return e->getNom() == juryCojuryNom; });

        auto creneau = std::find_if(m_creneaux.begin(), m_creneaux.end(),
                                    [&](auto &c) { return c->getDate() == creneauDate &&
                                                          c->getHeure() == creneauHeure; });

        if (etu != m_etudiants.end() && president != m_enseignants.end() &&
            cojury != m_enseignants.end() && creneau != m_creneaux.end()) {

            // Vérifier si cette affectation existe déjà
            const auto &affectationsExistantes = m_soutenance.getAffectations();
            auto it = std::find_if(affectationsExistantes.begin(), affectationsExistantes.end(),
                                   [&](const auto &existingAff) {
                                       return existingAff.etu == *etu &&
                                              existingAff.jury->getPresident() == *president &&
                                              existingAff.jury->getCojury() == *cojury &&
                                              existingAff.creneau == *creneau;
                                   });

            if (it == affectationsExistantes.end()) {
                auto jury = std::make_shared<Jury>(*president, *cojury);
                m_soutenance.assigner(*etu, jury, *creneau);
            }
        }
    }
}

bool TestProjet::aDejaUneSoutenance(const std::shared_ptr<Etudiant>& etudiant) const
{
    const auto& affectations = m_soutenance.getAffectations();
    return std::any_of(affectations.begin(), affectations.end(),
                       [&](const auto& aff) { return aff.etu == etudiant; });
}

int TestProjet::nombreSoutenancesPourCreneau(const std::shared_ptr<Creneau>& creneau) const
{
    const auto& affectations = m_soutenance.getAffectations();
    return std::count_if(affectations.begin(), affectations.end(),
                         [&](const auto& aff) { return aff.creneau == creneau; });
}
