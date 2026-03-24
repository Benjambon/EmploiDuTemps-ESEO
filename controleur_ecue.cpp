#include "controleur_ecue.h"
#include "ecuedialog.h"
#include "supprimerecuedialog.h"
#include <QMessageBox>
#include <QDebug>

Controleur_ecue::Controleur_ecue() {}

Ecue* Controleur_ecue::creationEcue(const std::vector<Enseignant>& listE, const std::vector<GroupeEtudiant>& listG)
{
    // Sécurité si aucune donnée n'existe pour créer un ECUE
    if (listE.empty() || listG.empty()) {
        return nullptr;
    }

    EcueDialog dialog(listE, listG, nullptr);

    // Initialisation pour forcer la boucle
    Ecue::code_erreur_heureRestante err_hr = Ecue::HEURERESTANTE_SUPERIEUR_TOTAL;

    while (!(err_hr == Ecue::HEURERESTANTE_OK || err_hr == Ecue::HEURERESTANTE_NUL || err_hr == Ecue::HEURERESTANTE_IMPAIR))
    {
        dialog.show();
        if (dialog.exec() == QDialog::Rejected) {
            return nullptr;
        }

        Enseignant prof = listE[dialog.getEnseignantIndex()];
        GroupeEtudiant groupe = listG[dialog.getGroupeIndex()];
        eTypeCours type = dialog.getTypeCours();
        int total = dialog.getHeureTotal();
        int restante = dialog.getHeureRestante();

        Ecue tempEcue(prof, groupe, type, total, restante);

        err_hr = tempEcue.isHeureRestanteValid(restante);

        if (err_hr == Ecue::HEURERESTANTE_SUPERIEUR_TOTAL) {
            QMessageBox::warning(&dialog, "Erreur", "Les heures restantes ne peuvent pas être supérieures aux heures totales.");
        } else if (err_hr == Ecue::HEURERESTANTE_NEGATIF) {
            QMessageBox::warning(&dialog, "Erreur", "Les heures restantes ne peuvent pas être négatives.");
        }
    }

    return new Ecue(listE[dialog.getEnseignantIndex()], listG[dialog.getGroupeIndex()], dialog.getTypeCours(), dialog.getHeureTotal(), dialog.getHeureRestante());
}

int Controleur_ecue::supprimerEcue(const std::vector<Ecue>& listeEcues)
{
    if (listeEcues.empty()) return -1;

    SupprimerEcueDialog dialog(listeEcues, nullptr);
    if (dialog.exec() == QDialog::Accepted) {
        return dialog.getSelectedIndex();
    }
    return -1;
}
