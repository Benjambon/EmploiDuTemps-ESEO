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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ==========================================
    // DEBUT DU BLOC DE TESTS UNITAIRES
    // ==========================================
    std::cout << "\n========== LANCEMENT DES TESTS UNITAIRES ==========\n" << std::endl;

    int totalErrors = 0;

    // 1. Test Enseignant
    TestEnseignant testEns;
    totalErrors += QTest::qExec(&testEns, argc, argv);

    // 2. Test Salle
    TestSalle testSalle;
    totalErrors += QTest::qExec(&testSalle, argc, argv);

    // 3. Test GroupeEtudiant
    TestGroupeEtudiant testGrp;
    totalErrors += QTest::qExec(&testGrp, argc, argv);

    // 4. Test Ecue
    TestEcue testEcue;
    totalErrors += QTest::qExec(&testEcue, argc, argv);

    // Bilan global
    if (totalErrors != 0) {
        qDebug() << " ATTENTION : Il y a eu" << totalErrors << "echec(s) dans les tests !";
        // return -1; // Décommenter pour bloquer le lancement si les tests échouent
    } else {
        qDebug() << " SUCCES : L'integralite des tests a reussi !";
    }

    // ==========================================
    // FIN DU BLOC DE TESTS
    // ==========================================


    // Recherche automatique et concise du dossier data
    QDir dir(QCoreApplication::applicationDirPath());
    while (!dir.exists("data") && dir.cdUp()) {}
    QString data_path = dir.absoluteFilePath("data") + "/";

    std::cout << "Data : " << data_path.toStdString() << std::endl;

    MainWindow w(data_path);
    w.show();

    return a.exec();
}
