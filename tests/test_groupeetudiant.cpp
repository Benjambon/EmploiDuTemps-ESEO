#include "test_groupeetudiant.h"

void TestGroupeEtudiant::testValidationNom()
{
    // Nom valide
    GroupeEtudiant g1("E5");
    QCOMPARE(g1.isNomValid(), GroupeEtudiant::NOM_OK);

    // Nom vide
    GroupeEtudiant g2("");
    QCOMPARE(g2.isNomValid(), GroupeEtudiant::NOM_VIDE);
}

void TestGroupeEtudiant::testJSON()
{
    GroupeEtudiant g1("E5");
    QJsonObject json = g1.toJSON();
    GroupeEtudiant g2 = GroupeEtudiant::fromJSON(json);

    QCOMPARE(QString::fromStdString(g2.getNom()), QString("E5"));
}
