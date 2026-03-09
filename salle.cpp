#include "salle.h"

int salle::getNumero() const
{
    return numero;
}

void salle::setNumero(int newNumero)
{
    numero = newNumero;
}

TypeSalle salle::getTypeSalle() const
{
    return typeSalle;
}

void salle::setTypeSalle(TypeSalle newTypeSalle)
{
    typeSalle = newTypeSalle;
}

salle::salle() {}
