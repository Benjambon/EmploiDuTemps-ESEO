#include "controleur_enseignant.h"
#include "enseignantdialog.h"
#include <QMessageBox>
#include <QDebug>

Controleur_enseignant::Controleur_enseignant() {}

Enseignant* Controleur_enseignant::creationEnseignant(void)
{
    EnseignantDialog dialog(nullptr);

    Enseignant::code_erreur_nom err_nom = Enseignant::NOM_VIDE;
    Enseignant::code_erreur_prenom err_prenom = Enseignant::PRENOM_VIDE;
    Enseignant::code_erreur_mail err_mail = Enseignant::MAIL_SYNTAXE;

    std::string nom, prenom, mail;

    while (!(err_nom == Enseignant::NOM_OK && err_prenom == Enseignant::PRENOM_OK && err_mail == Enseignant::MAIL_OK))
    {
        dialog.show();
        bool res_exec = dialog.exec();

        if (res_exec == QDialog::Rejected) {
            return nullptr;
        }

        nom = dialog.getNom();
        prenom = dialog.getPrenom();
        mail = dialog.getMail();

        Enseignant tempEnseignant;
        if (mail.empty()) {
            // Utilise le constructeur qui auto-génère l'e-mail
            tempEnseignant = Enseignant(nom, prenom);
        } else {
            tempEnseignant = Enseignant(nom, prenom, mail);
        }

        // 1. Validation du nom
        err_nom = tempEnseignant.isNomValid();
        switch (err_nom)
        {
        case Enseignant::NOM_OK: break;
        case Enseignant::NOM_VIDE:
            QMessageBox::warning(&dialog, "Erreur", "Le nom ne peut pas être vide.");
            break;
        case Enseignant::NOM_CHIFFRE:
            QMessageBox::warning(&dialog, "Erreur", "Le nom ne doit pas contenir de chiffres.");
            break;
        }

        // 2. Validation du prénom
        err_prenom = tempEnseignant.isPrenomValid();
        switch (err_prenom)
        {
        case Enseignant::PRENOM_OK: break;
        case Enseignant::PRENOM_VIDE:
            QMessageBox::warning(&dialog, "Erreur", "Le prénom ne peut pas être vide.");
            break;
        case Enseignant::PRENOM_CHIFFRE:
            QMessageBox::warning(&dialog, "Erreur", "Le prénom ne doit pas contenir de chiffres.");
            break;
        }

        // 3. Validation de l'e-mail (uniquement si le nom et prénom sont OK pour éviter l'accumulation de pop-ups)
        err_mail = tempEnseignant.isMailValid();
        if (err_nom == Enseignant::NOM_OK && err_prenom == Enseignant::PRENOM_OK) {
            switch (err_mail)
            {
            case Enseignant::MAIL_OK: break;
            case Enseignant::MAIL_SYNTAXE:
                QMessageBox::warning(&dialog, "Erreur", "Le format de l'adresse mail est invalide.");
                break;
            }
        }
    }

    if (mail.empty()) {
        return new Enseignant(nom, prenom);
    } else {
        return new Enseignant(nom, prenom, mail);
    }
}
