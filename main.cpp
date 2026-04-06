#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <iostream>
#include <QDebug>

#include <enseignant.h>
#include <salle.h>
#include <groupeetudiant.h>
#include <ecue.h>

#include "tests/test_enseignant.h"
#include "tests/test_salle.h"
#include "tests/test_groupeetudiant.h"
#include "tests/test_ecue.h"
#include "tests/test_creneau.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    int totalErrors = 0;

    TestEnseignant testEns;
    totalErrors += QTest::qExec(&testEns, argc, argv);

    TestSalle testSalle;
    totalErrors += QTest::qExec(&testSalle, argc, argv);

    TestGroupeEtudiant testGrp;
    totalErrors += QTest::qExec(&testGrp, argc, argv);

    TestEcue testEcue;
    totalErrors += QTest::qExec(&testEcue, argc, argv);

    TestCreneau testCreneau;
    totalErrors += QTest::qExec(&testCreneau, argc, argv);

    if (totalErrors != 0) {
        qDebug() << " ATTENTION : Il y a eu" << totalErrors << "echec(s) dans les tests !";
    } else {
        qDebug() << " SUCCES : L'integralite des tests a reussi !";
    }



    QDir dir(QCoreApplication::applicationDirPath());
    while (!dir.exists("data") && dir.cdUp()) {}
    QString data_path = dir.absoluteFilePath("data") + "/";

    std::cout << "Data : " << data_path.toStdString() << std::endl;

    MainWindow w(data_path);
    w.show();

    return a.exec();
}
