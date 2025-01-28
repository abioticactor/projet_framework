#include "PlanningDialog.h"
#include "creneauxdialog.h"


PlanningDialog::PlanningDialog(TestProjet &projet, QWidget *parent)
    : QDialog(parent),
    m_testProjet(projet)
{
    setWindowTitle("Planning");

    m_calendar = new QCalendarWidget(this);
    m_table    = new QTableWidget(this);
    m_table->setColumnCount(3);
    QStringList headers; headers << "Heure" << "Etudiant" << "Jury";
    m_table->setHorizontalHeaderLabels(headers);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_btnExporter = new QPushButton("Exporter", this); // Bouton Exporter
    m_btnFermer = new QPushButton("Fermer", this);


    QVBoxLayout *vlay = new QVBoxLayout(this);
    vlay->addWidget(m_calendar);
    vlay->addWidget(m_table);
    vlay->addWidget(m_btnExporter); // Ajouter le bouton Exporter
    vlay->addWidget(m_btnFermer);


    setLayout(vlay);

    connect(m_calendar, &QCalendarWidget::selectionChanged,
            this, &PlanningDialog::onDateChanged);

    // Bouton "Fermer" => ferme tout
    connect(m_btnFermer, &QPushButton::clicked,
            this, &PlanningDialog::onCloseAll);

    connect(m_btnExporter, &QPushButton::clicked,
            this, &PlanningDialog::onExporterSoutenances); // Connexion du bouton Exporter


    // Remplir pour la date du jour
    onDateChanged();
}

PlanningDialog::~PlanningDialog()
{}

void PlanningDialog::onDateChanged()
{
    QDate d = m_calendar->selectedDate();
    QString dateStr = d.toString("yyyy-MM-dd");
    remplirTable(dateStr);
}

void PlanningDialog::remplirTable(const QString &dateStr)
{
    m_table->clearContents();
    m_table->setRowCount(0);

    const std::vector<Soutenance::Affectation>& affectations = m_testProjet.getSoutenance().getAffectations();

    int row = 0;
    for (const auto& aff : affectations) {
        QString cDate = QString::fromStdString(aff.creneau->getDate());
        if (cDate == dateStr) { // Comparez correctement les dates
            m_table->insertRow(row);

            QString heure = QString::fromStdString(aff.creneau->getHeure());
            QString etu   = QString::fromStdString(aff.etu->getNom()) + " "
                          + QString::fromStdString(aff.etu->getPrenom());
            QString jury  = QString::fromStdString(aff.jury->getPresident()->getNom())
                           + " & "
                           + QString::fromStdString(aff.jury->getCojury()->getNom());

            m_table->setItem(row, 0, new QTableWidgetItem(heure));
            m_table->setItem(row, 1, new QTableWidgetItem(etu));
            m_table->setItem(row, 2, new QTableWidgetItem(jury));

            row++;
        }
    }
}


void PlanningDialog::onCloseAll()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirmation de fermeture",
        "Voulez-vous vraiment fermer l'application ?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QApplication::quit(); // Ferme tout si l'utilisateur confirme
    }
    // Sinon, ne rien faire (rester dans la fenêtre)
}

void PlanningDialog::closeEvent(QCloseEvent *event)
{
    // Si des créneaux existent, sauvegarder avant de fermer
    if (!m_testProjet.getCreneaux().empty()) {
        QString fichier = "backup.json";
        m_testProjet.sauvegarderDonnees(fichier);

        QMessageBox::information(this, "Sauvegarde",
                                 "Les données ont été sauvegardées automatiquement.");
    }

    event->accept(); // Accepter la fermeture
}

void PlanningDialog::onExporterSoutenances()
{
    // Afficher la boîte de choix
    QString ordre = choisirOrdreExport();
    if (ordre.isEmpty()) {
        return; // L'utilisateur a annulé
    }

    QString fichier = QFileDialog::getSaveFileName(this, "Exporter les soutenances", "", "Fichiers CSV (*.csv)");
    if (fichier.isEmpty()) {
        return; // L'utilisateur a annulé
    }

    QFile file(fichier);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible de créer le fichier CSV.");
        return;
    }

    QTextStream stream(&file);

    // En-têtes du fichier CSV
    stream << "Date,Heure,Etudiant,Jury President,Jury Co-jury\n";

    // Récupérer les affectations et les trier selon le choix
    auto affectations = m_testProjet.getSoutenance().getAffectations();

    if (ordre == "Date croissante") {
        std::sort(affectations.begin(), affectations.end(), [](const auto &a, const auto &b) {
            return (a.creneau->getDate() < b.creneau->getDate()) ||
                   (a.creneau->getDate() == b.creneau->getDate() && a.creneau->getHeure() < b.creneau->getHeure());
        });
    } else if (ordre == "Ordre alphabétique (Étudiants)") {
        std::sort(affectations.begin(), affectations.end(), [](const auto &a, const auto &b) {
            return a.etu->getNom() < b.etu->getNom();
        });
    } else if (ordre == "Date décroissante") {
        std::sort(affectations.begin(), affectations.end(), [](const auto &a, const auto &b) {
            return (a.creneau->getDate() > b.creneau->getDate()) ||
                   (a.creneau->getDate() == b.creneau->getDate() && a.creneau->getHeure() > b.creneau->getHeure());
        });
    }

    // Exporter les données triées
    for (const auto &aff : affectations) {
        stream << QString::fromStdString(aff.creneau->getDate()) << ","
               << QString::fromStdString(aff.creneau->getHeure()) << ","
               << QString::fromStdString(aff.etu->getNom()) << " " << QString::fromStdString(aff.etu->getPrenom()) << ","
               << QString::fromStdString(aff.jury->getPresident()->getNom()) << ","
               << QString::fromStdString(aff.jury->getCojury()->getNom()) << "\n";
    }

    file.close();

    QMessageBox::information(this, "Exportation terminée", "Les soutenances ont été exportées avec succès !");
}


QString PlanningDialog::choisirOrdreExport()
{
    QStringList options = {"Date croissante", "Ordre alphabétique (Étudiants)", "Date décroissante"};
    bool ok;

    QString choix = QInputDialog::getItem(
        this,
        "Choisir l'ordre d'exportation",
        "Veuillez choisir l'ordre pour exporter les soutenances :",
        options,
        0, // Index par défaut
        false, // Pas d'édition libre
        &ok
        );

    if (ok && !choix.isEmpty()) {
        return choix;
    }

    return ""; // Retourne une chaîne vide si l'utilisateur annule
}
