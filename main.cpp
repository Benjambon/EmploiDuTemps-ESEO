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

    // Ajout du test pour la classe Salle
    Salle salleInfo("001", TypeSalle::INFORMATIQUE);
    std::cout << "Affichage de la salle : " << salleInfo.toString() << std::endl;

    QString filepathSalles = data_path + "salles.json";
    std::vector<Salle> listeSalles;
    listeSalles.push_back(salleInfo);

    Salle::writeToJSON(listeSalles, filepathSalles);
    std::cout << "Salle sauvegardee dans : " << filepathSalles.toStdString() << std::endl;


    // TEST Controleurs

    /* tester si le resultat est bein celui quon souhaite

    std::string Nom = "Vadot";
    std::string resNom = Controleur_enseignant::TestNomEnseignant(Nom);
    std::cout << resNom << std::endl;


    std::string Nom2 = "";
    std::string resNom2 = Controleur_enseignant::TestNomEnseignant(Nom2);
    std::cout << resNom2 << std::endl;

    std::string Prenom = "Antoine";
    std::string resPrenom = Controleur_enseignant::TestPrenomEnseignant(Prenom);
    std::cout << resPrenom << std::endl;

    std::string Prenom2 = "";
    std::string resPrenom2 = Controleur_enseignant::TestPrenomEnseignant(Prenom2);
    std::cout << resPrenom2 << std::endl;

    std::string Mail = "antoine.vadot@gmail.com";
    std::string resMail = Controleur_enseignant::TestMailEnseignant(Mail);
    std::cout << resMail << std::endl;

    std::string Mail2 = "antoine.vadot.com";
    std::string resMail2 = Controleur_enseignant::TestMailEnseignant(Mail2);
    std::cout << resMail2 << std::endl;


    std::string nomGroupe1 = "Groupe A";
    std::string resGroupe1 = Controleur_groupeetudiant::TestNomGroupe(nomGroupe1);
    std::cout << resGroupe1 << std::endl; // Affiche "Nom de groupe OK"

    std::string nomGroupe2 = "";
    std::string resGroupe2 = Controleur_groupeetudiant::TestNomGroupe(nomGroupe2);
    std::cout << resGroupe2 << std::endl; // Affiche "Le nom du groupe ne peut pas etre vide !"


    // Test d'une salle valide
    std::string resSalle1 = Controleur_salle::TestSalle("104", TypeSalle::INFORMATIQUE);
    std::cout << resSalle1 << std::endl; // Affiche "Salle OK"

    // Test d'une salle invalide (lettres à la place des chiffres)
    std::string resSalle2 = Controleur_salle::TestSalle("A12", TypeSalle::SALLE);
    std::cout << resSalle2 << std::endl; // Affiche l'erreur

    // Test d'une salle invalide (trop de chiffres)
    std::string resSalle3 = Controleur_salle::TestSalle("1004", TypeSalle::ELECTRONIQUE);
    std::cout << resSalle3 << std::endl; // Affiche l'erreur

*/
    MainWindow w(data_path);
    w.show();

    return a.exec();
}
