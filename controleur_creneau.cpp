#include "controleur_creneau.h"
#include "creneaudialog.h"
#include "supprimercreneaudialog.h"
#include <QMessageBox>
#include <QDebug>

Controleur_creneau::Controleur_creneau() {}

Creneau* Controleur_creneau::creationCreneau(const std::vector<Ecue>& listeE, const std::vector<Salle>& listeS, const std::vector<Creneau>& listeC)
{
    if (listeE.empty() || listeS.empty()) return nullptr;

    CreneauDialog dialog(listeE, listeS, nullptr);
    bool isValid = false;

    while (!isValid)
    {
        if (dialog.exec() == QDialog::Rejected) {
            return nullptr;
        }

        QDate date = dialog.getDate();
        eHoraire horaire = dialog.getHoraire();
        eTypeCours typeCours = dialog.getTypeCours();
        Ecue ecue = listeE[dialog.getEcueIndex()];
        Salle salle = listeS[dialog.getSalleIndex()];

        // Création d'un objet temporaire pour utiliser ses méthodes de validation
        Creneau tempCreneau(horaire, date, ecue, typeCours, salle);

        // 1. Validation de l'intégrité des données
        if (tempCreneau.isDateValid() == Creneau::DATE_NULLE || tempCreneau.isDateValid() == Creneau::DATE_INVALIDE) {
            QMessageBox::warning(&dialog, "Erreur", "La date saisie n'est pas valide.");
            continue;
        } else if (tempCreneau.isDateValid() == Creneau::DATE_WEEKEND) {
            QMessageBox::warning(&dialog, "Erreur", "Impossible de planifier un créneau le week-end.");
            continue;
        } else if (tempCreneau.isHoraireValid() == Creneau::HORAIRE_NONDEFINIT) {
            QMessageBox::warning(&dialog, "Erreur", "L'horaire n'est pas défini.");
            continue;
        } else if (tempCreneau.isTypeCoursValid() == Creneau::TYPECOURS_NONDEFINIT) {
            QMessageBox::warning(&dialog, "Erreur", "Le type de cours n'est pas défini.");
            continue;
        } else if (tempCreneau.isEcueValid() == Creneau::ECUE_NONDEFINIT) {
            QMessageBox::warning(&dialog, "Erreur", "L'ECUE sélectionné n'est pas valide.");
            continue;
        } else if (tempCreneau.isSalleValid() == Creneau::SALLE_NONDEFINIT) {
            QMessageBox::warning(&dialog, "Erreur", "La salle sélectionnée n'est pas valide.");
            continue;
        }

        // 2. Validation des conflits dans l'emploi du temps
        bool conflit = false;
        QString msgConflit = "";

        for (const Creneau& c : listeC) {
            if (c.getDate() == date && c.getHoraire() == horaire) {
                if (c.getSalle().getNumero() == salle.getNumero()) {
                    conflit = true;
                    msgConflit = "La salle sélectionnée est déjà occupée à cette date et cet horaire.";
                    break;
                }
                if (c.getEcue().getEnseignant().getNom() == ecue.getEnseignant().getNom()) {
                    conflit = true;
                    msgConflit = "L'enseignant a déjà un cours à cette date et cet horaire.";
                    break;
                }
                if (c.getEcue().getNom() == ecue.getNom()) {
                    conflit = true;
                    msgConflit = "Cet ECUE est déjà programmé à cette date et cet horaire.";
                    break;
                }
                if (c.getEcue().getGroupeEtudiant().getNom() == ecue.getGroupeEtudiant().getNom()) {
                    conflit = true;
                    msgConflit = "Ce groupe d'étudiants a déjà un cours à cette date et cet horaire.";
                    break;
                }
            }
        }

        // Bilan
        if (conflit) {
            QMessageBox::warning(&dialog, "Conflit", msgConflit);
        } else {
            isValid = true;
            return new Creneau(horaire, date, ecue, typeCours, salle);
        }
    }
    return nullptr;
}

int Controleur_creneau::supprimerCreneau(const std::vector<Creneau>& listeCreneaux)
{
    if (listeCreneaux.empty()) return -1;

    SupprimerCreneauDialog dialog(listeCreneaux, nullptr);
    if (dialog.exec() == QDialog::Accepted) {
        return dialog.getSelectedIndex();
    }
    return -1;
}
