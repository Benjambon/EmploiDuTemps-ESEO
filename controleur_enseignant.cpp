#include "controleur_enseignant.h"

Controleur_enseignant::Controleur_enseignant()
{
}

std::string Controleur_enseignant::TestNomEnseignant(std::string nom)
{
    std::string prenom = "";
    std::string mail = "";

    Enseignant NouvelEnseignant{nom, prenom, mail};

    if(NouvelEnseignant.isNomValid())
    {
        return "Nom OK";
    }
    else
    {
        return "Le nom ne peut pas etre vide !";
    }
}

std::string Controleur_enseignant::TestPrenomEnseignant(std::string prenom)
{
    std::string nom = "";
    std::string mail = "";

    Enseignant NouvelEnseignant{nom, prenom, mail};

    if(NouvelEnseignant.isPrenomValid())
    {
        return "Prenom OK";
    }
    else
    {
        return "Le Prenom ne peut pas etre vide !";
    }
}

std::string Controleur_enseignant::TestMailEnseignant(std::string mail)
{
    std::string nom = "";
    std::string prenom = "";

    Enseignant NouvelEnseignant{nom, prenom, mail};

    if(NouvelEnseignant.isMailValid())
    {
        return "mail OK";
    }
    else
    {
        return "Le mail n'est pas OK";
    }
}