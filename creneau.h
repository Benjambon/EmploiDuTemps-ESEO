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

    // Déclaration complète et propre des codes d'erreur
    enum code_erreur_horaire { HORAIRE_OK, HORAIRE_NONDEFINIT };
    enum code_erreur_date { DATE_OK, DATE_NULLE, DATE_INVALIDE };
    enum code_erreur_typeCours { TYPECOURS_OK, TYPECOURS_NONDEFINIT };

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
    QDate getDate() const;
    void setDate(const QDate &newDate);
    eHoraire getHoraire() const;
    void setHoraire(eHoraire newHoraire);
    Ecue getEcue() const;
    void setEcue(const Ecue &newEcue);
    eTypeCours getTypeCours() const;
    void setTypeCours(eTypeCours newTypeCours);
    Salle getSalle() const;
    void setSalle(const Salle &newSalle);
    std::string to_string() const;

    //Méthodes de validation que j'ai rajoutées
    code_erreur_horaire isHoraireValid() const;
    code_erreur_date isDateValid() const;
    code_erreur_typeCours isTypeCoursValid() const;

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
