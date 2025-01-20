#include "Model/enseignantstage.h"

// Constructeur
EnseignantStage::EnseignantStage(const std::shared_ptr<Enseignant>& enseignant, const std::shared_ptr<Stage>& stage)
    : enseignant(enseignant), stage(stage) {}

// Gestion de l'enseignant
std::shared_ptr<Enseignant> EnseignantStage::getEnseignant() const {
    return enseignant;
}

void EnseignantStage::setEnseignant(const std::shared_ptr<Enseignant>& enseignant) {
    this->enseignant = enseignant;
}

// Gestion du stage
std::shared_ptr<Stage> EnseignantStage::getStage() const {
    return stage;
}

void EnseignantStage::setStage(const std::shared_ptr<Stage>& stage) {
    this->stage = stage;
}
