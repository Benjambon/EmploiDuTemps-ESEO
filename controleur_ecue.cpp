#include "controleur_ecue.h"
#include "ecuedialog.h"
#include "supprimerecuedialog.h"
#include <QMessageBox>
#include <QDebug>

Controleur_ecue::Controleur_ecue() {}

Ecue* Controleur_ecue::creationEcue(const std::vector<Enseignant>& listE, const std::vector<GroupeEtudiant>& listG)
{
    if (listE.empty() || listG.empty()) return nullptr;

    EcueDialog dialog(listE, listG, nullptr);
    bool isValid = false;

    while (!isValid)
    {
        if (dialog.exec() == QDialog::Rejected) {
            return nullptr;
        }

        std::string nom = dialog.getNom();
        std::map<eTypeCours, int> heures = dialog.getHeuresChoisies();

        // Vérification des heures impaires
        bool contientHeureImpaire = false;
        for (auto const& pair : heures) {
            if (Ecue::isHeureTotalValid(pair.second) == Ecue::HEURETOTAL_IMPAIR) {
                contientHeureImpaire = true;
                break;
            }
        }

        if (nom.empty()) {
            QMessageBox::warning(&dialog, "Erreur", "Le nom de l'ECUE ne peut pas être vide.");
        } else if (heures.empty()) {
            QMessageBox::warning(&dialog, "Erreur", "Vous devez définir au moins 2 heures pour un type de cours.");
        } else if (contientHeureImpaire) {
            QMessageBox::warning(&dialog, "Erreur", "Le nombre d'heures pour chaque type de cours doit être un nombre pair (créneaux de 2h).");
        } else {
            isValid = true;
            Enseignant prof = listE[dialog.getEnseignantIndex()];
            GroupeEtudiant groupe = listG[dialog.getGroupeIndex()];
            return new Ecue(nom, prof, groupe, heures);
        }
    }
    return nullptr;
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
