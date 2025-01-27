#ifndef CRENEAUXDIALOG_H
#define CRENEAUXDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QDateTimeEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Tests/TestProjet.h"
#include "PlanningDialog.h"

class CreneauxDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreneauxDialog(TestProjet &projet, QWidget *parent = nullptr);
    ~CreneauxDialog();

private slots:
    void onValiderCreneau();
    void onOuvrirPlanning();

private:
    TestProjet &m_testProjet;

    QComboBox   *m_comboEtudiants;
    QComboBox   *m_comboEnseignants;
    QCheckBox   *m_ckTousEtudiants;
    QCheckBox   *m_ckTousEnseignants;

    QDateTimeEdit *m_dateTimeEdit; // pour choisir date+heure

    QPushButton *m_btnValider;
    QPushButton *m_btnPlanning;
};

#endif // CRENEAUXDIALOG_H
