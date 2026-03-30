#include "controleur_creneau.h"
#include "creneaudialog.h"
#include "supprimercreneaudialog.h"
#include <QMessageBox>

Controleur_creneau::Controleur_creneau() {}

Creneau* Controleur_creneau::creationCreneau(const std::vector<Ecue>& listeE, const std::vector<Salle>& listeS)
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

        Creneau tempCreneau;
        tempCreneau.setDate(date);
        tempCreneau.setHoraire(horaire);
        tempCreneau.setTypeCours(typeCours);

        if (tempCreneau.isDateValid() != Creneau::DATE_OK) {
            QMessageBox::warning(&dialog, "Erreur", "La date saisie n'est pas valide.");
        } else if (tempCreneau.isHoraireValid() != Creneau::HORAIRE_OK) {
            QMessageBox::warning(&dialog, "Erreur", "L'horaire n'est pas défini.");
        } else if (tempCreneau.isTypeCoursValid() != Creneau::TYPECOURS_OK) {
            QMessageBox::warning(&dialog, "Erreur", "Le type de cours n'est pas défini.");
        } else {
            isValid = true;
            Ecue ecue = listeE[dialog.getEcueIndex()];
            Salle salle = listeS[dialog.getSalleIndex()];
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
