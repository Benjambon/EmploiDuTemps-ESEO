#ifndef GROUPEETUDIANT_H
#define GROUPEETUDIANT_H
#include <iostream>
#include <string>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

class GroupeEtudiant
{
private:
    std::string nom;
public:
    //Constructeurs
    GroupeEtudiant();
    GroupeEtudiant(const std::string &nom);

    //Getter Setter
    std::string getNom() const;
    void setNom(const std::string &newNom);

    //Methodes
    std::string toString(void) const;
    bool isNomValid(void);
    QJsonObject toJSON(void) const;

public:
    static GroupeEtudiant fromJSON(QJsonObject json);
    static void writeToJSON(std::vector<GroupeEtudiant> vector, QString filepath);
    static std::vector<GroupeEtudiant> readFromJSON(QString filepath);

};

#endif // GROUPEETUDIANT_H
