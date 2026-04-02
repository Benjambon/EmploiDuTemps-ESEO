#include "test_creneau.h"

void TestCreneau::testValidationHoraire()
{
    Creneau c;
    c.setHoraire(eHoraire::NONDEFINIT);
    QCOMPARE(c.isHoraireValid(), Creneau::HORAIRE_NONDEFINIT);

    c.setHoraire(eHoraire::MATIN1);
    QCOMPARE(c.isHoraireValid(), Creneau::HORAIRE_OK);
}

void TestCreneau::testValidationDate()
{
    Creneau c;
    c.setDate(QDate()); // Date nulle
    QCOMPARE(c.isDateValid(), Creneau::DATE_NULLE);

    // Un samedi (le 4 avril 2026 est un samedi)
    c.setDate(QDate(2026, 4, 4));
    QCOMPARE(c.isDateValid(), Creneau::DATE_WEEKEND);

    // Un lundi valide
    c.setDate(QDate(2026, 4, 6));
    QCOMPARE(c.isDateValid(), Creneau::DATE_OK);
}

void TestCreneau::testValidationEcueEtSalle()
{
    Creneau c;
    // Test initial (vide)
    QCOMPARE(c.isEcueValid(), Creneau::ECUE_NONDEFINIT);
    QCOMPARE(c.isSalleValid(), Creneau::SALLE_NONDEFINIT);

    // Ajout d'une salle valide
    Salle s("104", TypeSalle::SALLE);
    c.setSalle(s);
    QCOMPARE(c.isSalleValid(), Creneau::SALLE_OK);
}

void TestCreneau::testConversions()
{
    QCOMPARE(Creneau::horaireToString(eHoraire::MATIN1), QString("MATIN1"));
    QCOMPARE(Creneau::stringToHoraire("APRESMIDI2"), eHoraire::APRESMIDI2);
    QCOMPARE(Creneau::stringToHoraire("NIMPORTEQUOI"), eHoraire::NONDEFINIT);
}

void TestCreneau::testJSON()
{
    // Préparation d'un créneau factice
    Enseignant ens("Dupont", "Jean");
    GroupeEtudiant grp("E4");
    std::map<eTypeCours, int> heures;
    heures[eTypeCours::CM] = 10;
    Ecue ecue("Maths", ens, grp, heures);
    Salle salle("104", TypeSalle::SALLE);

    Creneau c(eHoraire::MATIN1, QDate(2026, 4, 6), ecue, eTypeCours::CM, salle);

    // Test toJSON -> fromJSON
    QJsonObject json = c.toJSON();
    Creneau c2 = Creneau::fromJSON(json);

    QCOMPARE(c2.getHoraire(), c.getHoraire());
    QCOMPARE(c2.getDate(), c.getDate());
    QCOMPARE(c2.getTypeCours(), c.getTypeCours());
    QCOMPARE(QString::fromStdString(c2.getSalle().getNumero()), QString("104"));
}
