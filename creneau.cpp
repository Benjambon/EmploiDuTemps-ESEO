#include "creneau.h"

Creneau::Creneau()
{
    this->horaire = eHoraire::NONDEFINIT;
    this->date = QDate();
    this->ecue = Ecue();
    this->typeCours = eTypeCours::DEFAULT;
    this->salle = Salle();
}

Creneau::Creneau(eHoraire horaire, QDate date, Ecue ecue, eTypeCours typeCours, Salle salle)
{
    this->horaire = horaire;
    this->date = date;
    this->ecue = ecue;
    this->typeCours = typeCours;
    this->salle = salle;
}

eHoraire Creneau::getHoraire() const
{
    return horaire;
}

void Creneau::setHoraire(eHoraire newHoraire)
{
    horaire = newHoraire;
}

Ecue Creneau::getEcue() const
{
    return ecue;
}

void Creneau::setEcue(const Ecue &newEcue)
{
    ecue = newEcue;
}

eTypeCours Creneau::getTypeCours() const
{
    return typeCours;
}

void Creneau::setTypeCours(eTypeCours newTypeCours)
{
    typeCours = newTypeCours;
}

Salle Creneau::getSalle() const
{
    return salle;
}

void Creneau::setSalle(const Salle &newSalle)
{
    salle = newSalle;
}

std::string Creneau::to_string() const
{
    std::string res = "Horaire : " + Creneau::horaireToString(horaire) + ", Date : " + date.toString() + ", Ecue : " + ecue.to_string() + ", Type de Cours : " + Ecue::typeCoursToString(typeCours) + ", Salle : " + salle.toString();
    return res;
}

QJsonObject Creneau::toJSON(void) const
{
    QJsonObject json;
    json["Horaire"] = horaireToString(this->horaire);
    json["Date"] = this->date.toString();
    json["Ecue"] = this->ecue.toJSON();
    json["typeCours"] = Ecue::typeCoursToString(this->typeCours);
    json["Salle"] = this->salle.toJSON();
    return json;
}

Creneau Creneau::fromJSON(QJsonObject json)
{
    eHoraire horaire = Creneau::stringToHoraire(json["Horaire"].toString());
    QDate date = QDate::fromString(json["Date"].toString());
    Ecue ecue = Ecue::fromJSON(json["Ecue"].toObject());
    eTypeCours typeCours = Ecue::stringToTypeCours(json["typeCours"].toString());
    Salle salle = Salle::fromJSON(json["Salle"].toObject());

    Creneau creneauObj(horaire, date, ecue, typeCours, salle);
    return creneauObj;
}

void Creneau::writeToJSON(std::vector<Creneau> vector, QString filepath){
    QFile file (filepath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QJsonArray tab;
    for (auto it =vector.begin(); it != vector.end(); it++) { tab.append(it->toJSON()); }
    file.write(QJsonDocument(tab).toJson(QJsonDocument::Indented));
    file.close();
}

std::vector<Creneau> Creneau::readFromJSON(QString filepath){
    QFile file (filepath);
    if (!file.open(QIODevice::ReadOnly)) return std::vector<Creneau>();
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray tab = doc.array();
    std::vector<Creneau> res;
    for (auto it = tab.begin(); it != tab.end();it++) { res.push_back(Creneau::fromJSON((*it).toObject())); }
    return res;
}

QString Creneau::horaireToString(eHoraire horaire)
{
    switch(horaire) {
    case eHoraire::MATIN1: return "MATIN1";
    case eHoraire::MATIN2: return "MATIN2";
    case eHoraire::APRESMIDI1: return "APRESMIDI1";
    case eHoraire::APRESMIDI2: return "APRESMIDI2";
    default: return "NONDEFINT";
    }
}

eHoraire Creneau::stringToHoraire(QString str)
{
    if(str == "MATIN1") return eHoraire::MATIN1;
    if(str == "MATIN2") return eHoraire::MATIN2;
    if(str == "APRESMIDI1") return eHoraire::APRESMIDI1;
    if(str == "APRESMIDI2") return eHoraire::APRESMIDI2;
    return eHoraire::NONDEFINIT;
}
