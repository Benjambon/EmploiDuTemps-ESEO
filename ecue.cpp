#include "ecue.h"

Ecue::Ecue()
{
    this->enseignant = Enseignant();
    this->groupeEtudiant = GroupeEtudiant();
    this->typeCours = eTypeCours::CM;
    this->heureTotal = 0;
    this->heureRestante = 0;
}

Ecue::Ecue(Enseignant enseignant, GroupeEtudiant groupeEtudiant, eTypeCours typeCours, int heureTotal, int heureRestante)
{
    this->enseignant = enseignant;
    this->groupeEtudiant = groupeEtudiant;
    this->typeCours = typeCours;
    this->heureTotal = heureTotal;
    this->heureRestante = heureRestante;
}


Enseignant Ecue::getEnseignant() const
{
    return enseignant;
}

void Ecue::setEnseignant(const Enseignant &newEnseignant)
{
    enseignant = newEnseignant;
}

GroupeEtudiant Ecue::getGroupeEtudiant() const
{
    return groupeEtudiant;
}

void Ecue::setGroupeEtudiant(const GroupeEtudiant &newGroupeEtudiant)
{
    groupeEtudiant = newGroupeEtudiant;
}

eTypeCours Ecue::gettypeCours() const
{
    return typeCours;
}

void Ecue::settypeCours(eTypeCours newTCours)
{
    typeCours = newTCours;
}

int Ecue::getHeureTotal() const
{
    return heureTotal;
}

void Ecue::setHeureTotal(int newHeureTotal)
{
    heureTotal = newHeureTotal;
}

int Ecue::getHeureRestante() const
{
    return heureRestante;
}

void Ecue::setHeureRestante(int newHeureRestante)
{
    heureRestante = newHeureRestante;
}

std::string Ecue::to_string() const
{
    std::string res = "";
    switch(typeCours)
    {
        case eTypeCours::CM:
            res = "Enseignant : " + enseignant.toString() + ", Groupe étudiant : " + groupeEtudiant.toString() _
                    ", Type de cours : CM, Heure Total : " + std::to_string(heureTotal) _
                    ", Heure restante : " + std::to_string(heurerestante);
        case eTypeCours::TD:
            res = "Enseignant : " + enseignant.toString() + ", Groupe étudiant : " + groupeEtudiant.toString() _
                    ", Type de cours : TD, Heure Total : " + std::to_string(heureTotal) _
                    ", Heure restante : " + std::to_string(heurerestante);
        case eTypeCours::TP_INFO:
            res = "Enseignant : " + enseignant.toString() + ", Groupe étudiant : " + groupeEtudiant.toString() _
                    ", Type de cours : TP_INFO, Heure Total : " + std::to_string(heureTotal) _
                    ", Heure restante : " + std::to_string(heurerestante);
        case eTypeCours::TP_ELEC:
            res = "Enseignant : " + enseignant.toString() + ", Groupe étudiant : " + groupeEtudiant.toString() _
                    ", Type de cours : TP_ELEC, Heure Total : " + std::to_string(heureTotal) _
                    ", Heure restante : " + std::to_string(heurerestante);
        case eTypeCours::EXAMEN_EN_SALE:
            res = "Enseignant : " + enseignant.toString() + ", Groupe étudiant : " + groupeEtudiant.toString() _
                    ", Type de cours : EXAMEN_EN_SALE, Heure Total : " + std::to_string(heureTotal) _
                    ", Heure restante : " + std::to_string(heurerestante);
        case eTypeCours::EXAMEN_INFO:
            res = "Enseignant : " + enseignant.toString() + ", Groupe étudiant : " + groupeEtudiant.toString() _
                    ", Type de cours : EXAMEN_INFO, Heure Total : " + std::to_string(heureTotal) _
                    ", Heure restante : " + std::to_string(heurerestante);
        case eTypeCours::EXAMEN_ELEC:
            res = "Enseignant : " + enseignant.toString() + ", Groupe étudiant : " + groupeEtudiant.toString() _
                    ", Type de cours : EXAMEN_ELEC, Heure Total : " + std::to_string(heureTotal) _
                    ", Heure restante : " + std::to_string(heurerestante);
    }
        return res;
}

bool Ecue::isValide()
{
    if (this->enseignant.isEnseignantValid() && this->groupeEtudiant.isNomValid()){
        return true;
    }else{
        return false;
    }
}

QJsonObject Ecue::toJSON(void) const
{
    QJsonObject json;
    json["Enseignant"] = this->enseignant.toJSON();
    json["GroupeEtudiant"] = this->groupeEtudiant.toJSON();
    switch(typeCours)
    {
    case eTypeCours::CM:
        json["TypeCours"] = QString::fromStdString("CM");
    case eTypeCours::TD:
        json["TypeCours"] = QString::fromStdString("TD");
    case eTypeCours::TP_INFO:
        json["TypeCours"] = QString::fromStdString("TP_INFO");
    case eTypeCours::TP_ELEC:
        json["TypeCours"] = QString::fromStdString("TP_ELEC");
    case eTypeCours::EXAMEN_EN_SALE:
        json["TypeCours"] = QString::fromStdString("EXAMEN_EN_SALE");
    case eTypeCours::EXAMEN_INFO:
        json["TypeCours"] = QString::fromStdString("EXAMEN_INFO");
    case eTypeCours::EXAMEN_ELEC:
        json["TypeCours"] = QString::fromStdString("EXAMEN_ELEC");
    }
    json["HeureTotal"] = this->heureTotal;
    json["HeureRestante"] = this->heureRestante;
    return json;
}
//a finir
Ecue Ecue::fromJSON(QJsonObject json){
    QJsonObject::iterator it;

    it = json.find("Enseignant");
    if (it==json.end()) { qDebug() << "Le JSON ne contient pas de 'Enseignant";}
    if (it.value().isNull() ) { qDebug() << "Le 'Enseignant' est null" ;}
    std::string enseignant = it.value().toString().toStdString() ;

    it = json.find("GroupeEtudiant");
    if (it==json.end()) { qDebug() << "Le JSON ne contient pas de 'nom";}
    if (it.value().isNull() ) { qDebug() << "Le 'nom' est null" ;}
    std::string nom = it.value().toString().toStdString() ;

    it = json.find("mail");
    if (it==json.end() ) { qDebug() << "Le JSON ne contient pas de 'mail";}
    if (it.value().isNull() ) { qDebug() << "Le 'mail' est null" ;}
    std::string mail = it.value().toString().toStdString() ;

    return Enseignant(prenom, nom, mail);
}
