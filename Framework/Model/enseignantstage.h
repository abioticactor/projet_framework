/*#ifndef ENSEIGNANTSTAGE_H
#define ENSEIGNANTSTAGE_H

#include "Model/enseignant.h"
#include "Model/stage.h"
#include <memory>

class EnseignantStage {
private:
    std::shared_ptr<Enseignant> enseignant; // Référence à l'enseignant
    std::shared_ptr<Stage> stage;           // Référence au stage

public:
    // Constructeur
    EnseignantStage(const std::shared_ptr<Enseignant>& enseignant, const std::shared_ptr<Stage>& stage);

    // Gestion de l'enseignant
    std::shared_ptr<Enseignant> getEnseignant() const;
    void setEnseignant(const std::shared_ptr<Enseignant>& enseignant);

    // Gestion du stage
    std::shared_ptr<Stage> getStage() const;
    void setStage(const std::shared_ptr<Stage>& stage);
};

#endif // ENSEIGNANTSTAGE_H*/
