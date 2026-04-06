#include "test_ecue.h"

void TestEcue::testValidationNom()
{
    QCOMPARE(Ecue::isNomValid("Mathématiques"), Ecue::NOM_OK);
    QCOMPARE(Ecue::isNomValid(""), Ecue::NOM_VIDE);
}

void TestEcue::testValidationHeuresTotales()
{
    QCOMPARE(Ecue::isHeureTotalValid(4), Ecue::HEURETOTAL_OK);
    QCOMPARE(Ecue::isHeureTotalValid(0), Ecue::HEURETOTAL_NUL);
    QCOMPARE(Ecue::isHeureTotalValid(-2), Ecue::HEURETOTAL_NEGATIF);
    QCOMPARE(Ecue::isHeureTotalValid(3), Ecue::HEURETOTAL_IMPAIR);
}

void TestEcue::testValidationHeuresRestantes()
{
    int total = 10;
    QCOMPARE(Ecue::isHeureRestanteValid(4, total), Ecue::HEURERESTANTE_OK);
    QCOMPARE(Ecue::isHeureRestanteValid(0, total), Ecue::HEURERESTANTE_NUL);
    QCOMPARE(Ecue::isHeureRestanteValid(-2, total), Ecue::HEURERESTANTE_NEGATIF);
    QCOMPARE(Ecue::isHeureRestanteValid(3, total), Ecue::HEURERESTANTE_IMPAIR);
    QCOMPARE(Ecue::isHeureRestanteValid(12, total), Ecue::HEURERESTANTE_SUPERIEUR_TOTAL);
}
void TestEcue::testConversions()
{
    QCOMPARE(Ecue::typeCoursToString(eTypeCours::CM), QString("CM"));
    QCOMPARE(Ecue::typeCoursToString(eTypeCours::TP_INFO), QString("TP_INFO"));
    QCOMPARE(Ecue::stringToTypeCours("TD"), eTypeCours::TD);
    QCOMPARE(Ecue::stringToTypeCours("INCONNU"), eTypeCours::DEFAULT);
}

void TestEcue::testJSON()
{
    Enseignant ens("Dupont", "Jean");
    GroupeEtudiant grp("E4");
    std::map<eTypeCours, int> heures;
    heures[eTypeCours::CM] = 10;
    heures[eTypeCours::TD] = 6;

    Ecue ecue("Physique", ens, grp, heures);

    QJsonObject json = ecue.toJSON();
    Ecue ecue2 = Ecue::fromJSON(json);

    QCOMPARE(QString::fromStdString(ecue2.getNom()), QString("Physique"));
    QCOMPARE(QString::fromStdString(ecue2.getEnseignant().getNom()), QString("Dupont"));
    QCOMPARE(ecue2.getHeuresTotales()[eTypeCours::CM], 10);
    QCOMPARE(ecue2.getHeuresTotales()[eTypeCours::TD], 6);
}
