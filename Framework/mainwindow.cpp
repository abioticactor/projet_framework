/*#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}*/

#include "MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Fenêtre 1 : Charger CSV");

    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    m_btnChargerCsv = new QPushButton("Charger un fichier CSV", this);
    m_labelInfo     = new QLabel("Aucun fichier chargé.", this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_btnChargerCsv);
    layout->addWidget(m_labelInfo);

    m_centralWidget->setLayout(layout);

    // Connexion
    connect(m_btnChargerCsv, &QPushButton::clicked,
            this, &MainWindow::onChargerCsv);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onChargerCsv()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Ouvrir CSV"), QString(),
        tr("Fichiers CSV (*.csv);;Tous les fichiers (*)"));
    if (fileName.isEmpty()) {
        return;
    }

    // Appel à la logique du TestProjet
    m_testProjet.extraireDonnees(fileName.toStdString());

    m_labelInfo->setText("Données extraites depuis : " + fileName);

    // Ensuite, on ouvre la 2ᵉ fenêtre
    CreneauxDialog *dlg = new CreneauxDialog(m_testProjet);
    dlg->show();

    // On ferme la fenêtre actuelle (MainWindow)
    this->close();
}

