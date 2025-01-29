#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>



#include "Tests/testprojet.h"
#include "creneauxdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onChargerCsv();

private:
    QPushButton *m_btnReprendre;
    QPushButton *m_btnSupprimer;

    void verifierEtatSauvegarde();
    void supprimerSauvegarde();
    void onReprendreSauvegarde();




private:
    QWidget     *m_centralWidget;
    QPushButton *m_btnChargerCsv;
    QLabel      *m_labelInfo;

    // Notre logique
    TestProjet   m_testProjet;
};

#endif // MAINWINDOW_H
