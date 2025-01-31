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
#include <QMessageBox>
#include <QCloseEvent>
#include <QFile>
#include <QCalendarWidget>



#include "Tests/testprojet.h"
#include "planningdialog.h"

class CreneauxDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreneauxDialog(TestProjet &projet, QWidget *parent = nullptr);
    ~CreneauxDialog();

private slots:
    void onValiderCreneau();
    void onOuvrirPlanning();
    void afficherCreneauxAttribues();
    void mettreAJourCreneaux();
    void supprimerCreneau();


protected:
    void closeEvent(QCloseEvent *event) override;


private:
    TestProjet &m_testProjet;

    QComboBox   *m_comboEtudiants;
    QComboBox   *m_comboEnseignants;
    QCheckBox   *m_ckTousEtudiants;
    QCheckBox   *m_ckTousEnseignants;
    QTableWidget *m_tableCreneaux;
    QPushButton *m_btnSupprimerCreneau;

    QDateTimeEdit *m_dateTimeEdit;

    QPushButton *m_btnValider;
    QPushButton *m_btnPlanning;

signals:
    void creneauxModifies();
};

#endif // CRENEAUXDIALOG_H
