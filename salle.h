#ifndef SALLE_H
#define SALLE_H
#include <iostream>
#include <string>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

enum TypeSalle{
    SALLE,
    ELECTRONIQUE,
    INFORMATIQUE
};

class salle
{
private:
    int numero;
    TypeSalle typeSalle;

public:
    salle();
    salle(int numero, TypeSalle typeSalle);
    int getNumero() const;
    void setNumero(int newNumero);
    TypeSalle getTypeSalle() const;
    void setTypeSalle(TypeSalle newTypeSalle);
};

#endif // SALLE_H
