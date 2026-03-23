#ifndef CONTROLEUR_ENSEIGNANT_H
#define CONTROLEUR_ENSEIGNANT_H

#include "enseignant.h"

class Controleur_enseignant
{
public:
    Controleur_enseignant();

    static Enseignant* creationEnseignant(void);
};

#endif // CONTROLEUR_ENSEIGNANT_H
