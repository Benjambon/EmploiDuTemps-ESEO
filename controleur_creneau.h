#ifndef CONTROLEUR_CRENEAU_H
#define CONTROLEUR_CRENEAU_H

#include <vector>
#include "creneau.h"
#include "ecue.h"
#include "salle.h"

class Controleur_creneau
{
public:
    Controleur_creneau();

    static Creneau* creationCreneau(const std::vector<Ecue>& listeE, const std::vector<Salle>& listeS);
    static int supprimerCreneau(const std::vector<Creneau>& listeCreneaux);
};

#endif // CONTROLEUR_CRENEAU_H
