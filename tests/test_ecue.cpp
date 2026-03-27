#include "test_ecue.h"

void TestEcue::testValidationNom()
{
    QCOMPARE(Ecue::isNomValid("Mathématiques"), Ecue::NOM_OK);
    QCOMPARE(Ecue::isNomValid(""), Ecue::NOM_VIDE);
}

void TestEcue::testValidationHeuresTotales()
{
    QCOMPARE(Ecue::isHeureTotalValid(4), Ecue::HEURETOTAL_OK);       // Pair, positif
    QCOMPARE(Ecue::isHeureTotalValid(0), Ecue::HEURETOTAL_NUL);      // Zéro
    QCOMPARE(Ecue::isHeureTotalValid(-2), Ecue::HEURETOTAL_NEGATIF); // Négatif
    QCOMPARE(Ecue::isHeureTotalValid(3), Ecue::HEURETOTAL_IMPAIR);   // Impair
}

void TestEcue::testValidationHeuresRestantes()
{
    int total = 10;
    QCOMPARE(Ecue::isHeureRestanteValid(4, total), Ecue::HEURERESTANTE_OK);
    QCOMPARE(Ecue::isHeureRestanteValid(0, total), Ecue::HEURERESTANTE_NUL);
    QCOMPARE(Ecue::isHeureRestanteValid(-2, total), Ecue::HEURERESTANTE_NEGATIF);
    QCOMPARE(Ecue::isHeureRestanteValid(3, total), Ecue::HEURERESTANTE_IMPAIR);
    QCOMPARE(Ecue::isHeureRestanteValid(12, total), Ecue::HEURERESTANTE_SUPERIEUR_TOTAL); // > total
}
