#ifndef ECUE_H
#define ECUE_H

#include <string>
#include <map>
#include <vector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include "enseignant.h"
#include "groupeetudiant.h"

enum class eTypeCours { CM, TD, TP_INFO, TP_ELEC, EXAMEN_EN_SALLE, EXAMEN_INFO, EXAMEN_ELEC, DEFAULT };

class Ecue
{
public:

    enum code_erreur_nom { NOM_OK, NOM_VIDE };
    enum code_erreur_typeCours { TYPECOURS_OK, TYPECOURS_NONDEFINIT };
    enum code_erreur_heureTotal { HEURETOTAL_OK, HEURETOTAL_NUL, HEURETOTAL_NEGATIF, HEURETOTAL_IMPAIR };
    enum code_erreur_heureRestante { HEURERESTANTE_OK, HEURERESTANTE_NUL, HEURERESTANTE_NEGATIF, HEURERESTANTE_IMPAIR, HEURERESTANTE_SUPERIEUR_TOTAL };

private:
    std::string nom;
    Enseignant enseignant;
    GroupeEtudiant groupeEtudiant;
    std::map<eTypeCours, int> heuresTotales;
    std::map<eTypeCours, int> heuresRestantes;

public:
    Ecue();
    Ecue(std::string nom, Enseignant enseignant, GroupeEtudiant groupeEtudiant, std::map<eTypeCours, int> heuresTotales);

    std::string getNom() const;
    Enseignant getEnseignant() const;
    GroupeEtudiant getGroupeEtudiant() const;
    std::map<eTypeCours, int> getHeuresTotales() const;
    std::map<eTypeCours, int> getHeuresRestantes() const;

    std::string to_string() const;

    // Méthodes de validation adaptées pour vérifier des valeurs isolées
    static code_erreur_nom isNomValid(const std::string& nomTest);
    static code_erreur_heureTotal isHeureTotalValid(int heureTotalTest);
    static code_erreur_heureRestante isHeureRestanteValid(int heureRestanteTest, int heureTotalAssociee);

    QJsonObject toJSON() const;
    static Ecue fromJSON(QJsonObject json);

    static void writeToJSON(std::vector<Ecue> vector, QString filepath);
    static std::vector<Ecue> readFromJSON(QString filepath);

    static QString typeCoursToString(eTypeCours type);
    static eTypeCours stringToTypeCours(QString str);
};

#endif // ECUE_H
