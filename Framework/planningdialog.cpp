#include "PlanningDialog.h"
#include <QItemDelegate>
#include <QApplication>
#include <QStyleOption>
#include <QPainter>

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

    // Layout principal
    QVBoxLayout *vlay = new QVBoxLayout(this);
    vlay->addWidget(m_calendar);
    vlay->addWidget(m_table);

    // Ajouter le bouton dans le coin inférieur droit
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_btnFermer);
    vlay->addLayout(buttonLayout);

    setLayout(vlay);

    connect(m_calendar, &QCalendarWidget::selectionChanged, this, &PlanningDialog::onDateChanged);
    connect(m_btnFermer, &QPushButton::clicked, this, &PlanningDialog::onCloseAll);

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
}
