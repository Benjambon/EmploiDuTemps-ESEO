#include "controleur_groupeetudiant.h"

Controleur_groupeetudiant::Controleur_groupeetudiant() {}

std::string Controleur_groupeetudiant::TestNomGroupe(std::string nom)
{
    GroupeEtudiant nouveauGroupe{nom};

    if(nouveauGroupe.isNomValid())
    {
        return "Nom de groupe OK";
    }
    else
    {
        return "Le nom du groupe ne peut pas etre vide !";
    }
}