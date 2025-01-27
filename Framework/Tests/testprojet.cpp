#include "TestProjet.h"
#include <iostream>
#include <algorithm>
#include <unordered_map>

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

void TestProjet::creerJurysEtAffecterEtudiants() {
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
