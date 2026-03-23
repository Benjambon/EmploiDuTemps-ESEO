#ifndef CONTROLEUR_ENSEIGNANT_H
#define CONTROLEUR_ENSEIGNANT_H

#include <string>
#include "enseignant.h"


class Controleur_enseignant
{
public:
    Controleur_enseignant();

    static std::string TestNomEnseignant(std::string nom);
    static std::string TestPrenomEnseignant(std::string prenom);
    static std::string TestMailEnseignant(std::string mail);
};

#endif // CONTROLEUR_ENSEIGNANT_H