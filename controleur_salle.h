#ifndef CONTROLEUR_SALLE_H
#define CONTROLEUR_SALLE_H

#include "salle.h"

class Controleur_salle
{
public:
    Controleur_salle();

    // Méthode principale qui pilote la création
    static Salle* creationSalle(void);
    static int supprimerSalle(const std::vector<Salle>& listeSalles);
};

#endif // CONTROLEUR_SALLE_H
