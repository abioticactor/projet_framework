#include "mainwindow.h"
#include "Tests/personnetest.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/

    //Test classe Personne
    PersonneTest::runTests();


    return 0;
}
