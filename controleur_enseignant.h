#ifndef CONTROLEUR_ENSEIGNANT_H
#define CONTROLEUR_ENSEIGNANT_H

#include "enseignant.h"
#include "enseignantdialog.h"
#include "supprimerenseignantdialog.h"
#include <QMessageBox>
#include <QDebug>

class Controleur_enseignant
{
public:
    Controleur_enseignant();

    static Enseignant* creationEnseignant(void);
    static int supprimerEnseignant(const std::vector<Enseignant>& listeEnseignants);
};

#endif // CONTROLEUR_ENSEIGNANT_H
