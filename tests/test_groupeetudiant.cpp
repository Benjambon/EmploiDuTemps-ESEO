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
