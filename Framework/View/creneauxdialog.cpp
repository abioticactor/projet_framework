#include "creneauxdialog.h"

CreneauxDialog::CreneauxDialog(TestProjet &projet, QWidget *parent)
    : QDialog(parent), m_testProjet(projet)
{
    setWindowTitle("Créer / Assigner Créneaux");

    // Application du style général
    setStyleSheet("QDialog { background-color: #f4f4f4; font-family: Arial, sans-serif; }");

    // ComboBox pour étudiants
    m_comboEtudiants = new QComboBox(this);
    m_comboEtudiants->addItem("Aucun"); // Option "Aucun"
    for (auto &etu : m_testProjet.getEtudiants()) {
        QString nom = QString::fromStdString(etu->getNom()) + " "
                      + QString::fromStdString(etu->getPrenom());
        m_comboEtudiants->addItem(nom, QVariant::fromValue((void*)etu.get()));
    }
    m_ckTousEtudiants = new QCheckBox("Tous les étudiants ?", this);

    // ComboBox pour enseignants
    m_comboEnseignants = new QComboBox(this);
    m_comboEnseignants->addItem("Aucun"); // Option "Aucun"
    for (auto &ens : m_testProjet.getEnseignants()) {
        QString nom = QString::fromStdString(ens->getNom());
        m_comboEnseignants->addItem(nom, QVariant::fromValue((void*)ens.get()));
    }
    m_ckTousEnseignants = new QCheckBox("Tous les enseignants ?", this);

    // QDateTimeEdit pour la date + heure
    m_dateTimeEdit = new QDateTimeEdit(this);
    m_dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
    m_dateTimeEdit->setDateTime(QDateTime(QDate(2025, 1, 1), QTime(9, 0)));
    m_dateTimeEdit->setCalendarPopup(true); // Activer le popup calendrier

    // Boutons
    m_btnValider  = new QPushButton("Valider le Créneau", this);
    m_btnPlanning = new QPushButton("Ouvrir Planning", this);
    m_btnSupprimerCreneau = new QPushButton("Supprimer Créneau", this);



    // Application de styles supplémentaires pour les widgets
    QString comboBoxStyle = "QComboBox {"
                            "  border: 2px solid #888;"
                            "  border-radius: 6px;"
                            "  padding: 6px;"
                            "  font-size: 15px;"
                            "  background-color: #f1f1f1;"
                            "  color: #333;"
                            "}"
                            "QComboBox::drop-down {"
                            "  border: none;"
                            "  width: 25px;"
                            "  background-color: #ddd;"
                            "  border-top-right-radius: 6px;"
                            "  border-bottom-right-radius: 6px;"
                            "}"
                            "QComboBox::down-arrow {"
                            "  image: url(:/icons/arrow-down.png);"
                            "  width: 15px;"
                            "  height: 15px;"
                            "}"
                            "QComboBox QAbstractItemView {"
                            "  border: 1px solid #aaa;"
                            "  background: #fff;"
                            "  selection-background-color: #0078d7;"
                            "  selection-color: #fff;"
                            "}";
    m_comboEtudiants->setStyleSheet(comboBoxStyle);
    m_comboEnseignants->setStyleSheet(comboBoxStyle);

    QString checkBoxStyle = "QCheckBox {"
                            "  font-size: 15px;"
                            "  color: #444;"
                            "}"
                            "QCheckBox::indicator {"
                            "  width: 20px;"
                            "  height: 20px;"
                            "  border: 2px solid #aaa;"
                            "  border-radius: 5px;"
                            "  background-color: white;"
                            "}"
                            "QCheckBox::indicator:checked {"
                            "  background-color: #fed0bc;"
                            "  border-color: #ffb7ac;"
                            "}";
    m_ckTousEtudiants->setStyleSheet(checkBoxStyle);
    m_ckTousEnseignants->setStyleSheet(checkBoxStyle);

    QString buttonStyle = "QPushButton {"
                          "  background-color: #fed0bc;"
                          "  color: black;"
                          "  border: 2px solid #ffb7ac;"
                          "  border-radius: 8px;"
                          "  padding: 10px 20px;"
                          "  font-size: 15px;"
                          "}"
                          "QPushButton:hover {"
                          "  background-color: #fdd0af;"
                          "  border-color: #fe988c;"
                          "}"
                          "QPushButton:pressed {"
                          "  background-color: #fe988c;"
                          "  border-color: #fe988c;"
                          "}";
    m_btnValider->setStyleSheet(buttonStyle);
    m_btnPlanning->setStyleSheet(buttonStyle);
    m_btnSupprimerCreneau->setStyleSheet(buttonStyle);


    QString dateTimeEditStyle = "QDateTimeEdit {"
                                "  border: 2px solid #888;"
                                "  border-radius: 6px;"
                                "  padding: 6px;"
                                "  font-size: 15px;"
                                "  background-color: #f9f9f9;"
                                "  color: #333;"
                                " height: 30px;"
                                "}"
                                "QDateTimeEdit::up-button {"
                                "  subcontrol-origin: border;"
                                "  subcontrol-position: top right;"
                                "  width: 15px;"
                                "  height: 15px;"
                                "  background-color: #ddd;"
                                "}"
                                "QDateTimeEdit::down-button {"
                                "  subcontrol-origin: border;"
                                "  subcontrol-position: bottom right;"
                                "  width: 15px;"
                                "  height: 15px;"
                                "  background-color: #ddd;"
                                "}";
    m_dateTimeEdit->setStyleSheet(dateTimeEditStyle);


    // Ajouter la table des créneaux attribués
    m_tableCreneaux = new QTableWidget(this);
    m_tableCreneaux->setColumnCount(3);
    QStringList headers;
    headers << "Date" << "Heure" << "Prénom";
    m_tableCreneaux->setHorizontalHeaderLabels(headers);
    m_tableCreneaux->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableCreneaux->setFixedHeight(150);


    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *labelEtudiants = new QLabel("Étudiants :", this);
    QLabel *labelEnseignants = new QLabel("Enseignants :", this);
    QLabel *labelDateTime = new QLabel("Date et heure :", this);

    QString labelStyle = "QLabel {"
                         "  font-size: 16px;"
                         "  font-weight: bold;"
                         "  color: #444;"
                         "}";
    labelEtudiants->setStyleSheet(labelStyle);
    labelEnseignants->setStyleSheet(labelStyle);
    labelDateTime->setStyleSheet(labelStyle);

    layout->addWidget(labelEtudiants);
    layout->addWidget(m_comboEtudiants);
    layout->addWidget(m_ckTousEtudiants);


    layout->addWidget(labelEnseignants);
    layout->addWidget(m_comboEnseignants);
    layout->addWidget(m_ckTousEnseignants);


    layout->addWidget(labelDateTime);
    layout->addWidget(m_dateTimeEdit);

    layout->addWidget(m_tableCreneaux); // Ajouter le tableau
    layout->addWidget(m_btnSupprimerCreneau); // Bouton ajouté sous le tableau


    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_btnValider);
    buttonLayout->addWidget(m_btnSupprimerCreneau);
    buttonLayout->addWidget(m_btnPlanning);

    layout->addLayout(buttonLayout);

    // Connexions
    connect(m_btnValider, &QPushButton::clicked, this, &CreneauxDialog::onValiderCreneau);
    connect(m_btnPlanning, &QPushButton::clicked, this, &CreneauxDialog::onOuvrirPlanning);
    connect(m_comboEtudiants, &QComboBox::currentTextChanged, this, &CreneauxDialog::afficherCreneauxAttribues);
    connect(m_comboEnseignants, &QComboBox::currentTextChanged, this, &CreneauxDialog::afficherCreneauxAttribues);
    connect(this, &CreneauxDialog::creneauxModifies, this, &CreneauxDialog::mettreAJourCreneaux);
    connect(m_btnSupprimerCreneau, &QPushButton::clicked, this, &CreneauxDialog::supprimerCreneau);



}

CreneauxDialog::~CreneauxDialog()
{
}

void CreneauxDialog::onValiderCreneau()
{
    QDateTime dt = m_dateTimeEdit->dateTime();
    QString dateStr = dt.date().toString("yyyy-MM-dd");
    QString heureStr = dt.time().toString("HH:mm");

    auto creneau = std::make_shared<Creneau>(dateStr.toStdString(), heureStr.toStdString());

    // Ajouter le créneau à m_creneaux dans TestProjet s'il n'existe pas déjà
    auto& creneaux = m_testProjet.getCreneaux();
    bool alreadyExists = std::any_of(creneaux.begin(), creneaux.end(),
                                     [&](auto& c) { return *c == *creneau; });

    if (!alreadyExists) {
        creneaux.push_back(creneau);
        std::cout << "Créneau ajouté : " << dateStr.toStdString() << " " << heureStr.toStdString() << "\n";
    } else {
        std::cout << "Créneau déjà existant : " << dateStr.toStdString() << " " << heureStr.toStdString() << "\n";
    }

    // Gestion des étudiants
    if (m_ckTousEtudiants->isChecked()) {
        // Affecter à tous les étudiants
        for (auto &etu : m_testProjet.getEtudiants()) {
            etu->ajouterDisponibiliteEtudiant(creneau);
            std::cout << "Ajout du créneau pour étudiant : " << etu->getNom() << "\n";
        }
    } else {
        // Affecter à un seul étudiant
        int indexEtu = m_comboEtudiants->currentIndex();
        if (indexEtu > 0) { // Ignore "Aucun" (index 0)
            auto &etu = m_testProjet.getEtudiants().at(indexEtu - 1); // Décalage de 1
            etu->ajouterDisponibiliteEtudiant(creneau);
            std::cout << "Ajout du créneau pour étudiant : " << etu->getNom() << "\n";
        }
    }

    // Gestion des enseignants
    if (m_ckTousEnseignants->isChecked()) {
        // Affecter à tous les enseignants
        for (auto &ens : m_testProjet.getEnseignants()) {
            ens->ajouterDisponibilite(creneau);
            std::cout << "Ajout du créneau pour enseignant : " << ens->getNom() << "\n";
        }
    } else {
        // Affecter à un seul enseignant
        int indexEns = m_comboEnseignants->currentIndex();
        if (indexEns > 0) { // Ignore "Aucun" (index 0)
            auto &ens = m_testProjet.getEnseignants().at(indexEns - 1); // Décalage de 1
            ens->ajouterDisponibilite(creneau);
            std::cout << "Ajout du créneau pour enseignant : " << ens->getNom() << "\n";
        }
    }

    std::cout << "Nombre total de créneaux : " << creneaux.size() << "\n";

    QMessageBox::information(this, "Créneau ajouté",
                             QString("<font color='black'>Créneau %1 %2 ajouté/associé !</font>").arg(dateStr, heureStr));
    emit creneauxModifies();

}


void CreneauxDialog::onOuvrirPlanning()
{
    // On appelle la méthode creerJurysEtAffecterEtudiants() du TestProjet
    // pour générer la planification
    m_testProjet.creerJurysEtAffecterEtudiants();
    // On ouvre la 3eme fenêtre
    PlanningDialog *dlg = new PlanningDialog(m_testProjet);
    dlg->show();

    // On ferme la 2ème fenêtre
    this->close();
}

void CreneauxDialog::closeEvent(QCloseEvent *event)
{
    if (!m_testProjet.getCreneaux().empty()) {
        QString fichier = "backup.json";
        m_testProjet.sauvegarderDonnees(fichier);
        std::cout << "[Sauvegarde] Données sauvegardées automatiquement.\n";
    }

    event->accept(); // Accepter la fermeture
}

void CreneauxDialog::afficherCreneauxAttribues() {
    m_tableCreneaux->setRowCount(0); // Réinitialiser la table

    QString selectedEtudiant = m_comboEtudiants->currentText();
    QString selectedEnseignant = m_comboEnseignants->currentText();

    bool filtrerEtudiant = !selectedEtudiant.isEmpty() && selectedEtudiant != "Aucun";
    bool filtrerEnseignant = !selectedEnseignant.isEmpty() && selectedEnseignant != "Aucun";

    qDebug() << "Étudiant sélectionné :" << selectedEtudiant;
    qDebug() << "Enseignant sélectionné :" << selectedEnseignant;

    if (filtrerEtudiant) {
        //Trouver l'étudiant sélectionné
        auto itEtu = std::find_if(m_testProjet.getEtudiants().begin(), m_testProjet.getEtudiants().end(),
                                  [&](const std::shared_ptr<Etudiant>& e) {
                                      return QString::fromStdString(e->getNom() + " " + e->getPrenom()) == selectedEtudiant;
                                  });

        if (itEtu != m_testProjet.getEtudiants().end()) {
            auto creneauxEtudiant = (*itEtu)->getDisponibilitesEtudiant();
            for (const auto& cren : creneauxEtudiant) {
                int row = m_tableCreneaux->rowCount();
                m_tableCreneaux->insertRow(row);

                QTableWidgetItem *dateItem = new QTableWidgetItem(QString::fromStdString(cren->getDate()));
                dateItem->setFlags(dateItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *heureItem = new QTableWidgetItem(QString::fromStdString(cren->getHeure()));
                heureItem->setFlags(heureItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *prenomItem = new QTableWidgetItem(QString::fromStdString((*itEtu)->getPrenom()));
                prenomItem->setFlags(prenomItem->flags() & ~Qt::ItemIsEditable);

                m_tableCreneaux->setItem(row, 0, dateItem);
                m_tableCreneaux->setItem(row, 1, heureItem);
                m_tableCreneaux->setItem(row, 2, prenomItem); // Affichage du prénom

            }
        }
    }

    if (filtrerEnseignant) {
        // Trouver l'enseignant sélectionné
        auto itEns = std::find_if(m_testProjet.getEnseignants().begin(), m_testProjet.getEnseignants().end(),
                                  [&](const std::shared_ptr<Enseignant>& e) {
                                      return QString::fromStdString(e->getNom()) == selectedEnseignant;
                                  });

        if (itEns != m_testProjet.getEnseignants().end()) {
            auto creneauxEnseignant = (*itEns)->getDisponibilites().getCalendrier();
            for (const auto& cren : creneauxEnseignant) {
                int row = m_tableCreneaux->rowCount();
                m_tableCreneaux->insertRow(row);

                QTableWidgetItem *dateItem = new QTableWidgetItem(QString::fromStdString(cren->getDate()));
                dateItem->setFlags(dateItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *heureItem = new QTableWidgetItem(QString::fromStdString(cren->getHeure()));
                heureItem->setFlags(heureItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *prenomItem = new QTableWidgetItem(QString::fromStdString((*itEns)->getNom()));
                prenomItem->setFlags(prenomItem->flags() & ~Qt::ItemIsEditable);

                m_tableCreneaux->setItem(row, 0, dateItem);
                m_tableCreneaux->setItem(row, 1, heureItem);
                m_tableCreneaux->setItem(row, 2, prenomItem);

            }
        }
    }
}


void CreneauxDialog::mettreAJourCreneaux() {
    afficherCreneauxAttribues(); //Rafraîchir directement les créneaux affichés
}

void CreneauxDialog::supprimerCreneau() {
    int selectedRow = m_tableCreneaux->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un créneau à supprimer.");
        return;
    }

    QString dateCreneau = m_tableCreneaux->item(selectedRow, 0)->text();
    QString heureCreneau = m_tableCreneaux->item(selectedRow, 1)->text();

    QString selectedEtudiant = m_comboEtudiants->currentText();
    QString selectedEnseignant = m_comboEnseignants->currentText();

    bool isEtudiant = !selectedEtudiant.isEmpty() && selectedEtudiant != "Aucun";
    bool isEnseignant = !selectedEnseignant.isEmpty() && selectedEnseignant != "Aucun";

    if (!isEtudiant && !isEnseignant) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un étudiant ou un enseignant.");
        return;
    }

    std::shared_ptr<Creneau> creneau = nullptr;
    for (const auto &c : m_testProjet.getCreneaux()) {
        if (QString::fromStdString(c->getDate()) == dateCreneau &&
            QString::fromStdString(c->getHeure()) == heureCreneau) {
            creneau = c;
            break;
        }
    }

    if (!creneau) {
        QMessageBox::warning(this, "Erreur", "Creneau introuvable.");
        return;
    }

    std::shared_ptr<Etudiant> etu = nullptr;
    std::shared_ptr<Enseignant> ens = nullptr;

    if (isEtudiant) {
        auto itEtu = std::find_if(m_testProjet.getEtudiants().begin(), m_testProjet.getEtudiants().end(),
                                  [&](const std::shared_ptr<Etudiant>& e) {
                                      return QString::fromStdString(e->getNom() + " " + e->getPrenom()) == selectedEtudiant;
                                  });

        if (itEtu != m_testProjet.getEtudiants().end()) {
            etu = *itEtu;
        }
    }

    if (isEnseignant) {
        auto itEns = std::find_if(m_testProjet.getEnseignants().begin(), m_testProjet.getEnseignants().end(),
                                  [&](const std::shared_ptr<Enseignant>& e) {
                                      return QString::fromStdString(e->getNom()) == selectedEnseignant;
                                  });

        if (itEns != m_testProjet.getEnseignants().end()) {
            ens = *itEns;
        }
    }

    //Appel de la bonne méthode de suppression
    m_testProjet.getSoutenanceModifiable().supprimerAffectationPartielle(etu, ens, creneau);

    QMessageBox::information(this, "Suppression réussie", "Le créneau a été supprimé.");

    m_tableCreneaux->removeRow(selectedRow);
    m_testProjet.sauvegarderDonnees("sauvegarde.json");
}
