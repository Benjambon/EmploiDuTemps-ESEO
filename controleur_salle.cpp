#include "controleur_salle.h"
#include "salledialog.h"
#include "supprimersalledialog.h"
#include <QMessageBox>
#include <QDebug>

Controleur_salle::Controleur_salle() {}

Salle* Controleur_salle::creationSalle(void)
{
    SalleDialog dialog(nullptr);

    Salle::code_erreur_numero err_num = Salle::NUMERO_PAS_CHIFFRE;
    Salle::code_erreur_type err_type = Salle::TYPE_INVALIDE;

    while (!(err_num == Salle::NUMERO_OK && err_type == Salle::TYPE_OK))
    {
        dialog.show();
        bool res_exec = dialog.exec();

        if (res_exec == QDialog::Rejected) {
            return nullptr;
        }

        Salle tempSalle(dialog.getNumero(), dialog.getTypeSalle());

        err_num = tempSalle.isNumeroValid();
        switch (err_num)
        {
        case Salle::NUMERO_OK:
            break;
        case Salle::NUMERO_TROP_LONG:
            qDebug() << "Le numero doit faire exactement 3 caracteres";
            QMessageBox::warning(&dialog, "Erreur", "Le numéro doit faire exactement 3 caractères.");
            break;
        case Salle::NUMERO_PAS_CHIFFRE:
            qDebug() << "Le numero ne doit contenir que des chiffres";
            QMessageBox::warning(&dialog, "Erreur", "Le numéro ne doit contenir que des chiffres.");
            break;
        }

        err_type = tempSalle.isTypeValid();
        switch (err_type)
        {
        case Salle::TYPE_OK:
            break;
        case Salle::TYPE_VIDE:
        case Salle::TYPE_INVALIDE:
            qDebug() << "Le type de salle est invalide";
            QMessageBox::warning(&dialog, "Erreur", "Le type de salle sélectionné est invalide.");
            break;
        }
    }

    return new Salle(dialog.getNumero(), dialog.getTypeSalle());
}

int Controleur_salle::supprimerSalle(const std::vector<Salle>& listeSalles)
{
    if (listeSalles.empty()) {
        return -1;
    }

    SupprimerSalleDialog dialog(listeSalles, nullptr);

    if (dialog.exec() == QDialog::Accepted) {
        return dialog.getSelectedIndex();
    }

    return -1;
}
