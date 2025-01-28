#include "PlanningDialog.h"
#include <QItemDelegate>
#include <QApplication>

PlanningDialog::PlanningDialog(TestProjet &projet, QWidget *parent)
    : QDialog(parent),
    m_testProjet(projet)
{
    setWindowTitle("Fenêtre 3 : Planning");

    m_calendar = new QCalendarWidget(this);
    m_table    = new QTableWidget(this);
    m_table->setColumnCount(3);
    QStringList headers; headers << "Heure" << "Etudiant" << "Jury";
    m_table->setHorizontalHeaderLabels(headers);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_btnFermer = new QPushButton("Fermer", this);

    QVBoxLayout *vlay = new QVBoxLayout(this);
    vlay->addWidget(m_calendar);
    vlay->addWidget(m_table);
    vlay->addWidget(m_btnFermer);

    setLayout(vlay);

    connect(m_calendar, &QCalendarWidget::selectionChanged,
            this, &PlanningDialog::onDateChanged);

    // Bouton "Fermer" => ferme tout
    connect(m_btnFermer, &QPushButton::clicked,
            this, &PlanningDialog::onCloseAll);

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
    // Fermer toutes les fenetres => on appelle:
    QApplication::quit();
}
