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
    setStyleSheet(
        "MainWindow { "
        "background-color: #eceae3; "  // Couleur de fond autour
        "border-radius: 15px; "       // Bordures arrondies
        "padding: 20px; "             // Espace autour des widgets
        "}"
        );

    QString buttonStyle = "QPushButton {"
                          "  background-color: #fed0bc;"
                          "  color: black;"
                          "  border: none;"
                          "  border-radius: 5px;"
                          "  padding: 10px 15px;"
                          "  font-size: 14px;"
                          "}"
                          "QPushButton:hover {"
                          "  background-color: #fca691;"
                          "}"
                          "QPushButton:pressed {"
                          "  background-color: #fca691;"
                          "}";

    QString labelStyle = "QLabel {"
                         "  font-size: 14px;"
                         "  color: #333;"
                         "  padding: 5px;"
                         "}";

    // Appliquer le style
    m_btnChargerCsv->setStyleSheet(buttonStyle);
    m_labelInfo->setStyleSheet(labelStyle);

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

