#ifndef SALLE_H
#define SALLE_H
#include <iostream>
#include <string>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <vector>
#include <QString>

enum TypeSalle{
    SALLE,
    ELECTRONIQUE,
    INFORMATIQUE
};

class Salle
{
private:
    std::string numero;
    TypeSalle typeSalle;

public:
    Salle();
    Salle(std::string numero, TypeSalle typeSalle);

    std::string getNumero() const;
    void setNumero(std::string newNumero);
    TypeSalle getTypeSalle() const;
    void setTypeSalle(TypeSalle newTypeSalle);
    std::string toString(void) const;
    QJsonObject toJSON(void) const;

public:
    static Salle fromJSON(QJsonObject json);
    static void writeToJSON(std::vector<Salle> vector, QString filepath);
    static std::vector<Salle> readFromJSON(QString filepath);
};

#endif // SALLE_H
