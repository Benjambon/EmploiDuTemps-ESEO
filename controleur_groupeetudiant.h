#ifndef CONTROLEUR_GROUPEETUDIANT_H
#define CONTROLEUR_GROUPEETUDIANT_H

#include "groupeetudiant.h"

class Controleur_groupeetudiant
{
public:
    Controleur_groupeetudiant();

    static GroupeEtudiant* creationGroupe(void);
    static int supprimerGroupe(const std::vector<GroupeEtudiant>& listeGroupes);
};

#endif // CONTROLEUR_GROUPEETUDIANT_H
