#include "mainwindow.h"
#include "ecue.h"

#include <iostream>
#include <QString>
#include <QCoreApplication>
#include <QApplication>
#include <QDir>

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

    GroupeEtudiant gE("E4e");

    Ecue ecue(e, gE, eTypeCours::CM, 14, 0);
    // 2. Préparation du chemin complet du fichier
    QString filepath = data_path + "ecue.json";

    // 3. Création du vecteur et ajout de l'enseignant
    std::vector<Ecue> listeEcue;
    listeEcue.push_back(ecue);

    //Enseignant e2("trenchant","vincent");
    //listeEcue.push_back(e2);

    // 4. Sauvegarde dans le fichier JSON
    Ecue::writeToJSON(listeEcue, filepath);
    std::cout << "Ecue sauvegarde dans : " << filepath.toStdString() << std::endl;
    MainWindow w(data_path);
    w.show();


    return 0 ;
}
