#ifndef CONTROLEUR_SALLE_H
#define CONTROLEUR_SALLE_H

#include "salle.h"

class Controleur_salle
{
public:
    Controleur_salle();

    // Méthode principale qui pilote la création
    static Salle* creationSalle(void);
};

#endif // CONTROLEUR_SALLE_H
