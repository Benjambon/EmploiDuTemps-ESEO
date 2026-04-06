#include "test_salle.h"

void TestSalle::testValidationNumero()
{
    Salle s1("104", TypeSalle::SALLE);
    QCOMPARE(s1.isNumeroValid(), Salle::NUMERO_OK);

    Salle s2("1044", TypeSalle::SALLE);
    QCOMPARE(s2.isNumeroValid(), Salle::NUMERO_TROP_LONG);

    Salle s3("12", TypeSalle::SALLE);
    QCOMPARE(s3.isNumeroValid(), Salle::NUMERO_TROP_LONG);

    Salle s4("A04", TypeSalle::SALLE);
    QCOMPARE(s4.isNumeroValid(), Salle::NUMERO_PAS_CHIFFRE);
}

void TestSalle::testValidationType()
{
    Salle s1("104", TypeSalle::ELECTRONIQUE);
    QCOMPARE(s1.isTypeValid(), Salle::TYPE_OK);

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
