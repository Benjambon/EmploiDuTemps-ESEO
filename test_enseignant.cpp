#include "test_enseignant.h"

void TestEnseignant::testValidationNom()
{
    Enseignant e1("Dupont", "Jean");
    QCOMPARE(e1.isNomValid(), Enseignant::NOM_OK);

    Enseignant e2("", "Jean");
    QCOMPARE(e2.isNomValid(), Enseignant::NOM_VIDE);

    Enseignant e3("Dup0nt", "Jean");
    QCOMPARE(e3.isNomValid(), Enseignant::NOM_CHIFFRE);
}

void TestEnseignant::testValidationMail()
{
    // Test constructeur par défaut (génère prenom.nom@eseo.fr)
    Enseignant e1("Trenchant", "Vincent");
    QCOMPARE(e1.isMailValid(), Enseignant::MAIL_OK);

    // Test mail invalide
    Enseignant e2("Doe", "John", "john.doe_sans_arobase.com");
    QCOMPARE(e2.isMailValid(), Enseignant::MAIL_SYNTAXE);
}
