/*#ifndef CSV_H
#define CSV_H

#include <QString>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <memory>
#include "Model/enseignant.h"
#include "Model/etudiant.h"

class CSV {
public:
    explicit CSV(QString cheminFichier);
    std::vector<std::vector<QString>> lireFichier();
    bool ecrireFichier(const std::vector<std::vector<QString>>& donnees);
    std::vector<std::shared_ptr<Enseignant>> importerEnseignants();
    std::vector<std::shared_ptr<Etudiant>> importerEtudiants();

private:
    QString cheminFichier;
};

#endif // CSV_H*/
