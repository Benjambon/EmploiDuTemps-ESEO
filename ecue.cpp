#include "ecue.h"

Ecue::Ecue()
{
    this->enseignant = Enseignant();
    this->groupeEtudiant = GroupeEtudiant();
    this->typeCours = eTypeCours::DEFAULT;
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
            res = "Enseignant : " + enseignant.toString() + ", Groupe étudiant : " + groupeEtudiant.toString() + ", Type de cours : CM, Heure Total : " + std::to_string(heureTotal) + ", Heure restante : " + std::to_string(heureRestante);
        case eTypeCours::TD:
            res = "Enseignant : " + enseignant.toString() + ", Groupe étudiant : " + groupeEtudiant.toString() + ", Type de cours : TD, Heure Total : " + std::to_string(heureTotal) + ", Heure restante : " + std::to_string(heureRestante);
        case eTypeCours::TP_INFO:
            res = "Enseignant : " + enseignant.toString() + ", Groupe étudiant : " + groupeEtudiant.toString() + ", Type de cours : TP_INFO, Heure Total : " + std::to_string(heureTotal) + ", Heure restante : " + std::to_string(heureRestante);
        case eTypeCours::TP_ELEC:
            res = "Enseignant : " + enseignant.toString() + ", Groupe étudiant : " + groupeEtudiant.toString() + ", Type de cours : TP_ELEC, Heure Total : " + std::to_string(heureTotal) + ", Heure restante : " + std::to_string(heureRestante);
        case eTypeCours::EXAMEN_EN_SALE:
            res = "Enseignant : " + enseignant.toString() + ", Groupe étudiant : " + groupeEtudiant.toString() + ", Type de cours : EXAMEN_EN_SALE, Heure Total : " + std::to_string(heureTotal) + ", Heure restante : " + std::to_string(heureRestante);
        case eTypeCours::EXAMEN_INFO:
            res = "Enseignant : " + enseignant.toString() + ", Groupe étudiant : " + groupeEtudiant.toString() + ", Type de cours : EXAMEN_INFO, Heure Total : " + std::to_string(heureTotal) + ", Heure restante : " + std::to_string(heureRestante);
        case eTypeCours::EXAMEN_ELEC:
            res = "Enseignant : " + enseignant.toString() + ", Groupe étudiant : " + groupeEtudiant.toString() + ", Type de cours : EXAMEN_ELEC, Heure Total : " + std::to_string(heureTotal) + ", Heure restante : " + std::to_string(heureRestante);
    }
        return res;
}

Ecue::code_erreur_typeCours Ecue::isTypeCoursValid(const eTypeCours& typeCours)
{
    if(typeCours == eTypeCours::DEFAULT) { return Ecue::TYPECOURS_NONDEFINIT; }
    return code_erreur_typeCours::TYPECOURS_OK;
}


Ecue::code_erreur_heureTotal Ecue::isHeureTotalValid(const int& heureTotal)
{
    if(heureTotal == 0) { return Ecue::HEURETOTAL_NUL; }
    if(heureTotal < 0) { return Ecue::HEURETOTAL_NEGATIF; }
    if(heureTotal % 2) { return Ecue::HEURETOTAL_IMPAIR; }
    return Ecue::HEURETOTAL_OK;
}

Ecue::code_erreur_heureRestante Ecue::isHeureRestanteValid(const int& heureRestante)
{
    if(heureRestante == 0) { return Ecue::HEURERESTANTE_NUL; }
    if(heureRestante < 0) { return Ecue::HEURERESTANTE_NEGATIF; }
    if(heureRestante % 2) { return Ecue::HEURERESTANTE_IMPAIR; }
    if(heureRestante > this->heureTotal) { return Ecue::HEURERESTANTE_SUPERIEUR_TOTAL; }
    return Ecue::HEURERESTANTE_OK;
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
    QJsonObject obj;

    it = json.find("Enseignant");
    if (it==json.end()) { qDebug() << "Le JSON ne contient pas de 'Enseignant'";}
    if (it.value().isNull() || it.value().isObject() ) { qDebug() << "Le 'Enseignant' est null" ;}

    QJsonObject JOEnseignant = it.value().toObject();

    it = JOEnseignant.find("prenom");
    if (it==JOEnseignant.end()) { qDebug() << "Le JSON Enseignant ne contient pas de 'prenom";}
    if (it.value().isNull() ) { qDebug() << "Le 'prenom' de Enseignant est null" ;}
    std::string sPrenomEnseignant = it.value().toString().toStdString() ;

    it = JOEnseignant.find("nom");
    if (it==JOEnseignant.end()) { qDebug() << "Le JSON Enseignant ne contient pas de 'nom";}
    if (it.value().isNull() ) { qDebug() << "Le 'nom' de Enseignant est null" ;}
    std::string sNomEnseignant = it.value().toString().toStdString() ;

    it = JOEnseignant.find("mail");
    if (it==JOEnseignant.end() ) { qDebug() << "Le JSON Enseignant ne contient pas de 'mail";}
    if (it.value().isNull() ) { qDebug() << "Le 'mail' de Enseignant est null" ;}
    std::string sMailEnseignant = it.value().toString().toStdString() ;

    it = json.find("GroupeEtudiant");
    if (it==json.end()) { qDebug() << "Le JSON ne contient pas de 'GroupeEtudiant'";}
    if (it.value().isNull() || it.value().isObject()) { qDebug() << "Le 'GroupeEtudiant' est null" ;}

    QJsonObject OJGroupeEtudiant = it.value().toObject();

    it = OJGroupeEtudiant.find("nom");
    if (it==OJGroupeEtudiant.end()) { qDebug() << "Le JSON GroupeEtudiant ne contient pas de 'nom'";}
    if (it.value().isNull() ) { qDebug() << "Le 'nom' de GroupeEtudiant est null" ;}
    std::string sNomGroupeEtudiant = it.value().toString().toStdString() ;

    it = json.find("TypeCours");
    if (it==json.end() ) { qDebug() << "Le JSON ne contient pas de 'TypeCours'";}
    if (it.value().isNull() ) { qDebug() << "Le 'TypeCours' est null" ;}
    std::string sTypeCours = it.value().toString().toStdString();

    it = json.find("HeureTotal");
    if (it==json.end() ) { qDebug() << "Le JSON ne contient pas de 'HeureTotal'";}
    if (it.value().isNull() ) { qDebug() << "Le 'HeureTotal' est null" ;}
    int iHeureTotal = it.value().toInt();

    it = json.find("HeureRestante");
    if (it==json.end() ) { qDebug() << "Le JSON ne contient pas de 'HeureRestante'";}
    if (it.value().isNull() ) { qDebug() << "Le 'HeureRestante' est null" ;}
    int iHeureRestante = it.value().toInt();

    if(sTypeCours == "CM"){
        return Ecue(Enseignant(sPrenomEnseignant, sNomEnseignant, sMailEnseignant), GroupeEtudiant(sNomGroupeEtudiant), eTypeCours::CM, iHeureTotal, iHeureRestante);
    }else if(sTypeCours == "TD"){
        return Ecue(Enseignant(sPrenomEnseignant, sNomEnseignant, sMailEnseignant), GroupeEtudiant(sNomGroupeEtudiant), eTypeCours::TD, iHeureTotal, iHeureRestante);
    }else if(sTypeCours == "TP_INFO"){
        return Ecue(Enseignant(sPrenomEnseignant, sNomEnseignant, sMailEnseignant), GroupeEtudiant(sNomGroupeEtudiant), eTypeCours::TP_INFO, iHeureTotal, iHeureRestante);
    }else if(sTypeCours == "TP_ELEC"){
        return Ecue(Enseignant(sPrenomEnseignant, sNomEnseignant, sMailEnseignant), GroupeEtudiant(sNomGroupeEtudiant), eTypeCours::TP_ELEC, iHeureTotal, iHeureRestante);
    }else if(sTypeCours == "EXAMEN_EN_SALE"){
        return Ecue(Enseignant(sPrenomEnseignant, sNomEnseignant, sMailEnseignant), GroupeEtudiant(sNomGroupeEtudiant), eTypeCours::EXAMEN_EN_SALE, iHeureTotal, iHeureRestante);
    }else if(sTypeCours == "EXAMEN_INFO"){
        return Ecue(Enseignant(sPrenomEnseignant, sNomEnseignant, sMailEnseignant), GroupeEtudiant(sNomGroupeEtudiant), eTypeCours::EXAMEN_INFO, iHeureTotal, iHeureRestante);
    }else if(sTypeCours == "EXAMEN_ELEC"){
        return Ecue(Enseignant(sPrenomEnseignant, sNomEnseignant, sMailEnseignant), GroupeEtudiant(sNomGroupeEtudiant), eTypeCours::EXAMEN_ELEC, iHeureTotal, iHeureRestante);
    }
}

void Ecue::writeToJSON(std::vector<Ecue> vector, QString filepath){
    QFile file (filepath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Erreur ouverture de";
        qDebug() << filepath.toStdString();
    }
    QJsonArray tab;
    for (auto it =vector.begin(); it != vector.end(); it++)
    {
        tab.append(it->toJSON());
    }
    file.write(QJsonDocument(tab).toJson(QJsonDocument::Indented));
    file.close();
}

std::vector<Ecue> Ecue::readFromJSON(QString filepath){
    QFile file (filepath);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "Erreur ouverture de";
        qDebug() << filepath.toStdString();
        return std::vector<Ecue>();
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(!doc.isArray()){
        qDebug() << "Erreur ouverture de";
        qDebug() << filepath;
        return std::vector<Ecue>();
    }
    QJsonArray tab =doc.array();
    std::vector<Ecue> res;
    for (auto it = tab.begin(); it != tab.end();it++){
        res.push_back(Ecue::fromJSON((*it).toObject()));
    }
    return res;
}
