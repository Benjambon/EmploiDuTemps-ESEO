#ifndef ECUE_H
#define ECUE_H

#include <iostream>
#include <string>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

#include "enseignant.h"
#include "groupeetudiant.h"

enum class eTypeCours
{
    CM, TD, TP_INFO, TP_ELEC, EXAMEN_EN_SALE, EXAMEN_INFO, EXAMEN_ELEC
};

class Ecue
{
private:
    Enseignant enseignant;
    GroupeEtudiant groupeEtudiant;
    eTypeCours typeCours;
    int heureTotal;
    int heureRestante;
public:
    Ecue();
    Ecue(Enseignant enseignant, GroupeEtudiant groupeEtudiant, eTypeCours TCours, int heureTotal, int heureRestante);

    eTypeCours gettypeCours() const;
    void settypeCours(eTypeCours newTCours);
    int getHeureTotal() const;
    void setHeureTotal(int newHeureTotal);
    int getHeureRestante() const;
    void setHeureRestante(int newHeureRestante);
    std::string to_string() const;
    Enseignant getEnseignant() const;
    void setEnseignant(const Enseignant &newEnseignant);
    GroupeEtudiant getGroupeEtudiant() const;
    void setGroupeEtudiant(const GroupeEtudiant &newGroupeEtudiant);

    bool isValide();


    QJsonObject toJSON(void) const;
    static Ecue fromJSON(QJsonObject json);
    static void writeToJSON(std::vector<Ecue> vector, QString filepath);
    static std::vector<Ecue> readFromJSON(QString filepath);
};

#endif // ECUE_H
