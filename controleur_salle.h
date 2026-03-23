#ifndef CONTROLEUR_SALLE_H
#define CONTROLEUR_SALLE_H

#include <string>
#include "salle.h"
class Controleur_salle
{
public:

    Controleur_salle();

    static std::string TestSalle(std::string numero, TypeSalle typeSalle);
};

#endif // CONTROLEUR_SALLE_H