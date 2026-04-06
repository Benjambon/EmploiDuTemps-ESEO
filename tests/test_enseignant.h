#ifndef TEST_ENSEIGNANT_H
#define TEST_ENSEIGNANT_H

#include <QtTest/QtTest>
#include <enseignant.h>

class TestEnseignant : public QObject
{
    Q_OBJECT

private slots:
    void testValidationNom();
    void testValidationMail();
    void testJSON();
};

#endif // TEST_ENSEIGNANT_H
