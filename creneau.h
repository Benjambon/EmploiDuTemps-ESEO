#ifndef CRENEAU_H
#define CRENEAU_H

#include <string>
#include <QDate>
#include "ecue.h"
#include "salle.h"

enum eHoraire { MATIN1, MATIN2, APRESMIDI1, APRESMIDI2, NONDEFINIT };

class Creneau
{
public:

    enum code_erreur_horaire { HORAIRE_OK, HORAIRE_NONDEEFINT };
    enum code_erreur_date { DATE_OK};

    //Attributs
    eHoraire horaire;
    QDate date;
    Ecue ecue;
    eTypeCours typeCours;
    Salle salle;

    //Constructeurs
    Creneau();
    Creneau(eHoraire horaire, QDate date, Ecue ecue, eTypeCours typeCours, Salle salle);

    //Getter Setter To_String
    eHoraire getHoraire() const;
    void setHoraire(eHoraire newHoraire);
    Ecue getEcue() const;
    void setEcue(const Ecue &newEcue);
    eTypeCours getTypeCours() const;
    void setTypeCours(eTypeCours newTypeCours);
    Salle getSalle() const;
    void setSalle(const Salle &newSalle);
    std::string to_string() const;

    //Méthodes de validation

    //Json
    QJsonObject toJSON() const;
    static Creneau fromJSON(QJsonObject json);

    static void writeToJSON(std::vector<Creneau> vector, QString filepath);
    static std::vector<Creneau> readFromJSON(QString filepath);

    //Méthodes
    static QString horaireToString(eHoraire horaire);
    static eHoraire stringToHoraire(QString str);
};

#endif // CRENEAU_H
