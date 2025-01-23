#include "Model/etudiant.h"

// Constructeur
Etudiant::Etudiant(const std::string& nom, const std::string& prenom, const std::string& classe, const std::vector<std::string>& options)
    : Personne(nom, prenom), classe(classe), options(options) {}

// Gestion des créneaux via le calendrier
void Etudiant::ajouterDisponibiliteEtudiant(std::shared_ptr<Creneau> creneau) {
    if (calendrier.estDispo(creneau)) {
        calendrier.ajouteCreneau(creneau);
    } else {
        std::cout << "Le créneau " << creneau->getDate() << " " << creneau->getHeure()
                  << " existe déjà dans le calendrier." << std::endl;
    }
}

void Etudiant::retirerDisponibiliteEtudiant(std::shared_ptr<Creneau> creneau) {
    calendrier.retireCreneau(creneau);
}

std::vector<std::shared_ptr<Creneau>> Etudiant::getDisponibilitesEtudiant() const {
    return calendrier.getCalendrier();
}


// Gestion des options
std::vector<std::string> Etudiant::getOptions() const {
    return options;
}

void Etudiant::setOptions(const std::vector<std::string>& options) {
    this->options = options;
}

// Gestion de la classe
std::string Etudiant::getClasse() const {
    return classe;
}

void Etudiant::setClasse(const std::string& classe) {
    this->classe = classe;
}

// Gestion des stages
void Etudiant::assignerStage(const std::shared_ptr<Stage>& stage) {
    this->stage = stage;
}

std::shared_ptr<Stage> Etudiant::getStage() const {
    return stage;
}

void Etudiant::setStage(const std::shared_ptr<Stage>& stage) {
    this->stage = stage;
}
