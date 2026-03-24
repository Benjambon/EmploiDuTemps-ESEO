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
    CM, TD, TP_INFO, TP_ELEC, EXAMEN_EN_SALLE, EXAMEN_INFO, EXAMEN_ELEC, DEFAULT
};

class Ecue
{
public:
    enum code_erreur_typeCours { TYPECOURS_OK, TYPECOURS_NONDEFINIT };
    enum code_erreur_heureTotal { HEURETOTAL_OK, HEURETOTAL_NUL, HEURETOTAL_NEGATIF, HEURETOTAL_IMPAIR };
    enum code_erreur_heureRestante { HEURERESTANTE_OK, HEURERESTANTE_NUL, HEURERESTANTE_NEGATIF, HEURERESTANTE_IMPAIR, HEURERESTANTE_SUPERIEUR_TOTAL };
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

    // methode pour i--

    code_erreur_typeCours isTypeCoursValid(const eTypeCours& typeCours);
    code_erreur_heureTotal isHeureTotalValid(const int& heureTotal);
    code_erreur_heureRestante isHeureRestanteValid(const int& heureRestante);

    QJsonObject toJSON(void) const;
    static Ecue fromJSON(QJsonObject json);
    static void writeToJSON(std::vector<Ecue> vector, QString filepath);
    static std::vector<Ecue> readFromJSON(QString filepath);
};

#endif // ECUE_H
