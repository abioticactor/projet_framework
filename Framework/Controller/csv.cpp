#include "csv.h"
#include <QMessageBox>
#include <QDebug>

CSV::CSV(QString cheminFichier) : cheminFichier(cheminFichier) {}

std::vector<std::vector<QString>> CSV::lireFichier() {
    std::vector<std::vector<QString>> data;
    QFile file(cheminFichier);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split('\t'); // Tabulation comme séparateur
            std::vector<QString> row;
            for (const QString& field : fields) {
                row.push_back(field.trimmed());
            }
            data.push_back(row);
        }
        file.close();
    } else {
        qDebug() << "Erreur ouverture fichier CSV : " << file.errorString();
    }
    return data;
}

bool CSV::ecrireFichier(const std::vector<std::vector<QString>>& donnees) {
    QFile file(cheminFichier);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto& row : donnees) {
            for (int i = 0; i < row.size(); ++i) {
                out << row[i];
                if (i < row.size() - 1) {
                    out << "\t"; // Tabulation comme séparateur
                }
            }
            out << "\n";
        }
        file.close();
        return true; // Succès
    } else {
        qDebug() << "Erreur ouverture fichier CSV (écriture) : " << file.errorString();
        return false; // Échec
    }
}

std::vector<std::shared_ptr<Enseignant>> CSV::importerEnseignants() {
    std::vector<std::shared_ptr<Enseignant>> enseignants;
    auto data = lireFichier();
    if (data.empty() || data[0].size() < 6) return enseignants;
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i].size() >= 6) {
            enseignants.push_back(std::make_shared<Enseignant>(
                data[i][0].toStdString(), // Nom
                data[i][5].toStdString()  // Tuteur ESEO
                ));
        } else {
            qDebug() << "Erreur ligne" << i << ": format incorrect pour Enseignant.";
        }
    }
    return enseignants;
}

std::vector<std::shared_ptr<Etudiant>> CSV::importerEtudiants() {
    std::vector<std::shared_ptr<Etudiant>> etudiants;
    auto data = lireFichier();
    if (data.empty() || data[0].size() < 6) return etudiants;
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i].size() >= 6) {
            etudiants.push_back(std::make_shared<Etudiant>(
                data[i][0].toStdString(), // Nom
                data[i][1].toStdString(), // Prénom
                data[i][2].toStdString(), // Classe
                std::vector<std::string>{data[i][3].toStdString(), data[i][4].toStdString()} // Options
                ));
        } else {
            qDebug() << "Erreur ligne" << i << ": format incorrect pour Etudiant.";
        }
    }
    return etudiants;
}
