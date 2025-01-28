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
#include <QItemDelegate>
#include <QApplication>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QInputDialog>


#include "Tests/TestProjet.h"

class PlanningDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PlanningDialog(TestProjet &projet, QWidget *parent = nullptr);
    ~PlanningDialog();
    void remplirTable(const QString &dateStr);

private slots:
    void onDateChanged();
    void onCloseAll();
    void onExporterSoutenances();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    TestProjet &m_testProjet;

    QCalendarWidget *m_calendar;
    QTableWidget    *m_table;
    QPushButton     *m_btnFermer;
    QPushButton *m_btnExporter;

    QString choisirOrdreExport();

};

#endif // PLANNINGDIALOG_H
