/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QWidget>

#include "Tests/TestProjet.h"
#include "CreneauxDialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onChargerCsv();

private:
    QWidget     *m_centralWidget;
    QPushButton *m_btnChargerCsv;
    QLabel      *m_labelInfo;

    // Notre logique
    TestProjet   m_testProjet;
};

#endif // MAINWINDOW_H
