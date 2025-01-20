// csv.h
#ifndef CSV_H
#define CSV_H

#include <QString>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <memory>


#include "enseignant.h"
#include "etudiant.h"
class Enseignant;
class Etudiant;



class CSV {

private:
    QString cheminFichier;



public:
    CSV(QString cheminFichier);


    std::vector<std::vector<QString>> lireFichier();


    bool ecrireFichier(const std::vector<std::vector<QString>>& donnees);



    std::vector<std::shared_ptr<Enseignant>> importerEnseignants();


    std::vector<std::shared_ptr<Etudiant>> importerEtudiants();


};

#endif // CSV_H
