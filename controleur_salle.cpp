#include "controleur_salle.h"

Controleur_salle::Controleur_salle()
{
}


std::string Controleur_salle::TestSalle(std::string numero, TypeSalle typeSalle)
{

    Salle nouvelleSalle{numero, typeSalle};

    if(nouvelleSalle.isSalleValid())
    {
        return "Salle OK";
    }
    else
    {
        return "Erreur : Le numero doit contenir exactement 3 chiffres et le type doit etre valide !";
    }
}