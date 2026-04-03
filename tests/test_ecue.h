#ifndef TEST_ECUE_H
#define TEST_ECUE_H

#include <QtTest/QtTest>
#include <ecue.h>

class TestEcue : public QObject
{
    Q_OBJECT

private slots:
    void testValidationNom();
    void testValidationHeuresTotales();
    void testValidationHeuresRestantes();
    void testConversions();
    void testJSON();
};

#endif // TEST_ECUE_H
