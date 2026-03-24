#include "ecue.h"
#include <QDebug>

Ecue::Ecue() {}

Ecue::Ecue(std::string nom, Enseignant enseignant, GroupeEtudiant groupeEtudiant, std::map<eTypeCours, int> heuresTotales)
{
    this->nom = nom;
    this->enseignant = enseignant;
    this->groupeEtudiant = groupeEtudiant;
    this->heuresTotales = heuresTotales;
    this->heuresRestantes = heuresTotales; // Initialisation automatique des heures restantes
}

std::string Ecue::getNom() const { return nom; }
Enseignant Ecue::getEnseignant() const { return enseignant; }
GroupeEtudiant Ecue::getGroupeEtudiant() const { return groupeEtudiant; }
std::map<eTypeCours, int> Ecue::getHeuresTotales() const { return heuresTotales; }
std::map<eTypeCours, int> Ecue::getHeuresRestantes() const { return heuresRestantes; }

QString Ecue::typeCoursToString(eTypeCours type)
{
    switch(type) {
    case eTypeCours::CM: return "CM";
    case eTypeCours::TD: return "TD";
    case eTypeCours::TP_INFO: return "TP_INFO";
    case eTypeCours::TP_ELEC: return "TP_ELEC";
    case eTypeCours::EXAMEN_EN_SALLE: return "EXAMEN_EN_SALLE";
    case eTypeCours::EXAMEN_INFO: return "EXAMEN_INFO";
    case eTypeCours::EXAMEN_ELEC: return "EXAMEN_ELEC";
    default: return "DEFAULT";
    }
}

eTypeCours Ecue::stringToTypeCours(QString str)
{
    if (str == "CM") return eTypeCours::CM;
    if (str == "TD") return eTypeCours::TD;
    if (str == "TP_INFO") return eTypeCours::TP_INFO;
    if (str == "TP_ELEC") return eTypeCours::TP_ELEC;
    if (str == "EXAMEN_EN_SALLE") return eTypeCours::EXAMEN_EN_SALLE;
    if (str == "EXAMEN_INFO") return eTypeCours::EXAMEN_INFO;
    if (str == "EXAMEN_ELEC") return eTypeCours::EXAMEN_ELEC;
    return eTypeCours::DEFAULT;
}

std::string Ecue::to_string() const
{
    std::string res = "[" + nom + "] " + groupeEtudiant.getNom() + " - Enseignant : " + enseignant.getNom();
    return res;
}

QJsonObject Ecue::toJSON(void) const
{
    QJsonObject json;
    json["Nom"] = QString::fromStdString(this->nom);
    json["Enseignant"] = this->enseignant.toJSON();
    json["GroupeEtudiant"] = this->groupeEtudiant.toJSON();

    QJsonObject hTot, hRest;
    for (auto const& pair : heuresTotales) {
        hTot[typeCoursToString(pair.first)] = pair.second;
    }
    for (auto const& pair : heuresRestantes) {
        hRest[typeCoursToString(pair.first)] = pair.second;
    }

    json["HeuresTotales"] = hTot;
    json["HeuresRestantes"] = hRest;
    return json;
}

Ecue Ecue::fromJSON(QJsonObject json)
{
    std::string sNom = json["Nom"].toString().toStdString();
    Enseignant ens = Enseignant::fromJSON(json["Enseignant"].toObject());
    GroupeEtudiant grp = GroupeEtudiant::fromJSON(json["GroupeEtudiant"].toObject());

    std::map<eTypeCours, int> mapTotales;
    std::map<eTypeCours, int> mapRestantes;

    QJsonObject hTot = json["HeuresTotales"].toObject();
    for (const QString& key : hTot.keys()) {
        mapTotales[stringToTypeCours(key)] = hTot[key].toInt();
    }

    QJsonObject hRest = json["HeuresRestantes"].toObject();
    for (const QString& key : hRest.keys()) {
        mapRestantes[stringToTypeCours(key)] = hRest[key].toInt();
    }

    Ecue ecueObj(sNom, ens, grp, mapTotales);
    ecueObj.heuresRestantes = mapRestantes;
    return ecueObj;
}

void Ecue::writeToJSON(std::vector<Ecue> vector, QString filepath){
    QFile file (filepath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QJsonArray tab;
    for (auto it =vector.begin(); it != vector.end(); it++) { tab.append(it->toJSON()); }
    file.write(QJsonDocument(tab).toJson(QJsonDocument::Indented));
    file.close();
}

std::vector<Ecue> Ecue::readFromJSON(QString filepath){
    QFile file (filepath);
    if (!file.open(QIODevice::ReadOnly)) return std::vector<Ecue>();
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray tab = doc.array();
    std::vector<Ecue> res;
    for (auto it = tab.begin(); it != tab.end();it++) { res.push_back(Ecue::fromJSON((*it).toObject())); }
    return res;
}
Ecue::code_erreur_nom Ecue::isNomValid(const std::string& nomTest)
{
    if(nomTest.empty()) { return Ecue::NOM_VIDE; }
    return Ecue::NOM_OK;
}

Ecue::code_erreur_heureTotal Ecue::isHeureTotalValid(int heureTotalTest)
{
    if(heureTotalTest == 0) { return Ecue::HEURETOTAL_NUL; }
    if(heureTotalTest < 0) { return Ecue::HEURETOTAL_NEGATIF; }
    if(heureTotalTest % 2 != 0) { return Ecue::HEURETOTAL_IMPAIR; }
    return Ecue::HEURETOTAL_OK;
}

Ecue::code_erreur_heureRestante Ecue::isHeureRestanteValid(int heureRestanteTest, int heureTotalAssociee)
{
    if(heureRestanteTest == 0) { return Ecue::HEURERESTANTE_NUL; }
    if(heureRestanteTest < 0) { return Ecue::HEURERESTANTE_NEGATIF; }
    if(heureRestanteTest % 2 != 0) { return Ecue::HEURERESTANTE_IMPAIR; }
    if(heureRestanteTest > heureTotalAssociee) { return Ecue::HEURERESTANTE_SUPERIEUR_TOTAL; }
    return Ecue::HEURERESTANTE_OK;
}
