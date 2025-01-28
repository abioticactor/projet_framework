#include "PlanningDialog.h"
#include <QItemDelegate>
#include <QApplication>
#include <QStyleOption>
#include <QPainter>
#include "creneauxdialog.h"


PlanningDialog::PlanningDialog(TestProjet &projet, QWidget *parent)
    : QDialog(parent),
    m_testProjet(projet)
{
    setWindowTitle("Fenêtre 3 : Planning");
    setWindowFlags(Qt::FramelessWindowHint); // Supprime la barre de titre

    // Ajouter une couleur de fond autour du calendrier et de la table
    setStyleSheet(
        "PlanningDialog { "
        "background-color: #eceae3; "  // Couleur de fond autour
        "border-radius: 15px; "       // Bordures arrondies
        "padding: 20px; "             // Espace autour des widgets
        "}"
        );
    setWindowTitle("Planning");

    m_calendar = new QCalendarWidget(this);
    m_table = new QTableWidget(this);
    m_table->setColumnCount(3);
    QStringList headers;
    headers << "Heure"
            << "Etudiant"
            << "Jury";
    m_table->setHorizontalHeaderLabels(headers);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Ajout du style personnalisé pour la table (déjà présent dans votre code)
    m_table->setStyleSheet(
        "QTableWidget { "
        "border-radius: 10px; "
        "background-color: #fff; "
        "padding: 5px; "
        "}"
        "QTableWidget::item { "
        "border: 1px solid #ccc; "
        "border-radius: 5px; "
        "padding: 10px; "
        "}"
        "QTableWidget QHeaderView::section { "
        "background-color: #ffbea3; "
        "color: black; "
        "border: none; "
        "font-weight: bold; "
        "padding: 5px; "
        "}"
        "QTableWidget::item:hover { "
        "background-color: #FFF; "
        "}"
        );

    m_btnFermer = new QPushButton("Fermer", this);
    m_btnFermer->setFixedSize(90, 30);
    m_btnFermer->setStyleSheet(
        "QPushButton { "
        "background-color: #fe7868; "
        "border-radius: 15px; "
        "color: white; "
        "font-weight: bold; "
        "border: none; "
        "}"
        "QPushButton:hover { background-color: darkred; }"
        );

    // Style du calendrier (déjà présent dans votre code)
    m_calendar->setStyleSheet(
        "QCalendarWidget { "
        "background-color: #FFF; "
        "border: none; "
        "}"
        "QCalendarWidget QWidget { "
        "background-color: #FFF; "
        "alternate-background-color: #ffbea3; "
        "color: black; "
        "}"
        "QCalendarWidget QAbstractItemView:enabled { "
        "selection-background-color: #ffbea3; "
        "selection-color: white; "
        "color: black; "
        "}"
        "QCalendarWidget QToolButton { "
        "background-color: #FFF; "
        "color: black; "
        "padding: 5px; "
        "font-size: 14px; "
        "font-weight: bold; "
        "}"
        "QCalendarWidget QToolButton:hover { "
        "background-color: #FFF; "
        "}"
        "QCalendarWidget QToolButton::menu-indicator { "
        "width: 0px; "
        "}"
        "QCalendarWidget QToolButton#qt_calendar_prevmonth, "
        "QCalendarWidget QToolButton#qt_calendar_nextmonth { "
        "background-color: #FFF; "
        "border: none; "
        "border-radius: 15px; "
        "color: black; "
        "font-size: 14px; "
        "padding: 5px; "
        "}"
        "QCalendarWidget QTableView { "
        "color: black; "
        "gridline-color: #CCC; "
        "}"
        "QCalendarWidget QHeaderView::section { "
        "color: black; "
        "background-color: #FFF; "
        "border: none; "
        "font-weight: bold; "
        "}"
        );


    QVBoxLayout *vlay = new QVBoxLayout(this);
    vlay->addWidget(m_calendar);
    vlay->addWidget(m_table);
    vlay->addWidget(m_btnExporter); // Ajouter le bouton Exporter
    vlay->addWidget(m_btnFermer);

    // Ajouter le bouton dans le coin inférieur droit
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_btnFermer);
    vlay->addLayout(buttonLayout);
    m_btnExporter = new QPushButton("Exporter", this); // Bouton Exporter
    m_btnFermer = new QPushButton("Fermer", this);

    setLayout(vlay);

    connect(m_calendar, &QCalendarWidget::selectionChanged, this, &PlanningDialog::onDateChanged);
    connect(m_btnFermer, &QPushButton::clicked, this, &PlanningDialog::onCloseAll);

    connect(m_btnExporter, &QPushButton::clicked,
            this, &PlanningDialog::onExporterSoutenances); // Connexion du bouton Exporter


    // Remplir pour la date du jour
    onDateChanged();

    showMaximized();
}

PlanningDialog::~PlanningDialog()
{
}

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

    const std::vector<Soutenance::Affectation> &affectations = m_testProjet.getSoutenance().getAffectations();

    int row = 0;
    for (const auto &aff : affectations)
    {
        QString cDate = QString::fromStdString(aff.creneau->getDate());
        if (cDate == dateStr)
        { // Comparez correctement les dates
            m_table->insertRow(row);

            QString heure = QString::fromStdString(aff.creneau->getHeure());
            QString etu = QString::fromStdString(aff.etu->getNom()) + " " + QString::fromStdString(aff.etu->getPrenom());
            QString jury = QString::fromStdString(aff.jury->getPresident()->getNom()) + " & " + QString::fromStdString(aff.jury->getCojury()->getNom());

            m_table->setItem(row, 0, new QTableWidgetItem(heure));
            m_table->setItem(row, 1, new QTableWidgetItem(etu));
            m_table->setItem(row, 2, new QTableWidgetItem(jury));

            row++;
        }
    }
}

void PlanningDialog::onCloseAll()
{
    QApplication::quit();
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
