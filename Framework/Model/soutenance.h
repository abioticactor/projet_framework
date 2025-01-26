#ifndef SOUTENANCE_H
#define SOUTENANCE_H

#include "Model/etudiant.h"
#include "Model/jury.h"
#include "Model/calendrier.h"
//#include "Model/matriceassociation.h"
#include <vector>
#include <memory>
#include <iostream>

class Soutenance {
private:
    std::vector<std::shared_ptr<Etudiant>> etudiants;  // Liste des étudiants gérés
    std::vector<std::shared_ptr<Jury>> jurys;          // Liste des jurys assignés
    std::shared_ptr<Calendrier> calendrier;           // Calendrier global pour la soutenance

    struct Affectation {
        std::shared_ptr<Etudiant> etu;
        std::shared_ptr<Jury>     jury;
        std::shared_ptr<Creneau>  creneau;
    };

    // NOUVEAU : liste de toutes les affectations
    std::vector<Affectation> m_affectations;

public:
    // Constructeur
    Soutenance();

    // Gestion des étudiants
    void ajouterEtudiant(const std::shared_ptr<Etudiant>& etudiant);
    const std::vector<std::shared_ptr<Etudiant>>& getEtudiants() const;

    // Gestion des jurys
    void ajouterJury(const std::shared_ptr<Jury>& jury);
    const std::vector<std::shared_ptr<Jury>>& getJurys() const;

    // Vérifie les disponibilités entre un étudiant et un jury
    bool verifierDisponibilites(const Etudiant& etudiant, const Jury& jury) const;

    // Affecte automatiquement un jury à un étudiant
    bool affecterJury(Etudiant& etudiant, const std::vector<std::shared_ptr<Enseignant>>& enseignants);

    // Organisation des données avec MatriceAssociation
    //void organiserDonnees(std::shared_ptr<MatriceAssociation> matrice);

    // NOUVEAU : méthode pour assigner d'un coup
    void assigner(const std::shared_ptr<Etudiant>& etu,
                  const std::shared_ptr<Jury>& jury,
                  const std::shared_ptr<Creneau>& creneau);

    // NOUVEAU : accès à la liste des affectations
    const std::vector<Affectation>& getAffectations() const;


};

#endif // SOUTENANCE_H
