#include "test_salle.h"

void TestSalle::testValidationNumero()
{
    // Numéro valide (3 chiffres)
    Salle s1("104", TypeSalle::SALLE);
    QCOMPARE(s1.isNumeroValid(), Salle::NUMERO_OK);

    // Numéro trop long
    Salle s2("1044", TypeSalle::SALLE);
    QCOMPARE(s2.isNumeroValid(), Salle::NUMERO_TROP_LONG);

    // Numéro trop court (votre code renvoie aussi TROP_LONG si la taille != 3)
    Salle s3("12", TypeSalle::SALLE);
    QCOMPARE(s3.isNumeroValid(), Salle::NUMERO_TROP_LONG);

    // Numéro avec des lettres
    Salle s4("A04", TypeSalle::SALLE);
    QCOMPARE(s4.isNumeroValid(), Salle::NUMERO_PAS_CHIFFRE);
}

void TestSalle::testValidationType()
{
    // Type valide
    Salle s1("104", TypeSalle::ELECTRONIQUE);
    QCOMPARE(s1.isTypeValid(), Salle::TYPE_OK);

    // Type invalide (en forçant une valeur qui n'est pas dans l'enum)
    Salle s2("104", static_cast<TypeSalle>(99));
    QCOMPARE(s2.isTypeValid(), Salle::TYPE_INVALIDE);
}

void TestSalle::testJSON()
{
    Salle s1("104", TypeSalle::INFORMATIQUE);
    QJsonObject json = s1.toJSON();
    Salle s2 = Salle::fromJSON(json);

    QCOMPARE(QString::fromStdString(s2.getNumero()), QString("104"));
    QCOMPARE(s2.getTypeSalle(), TypeSalle::INFORMATIQUE);
}
