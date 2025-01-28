#include "CreneauxDialog.h"
#include <QMessageBox>
#include <QCalendarWidget>


/*CreneauxDialog::CreneauxDialog(TestProjet &projet, QWidget *parent)
    : QDialog(parent),
    m_testProjet(projet)
{
    setWindowTitle("Fenêtre 2 : Créer / Assigner Creneaux");

    // ComboBox pour étudiants
    m_comboEtudiants = new QComboBox(this);
    m_ckTousEtudiants = new QCheckBox("Tous les étudiants ?", this);

    // On peuple la combo avec la liste d’étudiants du TestProjet
    for (auto &etu : m_testProjet.getEtudiants()) {
        QString nom = QString::fromStdString(etu->getNom())
        + " "
            + QString::fromStdString(etu->getPrenom());
        m_comboEtudiants->addItem(nom, QVariant::fromValue((void*)etu.get()));
        // ou on stocke un index autrement
    }

    // ComboBox pour enseignants
    m_comboEnseignants = new QComboBox(this);
    m_ckTousEnseignants = new QCheckBox("Tous les enseignants ?", this);

    for (auto &ens : m_testProjet.getEnseignants()) {
        QString nom = QString::fromStdString(ens->getNom());
        m_comboEnseignants->addItem(nom, QVariant::fromValue((void*)ens.get()));
    }

    // QDateTimeEdit pour la date+heure
    m_dateTimeEdit = new QDateTimeEdit(this);
    m_dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
    m_dateTimeEdit->setDateTime(QDateTime(QDate(2025,1,1), QTime(9,0)));

    // Boutons
    m_btnValider   = new QPushButton("Valider le Créneau", this);
    m_btnPlanning  = new QPushButton("Ouvrir Planning", this);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Choisir un étudiant :"));
    layout->addWidget(m_comboEtudiants);
    layout->addWidget(m_ckTousEtudiants);

    layout->addWidget(new QLabel("Choisir un enseignant :"));
    layout->addWidget(m_comboEnseignants);
    layout->addWidget(m_ckTousEnseignants);

    layout->addWidget(new QLabel("Date/Heure du créneau :"));
    layout->addWidget(m_dateTimeEdit);

    layout->addWidget(m_btnValider);
    layout->addWidget(m_btnPlanning);

    setLayout(layout);

    // Connect
    connect(m_btnValider, &QPushButton::clicked,
            this, &CreneauxDialog::onValiderCreneau);

    connect(m_btnPlanning, &QPushButton::clicked,
            this, &CreneauxDialog::onOuvrirPlanning);
}*/

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

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_btnValider);
    buttonLayout->addWidget(m_btnPlanning);

    layout->addLayout(buttonLayout);

    // Connexions
    connect(m_btnValider, &QPushButton::clicked, this, &CreneauxDialog::onValiderCreneau);
    connect(m_btnPlanning, &QPushButton::clicked, this, &CreneauxDialog::onOuvrirPlanning);
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

    QMessageBox::information(this, "Créneau ajouté",
                             QString("<font color='black'>Créneau %1 %2 ajouté/associé !</font>").arg(dateStr, heureStr));
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
