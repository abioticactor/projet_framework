#include "CreneauxDialog.h"
#include <QMessageBox>

CreneauxDialog::CreneauxDialog(TestProjet &projet, QWidget *parent)
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
}

CreneauxDialog::~CreneauxDialog()
{
}

void CreneauxDialog::onValiderCreneau()
{
    // On récupère la date/heure
    QDateTime dt = m_dateTimeEdit->dateTime();
    QString dateStr  = dt.date().toString("yyyy-MM-dd");
    QString heureStr = dt.time().toString("HH:mm");

    // On sait que la méthode 'creerEtAssignerCreneaux()' de TestProjet
    // crée déjà par exemple 5 jours, 9..17h, etc.
    // Si on ne modifie pas TestProjet, on ne peut pas paramétrer la date/heure.
    //
    // Donc, soit on recopie la logique => on code localement la creation d'un Creneau
    // soit on modifie TestProjet pour avoir "creerCreneau(date, heure, etc.)".
    //
    // Pour la démo, on va simuler :
    auto c = std::make_shared<Creneau>(dateStr.toStdString(), heureStr.toStdString());

    // Si la checkbox "Tous les étudiants" est cochée => on associe ce creneau à tous
    // Sinon => on prend l'étudiant choisi
    if (m_ckTousEtudiants->isChecked()) {
        // associer c à tous les étudiants
        for (auto &etu : m_testProjet.getEtudiants()) {
            etu->ajouterDisponibiliteEtudiant(c);
        }
    } else {
        // un seul étudiant (celui choisi)
        int index = m_comboEtudiants->currentIndex();
        // on a stocké un pointer, c'est un peu tricky. On peut
        // en vrai stocker un ID ou un shared_ptr
        // ...
        // Pour la démonstration, on va par ex. re-chercher l'Etudiant
        // via index
        auto &etudiants = m_testProjet.getEtudiants();
        if (index >= 0 && index < (int)etudiants.size()) {
            etudiants[index]->ajouterDisponibiliteEtudiant(c);
        }
    }

    // Idem pour les enseignants
    if (m_ckTousEnseignants->isChecked()) {
        for (auto &ens : m_testProjet.getEnseignants()) {
            ens->ajouterDisponibilite(c);
        }
    } else {
        int idxEnseignant = m_comboEnseignants->currentIndex();
        auto &enseignants = m_testProjet.getEnseignants();
        if (idxEnseignant >= 0 && idxEnseignant < (int)enseignants.size()) {
            enseignants[idxEnseignant]->ajouterDisponibilite(c);
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
