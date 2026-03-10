#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <iostream>
#include "enseignant.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Recherche automatique et concise du dossier data
    QDir dir(QCoreApplication::applicationDirPath());
    while (!dir.exists("data") && dir.cdUp()) {}
    QString data_path = dir.absoluteFilePath("data") + "/";

    std::cout << "Data : " << data_path.toStdString() << std::endl;

    // 1. Création de l'enseignant
    Enseignant e("zidane", "zinedine");

    // 2. Préparation du chemin complet du fichier
    QString filepath = data_path + "enseignants.json";

    // 3. Création du vecteur et ajout de l'enseignant
    std::vector<Enseignant> listeEnseignants;
    listeEnseignants.push_back(e);

    Enseignant e2("trenchant","vincent");
    listeEnseignants.push_back(e2);

    // 4. Sauvegarde dans le fichier JSON
    Enseignant::writeToJSON(listeEnseignants, filepath);
    std::cout << "Enseignant sauvegarde dans : " << filepath.toStdString() << std::endl;
    MainWindow w(data_path);
    w.show();


    return a.exec();
}
