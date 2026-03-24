#include "groupeetudiant.h"

std::string GroupeEtudiant::getNom() const
{
    return nom;
}

void GroupeEtudiant::setNom(const std::string &newNom)
{
    nom = newNom;
}

GroupeEtudiant::GroupeEtudiant() {}

GroupeEtudiant::GroupeEtudiant(const std::string &nom) : nom(nom)
{}

std::string GroupeEtudiant::toString(void) const{
    std::string res = nom;
    return res;
}

GroupeEtudiant::code_erreur_nom GroupeEtudiant::isNomValid(void){
    if(this->getNom() == ""){
        return GroupeEtudiant::NOM_VIDE;
    }
    else{
        return GroupeEtudiant::NOM_OK;
    }
}

QJsonObject GroupeEtudiant::toJSON(void) const{
    QJsonObject json;
    json["nom"] = QString::fromStdString(this->nom);
    return json;
}

GroupeEtudiant GroupeEtudiant::fromJSON(QJsonObject json){
    QJsonObject::iterator it;

    it = json.find("nom");
    if (it==json.end()) { qDebug() << "Le JSON ne contient pas de 'nom";}
    if (it.value().isNull() ) { qDebug() << "Le 'nom' est null" ;}
    std::string nom = it.value().toString().toStdString() ;

    return GroupeEtudiant(nom);
}

void GroupeEtudiant::writeToJSON(std::vector<GroupeEtudiant> vector, QString filepath){
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

std::vector<GroupeEtudiant> GroupeEtudiant::readFromJSON(QString filepath){
    QFile file (filepath);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "Erreur ouverture de";
        qDebug() << filepath.toStdString();
        return std::vector<GroupeEtudiant>();
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(!doc.isArray()){
        qDebug() << "Erreur ouverture de";
        qDebug() << filepath;
        return std::vector<GroupeEtudiant>();
    }
    QJsonArray tab =doc.array();
    std::vector<GroupeEtudiant> res;
    for (auto it = tab.begin(); it != tab.end();it++){
        res.push_back(GroupeEtudiant::fromJSON((*it).toObject()));
    }
    return res;
}
