#include "salle.h"

std::string Salle::getNumero() const
{
    return numero;
}

void Salle::setNumero(std::string newNumero)
{
    numero = newNumero;
}

TypeSalle Salle::getTypeSalle() const
{
    return typeSalle;
}

void Salle::setTypeSalle(TypeSalle newTypeSalle)
{
    typeSalle = newTypeSalle;
}

Salle::Salle() {
    this->numero="000";
    this->typeSalle=TypeSalle::SALLE;
}

bool Salle::isSalleValid(void){
    if (this->numero.length() != 3) {
        return false;
    }


    for (char c : this->numero) {
        if (!std::isdigit(c)) {
            return false;
        }
    }

    if (typeSalle != TypeSalle::SALLE &&
        typeSalle != TypeSalle::ELECTRONIQUE &&
        typeSalle != TypeSalle::INFORMATIQUE) {
        return false;
    }

    return true;
}

std::string Salle::toString(void) const {
    std::string typeStr;

    switch (typeSalle) {
    case TypeSalle::SALLE:
        typeStr = "Salle";
        break;
    case TypeSalle::ELECTRONIQUE:
        typeStr = "Electronique";
        break;
    case TypeSalle::INFORMATIQUE:
        typeStr = "Informatique";
        break;
    default:
        typeStr = "Inconnu";
        break;
    }

    return typeStr + " " + numero;
}
QJsonObject Salle::toJSON(void) const{
    QJsonObject json;
    json["numero"] = QString::fromStdString(this->numero);
    json["typeSalle"] = static_cast<int>(this->typeSalle);
    return json;
}

Salle Salle::fromJSON(QJsonObject json){
    QJsonObject::iterator it;

    it = json.find("numero");
    if (it==json.end()) { qDebug() << "Le JSON ne contient pas de 'numero";}
    if (it.value().isNull() ) { qDebug() << "Le 'numero' est null" ;}
    std::string numero = it.value().toString().toStdString() ;

    it = json.find("typeSalle");
    if (it==json.end()) { qDebug() << "Le JSON ne contient pas de 'typeSalle";}
    if (it.value().isNull() ) { qDebug() << "Le 'typeSalle' est null" ;}
    TypeSalle typeSalle = static_cast<TypeSalle>(json["typeSalle"].toInt());


    return Salle(numero, typeSalle);
}

void Salle::writeToJSON(std::vector<Salle> vector, QString filepath){
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

std::vector<Salle> Salle::readFromJSON(QString filepath){
    QFile file (filepath);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "Erreur ouverture de";
        qDebug() << filepath.toStdString();
        return std::vector<Salle>();
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(!doc.isArray()){
        qDebug() << "Erreur ouverture de";
        qDebug() << filepath;
        return std::vector<Salle>();
    }
    QJsonArray tab =doc.array();
    std::vector<Salle> res;
    for (auto it = tab.begin(); it != tab.end();it++){
        res.push_back(Salle::fromJSON((*it).toObject()));
    }
    return res;
}

Salle::Salle(std::string numero, TypeSalle typeSalle) : numero(numero),
    typeSalle(typeSalle)
{}
