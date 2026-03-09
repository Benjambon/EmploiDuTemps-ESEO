#include "enseignant.h"


//Getter Setter
std::string Enseignant::getNom() const
{
    return nom;
}

void Enseignant::setNom(const std::string &newNom)
{
    nom = newNom;
}

std::string Enseignant::getPrenom() const
{
    return prenom;
}

void Enseignant::setPrenom(const std::string &newPrenom)
{
    prenom = newPrenom;
}


std::string Enseignant::getMail() const
{
    return mail;
}

void Enseignant::setMail(const std::string &newMail)
{
    mail = newMail;
}


//Constructeurs
Enseignant::Enseignant() {}

Enseignant::Enseignant(const std::string &nom, const std::string &prenom, const std::string &mail) : nom(nom),
    prenom(prenom),
    mail(mail)
{}

Enseignant::Enseignant(const std::string &nom, const std::string &prenom) : nom(nom),
    prenom(prenom),
    mail(prenom+"."+nom+"@eseo.fr")
{}

bool Enseignant::isMailValid(void)
{

    // Regular expression definition
    const std::regex pattern(
        "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

    // Match the string pattern
    // with regular expression
    return regex_match(this->getMail(), pattern);
}

bool Enseignant::isNomValid(void){
    if(this->getNom()==""){
        return false;
    }
    else{
        return true;
    }

}

bool Enseignant::isPrenomValid(void){
    if(this->getPrenom()==""){
        return false;
    }
    else{
        return true;
    }

}

std::string Enseignant::toString(void) const{
    std::string res= nom + " " + prenom +" "+ mail;
    return res;
}

QJsonObject Enseignant::toJSON(void) const{
    QJsonObject json;
    json["prenom"] = QString::fromStdString(this->prenom);
    json["nom"] = QString::fromStdString(this->nom);
    json["mail"] = QString::fromStdString(this->mail);
    return json;
}

Enseignant Enseignant::fromJSON(QJsonObject json){
    QJsonObject::iterator it;

    it = json.find("prenom");
    if (it==json.end()) { qDebug() << "Le JSON ne contient pas de 'prenom";}
    if (it.value().isNull() ) { qDebug() << "Le 'prenom' est null" ;}
    std::string prenom = it.value().toString().toStdString() ;

    it = json.find("nom");
    if (it==json.end()) { qDebug() << "Le JSON ne contient pas de 'nom";}
    if (it.value().isNull() ) { qDebug() << "Le 'nom' est null" ;}
    std::string nom = it.value().toString().toStdString() ;

    it = json.find("mail");
    if (it==json.end() ) { qDebug() << "Le JSON ne contient pas de 'mail";}
    if (it.value().isNull() ) { qDebug() << "Le 'mail' est null" ;}
    std::string mail = it.value().toString().toStdString() ;

    return Enseignant(prenom, nom, mail);
}

void Enseignant::writeToJSON(std::vector<Enseignant> vector, QString filepath){
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

std::vector<Enseignant> Enseignant::readFromJSON(QString filepath){
    QFile file (filepath);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "Erreur ouverture de";
        qDebug() << filepath.toStdString();
        return std::vector<Enseignant>();
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(!doc.isArray()){
        qDebug() << "Erreur ouverture de";
        qDebug() << filepath;
        return std::vector<Enseignant>();
    }
    QJsonArray tab =doc.array();
    std::vector<Enseignant> res;
    for (auto it = tab.begin(); it != tab.end();it++){
        res.push_back(Enseignant::fromJSON((*it).toObject()));
    }
    return res;
}
