#ifndef PERSONNE_H
#define PERSONNE_H

#include <string>

class Personne {
private:
    static int identifiant; // Variable statique pour générer des IDs uniques
    int id;                 // Identifiant unique de la personne
    std::string nom;        // Nom de la personne
    std::string prenom;     // Prénom de la personne

public:
    // Constructeur
    Personne(const std::string& nom, const std::string& prenom);

    // Getters
    std::string getNom() const;
    std::string getPrenom() const;
    int getId() const;

    // Setters
    void setNom(const std::string& nom);
    void setPrenom(const std::string& prenom);
};

#endif // PERSONNE_H
