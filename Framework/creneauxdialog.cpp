#include "CreneauxDialog.h"
#include <QMessageBox>

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
    setWindowTitle("Fenêtre 2 : Créer / Assigner Créneaux");

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

    // Boutons
    m_btnValider  = new QPushButton("Valider le Créneau", this);
    m_btnPlanning = new QPushButton("Ouvrir Planning", this);

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
}


CreneauxDialog::~CreneauxDialog()
{
}

/*void CreneauxDialog::onValiderCreneau()
{
    QDateTime dt = m_dateTimeEdit->dateTime();
    QString dateStr = dt.date().toString("yyyy-MM-dd");
    QString heureStr = dt.time().toString("HH:mm");

    // Crée un nouveau créneau
    auto creneau = std::make_shared<Creneau>(dateStr.toStdString(), heureStr.toStdString());

    // Ajouter le créneau à m_creneaux dans TestProjet s'il n'existe pas déjà
    auto& creneaux = m_testProjet.getCreneaux(); // Ajoutez un getter pour m_creneaux dans TestProjet
    bool alreadyExists = std::any_of(creneaux.begin(), creneaux.end(),
                                     [&](auto& c) { return *c == *creneau; });

    if (!alreadyExists) {
        creneaux.push_back(creneau);
        std::cout << "Créneau ajouté : " << dateStr.toStdString() << " " << heureStr.toStdString() << "\n";
    } else {
        std::cout << "Créneau déjà existant : " << dateStr.toStdString() << " " << heureStr.toStdString() << "\n";
    }

    // Associer ce créneau aux étudiants ou enseignants si demandé
    if (m_ckTousEtudiants->isChecked()) {
        for (auto &etu : m_testProjet.getEtudiants()) {
            etu->ajouterDisponibiliteEtudiant(creneau);
            std::cout << "Ajout du créneau pour étudiant : " << etu->getNom() << "\n";
        }
    } else {
        int index = m_comboEtudiants->currentIndex();
        if (index > 0) {
            auto &etu = m_testProjet.getEtudiants().at(index);
            etu->ajouterDisponibiliteEtudiant(creneau);
            std::cout << "Ajout du créneau pour étudiant unique : " << etu->getNom() << "\n";
        }
    }

    if (m_ckTousEnseignants->isChecked()) {
        for (auto &ens : m_testProjet.getEnseignants()) {
            ens->ajouterDisponibilite(creneau);
            std::cout << "Ajout du créneau pour enseignant : " << ens->getNom() << "\n";
        }
    } else {
        int index = m_comboEnseignants->currentIndex();
        if (index > 0) {
            auto &ens = m_testProjet.getEnseignants().at(index);
            ens->ajouterDisponibilite(creneau);
            std::cout << "Ajout du créneau pour enseignant unique : " << ens->getNom() << "\n";
        }
    }

    QMessageBox::information(this, "Créneau ajouté",
                             QString("Créneau %1 %2 ajouté/associé !").arg(dateStr, heureStr));
}*/

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
                             QString("Créneau %1 %2 ajouté/associé !").arg(dateStr, heureStr));
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
