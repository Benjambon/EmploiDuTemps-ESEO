#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <iostream>
#include "enseignant.h"
#include "salle.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Recherche automatique et concise du dossier data
    QDir dir(QCoreApplication::applicationDirPath());
    while (!dir.exists("data") && dir.cdUp()) {}
    QString data_path = dir.absoluteFilePath("data") + "/";

    std::cout << "Data : " << data_path.toStdString() << std::endl;

    MainWindow w(data_path);
    w.show();

    return a.exec();
}
