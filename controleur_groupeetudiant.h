#ifndef CONTROLEUR_GROUPEETUDIANT_H
#define CONTROLEUR_GROUPEETUDIANT_H

#include "groupeetudiant.h"

class Controleur_groupeetudiant
{
public:
    Controleur_groupeetudiant();

    // Méthode principale qui pilote la création
    static GroupeEtudiant* creationGroupe(void);
};

#endif // CONTROLEUR_GROUPEETUDIANT_H
