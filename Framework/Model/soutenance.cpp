#include "soutenance.h"

// Constructeur
Soutenance::Soutenance() : calendrier(std::make_shared<Calendrier>()) {}

// Ajouter un étudiant à la soutenance
void Soutenance::ajouterEtudiant(const std::shared_ptr<Etudiant>& etudiant) {
    etudiants.push_back(etudiant);
}

// Récupérer la liste des étudiants
const std::vector<std::shared_ptr<Etudiant>>& Soutenance::getEtudiants() const {
    return etudiants;
}

// Ajouter un jury à la soutenance
void Soutenance::ajouterJury(const std::shared_ptr<Jury>& jury) {
    jurys.push_back(jury);
}

// Récupérer la liste des jurys
const std::vector<std::shared_ptr<Jury>>& Soutenance::getJurys() const {
    return jurys;
}

// Vérifie si l'étudiant a un créneau commun avec le jury au complet
bool Soutenance::verifierDisponibilites(const Etudiant& etudiant, const Jury& jury) const {
    const auto& calendrierEtudiant = etudiant.getDisponibilitesEtudiant();
    const auto& calendrierPresident = jury.getPresident()->getDisponibilites().getCalendrier();
    const auto& calendrierCojury = jury.getCojury()->getDisponibilites().getCalendrier();

    for (const auto& creneauEtudiant : calendrierEtudiant) {
        for (const auto& creneauPresident : calendrierPresident) {
            for (const auto& creneauCojury : calendrierCojury) {
                if (*creneauEtudiant == *creneauPresident && *creneauEtudiant == *creneauCojury) {
                    return true; // Créneau commun trouvé
                }
            }
        }
    }

    return false; // Aucun créneau commun
}


// Affecte automatiquement un jury à un étudiant
bool Soutenance::affecterJury(Etudiant& etudiant, const std::vector<std::shared_ptr<Enseignant>>& enseignants) {
    // Récupérer le tuteur depuis le stage de l'étudiant
    auto tuteur = etudiant.getStage()->getTuteur();
    if (!tuteur) {
        std::cerr << "Erreur : Le stage de l'étudiant n'a pas de tuteur assigné.\n";
        return false;
    }

    // Trouver un co-jury compatible
    std::shared_ptr<Enseignant> coJury = nullptr;
    for (const auto& enseignant : enseignants) {
        if (enseignant != tuteur && Jury(tuteur, enseignant).verifDispo()) {
            coJury = enseignant;
            break;
        }
    }

    if (!coJury) {
        std::cerr << "Erreur : Aucun co-jury compatible trouvé pour le tuteur.\n";
        return false;
    }

    // Créer le jury avec le tuteur et le co-jury trouvés
    auto jury = std::make_shared<Jury>(tuteur, coJury);

    // Vérifier les disponibilités entre l'étudiant et le jury
    if (this->verifierDisponibilites(etudiant, *jury)) {
        jurys.push_back(jury); // Ajouter le jury à la soutenance
        std::cout << "Jury assigné avec succès à l'étudiant.\n";
        return true;
    } else {
        std::cerr << "Erreur : Aucun créneau compatible trouvé entre l'étudiant et le jury.\n";
        return false;
    }
}


// Exemple d'implémentation
void Soutenance::assigner(const std::shared_ptr<Etudiant>& etu,
                          const std::shared_ptr<Jury>&     jury,
                          const std::shared_ptr<Creneau>&  creneau)
{
    // Option : si vous voulez être sûr de ne pas dupliquer un étudiant
    // ou un jury dans vos vecteurs, vous pouvez vérifier avant de push_back.
    // Ou bien vous laissez tel quel.

    etudiants.push_back(etu);
    jurys.push_back(jury);

    // On construit la triple liaison
    Affectation aff{ etu, jury, creneau };
    m_affectations.push_back(aff);

}

// Accesseur
const std::vector<Soutenance::Affectation>& Soutenance::getAffectations() const
{
    return m_affectations;
}

void Soutenance::clearAffectations()
{
    m_affectations.clear(); // Efface les affectations
    etudiants.clear();      // Réinitialise la liste des étudiants
    jurys.clear();          // Réinitialise la liste des jurys
}

