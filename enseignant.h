#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H
#include <iostream>
#include <string>
#include <regex>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

class Enseignant
{
private:
    std::string nom;
    std::string prenom;
    std::string mail;


public:

    //Constructeurs
    Enseignant();
    Enseignant(const std::string &nom, const std::string &prenom, const std::string &mail);
    Enseignant(const std::string &nom, const std::string &prenom);


    //Getter Setter
    std::string getNom() const;
    void setNom(const std::string &newNom);
    std::string getPrenom() const;
    void setPrenom(const std::string &newPrenom);
    std::string getMail() const;
    void setMail(const std::string &newMail);


    //Methodes
    std::string toString(void) const;
    bool isMailValid(void);
    bool isNomValid(void);
    bool isPrenomValid(void);
    bool isEnseignantValid(void);
    QJsonObject toJSON(void) const;

public:
    static Enseignant fromJSON(QJsonObject json);
    static void writeToJSON(std::vector<Enseignant> vector, QString filepath);
    static std::vector<Enseignant> readFromJSON(QString filepath);

};

#endif // ENSEIGNANT_H
