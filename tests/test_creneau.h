#ifndef TEST_CRENEAU_H
#define TEST_CRENEAU_H

#include <QtTest/QtTest>
#include <creneau.h>

class TestCreneau : public QObject
{
    Q_OBJECT

private slots:
    void testValidationHoraire();
    void testValidationDate();
    void testValidationEcueEtSalle();
    void testConversions();
    void testJSON();
};

#endif // TEST_CRENEAU_H
