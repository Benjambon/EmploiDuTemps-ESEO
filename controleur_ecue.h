#ifndef CONTROLEUR_ECUE_H
#define CONTROLEUR_ECUE_H

#include <vector>
#include "ecue.h"
#include "enseignant.h"
#include "groupeetudiant.h"

class Controleur_ecue
{
public:
    Controleur_ecue();

    static Ecue* creationEcue(const std::vector<Enseignant>& listE, const std::vector<GroupeEtudiant>& listG);
    static int supprimerEcue(const std::vector<Ecue>& listeEcues);
};

#endif // CONTROLEUR_ECUE_H
