#ifndef PLANNINGDIALOG_H
#define PLANNINGDIALOG_H

#include <QDialog>
#include <QCalendarWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDate>
#include <QHeaderView>
#include "Tests/TestProjet.h"

class PlanningDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PlanningDialog(TestProjet &projet, QWidget *parent = nullptr);
    ~PlanningDialog();

private slots:
    void onDateChanged();
    void onCloseAll();

private:
    TestProjet &m_testProjet;

    QCalendarWidget *m_calendar;
    QTableWidget    *m_table;
    QPushButton     *m_btnFermer;

    void remplirTable(const QString &dateStr);
};

#endif // PLANNINGDIALOG_H
