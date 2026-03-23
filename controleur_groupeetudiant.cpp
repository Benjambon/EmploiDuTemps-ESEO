#include "controleur_groupeetudiant.h"
#include "groupeetudiantdialog.h"
#include <QMessageBox>
#include <QDebug>

Controleur_groupeetudiant::Controleur_groupeetudiant() {}

GroupeEtudiant* Controleur_groupeetudiant::creationGroupe(void)
{
    GroupeEtudiantDialog dialog(nullptr);

    // Initialisation avec une erreur pour forcer l'entrée dans la boucle
    GroupeEtudiant::code_erreur_nom err_nom = GroupeEtudiant::NOM_VIDE;

    while (!(err_nom == GroupeEtudiant::NOM_OK))
    {
        dialog.show();
        bool res_exec = dialog.exec();

        // Si l'utilisateur annule
        if (res_exec == QDialog::Rejected) {
            return nullptr;
        }

        // Instance temporaire pour validation
        GroupeEtudiant tempGroupe(dialog.getNom());

        err_nom = tempGroupe.isNomValid();

        switch (err_nom)
        {
        case GroupeEtudiant::NOM_OK:
            break;
        case GroupeEtudiant::NOM_VIDE:
            qDebug() << "Le nom du groupe ne peut pas etre vide";
            QMessageBox::warning(&dialog, "Erreur", "Le nom du groupe ne peut pas être vide.");
            break;
        }
    }

    // Sortie de la boucle : le nom est valide
    return new GroupeEtudiant(dialog.getNom());
}
